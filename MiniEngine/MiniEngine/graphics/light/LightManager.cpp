#include "stdafx.h"
#include "LightManager.h"
#include "prefab/light/DirectionLight.h"
#include "prefab/light/PointLight.h"

namespace Engine {
	using namespace prefab;

	void CLightManager::Init()
	{
		//�A���r�G���g���C�g�̏������B
		SetAmbientLight({ 0.5f,0.5f,0.5f });
		//���C�g�̃p�����[�^�p�̒萔�o�b�t�@���쐬�B
		m_lightParamCB.Init(sizeof(SLightParam), nullptr);
		//�f�B���N�V�������C�g�p�̃X�g���N�`���o�b�t�@���쐬�B
		m_directionLightSB.Init(sizeof(SDirectionLight), MAX_DIRECTION_LIGHT, nullptr);
		//�|�C���g���C�g�p�̃X�g���N�`���o�b�t�@���쐬�B
		m_pointLightSB.Init(sizeof(SPointLight), MAX_POINT_LIGHT, nullptr);
	}

	void CLightManager::AddLight(prefab::CLightBase* light)
	{
		//���C�g�̐U�蕪��
		const std::type_info& typeInfo = typeid(*light);
		if (typeInfo == typeid(CDirectionLight)) {
			//�o�^�ς݂����ׂ�B
			auto findIt = std::find(m_directionLights.begin(), m_directionLights.end(), light);
			if (findIt == m_directionLights.end()) {
				//�V�K�o�^�B
				m_directionLights.push_back(reinterpret_cast<CDirectionLight*>(light));
			}
			else {
				//���ɓo�^����Ă���B
				return;
			}
		}
		if (typeInfo == typeid(CPointLight)) {
			//�o�^�ς݂����ׂ�B
			auto findIt = std::find(m_pointLights.begin(), m_pointLights.end(), light);
			if (findIt == m_pointLights.end()) {
				//�V�K�o�^�B
				m_pointLights.push_back(reinterpret_cast<CPointLight*>(light));
			}
			else {
				//���ɓo�^����Ă���B
				return;
			}
		}
	}

	void CLightManager::RemoveLight(prefab::CLightBase* light)
	{
		//�o�^����������B
		const std::type_info& typeInfo = typeid(*light);
		if(typeInfo == typeid(CDirectionLight)){
			m_directionLights.erase(
				std::remove(m_directionLights.begin(),m_directionLights.end(),light),
				m_directionLights.end()			
			);
		}
		else if(typeInfo == typeid(CPointLight)){
			m_pointLights.erase(
				std::remove(m_pointLights.begin(), m_pointLights.end(),light),
				m_pointLights.end()
			);
		}
	}

	void CLightManager::LightUpdate()
	{
		//�f�B���N�V�������C�g�̃X�g���N�`���[�o�b�t�@���X�V�B
		int ligNo = 0;
		for (auto lig : m_directionLights) {
			if (lig->IsActive() == false) {
				//�A�N�e�B�u����Ȃ��z�̓X�L�b�v�B
				continue;
			}
			m_rawDirectionLights[ligNo] = lig->GetRawData();
			ligNo++;
		}
		int numDirLig = ligNo;		//�f�B���N�V�������C�g�̐��B

		//�|�C���g���C�g�������悤�ɍX�V�B
		ligNo = 0;
		for (auto lig : m_pointLights) {
			if (lig->IsActive() == false) {
				//�A�N�e�B�u����Ȃ��z�̓X�L�b�v�B
				continue;
			}
			m_rawPointLights[ligNo] = lig->GetRawData();
			ligNo++;
		}
		
		int numPointLig = ligNo;

		m_lightParam.numDirectionLight = numDirLig;		//�f�B���N�V�������C�g�̐��B
		m_lightParam.numPointLight = numPointLig;		//�|�C���g���C�g�̐��B
		m_lightParam.eyePos = MainCamera().GetPosition();//���_�̍��W�B
		m_lightParam.screenParam.x = 0.0f;				//near
		m_lightParam.screenParam.y = 0.0f;				//far
		m_lightParam.screenParam.z = static_cast<float>(GraphicsEngine()->GetFrameBufferWidth());	//screenWidth
		m_lightParam.screenParam.w = static_cast<float>(GraphicsEngine()->GetFrameBufferHeight());	//screenHeight
	}

	void CLightManager::Render(RenderContext& rc)
	{
		//���C�g�p�����[�^�̃f�[�^���X�V�B
		m_lightParamCB.CopyToVRAM(&m_lightParam);
		//�f�B���N�V�������C�g�̃f�[�^���X�V�B
		m_directionLightSB.Update(&m_rawDirectionLights);
		//�|�C���g���C�g�̃f�[�^���X�V�B
		m_pointLightSB.Update(&m_rawPointLights);
	}

	void CLightManager::SendLightDataToGPU(RenderContext& rc)
	{
		//���ɏ����Ȃ�������B
	}

}	////////namespace Engine
