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
				//�`�����N�̈ʒu�����Z
				float geta = 0;
				geta = OBJECT_UNIT * ChunkWidth;
				//���W{0,0}������
				pos.x += geta * m_ChunkID[0];
				pos.z += geta * m_ChunkID[1];
				//�R���W�������쐬
				m_StaticCol[x][y][z].CreateBox(pos, Quaternion::Identity, BLOCK_SIZE);
				m_StaticCol[x][y][z].GetRigidBody().GetBody()->setUserIndex(ColliderUserIndex::enCollisionAttr_Ground_RayBlock);
				//�u���b�N�̃|�C���^��n���Ă���
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
	//�`�����NID���Z�b�g
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
				//�`�����N�̈ʒu�����Z
				float geta = 0;
				geta = OBJECT_UNIT * ChunkWidth;
				pos.x += geta * m_ChunkID[0];
				pos.z += geta * m_ChunkID[1];
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