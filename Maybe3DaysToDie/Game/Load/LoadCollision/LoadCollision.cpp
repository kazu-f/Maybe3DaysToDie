#include "stdafx.h"
#include "LoadCollision.h"
#include "Load/ChunkBlock/ChunkBlock.h"
#include "TerrainManager/TerrainChunkData.h"

void LoadCollision::Init()
{
	//コリジョンを初期化
	NewCol();
}

void LoadCollision::NewCol()
{
	for (auto& x : m_StaticCol)
	{
		for (auto& y : x)
		{
			for (auto& col : y)
			{
				//コリジョンを作成
				col.CreateBox(Vector3::Zero, Quaternion::Identity, BLOCK_SIZE);
				col.GetRigidBody().GetBody()->setUserIndex(ColliderUserIndex::enCollisionAttr_Ground_RayBlock);
			}
		}
	}
}

void LoadCollision::Update()
{
	//まずはプレイヤーがいるチャンク内での位置を計算
	Vector3 Pos = m_PlayerPos;
	Pos /= 100.0f;
	m_PosInChunk.x = static_cast<int>(Pos.x);
	m_PosInChunk.y = static_cast<int>(Pos.y);
	m_PosInChunk.z = static_cast<int>(Pos.z);

	m_PosInChunk.x %= ChunkWidth;
	m_PosInChunk.y %= ChunkWidth;
	m_PosInChunk.z %= ChunkWidth;

	m_PosInChunk.x -= (Cols / 2);
	m_PosInChunk.y -= (Cols / 2);
	m_PosInChunk.z -= (Cols / 2);

	UpdateColForBlock();
}

void LoadCollision::UpdateColForBlock()
{

	for (int x = 0; x < Cols; x++)
	{
		for (int y = 0; y < Cols; y++)
		{
			for (int z = 0; z < Cols; z++)
			{
				int NowID[2] = { 1 };
				//まずは位置を計算
				m_PosInChunk.x += x;
				m_PosInChunk.y += y;
				m_PosInChunk.z += z;
				if (m_PosInChunk.x < 0)
				{
					NowID[0]--;
				}
				else if (m_PosInChunk.x > ChunkWidth)
				{
					NowID[0]++;
				}
				if (m_PosInChunk.z < 0)
				{
					NowID[1]--;
				}
				else if (m_PosInChunk.z > ChunkWidth)
				{
					NowID[1]++;
				}

				//ブロックのポインタを渡しておく
				auto& blocks = m_ChunkBlocks[NowID[0]][NowID[1]]->m_Block[x][y][z];
				if (blocks.GetParam().Durable > 0)
				{
					//タグをつける
					m_StaticCol[x][y][z].GetRigidBody().GetBody()->setUserIndex(ColliderUserIndex::enCollisionAttr_Ground_RayBlock);
					m_StaticCol[x][y][z].GetRigidBody().GetBody()->setUserPointer((void*)blocks.GetPointer());
				}
			}
		}
	}
}