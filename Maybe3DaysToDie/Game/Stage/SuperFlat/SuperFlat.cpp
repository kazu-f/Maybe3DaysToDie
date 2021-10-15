#include "stdafx.h"
#include "SuperFlat.h"


void SuperFlat::OnDestroy()
{
	//モデルを削除
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

}

void SuperFlat::CreateStage()
{
	////モデルをnew
	m_model = NewGO<prefab::ModelRender>(0);
	////モデルの各種情報
	ModelInitData modelInitData;
	modelInitData.m_tkmFilePath = "Assets/modelData/CubeBlock/woodBlock.tkm";
	////モデルを初期化
	m_model->Init(modelInitData, nullptr, 0, ChunkWidth * ChunkDepth);

	//チャンクごとにマップを生成
	for (int Width = 0; Width < ChunkWidth; Width++)
	{
		for (int Depth = 0; Depth < ChunkDepth; Depth++)
		{
			////モデルをnew
			//m_model = NewGO<prefab::ModelRender>(0);
			////モデルの各種情報
			//ModelInitData modelInitData;
			//modelInitData.m_tkmFilePath = "Assets/modelData/CubeBlock/woodBlock.tkm";
			//modelInitData.m_shaderData.vsFxFilePath = L"Assets/shader/model.fx";
			//modelInitData.m_shaderData.vsEntryPointFunc = "VSMain";
			//modelInitData.m_shaderData.psFxFilePath = L"Assets/shader/ObjectPreview.fx";
			//modelInitData.m_shaderData.psEntryPointFunc = "PSMain";
			////モデルを初期化
			//m_model->Init(modelInitData, nullptr, 0, ChunkWidth * ChunkDepth);
			Vector3 pos = { 100.0f,-100.0f,100.0f };
			pos.x *= Width;
			pos.z *= Depth;
			m_model->UpdateInstancingData(pos, Quaternion::Identity, Vector3::One);
			//m_model->SetPosition(pos);
			//m_model[Width][Depth]->SetActiveFlag(false);
			//コライダーを作成
			m_StaticCol[Width][Depth].CreateMesh(pos, Quaternion::Identity, Vector3::One, m_model);
		}
	}
}

void SuperFlat::Draw()
{

}