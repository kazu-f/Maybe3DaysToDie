#include "stdafx.h"
#include "ChunkCollision.h"
#include "Load/ChunkBlock/ChunkBlock.h"

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
				//座標{0,0}が左下
				pos.x += geta * m_ChunkID[0];
				pos.z += geta * m_ChunkID[1];
				//コリジョンを作成
				m_StaticCol[x][y][z].CreateBox(pos, Quaternion::Identity, BLOCK_SIZE);
				m_StaticCol[x][y][z].GetRigidBody().GetBody()->setUserIndex(ColliderUserIndex::enCollisionAttr_Ground_RayBlock);
				//ブロックのポインタを渡しておく
				//auto& blocks = m_BlockManager->GetChunkBlock(m_ChunkID);
				//m_StaticCol[x][y][z].GetRigidBody().GetBody()->setUserPointer((void*)blocks.m_Block[x][y][z].GetPointer());
				auto& blocks = m_ChunkBlocks->m_Block[x][y][z];
				m_StaticCol[x][y][z].GetRigidBody().GetBody()->setUserPointer((void*)blocks.GetPointer());
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
				//auto& blocks = m_BlockManager->GetChunkBlock(m_ChunkID);
				auto& blocks = m_ChunkBlocks->m_Block[x][y][z];
				if (blocks.GetParam().Durable > 0)
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
	if (IsMove == false)
	{
		return;
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
				m_StaticCol[x][y][z].SetPosAndRot(pos, Quaternion::Identity);
				m_StaticCol[x][y][z].GetRigidBody().GetBody()->setUserIndex(ColliderUserIndex::enCollisionAttr_Ground_RayBlock);
				//ブロックのポインタをコライダーに渡しておく
				//auto& blocks = m_BlockManager->GetChunkBlock(m_ChunkID);
				//m_StaticCol[x][y][z].GetRigidBody().GetBody()->setUserPointer((void*)blocks.m_Block[x][y][z].GetPointer());
				auto& blocks = m_ChunkBlocks->m_Block[x][y][z];
				m_StaticCol[x][y][z].GetRigidBody().GetBody()->setUserPointer((void*)blocks.GetPointer());
				if (blocks.GetParam().Durable > 0)
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