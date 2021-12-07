#pragma once
#include "Block/BlockManager/BlockManager.h"

//チャンクごとのブロック
class ChunkBlock
{
public:
	ChunkBlock();
	~ChunkBlock();

	void Init();

	/// <summary>
	/// コライダーを更新
	/// </summary>
	void UpdateCol();

	/// <summary>
	/// コライダーを初期化
	/// </summary>
	void InitCol();

	/// <summary>
	/// コライダーの位置をチャンクに合わせて移動する
	/// </summary>
	/// <param name="ChunkID">チャンクID</param>
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
	CPhysicsStaticObject m_StaticCol[ChunkWidth][ChunkHeight][ChunkWidth];		//静的物理オブジェクト
	const Vector3 BLOCK_SIZE = { OBJECT_UNIT ,OBJECT_UNIT ,OBJECT_UNIT };
	BlockManager* m_BlockManager = nullptr;
	int m_ChunkID[2] = { 0 };
};