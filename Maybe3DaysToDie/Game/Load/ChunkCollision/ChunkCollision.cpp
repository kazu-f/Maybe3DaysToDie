#include "stdafx.h"
#include "ChunkCollision.h"
#include "Load/ChunkBlock/ChunkBlock.h"
#include "TerrainManager/TerrainChunkData.h"

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
				auto& blocks = m_ChunkBlocks->m_Block[x][y][z];
				m_StaticCol[x][y][z].GetRigidBody().GetBody()->setUserPointer((void*)blocks.GetPointer());
			}
		}
	}
}

void ChunkCollision::UpdateCol()
{
	if (m_ChunkBlocks->IsBlockDirty() == false && m_TerrainData->IsUpdated() == false)
	{
		//対応しているチャンクブロックが更新する必要のないとき
		return;
	}


	//todo 地形にrayhitするようにする
	//地形のコリジョンはまだ全く触っていない。
	//ブロック用にコリジョン更新
	UpdateColForBlock();
	//地形用にコリジョン更新
	UpdateColForTerrain();
}

void ChunkCollision::UpdateColForBlock()
{
	for (int x = 0; x < ChunkWidth; x++)
	{
		for (int y = 0; y < ChunkHeight; y++)
		{
			for (int z = 0; z < ChunkWidth; z++)
			{
				//ブロックのポインタをコライダーに渡しておく
				auto& blocks = m_ChunkBlocks->m_Block[x][y][z];
				if (blocks.GetParam().Durable > 0)
				{
					PhysicsWorld().AddRigidBody(m_StaticCol[x][y][z].GetRigidBody());
					m_StaticCol[x][y][z].GetRigidBody().GetBody()->setUserPointer((void*)blocks.GetPointer());
					m_StaticCol[x][y][z].GetRigidBody().GetBody()->setUserIndex(ColliderUserIndex::enCollisionAttr_Ground_RayBlock);
				}
				else
				{
					PhysicsWorld().RemoveRigidBody(m_StaticCol[x][y][z].GetRigidBody());
				}
			}
		}
	}

	m_ChunkBlocks->ResetBlockDirty();
}

void ChunkCollision::UpdateColForTerrain()
{
	for (int x = 0; x < ChunkWidth; x++)
	{
		for (int y = 0; y < ChunkHeight; y++)
		{
			for (int z = 0; z < ChunkWidth; z++)
			{
				//ブロックのポインタをコライダーに渡しておく
				const auto& terrain = m_TerrainData->GetTerrainData({ x,y,z });
				if (terrain->GetVoxel() > 0)
				{
					PhysicsWorld().AddRigidBody(m_StaticCol[x][y][z].GetRigidBody());
					m_StaticCol[x][y][z].GetRigidBody().GetBody()->setUserPointer((void*)terrain->GetPointer());
					m_StaticCol[x][y][z].GetRigidBody().GetBody()->setUserIndex(ColliderUserIndex::enCollisionAttr_RayBlock);
				}
			}
		}
	}
}

void ChunkCollision::MoveChunk()
{
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
			}
		}
	}
	UpdateCol();
}