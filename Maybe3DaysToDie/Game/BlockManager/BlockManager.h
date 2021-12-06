#pragma once
#include "DestructibleObject/Block/Block.h"

static const int BlockKinds = 1;		//ブロックの種類
static const int MaxInstanceNum = ChunkWidth * ChunkWidth * ChunkHeight;

class BlockManager :public IGameObject
{
private:
	struct Chunk_Block 
	{
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
	Block& GetBlock(const int pos[3])
	{
		return m_ChunkBlock[0][0].m_Block[pos[0]][pos[1]][pos[2]];
	}

private:
	//Block m_Block[ChunkWidth][ChunkHeight][ChunkWidth];
	Chunk_Block m_ChunkBlock[16][16];
	std::vector<prefab::ModelRender*>BlockModel = { nullptr };		//ブロックのモデル
	int m_modelNum = 0;
};

