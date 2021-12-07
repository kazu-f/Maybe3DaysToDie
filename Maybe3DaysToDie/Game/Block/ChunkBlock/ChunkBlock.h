#pragma once

//チャンクごとのブロック
class ChunkBlock
{
public:
	ChunkBlock();
	~ChunkBlock();

	/// <summary>
	/// コライダーを初期化
	/// </summary>
	void InitCol();

	/// <summary>
	/// コライダーの位置をチャンクに合わせて移動する
	/// </summary>
	/// <param name="ChunkID">チャンクID</param>
	void MoveChunk(int ChunkID[2]);
private:
	CPhysicsStaticObject m_StaticCol[ChunkWidth][ChunkHeight][ChunkWidth];		//静的物理オブジェクト
	const Vector3 BLOCK_SIZE = { OBJECT_UNIT ,OBJECT_UNIT ,OBJECT_UNIT };
};