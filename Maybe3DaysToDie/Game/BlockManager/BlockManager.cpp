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
	for (auto& model : BlockModel)
	{
		if (BlockName == model->GetInitData().m_tkmFilePath)
		{
			//�u���b�N�̖��O�����Ԃ��Ă���Ƃ�
			model->AddInstancing(pos, rot, scale);
			return;
		}
	}		
	//�u���b�N�̖��O�����Ԃ��Ă��Ȃ��̂ł܂��A���̃��f�����Ȃ�
	ModelInitData InitData;
	InitData.m_tkmFilePath = BlockName;
	prefab::ModelRender* model = NewGO<prefab::ModelRender>(0);
	model->Init(InitData);
	model->SetPosition(pos);
	model->SetRotation(rot);
	model->SetScale(scale);
	BlockModel.push_back(std::move(model));
}