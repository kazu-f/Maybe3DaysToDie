#include "stdafx.h"
#include "ChunkBlock.h"

void ChunkBlock::Init()
{

}

void ChunkBlock::MoveChunk(int ChunkID[2])
{
	//チャンクIDをセット
	SetChunkID(ChunkID);
	//セーブデータファイルからチャンクの情報を取得
	auto& chunkData = m_SaveDataFile->m_ChunkData[m_ChunkID[0]][m_ChunkID[1]];
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
				//パラメータをセット
				m_Block[x][y][z].SetParams(param);
			}
		}
	}

}