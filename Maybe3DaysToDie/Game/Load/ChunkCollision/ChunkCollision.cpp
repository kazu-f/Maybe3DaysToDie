#include "stdafx.h"
#include "ChunkCollision.h"

ChunkCollision::ChunkCollision()
{

}

ChunkCollision::~ChunkCollision()
{

}

void ChunkCollision::Init()
{
	InitCol();
}

void ChunkCollision::InitCol()
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
				//座標{0,0}が中心なので減算
				pos.x += geta * (m_ChunkID[0] - MAX_CHUNK_SIDE / 2);
				pos.z += geta * (m_ChunkID[1] - MAX_CHUNK_SIDE / 2);
				//コリジョンを作成
				m_StaticCol[x][y][z].CreateBox(pos, Quaternion::Identity, BLOCK_SIZE);
				m_StaticCol[x][y][z].GetRigidBody().GetBody()->setUserIndex(ColliderUserIndex::enCollisionAttr_Ground_RayBlock);
				//ブロックのポインタを渡しておく
				auto& blocks = m_BlockManager->GetChunkBlock(m_ChunkID);
				m_StaticCol[x][y][z].GetRigidBody().GetBody()->setUserPointer((void*)blocks.m_Block[x][y][z].GetPointer());
			}
		}
	}
}

void ChunkCollision::UpdateCol()
{
	for (int x = 0; x < ChunkWidth; x++)
	{
		for (int y = 0; y < ChunkHeight; y++)
		{
			for (int z = 0; z < ChunkWidth; z++)
			{
				//ブロックのポインタをコライダーに渡しておく
				auto& blocks = m_BlockManager->GetChunkBlock(m_ChunkID);
				if (blocks.m_Block[x][y][z].GetParam().Durable > 0)
				{
					PhysicsWorld().AddRigidBody(m_StaticCol[x][y][z].GetRigidBody());
				}
				else
				{
					PhysicsWorld().RemoveRigidBody(m_StaticCol[x][y][z].GetRigidBody());
				}

				if (y == 0)
				{
					if (IsDebug)
					{
						PhysicsWorld().AddRigidBody(m_StaticCol[x][y][z].GetRigidBody());

					}
				}
			}
		}
	}
}


void ChunkCollision::MoveChunk(int ChunkID[2])
{
	//チャンクIDをセット
	SetChunkID(ChunkID);
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
				pos.x += geta * (m_ChunkID[0] - MAX_CHUNK_SIDE / 2);
				pos.z += geta * (m_ChunkID[1] - MAX_CHUNK_SIDE / 2);
				//ポジションをセット
				m_StaticCol[x][y][z].SetPosAndRot(pos, Quaternion::Identity);
				m_StaticCol[x][y][z].GetRigidBody().GetBody()->setUserIndex(ColliderUserIndex::enCollisionAttr_Ground_RayBlock);
				//ブロックのポインタをコライダーに渡しておく
				auto& blocks = m_BlockManager->GetChunkBlock(m_ChunkID);
				m_StaticCol[x][y][z].GetRigidBody().GetBody()->setUserPointer((void*)blocks.m_Block[x][y][z].GetPointer());
				if (blocks.m_Block[x][y][z].GetParam().Durable > 0)
				{
					PhysicsWorld().AddRigidBody(m_StaticCol[x][y][z].GetRigidBody());
				}
				else
				{
					PhysicsWorld().RemoveRigidBody(m_StaticCol[x][y][z].GetRigidBody());
				}
				if (y == 0)
				{
					if (IsDebug)
					{
						PhysicsWorld().AddRigidBody(m_StaticCol[x][y][z].GetRigidBody());

					}
				}
			}
		}
	}
}