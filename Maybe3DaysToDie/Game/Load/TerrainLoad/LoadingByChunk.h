#pragma once
#include "Load/ChunkCollision/ChunkCollision.h"
#include "Load/ChunkBlock/ChunkBlock.h"
#include "TerrainManager/TerrainManager.h"

class ItemDataFile;

class LoadingByChunk :public IGameObject
{
private:

public:
	LoadingByChunk();
	~LoadingByChunk();


	void OnDestroy();

	/// <summary>
	/// セーブデータファイルをセット
	/// </summary>
	/// <param name="file">セーブデータファイル</param>
	void SetSaveDataFile(SaveDataFile* file)
	{
		m_SaveDataFile = file;
	}

	void SetTerrainManager(nsTerrain::TerrainManager* manager)
	{
		m_TerrainManager = manager;
	}

	/// <summary>
	/// プレイヤーのポジションをセットして読み込むチャンクを指定
	/// </summary>
	/// <param name="pos">プレイヤーのポジション</param>
	void SetPlayerPos(const Vector3& pos)
	{
		int Limit = static_cast<int>(LoadingChunks / 2);
		int GridPos[2] = { 0 };
		GridPos[0] = static_cast<int>(std::floor((pos.x / OBJECT_UNIT) / ChunkWidth));// +MAX_CHUNK_SIDE / 2;
		GridPos[1] = static_cast<int>(std::floor((pos.z / OBJECT_UNIT) / ChunkWidth));// +MAX_CHUNK_SIDE / 2;
		GridPos[0] = max(min(MAX_CHUNK_SIDE - Limit, GridPos[0]), Limit);
		GridPos[1] = max(min(MAX_CHUNK_SIDE - Limit, GridPos[1]), Limit);
		for (int i = 0; i < 2; i++)
		{
			if (PlayerPosInGrid[i] != GridPos[i])
			{
				PlayerPosInGrid[i] = GridPos[i];
				m_isDirty = true;
			}
		}
	}

	bool Start();

	/// <summary>
	/// コライダーの初期化
	/// </summary>
	void InitChunkCols();

	/// <summary>
	/// ブロックの初期化
	/// </summary>
	void InitChunkBlocks();

	/// <summary>
	/// モデルの初期化
	/// </summary>
	void InitModels();

	void Update();

	/// <summary>
	/// チャンクを移動したときの更新
	/// </summary>
	void UpdateMoveChunk();

	/// <summary>
	/// コライダーの更新
	/// </summary>
	void UpdateChunkCols();

	/// <summary>
	/// ブロックの更新
	/// </summary>
	void UpdateChunkBlocksAndTerrains();

	/// <summary>
	/// テラインの更新
	/// </summary>
	void UpdateTerains();

	/// <summary>
	/// ワールドテーブルデータの更新
	/// </summary>
	void UpdateWorldTableData();

	/// <summary>
	/// チャンクブロックをチャンクコライダーと紐づけする
	/// </summary>
	void LinkChunk();

	/// <summary>
	/// ポジションから対応するチャンクブロックを取得
	/// </summary>
	ChunkBlock& GetChunkBlocks(int ID[2]);

	/// <summary>
	/// モデルの更新
	/// </summary>
	void UpdateModels();

	/// <summary>
	/// ナビメッシュを更新するかどうか
	/// </summary>
	bool IsNvmDirty(int x,int z)
	{
		return m_IsUpdatedChunk[x][z];
	}

	/// <summary>
	/// ナビメッシュ更新のフラグ下す
	/// </summary>
	void NvmDirtyFlagDown(int x,int z)
	{
		m_IsUpdatedChunk[x][z] = false;
	}

	/// <summary>
	/// ナビメッシュ更新のフラグを立てる
	/// </summary>
	void NvmDirtyFlagUp(int x,int z)
	{
		m_IsUpdatedChunk[x][z] = true;
	}

	ChunkBlock* GetChunkBlock(int x, int z)
	{
		return &m_ChunkBlock[x][z];
	}
 private:
	 ItemDataFile* m_itemDatas = nullptr;
	SaveDataFile* m_SaveDataFile = nullptr;
	int PlayerPosInGrid[2] = { 0 };
	bool m_isDirty = true;		//更新するかどうか
	ChunkCollision m_ChunkCol[LoadingChunkCols][LoadingChunkCols];		//チャンクごとのブロック
	ChunkBlock m_ChunkBlock[LoadingChunks][LoadingChunks];
	nsTerrain::TerrainManager* m_TerrainManager = nullptr;		//テラインマネージャー
	std::vector<prefab::ModelRender*>BlockModel = { nullptr };		//ブロックのモデル
	bool m_IsUpdatedChunk[LoadingChunks][LoadingChunks];
};