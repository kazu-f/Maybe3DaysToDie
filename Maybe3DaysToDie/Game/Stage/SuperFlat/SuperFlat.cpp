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
	//モデルの各種情報
	ModelInitData modelInitData;
	modelInitData.m_tkmFilePath = "Assets/modelData/CubeBlock/woodBlock.tkm";

	//チャンクごとにマップを生成
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
			//コライダーを作成
			CPhysicsStaticObject* col = nullptr;
			col = new CPhysicsStaticObject;
			col->CreateMesh(pos, Quaternion::Identity, Vector3::One, m_ptr);
			//メモリ確保
			nsTerrain::Terrain* t_ptr = new nsTerrain::Terrain();
			//コライダーの作成
			//t_ptr->CreateCollider(m_ptr);
			//配列に追加
			m_model.push_back(std::move(m_ptr));
			m_Terrain.push_back(std::move(t_ptr));
		}
	}
}

void SuperFlat::ReCreate()
{
	////モデルの各種情報
	//ModelInitData modelInitData;
	//modelInitData.m_tkmFilePath = "Assets/modelData/CubeBlock/woodBlock.tkm";
	////モデルを初期化
	//m_model->Init(modelInitData, nullptr, 0, 5 * 5);
	//m_model->ResetInstancingDatas();
	////チャンクごとにマップを生成
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