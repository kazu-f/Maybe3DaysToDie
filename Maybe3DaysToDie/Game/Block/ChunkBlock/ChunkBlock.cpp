#include "stdafx.h"
#include "ChunkBlock.h"

ChunkBlock::ChunkBlock()
{

}

ChunkBlock::~ChunkBlock()
{

}

void ChunkBlock::Init()
{
	InitCol();
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
				//�`�����N�̈ʒu�����Z
				float geta = 0;
				geta = OBJECT_UNIT * ChunkWidth;
				//���W{0,0}�����S�Ȃ̂Ō��Z
				pos.x += geta * m_ChunkID[0] - MAX_CHUNK_SIDE / 2;
				pos.z += geta * m_ChunkID[1] - MAX_CHUNK_SIDE / 2;
				//�R���W�������쐬
				m_StaticCol[x][y][z].CreateBox(pos, Quaternion::Identity, BLOCK_SIZE);
				m_StaticCol[x][y][z].GetRigidBody().GetBody()->setUserIndex(ColliderUserIndex::enCollisionAttr_Ground_RayBlock);
			}
		}
	}
}

void ChunkBlock::UpdateCol()
{
	for (int x = 0; x < ChunkWidth; x++)
	{
		for (int y = 0; y < ChunkHeight; y++)
		{
			for (int z = 0; z < ChunkWidth; z++)
			{
				//�u���b�N�̃|�C���^���R���C�_�[�ɓn���Ă���
				auto& blocks = m_BlockManager->GetChunkBlock(m_ChunkID);
				if (blocks.m_Block[x][y][z].GetParam().Durable > 0)
				{
					PhysicsWorld().AddRigidBody(m_StaticCol[x][y][z].GetRigidBody());
				}
				else
				{
					PhysicsWorld().RemoveRigidBody(m_StaticCol[x][y][z].GetRigidBody());
				}
			}
		}
	}
}


void ChunkBlock::MoveChunk()
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
				//�`�����N�̈ʒu�����Z
				float geta = 0;
				geta = OBJECT_UNIT * ChunkWidth;
				pos.x += geta * m_ChunkID[0] - MAX_CHUNK_SIDE / 2;
				pos.z += geta * m_ChunkID[1] - MAX_CHUNK_SIDE / 2;
				//�|�W�V�������Z�b�g
				m_StaticCol[x][y][z].SetPosAndRot(pos, Quaternion::Identity);
				m_StaticCol[x][y][z].GetRigidBody().GetBody()->setUserIndex(ColliderUserIndex::enCollisionAttr_Ground_RayBlock);
				//�u���b�N�̃|�C���^���R���C�_�[�ɓn���Ă���
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
			}
		}
	}
}