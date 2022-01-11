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
	for (int Chunk_X = 0; Chunk_X < LoadingChunkCols; Chunk_X++)
	{
		for (int Chunk_Z = 0; Chunk_Z < LoadingChunkCols; Chunk_Z++)
		{
			//IDをセット
			int ChunkID[2] = { 0 };
			ChunkID[0] += PlayerPosInGrid[0] + Chunk_X - 1;
			ChunkID[1] += PlayerPosInGrid[1] + Chunk_Z - 1;
			m_ChunkCol[Chunk_X][Chunk_Z].SetChunkID(ChunkID);
			//初期化
			m_ChunkCol[Chunk_X][Chunk_Z].Init();
		}
	}
}

void LoadingByChunk::InitChunkBlocks()
{
	for (int Chunk_X = 0; Chunk_X < LoadingChunks; Chunk_X++)
	{
		for (int Chunk_Z = 0; Chunk_Z < LoadingChunks; Chunk_Z++)
		{
			//IDをセット
			int ChunkID[2] = { 0 };
			ChunkID[0] += PlayerPosInGrid[0] + Chunk_X - 1;
			ChunkID[1] += PlayerPosInGrid[1] + Chunk_Z - 1;
			m_ChunkBlock[Chunk_X][Chunk_Z].SetChunkID(ChunkID);
			//初期化
			m_ChunkBlock[Chunk_X][Chunk_Z].Init();
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
	//todo めちゃくちゃ汚いコードなので後から見直し
	int Grid[2] = { 0 };
	Grid[0] -= std::floor(LoadingChunkCols / 2);
	Grid[1] -= std::floor(LoadingChunkCols / 2);

	//左下
	Grid[0] += PlayerPosInGrid[0];
	Grid[1] += PlayerPosInGrid[1];

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