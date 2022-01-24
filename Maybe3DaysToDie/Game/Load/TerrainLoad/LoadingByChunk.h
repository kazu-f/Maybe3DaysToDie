#pragma once
#include "Load/ChunkCollision/ChunkCollision.h"
#include "Load/ChunkBlock/ChunkBlock.h"
#include "TerrainManager/TerrainManager.h"
#include "GameConfig/WorldConfig/WorldConfig.h"

class SaveDataFile;
class WorldConfig;
class LoadingByChunk :public IGameObject
{
private:

public:
	LoadingByChunk()
	{
		//サイズの最大値セット
		BlockModel.resize(BlockKinds);
	}
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

	/// <summary>
	/// ワールド設定をセット
	/// </summary>
	/// <param name="config">ワールド設定</param>
	void SetWorldConfig(WorldConfig* config)
	{
		m_config = config;
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
		int GridPos[2] = { 0 };
		GridPos[0] = static_cast<int>(std::floor((pos.x / OBJECT_UNIT) / ChunkWidth));// +MAX_CHUNK_SIDE / 2;
		GridPos[1] = static_cast<int>(std::floor((pos.z / OBJECT_UNIT) / ChunkWidth));// +MAX_CHUNK_SIDE / 2;
		GridPos[0] = max(min(MAX_CHUNK_SIDE - 1, GridPos[0]), 1);
		GridPos[1] = max(min(MAX_CHUNK_SIDE - 1, GridPos[1]), 1);
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

 private:
	WorldConfig* m_config = nullptr;
	SaveDataFile* m_SaveDataFile = nullptr;
	int PlayerPosInGrid[2] = { 0 };
	bool m_isDirty = true;		//更新するかどうか
	ChunkCollision m_ChunkCol[LoadingChunkCols][LoadingChunkCols];		//チャンクごとのブロック
	ChunkBlock m_ChunkBlock[LoadingChunks][LoadingChunks];
	nsTerrain::TerrainManager* m_TerrainManager = nullptr;		//テラインマネージャー
	std::vector<prefab::ModelRender*>BlockModel = { nullptr };		//ブロックのモデル
};