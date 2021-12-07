#pragma once
#include "DestructibleObject/Block/Block.h"
//#include "Block/ChunkBlock/ChunkBlock.h"

static const int BlockKinds = 1;		//ブロックの種類
static const int MaxInstanceNum = ChunkWidth * ChunkWidth * ChunkHeight;

class BlockManager :public IGameObject
{
private:
	struct Chunk_Block 
	{
	public:
		Block m_Block[ChunkWidth][ChunkHeight][ChunkWidth];
	};

public:
	BlockManager() 
	{
		//サイズの最大値セット
		BlockModel.resize(BlockKinds);
	}
	~BlockManager() override final {}

	void OnDestroy()override final;
	bool Start()override final;
	void Update()override final;
	void AddBlock(const char* BlockName, Vector3& pos, Quaternion& rot, Vector3& scale);
	void RemoveBlock(Block*blockptr);
	Block& GetBlock(const Vector3& pos);
	//Block& GetBlock(const int pos[3])
	//{
	//	return m_Block[pos[0]][pos[1]][pos[2]];
	//}

	Chunk_Block& GetChunkBlock(int ChunkID[2])
	{
		return m_ChunkBlock[ChunkID[0]][ChunkID[1]];
	}

	bool IsBlockDirty()
	{
		return ChunkBlockDirty;
	}

	void ResetBlockDirty()
	{
		ChunkBlockDirty = false;
	}
private:
	Chunk_Block m_ChunkBlock[64][64];
	//Block m_Block[ChunkWidth][ChunkHeight][ChunkWidth];
	//ChunkBlock m_ChunkBlock[16][16];
	std::vector<prefab::ModelRender*>BlockModel = { nullptr };		//ブロックのモデル
	int m_modelNum = 0;
	bool ChunkBlockDirty = true;
};

