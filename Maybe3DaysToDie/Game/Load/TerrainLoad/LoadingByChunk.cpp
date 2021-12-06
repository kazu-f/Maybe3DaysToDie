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
	return true;
}

void LoadingByChunk::Update()
{
	//ロードするチャンクの一辺の大きさ
	int LoadingRange = static_cast<int>(m_LoadingRange);
	LoadingRange *= 2;
	LoadingRange + 1;

	for (int Chunk_X = 0; Chunk_X < LoadingRange; Chunk_X++)
	{
		for (int Chunk_Y = 0; Chunk_Y < LoadingRange; Chunk_Y++)
		{

		}
	}
}