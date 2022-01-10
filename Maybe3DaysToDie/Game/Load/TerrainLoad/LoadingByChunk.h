#pragma once
#include "Load/ChunkCollision/ChunkCollision.h"
#include "GameConfig/WorldConfig/WorldConfig.h"

class SaveDataFile;
class WorldConfig;
class LoadingByChunk :public IGameObject
{
private:

public:
	LoadingByChunk();
	~LoadingByChunk();

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
				//todo この処理気に入らん
				if (PlayerPosInGrid[i] < GridPos[i])
				{
					//上方向に移動したかどうか
					IsMoveUp[i] = true;
				}
				PlayerPosInGrid[i] = GridPos[i];
				IsChunkMove[i] = true;
				m_isDirty = true;
			}
		}
	}

	/// <summary>
	/// ChunkBlockにBlockManagerをセット
	/// </summary>
	/// <param name="manag"></param>
	void SetBlockManagerForChunkBlock(BlockManager* manag)
	{
		m_BlockManager = manag;
		for (int Chunk_X = 0; Chunk_X < LoadingChunks; Chunk_X++)
		{
			for (int Chunk_Z = 0; Chunk_Z < LoadingChunks; Chunk_Z++)
			{
				m_ChunkCol[Chunk_X][Chunk_Z].SetBlockManager(manag);
			}
		}
		IsBlockManagerSet = true;
	}

	bool Start();

	void Update();

	void UpdateMoveChunk();
private:
	WorldConfig* m_config = nullptr;
	SaveDataFile* m_SaveDataFile = nullptr;
	int PlayerPosInGrid[2] = { 0 };
	bool m_isDirty = true;		//更新するかどうか
	ChunkCollision m_ChunkCol[LoadingChunks][LoadingChunks];		//チャンクごとのブロック
	bool IsBlockManagerSet = false;
	BlockManager* m_BlockManager = nullptr;
	bool IsChunkMove[2] = { false };
	bool IsMoveUp[2] = { false };
};