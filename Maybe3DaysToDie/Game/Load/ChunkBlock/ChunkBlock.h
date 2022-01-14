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
	/// ブロックの位置をチャンクに合わせて移動する
	/// </summary>
	void MoveChunk();

	/// <summary>
	/// セーブデータファイルをセット
	/// </summary>
	/// <param name="file">セーブデータファイル</param>
	void SetSaveDataFile(SaveDataFile* file)
	{
		m_SaveDataFile = file;
	}


	Block& GetBlock(Vector3 pos);
public:
	Block m_Block[ChunkWidth][ChunkHeight][ChunkWidth];		//ブロック
private:
	BlockManager* m_BlockManager = nullptr;
	int m_ChunkID[2] = { 0 };
	SaveDataFile* m_SaveDataFile = nullptr;
	bool IsMove = false;
};

