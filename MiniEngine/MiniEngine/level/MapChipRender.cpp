#include "stdafx.h"
#include "MapChipRender.h"

namespace Engine {
	CMapChipRender::CMapChipRender()
	{
	}
	CMapChipRender::~CMapChipRender()
	{
	}
	void CMapChipRender::OnDestroy()
	{
		DeleteGO(m_modelRender);
	}
	void CMapChipRender::Update()
	{
		if (m_renderObjDatas.size() > 1 && m_numRenderObject < m_renderObjDatas.size()) {
			for (auto& objData : m_renderObjDatas) {
				m_modelRender->UpdateInstancingData(objData.position, objData.rotation, objData.scale);
				m_numRenderObject++;
			}
		}
	}
	void CMapChipRender::InitAfterAddAllRenderObjects()
	{
		//���f�������_�[�̏������B
		m_modelRender = NewGO<prefab::ModelRender>(0);
		//�t�@�C���p�X�쐬�B
		wchar_t filePath[256];
		swprintf_s(filePath, L"Assets/modelData/%s.tkm", m_renderObjDatas[0].name);

		size_t oriSize = wcslen(filePath) + 1;
		size_t convertedChars = 0;
		char strConcat[] = "";
		size_t strConcatSize = (strlen(strConcat) + 1) * 2;
		const size_t newSize = oriSize * 2;
		char* nString = new char[newSize + strConcatSize];
		wcstombs_s(&convertedChars, nString, newSize, filePath, _TRUNCATE);
		_mbscat_s((unsigned char*)nString, newSize + strConcatSize, (unsigned char*)strConcat);

		ModelInitData initData;
		initData.m_tkmFilePath = nString;

		if (m_renderObjDatas.size() > 1) {
			//�C���X�^���V���O�`��B
			m_modelRender->Init(initData, nullptr, 0, static_cast<int>(m_renderObjDatas.size()));
		}
		else {
			//�ʏ�`��B
			m_modelRender->Init(initData);
			m_modelRender->SetPosition(m_renderObjDatas[0].position);
			m_modelRender->SetRotation(m_renderObjDatas[0].rotation);
			m_modelRender->SetScale(m_renderObjDatas[0].scale);
		}
		m_modelRender->SetShadowCasterFlag(m_renderObjDatas[0].isShadowCaster);
		m_modelRender->SetShadowReceiverFlag(m_renderObjDatas[0].isShadowReceiver);
	}
}