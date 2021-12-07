#pragma once
#include "Block/BlockManager/BlockManager.h"

//�`�����N���Ƃ̃u���b�N
class ChunkBlock
{
public:
	ChunkBlock();
	~ChunkBlock();

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
	/// <param name="ChunkID">�`�����NID</param>
	void MoveChunk();

	void SetBlockManager(BlockManager* manag)
	{
		m_BlockManager = manag;
	}

	void SetChunkID(int ChunkID[2])
	{
		m_ChunkID[0] = ChunkID[0];
		m_ChunkID[1] = ChunkID[1];
	}
private:
	CPhysicsStaticObject m_StaticCol[ChunkWidth][ChunkHeight][ChunkWidth];		//�ÓI�����I�u�W�F�N�g
	const Vector3 BLOCK_SIZE = { OBJECT_UNIT ,OBJECT_UNIT ,OBJECT_UNIT };
	BlockManager* m_BlockManager = nullptr;
	int m_ChunkID[2] = { 0 };
};