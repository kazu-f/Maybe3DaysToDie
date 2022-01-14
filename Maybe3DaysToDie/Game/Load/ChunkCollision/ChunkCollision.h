#pragma once
#include "Block/BlockManager/BlockManager.h"

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
	/// �R���C�_�[��������
	/// </summary>
	void InitCol();

	/// <summary>
	/// �R���C�_�[�̈ʒu���`�����N�ɍ��킹�Ĉړ�����
	/// </summary>
	void MoveChunk();

	void SetBlockManager(BlockManager* manag)
	{
		m_BlockManager = manag;
	}

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
private:
	CPhysicsStaticObject m_StaticCol[ChunkWidth][ChunkHeight][ChunkWidth];		//�ÓI�����I�u�W�F�N�g
	const Vector3 BLOCK_SIZE = { OBJECT_UNIT ,OBJECT_UNIT ,OBJECT_UNIT };
	BlockManager* m_BlockManager = nullptr;
	ChunkBlock* m_ChunkBlocks = nullptr;
	int m_ChunkID[2] = { 0 };
	bool IsDebug = true;		//��ŏ����\�蔭�\�p
	bool IsMove = false;
};