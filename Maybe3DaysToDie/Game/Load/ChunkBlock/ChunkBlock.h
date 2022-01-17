#pragma once
#include "DestructibleObject/Block/Block.h"
#include "SaveDataFile.h"

static const int BlockKinds = 1;		//ブロックの種類
static const int MaxInstanceNum = ChunkWidth * ChunkWidth * ChunkHeight;

class ChunkBlock
{
public:
	ChunkBlock() 
	{		
		//サイズの最大値セット
		BlockModel.resize(BlockKinds);
	}
	~ChunkBlock() 
	{
		OnDestroy();
	}

	void OnDestroy();
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

	/// <summary>
	/// モデルの追加
	/// </summary>
	void AddModel(ObjectParams& params, Vector3& pos, Quaternion& rot, Vector3& scale);

	/// <summary>
	/// モデルの削除
	/// </summary>
	void RemoveBlock(Block* blockptr);

	Block& GetBlock(Vector3 pos);

	bool IsBlockDirty()
	{
		return ChunkBlockDirty;
	}

	void ResetBlockDirty()
	{
		ChunkBlockDirty = false;
	}
public:
	Block m_Block[ChunkWidth][ChunkHeight][ChunkWidth];		//ブロック
private:
	int m_ChunkID[2] = { 0 };
	SaveDataFile* m_SaveDataFile = nullptr;
	bool IsMove = false;
	//todo ChunkBlockでモデル表示できるようにBlockManagerからモデルを削除する
	std::vector<prefab::ModelRender*>BlockModel = { nullptr };		//ブロックのモデル
	int m_modelNum = 0;
	bool ChunkBlockDirty = true;
};

