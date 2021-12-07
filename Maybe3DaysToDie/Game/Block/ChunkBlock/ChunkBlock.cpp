#include "stdafx.h"
#include "ChunkBlock.h"

ChunkBlock::ChunkBlock()
{

}

ChunkBlock::~ChunkBlock()
{

}

void ChunkBlock::InitCol()
{
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
				m_StaticCol[x][y][z].CreateBox(pos, Quaternion::Identity, BLOCK_SIZE);
				m_StaticCol[x][y][z].GetRigidBody().GetBody()->setUserIndex(ColliderUserIndex::enCollisionAttr_Ground_RayBlock);
			}
		}
	}
}

void ChunkBlock::MoveChunk(int ChunkID[2])
{
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
				pos.x += geta * ChunkID[0];
				pos.z += geta * ChunkID[1];
				//ポジションをセット
				m_StaticCol[x][y][z].SetPosAndRot(pos, Quaternion::Identity);
				m_StaticCol[x][y][z].GetRigidBody().GetBody()->setUserIndex(ColliderUserIndex::enCollisionAttr_Ground_RayBlock);
				//ブロックのポインタをコライダーに渡しておく
				auto& blocks = m_BlockManager->GetChunkBlock(ChunkID);
				m_StaticCol[x][y][z].GetRigidBody().GetBody()->setUserPointer((void*)blocks.m_Block[x][y][z].GetPointer());
			}
		}
	}
}