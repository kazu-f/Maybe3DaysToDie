#include "stdafx.h"
#include "BlockManager.h"

void BlockManager::OnDestroy()
{
	for (auto& model : BlockModel)
	{
		if (model != nullptr)
		{
			DeleteGO(model);
			model = nullptr;
		}
	}
}

bool BlockManager::Start()
{
	return true;
}

void BlockManager::Update()
{

}

void BlockManager::AddBlock(const char* BlockName, Vector3& pos, Quaternion& rot, Vector3& scale)
{
	if (m_modelNum > 0)
	{
		for (auto& model : BlockModel)
		{
			if (BlockName == model->GetInitData().m_tkmFilePath)
			{
				//ブロックの名前がかぶっているとき
				//model->AddInstancing(pos, rot, scale);
				return;
			}
		}
	}
	//ブロックの名前がかぶっていないのでまだ、そのモデルがない
	ModelInitData InitData;
	InitData.m_tkmFilePath = BlockName;
	prefab::ModelRender* model = NewGO<prefab::ModelRender>(0);
	model->Init(InitData);
	model->SetPosition(pos);
	model->SetRotation(rot);
	model->SetScale(scale);
	BlockModel[m_modelNum] = std::move(model);
	m_modelNum++;
}