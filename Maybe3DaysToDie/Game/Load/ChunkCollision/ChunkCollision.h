#pragma once
#include "TerrainManager/TerrainWorld.h"

class ChunkBlock;
//チャンクごとのブロック
class ChunkCollision
{
public:
	ChunkCollision();
	~ChunkCollision();

	void Init();

	/// <summary>
	/// コライダーを更新
	/// </summary>
	void UpdateCol();

	/// <summary>
	/// ブロックに向けてコリジョンを更新する
	/// </summary>
	void UpdateColForBlock();

	/// <summary>
	/// 地形に向けてコリジョンを更新する
	/// </summary>
	void UpdateColForTerrain();

	/// <summary>
	/// コライダーを初期化
	/// </summary>
	void InitCol();

	/// <summary>
	/// コライダーの位置をチャンクに合わせて移動する
	/// </summary>
	void MoveChunk();

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
	/// チャンクブロックとリンクさせる
	/// </summary>
	/// <param name="CB">対応するチャンクブロック</param>
	void LinkChunkBlocks(ChunkBlock*CB)
	{
		m_ChunkBlocks = CB;
	}

	/// <summary>
	/// テラインチャンクデータとリンクさせる
	/// </summary>
	/// <param name="TW">対応するテラインチャンクデータ</param>
	void LinkTerrainWorld(nsTerrain::TerrainChunkData*TCD)
	{
		m_TerrainData = TCD;
	}

private:
	CPhysicsStaticObject m_StaticCol[ChunkWidth][ChunkHeight][ChunkWidth];		//静的物理オブジェクト
	const Vector3 BLOCK_SIZE = { OBJECT_UNIT ,OBJECT_UNIT ,OBJECT_UNIT };
	ChunkBlock* m_ChunkBlocks = nullptr;
	nsTerrain::TerrainChunkData* m_TerrainData = nullptr;
	int m_ChunkID[2] = { 0 };
	bool IsMove = false;
};