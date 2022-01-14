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
		for (int i = 0; i < 2; i++)
		{
			if (m_ChunkID[i] != ChunkID[i])
			{
				m_ChunkID[i] = ChunkID[i];
				IsMove = true;
			}
		}
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
	/// �u���b�N�̈ʒu���`�����N�ɍ��킹�Ĉړ�����
	/// </summary>
	void MoveChunk();

	/// <summary>
	/// �Z�[�u�f�[�^�t�@�C�����Z�b�g
	/// </summary>
	/// <param name="file">�Z�[�u�f�[�^�t�@�C��</param>
	void SetSaveDataFile(SaveDataFile* file)
	{
		m_SaveDataFile = file;
	}


	Block& GetBlock(Vector3 pos);
public:
	Block m_Block[ChunkWidth][ChunkHeight][ChunkWidth];		//�u���b�N
private:
	BlockManager* m_BlockManager = nullptr;
	int m_ChunkID[2] = { 0 };
	SaveDataFile* m_SaveDataFile = nullptr;
	bool IsMove = false;
};

