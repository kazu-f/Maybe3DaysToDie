#pragma once
#include "TerrainManager/TerrainWorld.h"
#include "SaveDataFile.h"

class ChunkBlock;
class LoadCollision
{
public:
	LoadCollision() {}
	~LoadCollision() {}

	/// <summary>
	/// 初期化
	/// </summary>
	void Init();
	/// <summary>
	/// チャンクブロックとリンクさせる
	/// </summary>
	/// <param name="ptr">ポインタ</param>
	/// <param name="ChunkX">プレイヤーを中心とした3*3のチャンクのX</param>
	/// <param name="ChunkZ">プレイヤーを中心とした3*3のチャンクのZ</param>
	void LinkChunk(ChunkBlock* ptr, int ChunkX, int ChunkZ)
	{
		m_ChunkBlocks[ChunkX][ChunkZ] = ptr;
	}

	/// <summary>
	/// テラインチャンクデータとリンクさせる
	/// </summary>
	/// <param name="ptr">ポインタ</param>
	/// <param name="ChunkX">プレイヤーを中心とした3*3のチャンクのX</param>
	/// <param name="ChunkZ">プレイヤーを中心とした3*3のチャンクのZ</param>
	void LinkTerrainWorld(nsTerrain::TerrainChunkData* ptr,int ChunkX,int ChunkZ)
	{
		m_TerrainData[ChunkX][ChunkZ] = ptr;
	}

	/// <summary>
	/// プレイヤーの位置をセット
	/// </summary>
	/// <param name="pos">プレイヤーの位置</param>
	void SetPlayerPos(const Vector3& pos)
	{
		m_PlayerPos = pos;
	}

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// セーブデータファイルをセット
	/// </summary>
	void SetSaveDataFile(SaveDataFile* ptr)
	{
		m_SaveDataFile = ptr;
	}

private:
	/// <summary>
	/// コライダーを作成
	/// </summary>
	void NewCol();

	/// <summary>
	/// コライダーをブロック用に更新
	/// </summary>
	void UpdateColForBlock();

private:
	static const int Cols = PlayerRange * 2 + 1;
	const Vector3 BLOCK_SIZE = { OBJECT_UNIT ,OBJECT_UNIT ,OBJECT_UNIT };
	CPhysicsStaticObject m_StaticCol[Cols][Cols][Cols];		//サイズはプレイヤーのポジションがあるので2倍+1
	ChunkBlock* m_ChunkBlocks[LoadingChunkCols][LoadingChunkCols] = { nullptr };		//プレイヤーを中心に3*3のチャンクが必要(移動によってチャンクまたぐ可能性があるので)
	nsTerrain::TerrainChunkData* m_TerrainData[LoadingChunkCols][LoadingChunkCols] = { nullptr };
	Vector3 m_PlayerPos = Vector3::Zero;
	Vector3Int m_PosInChunk = { 0,0,0 };
	SaveDataFile* m_SaveDataFile = nullptr;
};