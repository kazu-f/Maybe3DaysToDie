#pragma once
#include "Block/ChunkBlock/ChunkBlock.h"

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
		GridPos[0] = static_cast<int>(std::floor(pos.x / OBJECT_UNIT)) + MAX_CHUNK_SIDE / 2;
		GridPos[1] = static_cast<int>(std::floor(pos.z / OBJECT_UNIT)) + MAX_CHUNK_SIDE / 2;
		for (int i = 0; i < 2; i++)
		{
			if (PlayerPosInGrid[i] != GridPos[i])
			{
				PlayerPosInGrid[i] = GridPos[i];
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
		for (int Chunk_X = 0; Chunk_X < LoadingChunks; Chunk_X++)
		{
			for (int Chunk_Z = 0; Chunk_Z < LoadingChunks; Chunk_Z++)
			{
				m_ChunkBlock[Chunk_X][Chunk_Z].SetBlockManager(manag);
			}
		}
	}

	bool Start();

	void Update();
private:
	WorldConfig* m_config = nullptr;
	SaveDataFile* m_SaveDataFile = nullptr;
	int PlayerPosInGrid[2] = { 0 };
	bool m_isDirty = false;		//更新するかどうか
	ChunkBlock m_ChunkBlock[LoadingChunks][LoadingChunks];		//チャンクごとのブロック
};