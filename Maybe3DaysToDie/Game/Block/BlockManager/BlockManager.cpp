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
	for (int Chunk_X = 0; Chunk_X < MAX_CHUNK_SIDE; Chunk_X++)
	{
		for (int Chunk_Z = 0; Chunk_Z < MAX_CHUNK_SIDE; Chunk_Z++)
		{
			for (int x = 0; x < ChunkWidth; x++)
			{
				for (int y = 0; y < ChunkHeight; y++)
				{
					for (int z = 0; z < ChunkWidth; z++)
					{
						//マネージャーをセット
						m_ChunkBlock[Chunk_X][Chunk_Z].m_Block[x][y][z].SetBlockManager(this);
						Vector3 pos;
						pos.x = static_cast<float>(x) * OBJECT_UNIT;
						pos.y = static_cast<float>(y) * OBJECT_UNIT;
						pos.z = static_cast<float>(z) * OBJECT_UNIT;
						m_ChunkBlock[Chunk_X][Chunk_Z].m_Block[x][y][z].SetPosition(pos);
					}
				}

			}
		}
	}

	return true;
}

void BlockManager::Update()
{

}

void BlockManager::AddModel(ObjectParams& params, Vector3& pos, Quaternion& rot, Vector3& scale)
{
	ChunkBlockDirty = true;
	if (m_modelNum > 0)
	{
		for (auto& model : BlockModel)
		{
			if (params.BlockName == model->GetInitData().m_tkmFilePath)
			{
				//ブロックの名前がかぶっているとき
				//インスタンシングデータを更新
				model->UpdateInstancingData(pos, rot, scale);
				return;
			}
		}
	}
	//ブロックの名前がかぶっていないのでまだ、そのモデルがない
	ModelInitData InitData;
	InitData.m_tkmFilePath = params.BlockName;
	prefab::ModelRender* model = NewGO<prefab::ModelRender>(0);
	//チャンクのサイズ分インスタンシング描画する
	model->Init(InitData, nullptr, 0, MaxInstanceNum);
	model->UpdateInstancingData(pos, rot, scale);
	BlockModel[m_modelNum] = model;
	m_modelNum++;
}

void BlockManager::RemoveBlock(Block* blockptr)
{
	ChunkBlockDirty = true;
	const char* Name = blockptr->GetParam().BlockName;
	if (Name == nullptr)
	{
		//名前がセットされていないので何か分からないものを壊そうとしている
		return;
	}
	for (auto& model : BlockModel)
	{
		blockptr->ResetParams();
		//インスタンシングデータをリセット
		model->ResetInstancingDatas();
		//ここからセットしなおす
		for (int Chunk_X = 0; Chunk_X < MAX_CHUNK_SIDE; Chunk_X++)
		{
			for (int Chunk_Z = 0; Chunk_Z < MAX_CHUNK_SIDE; Chunk_Z++)
			{

				for (int x = 0; x < ChunkWidth; x++)
				{
					for (int y = 0; y < ChunkHeight; y++)
					{
						for (int z = 0; z < ChunkWidth; z++)
						{
							auto& block = m_ChunkBlock[Chunk_X][Chunk_Z].m_Block[x][y][z];
							if (block.GetParam().BlockName == Name)
							{
								model->UpdateInstancingData(block.GetPosition(), block.GetRotation(), block.GetScale());
							}
						}
					}
				}
			}
		}
	}
}