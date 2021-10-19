#include "stdafx.h"
#include "SuperFlat.h"


void SuperFlat::OnDestroy()
{
	//���f�����폜
	//for (int Width = 0; Width < ChunkWidth; Width++)
	//{
	//	for (int Depth = 0; Depth < ChunkDepth; Depth++)
	//	{
	//		if (m_model[Width][Depth] != nullptr)
	//		{
	//			DeleteGO(m_model[Width][Depth]);
	//			m_model[Width][Depth] = nullptr;
	//		}
	//	}
	//}
	if (m_model != nullptr)
	{
		DeleteGO(m_model);
		m_model = nullptr;
	}
	if (m_Terrain != nullptr)
	{
		delete m_Terrain;
		m_Terrain = nullptr;
	}

}

void SuperFlat::CreateStage()
{
	////���f����new
	m_model = NewGO<prefab::ModelRender>(0);
	////���f���̊e����
	ModelInitData modelInitData;
	modelInitData.m_tkmFilePath = "Assets/modelData/CubeBlock/woodBlock.tkm";
	////���f����������
	m_model->Init(modelInitData, nullptr, 0, ChunkWidth * ChunkDepth);

	//�`�����N���ƂɃ}�b�v�𐶐�
	for (int Width = 0; Width < ChunkWidth; Width++)
	{
		for (int Depth = 0; Depth < ChunkDepth; Depth++)
		{
			////���f����new
			//m_model = NewGO<prefab::ModelRender>(0);
			////���f���̊e����
			//ModelInitData modelInitData;
			//modelInitData.m_tkmFilePath = "Assets/modelData/CubeBlock/woodBlock.tkm";
			//modelInitData.m_shaderData.vsFxFilePath = L"Assets/shader/model.fx";
			//modelInitData.m_shaderData.vsEntryPointFunc = "VSMain";
			//modelInitData.m_shaderData.psFxFilePath = L"Assets/shader/ObjectPreview.fx";
			//modelInitData.m_shaderData.psEntryPointFunc = "PSMain";
			////���f����������
			//m_model->Init(modelInitData, nullptr, 0, ChunkWidth * ChunkDepth);
			Vector3 pos = { 100.0f,-100.0f,100.0f };
			pos.x *= Width;
			pos.z *= Depth;
			m_model->UpdateInstancingData(pos, Quaternion::Identity, Vector3::One);
			//�R���C�_�[���쐬
			m_StaticCol[Width][Depth].CreateMesh(pos, Quaternion::Identity, Vector3::One, m_model);
		}
	}
	m_Terrain = new nsTerrain::Terrain;
	m_Terrain->SetModel(m_model);
}

void SuperFlat::ReCreate()
{
	////���f���̊e����
	ModelInitData modelInitData;
	modelInitData.m_tkmFilePath = "Assets/modelData/CubeBlock/woodBlock.tkm";
	////���f����������
	m_model->Init(modelInitData, nullptr, 0, 5 * 5);
	m_model->ResetInstancingDatas();
	//�`�����N���ƂɃ}�b�v�𐶐�
	for (int Width = 0; Width < 5; Width++)
	{
		for (int Depth = 0; Depth < 5; Depth++)
		{
			Vector3 pos = { 100.0f,-100.0f,100.0f };
			pos.x *= Width;
			pos.z *= Depth;
			m_model->UpdateInstancingData(pos, Quaternion::Identity, Vector3::One);
		}
	}
	m_Terrain->SetModel(m_model);

}