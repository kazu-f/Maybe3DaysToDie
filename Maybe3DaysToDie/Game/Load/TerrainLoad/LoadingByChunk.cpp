#include "stdafx.h"
#include "LoadingByChunk.h"

LoadingByChunk::LoadingByChunk()
{

}

LoadingByChunk::~LoadingByChunk()
{

}

bool LoadingByChunk::Start()
{
	if (IsBlockManagerSet == false)
	{
		//BlockManagerをセットしてください。
		std::abort();
	}
	SetPlayerPos(Vector3::Zero);
	InitChunkCols();
	InitChunkBlocks();
	return true;
}

void LoadingByChunk::InitChunkCols()
{
	int Grid[2] = { 0 };
	//プレイヤーのいるチャンク
	Grid[0] = PlayerPosInGrid[0];
	Grid[1] = PlayerPosInGrid[1];
	Grid[0] -= std::floor(LoadingChunkCols / 2);
	Grid[1] -= std::floor(LoadingChunkCols / 2);
	//最大値と最小値を決めておく
	//最大値はチャンクの端からロードするチャンクの半分を引いたもの
	//最小値は0
	Grid[0] = max(min(Grid[0], MAX_CHUNK_SIDE - std::floor(LoadingChunkCols / 2)), 0);
	Grid[1] = max(min(Grid[1], MAX_CHUNK_SIDE - std::floor(LoadingChunkCols / 2)), 0);

	//現在移動中のグリッド
	int NowGrid[2];
	for (int i = 0; i < 2; i++)
	{
		for (int x = 0; x < LoadingChunkCols; x++)
		{
			NowGrid[0] = Grid[0] + x;
			for (int z = 0; z < LoadingChunkCols; z++)
			{
				NowGrid[1] = Grid[1] + z;
				m_ChunkCol[x][z].SetChunkID(NowGrid);
				//初期化
				m_ChunkCol[x][z].Init();
			}
		}
	}
}

void LoadingByChunk::InitChunkBlocks()
{
	int Grid[2] = { 0 };
	//プレイヤーのいるチャンク
	Grid[0] = PlayerPosInGrid[0];
	Grid[1] = PlayerPosInGrid[1];
	Grid[0] -= std::floor(LoadingChunks / 2);
	Grid[1] -= std::floor(LoadingChunks / 2);
	//最大値と最小値を決めておく
	//最大値はチャンクの端からロードするチャンクの半分を引いたもの
	//最小値は0
	Grid[0] = max(min(Grid[0], MAX_CHUNK_SIDE - std::floor(LoadingChunks / 2)), 0);
	Grid[1] = max(min(Grid[1], MAX_CHUNK_SIDE - std::floor(LoadingChunks / 2)), 0);
	//現在移動中のグリッド
	int NowGrid[2];
	for (int i = 0; i < 2; i++)
	{
		for (int x = 0; x < LoadingChunks; x++)
		{
			NowGrid[0] = Grid[0] + x;
			for (int z = 0; z < LoadingChunks; z++)
			{
				NowGrid[1] = Grid[1] + z;
				m_ChunkBlock[x][z].SetChunkID(NowGrid);
				//初期化
				m_ChunkBlock[x][z].Init();
			}
		}
	}
}

void LoadingByChunk::Update()
{
	if (m_BlockManager->IsBlockDirty())
	{
		for (int Chunk_X = 0; Chunk_X < LoadingChunkCols; Chunk_X++)
		{
			for (int Chunk_Z = 0; Chunk_Z < LoadingChunkCols; Chunk_Z++)
			{
				//コライダーを更新
				m_ChunkCol[Chunk_X][Chunk_Z].UpdateCol();
			}
		}
		m_BlockManager->ResetBlockDirty();
	}


	if (m_isDirty == false)
	{
		return;
	}

	UpdateMoveChunk();

	////////////////////////////////////////////
	/////ここから下は更新する必要があるとき/////
	////////////////////////////////////////////
	for (int Chunk_X = 0; Chunk_X < m_config->GetLoadingChunkRange(); Chunk_X++)
	{
		for (int Chunk_Y = 0; Chunk_Y < m_config->GetLoadingChunkRange(); Chunk_Y++)
		{
			//プレイヤーを中心にロードする
			int LoadingGrid[2] = { 0 };
			for (int i = 0; i < 2; i++)
			{
				LoadingGrid[i] = PlayerPosInGrid[i];
				LoadingGrid[i] -= m_config->GetLoadingChunkRange() / 2;
			}
			LoadingGrid[0] += Chunk_X;
			LoadingGrid[1] += Chunk_Y;

			//ロードする
		}
	}

	//更新フラグを下す
	m_isDirty = false;
}

void LoadingByChunk::UpdateMoveChunk()
{
	//コライダーを移動
	UpdateChunkCols();
	//ブロックを移動
	UpdateChunkBlocks();
}

void LoadingByChunk::UpdateChunkCols()
{
	int Grid[2] = { 0 };
	//プレイヤーの左下のチャンク
	Grid[0] = PlayerPosInGrid[0];
	Grid[1] = PlayerPosInGrid[1];
	Grid[0] -= std::floor(LoadingChunkCols / 2);
	Grid[1] -= std::floor(LoadingChunkCols / 2);
	//最大値と最小値を決めておく
	//最大値はチャンクの端からロードするチャンクの半分を引いたもの
	//最小値は0
	Grid[0] = max(min(Grid[0], MAX_CHUNK_SIDE - std::floor(LoadingChunkCols / 2)), 0);
	Grid[1] = max(min(Grid[1], MAX_CHUNK_SIDE - std::floor(LoadingChunkCols / 2)), 0);

	//現在移動中のグリッド
	int NowGrid[2];
	for (int i = 0; i < 2; i++)
	{
		for (int x = 0; x < LoadingChunkCols; x++)
		{
			NowGrid[0] = Grid[0] + x;
			for (int z = 0; z < LoadingChunkCols; z++)
			{
				NowGrid[1] = Grid[1] + z;
				m_ChunkCol[x][z].MoveChunk(NowGrid);
			}
		}
	}


}

void LoadingByChunk::UpdateChunkBlocks()
{
	int Grid[2] = { 0 };
	//プレイヤーの左下のチャンク
	Grid[0] = PlayerPosInGrid[0];
	Grid[1] = PlayerPosInGrid[1];
	Grid[0] -= std::floor(LoadingChunks / 2);
	Grid[1] -= std::floor(LoadingChunks / 2);
	//最大値と最小値を決めておく
	//最大値はチャンクの端からロードするチャンクの半分を引いたもの
	//最小値は0
	Grid[0] = max(min(Grid[0], MAX_CHUNK_SIDE - std::floor(LoadingChunks / 2)), 0);
	Grid[1] = max(min(Grid[1], MAX_CHUNK_SIDE - std::floor(LoadingChunks / 2)), 0);
	//現在移動中のグリッド
	int NowGrid[2];
	for (int i = 0; i < 2; i++)
	{
		for (int x = 0; x < LoadingChunks; x++)
		{
			NowGrid[0] = Grid[0] + x;
			for (int z = 0; z < LoadingChunks; z++)
			{
				NowGrid[1] = Grid[1] + z;
				m_ChunkBlock[x][z].MoveChunk(NowGrid);
			}
		}
	}
}