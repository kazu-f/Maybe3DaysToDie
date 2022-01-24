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
		//�Ή����Ă���`�����N�u���b�N���X�V����K�v�̂Ȃ��Ƃ�
		return;
	}


	//todo �n�`��rayhit����悤�ɂ���
	//�n�`�̃R���W�����͂܂��S���G���Ă��Ȃ��B
	//�u���b�N�p�ɃR���W�����X�V
	UpdateColForBlock();
	//�n�`�p�ɃR���W�����X�V
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
				//�u���b�N�̃|�C���^���R���C�_�[�ɓn���Ă���
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
				//�u���b�N�̃|�C���^���R���C�_�[�ɓn���Ă���
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
				//�`�����N�̈ʒu�����Z
				float geta = 0;
				geta = OBJECT_UNIT * ChunkWidth;
				pos.x += geta * m_ChunkID[0];
				pos.z += geta * m_ChunkID[1];
				//�|�W�V�������Z�b�g
				m_StaticCol[x][y][z].SetPosAndRot(pos, Quaternion::Identity);
			}
		}
	}
	UpdateCol();
}