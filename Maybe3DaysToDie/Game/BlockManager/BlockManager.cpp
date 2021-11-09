#include "stdafx.h"
#include "BlockManager.h"

void BlockManager::OnDestroy()
{

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
			model->UpdateInstancingData(pos, rot, scale);
		}
	}
}