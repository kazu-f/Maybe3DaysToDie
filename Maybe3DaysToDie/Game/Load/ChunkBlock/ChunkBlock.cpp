#include "stdafx.h"
#include "ChunkBlock.h"

void ChunkBlock::OnDestroy()
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

void ChunkBlock::Init()
{
	for (int x = 0; x < ChunkWidth; x++)
	{
		for (int y = 0; y < ChunkHeight; y++)
		{
			for (int z = 0; z < ChunkWidth; z++)
			{
				m_Block[x][y][z].SetChunkBlock(this);
				Vector3 pos;
				pos.x = static_cast<float>(x) * OBJECT_UNIT;
				pos.y = static_cast<float>(y) * OBJECT_UNIT;
				pos.z = static_cast<float>(z) * OBJECT_UNIT;
				//チャンクの位置を加算
				float geta = 0;
				geta = OBJECT_UNIT * ChunkWidth;
				pos.x += geta * m_ChunkID[0];
				pos.z += geta * m_ChunkID[1];
				//ポジションをセット
				m_Block[x][y][z].SetPosAndRot(pos, Quaternion::Identity);
			}
		}
	}
}

void ChunkBlock::MoveChunk()
{
	if (IsMove == false)
	{
		//チャンク移動がない
		return;
	}
	//セーブデータファイルからチャンクの情報を取得
	auto& chunkData = m_SaveDataFile->m_ChunkData[m_ChunkID[0]][m_ChunkID[1]];
	if (m_modelNum > 0)
	{
		for (auto& model : BlockModel)
		{
			//インスタンシングデータをリセット
			model->ResetInstancingDatas();
		}
	}
	for (int x = 0; x < ChunkWidth; x++)
	{
		for (int y = 0; y < ChunkHeight; y++)
		{
			for (int z = 0; z < ChunkWidth; z++)
			{
				Vector3 pos;
				pos.x = static_cast<float>(x) * OBJECT_UNIT;
				pos.y = static_cast<float>(y) * OBJECT_UNIT;
				pos.z = static_cast<float>(z) * OBJECT_UNIT;
				//チャンクの位置を加算
				float geta = 0;
				geta = OBJECT_UNIT * ChunkWidth;
				pos.x += geta * m_ChunkID[0];
				pos.z += geta * m_ChunkID[1];
				//ポジションをセット
				m_Block[x][y][z].SetPosAndRot(pos, Quaternion::Identity);
				//パラメータ
				ObjectParams param;
				param.BlockID = chunkData.ObjId[x][y][z];
				param.Durable = chunkData.ObjDurable[x][y][z];
				int id = static_cast<int>(param.BlockID);
				param.BlockName = m_SaveDataFile->ObjectFilePath[id];
				//パラメータをセット
				m_Block[x][y][z].SetParams(param);

				if (param.Durable > 0)
				{
					bool InitedModel = false;
					if (m_modelNum > 0)
					{
						for (auto& model : BlockModel)
						{
							//今はモデル1種類だけだからファイルパス固定
							if (param.BlockName == model->GetInitData().m_tkmFilePath)
							{
								//ブロックの名前がかぶっているとき
								//インスタンシングデータを更新
								Quaternion rot = Quaternion::Identity;
								Vector3 scale = Vector3::One;
								model->UpdateInstancingData(pos, rot, scale);
								InitedModel = true;
								break;
							}

						}
					}
					if (InitedModel == false)
					{
						//ブロックの名前がかぶっていないのでまだ、そのモデルがない
						ModelInitData InitData;
						Quaternion rot = Quaternion::Identity;
						Vector3 scale = Vector3::One;
						InitData.m_tkmFilePath = param.BlockName;
						prefab::ModelRender* model = NewGO<prefab::ModelRender>(0);
						//チャンクのサイズ分インスタンシング描画する
						model->Init(InitData, nullptr, 0, MaxInstanceNum);
						model->UpdateInstancingData(pos, rot, scale);
						BlockModel[m_modelNum] = model;
						m_modelNum++;
					}
				}
			}
		}
	}
	IsMove = false;
}

Block& ChunkBlock::GetBlock(Vector3 pos)
{
	//ポジションに対応するブロックを取得
	int x = pos.x / OBJECT_UNIT;
	x = static_cast<int>(x % ChunkWidth);
	int y = pos.y / OBJECT_UNIT;
	y = static_cast<int>(y % ChunkHeight);
	int z = pos.z / OBJECT_UNIT;
	z = static_cast<int>(z % ChunkWidth);

	return m_Block[x][y][z];
}

void ChunkBlock::AddModel(ObjectParams& params, Vector3& pos, Quaternion& rot, Vector3& scale)
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

void ChunkBlock::RemoveBlock(Block* blockptr)
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

		for (int x = 0; x < ChunkWidth; x++)
		{
			for (int y = 0; y < ChunkHeight; y++)
			{
				for (int z = 0; z < ChunkWidth; z++)
				{
					auto& block = m_Block[x][y][z];
					if (block.GetParam().Durable > 0)
					{
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