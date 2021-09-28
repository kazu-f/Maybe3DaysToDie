#include "MiniEngine.h"
#include "Sky.h"
#include "graphics/Material.h"

namespace Engine {
	namespace prefab {

		namespace {
			const wchar_t* SKY_SHADER_FILEPATH = L"Assets/shader/SkyCube.fx";
			const char* VS_SKY_ENTRY_POINT = "VSMain_SkyCube";
			const char* PS_SKY_ENTRY_POINT = "PSMain_SkyCube";
		}


		CSky::CSky()
		{
		}

		CSky::~CSky()
		{
		}

		void CSky::OnDestroy()
		{
			DeleteGO(m_modelRender);
		}

		bool CSky::Start()
		{
			//���f�������_�[�B
			m_modelRender = NewGO<prefab::ModelRender>(0);
			m_modelData.m_tkmFilePath = m_skyModelFilePath.c_str();
			m_modelData.m_shaderData.vsFxFilePath = SKY_SHADER_FILEPATH;
			m_modelData.m_shaderData.vsEntryPointFunc = VS_SKY_ENTRY_POINT;
			m_modelData.m_shaderData.psFxFilePath = SKY_SHADER_FILEPATH;
			m_modelData.m_shaderData.psEntryPointFunc = PS_SKY_ENTRY_POINT;
			m_modelRender->Init(m_modelData);
			//��̓f�B�t�@�[�h�ł͍s��Ȃ��B
			m_modelRender->SetForwardRenderFlag(true);
			m_skyCube.InitFromDDSFile(m_skyCubeMapFilePath.c_str());
			m_modelRender->FindMaterial([&](auto* mat) {
				mat->SetAlbedoMap(m_skyCube);
				});
			//�f�B�t�@�[�h�ɓo�^�B
			GraphicsEngine()->GetDefferd()->SetCubeMapTexture(m_skyCube);

			//����͍X�V���K�v�B
			m_isDirty = true;

			return true;
		}

		void CSky::Update()
		{
			//�X�V�̕K�v������B
			if (m_isDirty) {
				//m_modelRender->SetPosition(m_position);
				m_modelRender->SetScale(m_scale);
				m_modelRender->SetEmissionColor(m_emissionColor);

				m_isDirty = false;
			}

			m_modelRender->SetPosition(MainCamera().GetPosition());
		}


	}//namespace prefab;
}//namespace Engine;

