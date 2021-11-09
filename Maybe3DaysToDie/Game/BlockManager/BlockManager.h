#pragma once
#include "DestructibleObject/Block/Block.h"

static const int BlockKinds = 1;		//�u���b�N�̎��
static const int MaxInstanceNum = ChunkWidth * ChunkWidth * ChunkHeight;

class BlockManager :public IGameObject
{
public:
	BlockManager() 
	{
		//�T�C�Y�̍ő�l�Z�b�g
		BlockModel.resize(BlockKinds);
	}
	~BlockManager() override final {}

	void OnDestroy()override final;
	bool Start()override final;
	void Update()override final;
	void AddBlock(const char* BlockName, Vector3& pos, Quaternion& rot, Vector3& scale);
	void RemoveBlock(Block*blockptr);
	Block& GetBlock(const Vector3& pos);

private:
	Block m_Block[ChunkWidth][ChunkHeight][ChunkWidth];
	std::vector<prefab::ModelRender*>BlockModel = { nullptr };		//�u���b�N�̃��f��
	int m_modelInstanceNum[BlockKinds] = { 0 };
	int m_modelNum = 0;
};

