#pragma once
#include "TerrainManager/TerrainWorld.h"

class ChunkBlock;
//�`�����N���Ƃ̃u���b�N
class ChunkCollision
{
public:
	ChunkCollision();
	~ChunkCollision();

	void Init();

	/// <summary>
	/// �R���C�_�[���X�V
	/// </summary>
	void UpdateCol();

	/// <summary>
	/// �u���b�N�Ɍ����ăR���W�������X�V����
	/// </summary>
	void UpdateColForBlock();

	/// <summary>
	/// �n�`�Ɍ����ăR���W�������X�V����
	/// </summary>
	void UpdateColForTerrain();

	/// <summary>
	/// �R���C�_�[��������
	/// </summary>
	void InitCol();

	/// <summary>
	/// �R���C�_�[�̈ʒu���`�����N�ɍ��킹�Ĉړ�����
	/// </summary>
	void MoveChunk();

	void SetChunkID(int ChunkID[2])
	{
		for (int i = 0; i < 2; i++)
		{
			if (m_ChunkID[i] != ChunkID[i])
			{
				m_ChunkID[i] = ChunkID[i];
				IsMove = true;
			}
		}
	}

	void GetChunkID(int id[2])
	{
		id[0] = m_ChunkID[0];
		id[1] = m_ChunkID[1];
	}

	/// <summary>
	/// �`�����N�u���b�N�ƃ����N������
	/// </summary>
	/// <param name="CB">�Ή�����`�����N�u���b�N</param>
	void LinkChunkBlocks(ChunkBlock*CB)
	{
		m_ChunkBlocks = CB;
	}

	/// <summary>
	/// �e���C���`�����N�f�[�^�ƃ����N������
	/// </summary>
	/// <param name="TW">�Ή�����e���C���`�����N�f�[�^</param>
	void LinkTerrainWorld(nsTerrain::TerrainChunkData*TCD)
	{
		m_TerrainData = TCD;
	}

private:
	CPhysicsStaticObject m_StaticCol[ChunkWidth][ChunkHeight][ChunkWidth];		//�ÓI�����I�u�W�F�N�g
	const Vector3 BLOCK_SIZE = { OBJECT_UNIT ,OBJECT_UNIT ,OBJECT_UNIT };
	ChunkBlock* m_ChunkBlocks = nullptr;
	nsTerrain::TerrainChunkData* m_TerrainData = nullptr;
	int m_ChunkID[2] = { 0 };
	bool IsMove = false;
};