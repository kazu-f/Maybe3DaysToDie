#include "stdafx.h"
#include "ChunkBlock.h"
#include "Load/TerrainLoad/LoadingByChunk.h"

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
	ChunkBlockDirty = true;
	m_IsModelUpdated = true;

	//セーブデータファイルからチャンクの情報を取得
	auto& chunkData = m_SaveDataFile->m_ChunkData[m_ChunkID[0]][m_ChunkID[1]];

	//インスタンシングデータをリセット
	for (auto& data : m_InstancingData)
	{
		data.clear();
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
				param.BlockID = chunkData.ObjData[x][y][z].ObjId;
				param.Durable = chunkData.ObjData[x][y][z].ObjDurable;
				int BlockID = static_cast<int>(param.BlockID);
				if (m_SaveDataFile->ObjectType[BlockID] != ObjectType::Block)
				{
					continue;
				}
				if (BlockID < 0 || BlockID >= BlockKinds)
				{
					//ブロックIDがマイナスか最大値より大きいときreturn
					continue;
				}

				//ファイルパス作成。
				wchar_t filePath[256];
				swprintf_s(filePath, L"Assets/modelData/CubeBlock/%s.tkm", m_SaveDataFile->ObjectFilePath[BlockID].c_str());

				size_t oriSize = wcslen(filePath) + 1;
				size_t convertedChars = 0;
				char strConcat[] = "";
				size_t strConcatSize = (strlen(strConcat) + 1) * 2;
				const size_t newSize = oriSize * 2;
				char* nString = new char[newSize + strConcatSize];
				wcstombs_s(&convertedChars, nString, newSize, filePath, _TRUNCATE);
				_mbscat_s((unsigned char*)nString, newSize + strConcatSize, (unsigned char*)strConcat);
				param.BlockName = nString;
				//パラメータをセット
				m_Block[x][y][z].SetParams(param);

				if (param.Durable > 0)
				{
					//ブロックの名前がかぶっているとき
					//インスタンシングデータを更新
					Quaternion rot = Quaternion::Identity;
					Vector3 scale = Vector3::One;
					//データを作成
					InstancingData data;
					data.pos = pos;
					data.rot = rot;
					data.scale = scale;
					//配列に追加
					m_InstancingData[BlockID].push_back(data);
				}
			}
		}
	}


	
	IsMove = false;
}

Block* ChunkBlock::GetBlock(Vector3 pos)
{
	//ポジションに対応するブロックを取得
	int x = pos.x / OBJECT_UNIT;
	x = static_cast<int>(x % ChunkWidth);
	int y = pos.y / OBJECT_UNIT;
	y = static_cast<int>(y % ChunkHeight);
	int z = pos.z / OBJECT_UNIT;
	z = static_cast<int>(z % ChunkWidth);

	return &m_Block[x][y][z];
}

void ChunkBlock::AddModel(ObjectParams& params, Vector3& pos, Quaternion& rot, Vector3& scale)
{
	int BlockID = static_cast<int>(params.BlockID);
	if (m_SaveDataFile->ObjectType[BlockID] != ObjectType::Block)
	{
		return;
	}
	if (BlockID < 0 || BlockID >= BlockKinds)
	{
		//ブロックIDがマイナスか最大値より大きいときreturn
		return;
	}
	ChunkBlockDirty = true;
	m_IsModelUpdated = true;
	//ブロックに名前をセット
	//ファイルパス作成。
	wchar_t filePath[256];
	swprintf_s(filePath, L"Assets/modelData/CubeBlock/%s.tkm", m_SaveDataFile->ObjectFilePath[BlockID].c_str());

	size_t oriSize = wcslen(filePath) + 1;
	size_t convertedChars = 0;
	char strConcat[] = "";
	size_t strConcatSize = (strlen(strConcat) + 1) * 2;
	const size_t newSize = oriSize * 2;
	char* nString = new char[newSize + strConcatSize];
	wcstombs_s(&convertedChars, nString, newSize, filePath, _TRUNCATE);
	_mbscat_s((unsigned char*)nString, newSize + strConcatSize, (unsigned char*)strConcat);

	params.BlockName = nString;
	//データを作成
	InstancingData data;
	data.pos = pos;
	data.rot = rot;
	data.scale = scale;
	//配列に追加
	m_InstancingData[BlockID].push_back(data);
	//ナビメッシュ更新のフラグを立てる。
	m_LoadingByChunk->NvmDirtyFlagUp(m_LoadID[0], m_LoadID[1]);
}

void ChunkBlock::RemoveBlock(Block* blockptr)
{
	int BlockID = static_cast<int>(blockptr->GetParam().BlockID);
	if (m_SaveDataFile->ObjectType[BlockID] != ObjectType::Block)
	{
		return;
	}
	if (BlockID < 0 || BlockID >= BlockKinds)
	{
		//ブロックIDがマイナスか最大値より大きいときreturn
		return;
	}
	ChunkBlockDirty = true;
	m_IsModelUpdated = true;

	//削除するブロックの値をリセット
	blockptr->ResetParams();
	//インスタンシングデータをクリア
	m_InstancingData[BlockID].clear();
	//インスタンシングデータをリセット
	//ここからセットしなおす
	for (int x = 0; x < ChunkWidth; x++)
	{
		for (int y = 0; y < ChunkHeight; y++)
		{
			for (int z = 0; z < ChunkWidth; z++)
			{
				auto& block = m_Block[x][y][z];
				if (block.GetParam().BlockID != blockptr->GetParam().BlockID)
				{
					continue;
				}
				if (static_cast<int>(block.GetParam().Durable) > 0)
				{
					//データを作成
					InstancingData data;
					data.pos = block.GetPosition();
					data.rot = block.GetRotation();
					data.scale = block.GetScale();
					//配列に追加
					m_InstancingData[BlockID].push_back(data);
				}
			}
		}
	}
	//ナビメッシュ更新のフラグを立てる。
	m_LoadingByChunk->NvmDirtyFlagUp(m_LoadID[0], m_LoadID[1]);
}