#include "stdafx.h"
#include "SuperFlat.h"


void SuperFlat::OnDestroy()
{
	for (auto& ptr : m_model)
	{
		if (ptr != nullptr)
		{
			delete ptr;
			ptr = nullptr;
		}
	}
	for (auto& ptr : m_Terrain)
	{
		if (ptr != nullptr)
		{
			delete ptr;
			ptr = nullptr;
		}
	}
}

void SuperFlat::CreateStage()
{
	//���f���̊e����
	ModelInitData modelInitData;
	modelInitData.m_tkmFilePath = "Assets/modelData/CubeBlock/woodBlock.tkm";

	//�`�����N���ƂɃ}�b�v�𐶐�
	for (int Width = 0; Width < ChunkWidth; Width++)
	{
		for (int Depth = 0; Depth < ChunkWidth; Depth++)
		{
			prefab::ModelRender* m_ptr = NewGO<prefab::ModelRender>(0);
			m_ptr->Init(modelInitData);
			Vector3 pos = { 100.0f,-100.0f,100.0f };
			pos.x *= Width;
			pos.z *= Depth;
			m_ptr->SetPosition(pos);
			//�R���C�_�[���쐬
			CPhysicsStaticObject* col = nullptr;
			col = new CPhysicsStaticObject;
			col->CreateMesh(pos, Quaternion::Identity, Vector3::One, m_ptr);
			//�������m��
			nsTerrain::Terrain* t_ptr = new nsTerrain::Terrain();
			//�R���C�_�[�̍쐬
			//t_ptr->CreateCollider(m_ptr);
			//�z��ɒǉ�
			m_model.push_back(std::move(m_ptr));
			m_Terrain.push_back(std::move(t_ptr));
		}
	}
}

void SuperFlat::ReCreate()
{
	////���f���̊e����
	//ModelInitData modelInitData;
	//modelInitData.m_tkmFilePath = "Assets/modelData/CubeBlock/woodBlock.tkm";
	////���f����������
	//m_model->Init(modelInitData, nullptr, 0, 5 * 5);
	//m_model->ResetInstancingDatas();
	////�`�����N���ƂɃ}�b�v�𐶐�
	//for (int Width = 0; Width < 5; Width++)
	//{
	//	for (int Depth = 0; Depth < 5; Depth++)
	//	{
	//		Vector3 pos = { 100.0f,-100.0f,100.0f };
	//		pos.x *= Width;
	//		pos.z *= Depth;
	//		m_model->UpdateInstancingData(pos, Quaternion::Identity, Vector3::One);
	//	}
	//}
}