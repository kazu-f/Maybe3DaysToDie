#include "stdafx.h"
#include "SuperFlat.h"


void SuperFlat::OnDestroy()
{
	//���f�����폜
	for (int Width = 0; Width < ChunkWidth; Width++)
	{
		for (int Depth = 0; Depth < ChunkDepth; Depth++)
		{
			if (m_model[Width][Depth] != nullptr)
			{
				DeleteGO(m_model[Width][Depth]);
				m_model[Width][Depth] = nullptr;
			}
		}
	}
}

void SuperFlat::CreateStage()
{
	//�`�����N���ƂɃ}�b�v�𐶐�
	for (int Width = 0; Width < ChunkWidth; Width++)
	{
		for (int Depth = 0; Depth < ChunkDepth; Depth++)
		{
			//���f����new
			m_model[Width][Depth] = NewGO<prefab::ModelRender>(0);
			//���f���̊e����
			ModelInitData modelInitData;
			modelInitData.m_tkmFilePath = "Assets/modelData/CubeBlock/woodBlock.tkm";
			//modelInitData.m_shaderData.vsFxFilePath = L"Assets/shader/model.fx";
			//modelInitData.m_shaderData.vsEntryPointFunc = "VSMain";
			//modelInitData.m_shaderData.psFxFilePath = L"Assets/shader/ObjectPreview.fx";
			//modelInitData.m_shaderData.psEntryPointFunc = "PSMain";
			//���f����������
			m_model[Width][Depth]->Init(modelInitData);
			Vector3 pos = { 100.0f,-100.0f,100.0f };
			pos.x *= Width;
			pos.z *= Depth;
			m_model[Width][Depth]->SetPosition(pos);

			//�R���C�_�[���쐬
			m_StaticCol[Width][Depth].CreateMesh(pos, Quaternion::Identity, Vector3::One, m_model[Width][Depth]);
		}
	}
}