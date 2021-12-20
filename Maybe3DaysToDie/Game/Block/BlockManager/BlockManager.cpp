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

Block& BlockManager::GetBlock(const Vector3& pos)
{
	//レイテストの関係でfloatの値がずれるときがあるので下駄をはかす
	Vector3 Pos = pos;
	Pos.x += OBJECT_UNIT / 2;
	Pos.y += OBJECT_UNIT / 2;
	Pos.z += OBJECT_UNIT / 2;
	
	//int Chunk_X = pos.x / (MAX_CHUNK_SIDE * ChunkWidth);
	//int Chunk_Z = pos.z / (MAX_CHUNK_SIDE * ChunkWidth);
	int Chunk_X = static_cast<int>(std::floor((pos.x / OBJECT_UNIT) / ChunkWidth)) + MAX_CHUNK_SIDE / 2;
	int Chunk_Z = static_cast<int>(std::floor((pos.z / OBJECT_UNIT) / ChunkWidth)) + MAX_CHUNK_SIDE / 2;
	int resX = static_cast<int>(std::floor(Pos.x / OBJECT_UNIT));
	int resY = static_cast<int>(std::floor(Pos.y / OBJECT_UNIT));
	int resZ = static_cast<int>(std::floor(Pos.z / OBJECT_UNIT));

	return m_ChunkBlock[Chunk_X][Chunk_Z].m_Block[resX][resY][resZ];
}


void BlockManager::AddBlock(ObjectParams& params, Vector3& pos, Quaternion& rot, Vector3& scale)
{
	ChunkBlockDirty = true;
	//ブロックを取得
	auto& block = GetBlock(pos);

	if (m_modelNum > 0)
	{
		for (auto& model : BlockModel)
		{
			if (params.BlockName == model->GetInitData().m_tkmFilePath)
			{
				//ブロックの名前がかぶっているとき
				model->UpdateInstancingData(pos, rot, scale);
				//パラメータをセット
				block.SetParams(params);
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
	//パラメータをセット
	block.SetParams(params);

	m_modelNum++;
}

void BlockManager::RemoveBlock(Block* blockptr)
{
	ChunkBlockDirty = true;
	for (auto& model : BlockModel)
	{
		const char* Name = blockptr->GetParam().BlockName;
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