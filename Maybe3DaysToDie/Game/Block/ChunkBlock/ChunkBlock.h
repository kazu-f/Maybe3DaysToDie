#pragma once
#include "Block/BlockManager/BlockManager.h"

//チャンクごとのブロック
class ChunkBlock
{
public:
	ChunkBlock();
	~ChunkBlock();

	/// <summary>
	/// コライダーを初期化
	/// </summary>
	void InitCol(int ChunkID[2]);

	/// <summary>
	/// コライダーの位置をチャンクに合わせて移動する
	/// </summary>
	/// <param name="ChunkID">チャンクID</param>
	void MoveChunk(int ChunkID[2]);

	void SetBlockManager(BlockManager* manag)
	{
		m_BlockManager = manag;
	}
private:
	CPhysicsStaticObject m_StaticCol[ChunkWidth][ChunkHeight][ChunkWidth];		//静的物理オブジェクト
	const Vector3 BLOCK_SIZE = { OBJECT_UNIT ,OBJECT_UNIT ,OBJECT_UNIT };
	BlockManager* m_BlockManager = nullptr;
};