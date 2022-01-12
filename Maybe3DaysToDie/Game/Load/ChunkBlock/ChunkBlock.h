#pragma once
#include "DestructibleObject/Block/Block.h"
#include "SaveDataFile.h"

class ChunkBlock
{
public:
	ChunkBlock() {}
	~ChunkBlock() {}

	void Init();

	void SetChunkID(int ChunkID[2])
	{
		m_ChunkID[0] = ChunkID[0];
		m_ChunkID[1] = ChunkID[1];
	}
	void SetBlockManager(BlockManager* manag)
	{
		m_BlockManager = manag;
	}

	void GetChunkID(int id[2])
	{
		id[0] = m_ChunkID[0];
		id[1] = m_ChunkID[1];
	}

	/// <summary>
	/// �R���C�_�[�̈ʒu���`�����N�ɍ��킹�Ĉړ�����
	/// </summary>
	/// <param name="ChunkID">�`�����NID</param>
	void MoveChunk(int ChunkID[2]);

	/// <summary>
	/// �Z�[�u�f�[�^�t�@�C�����Z�b�g
	/// </summary>
	/// <param name="file">�Z�[�u�f�[�^�t�@�C��</param>
	void SetSaveDataFile(SaveDataFile* file)
	{
		m_SaveDataFile = file;
	}
private:
	Block m_Block[ChunkWidth][ChunkHeight][ChunkWidth];
	BlockManager* m_BlockManager = nullptr;
	int m_ChunkID[2] = { 0 };
	SaveDataFile* m_SaveDataFile = nullptr;
};
