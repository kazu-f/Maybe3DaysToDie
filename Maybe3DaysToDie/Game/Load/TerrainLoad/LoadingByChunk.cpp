#include "stdafx.h"
#include "LoadingByChunk.h"
#include "GameConfig/WorldConfig/WorldConfig.h"

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
	if (m_isDirty == false)
	{
		return;
	}

	////////////////////////////////////////////
	/////ここから下は更新する必要があるとき/////
	////////////////////////////////////////////
	for (int Chunk_X = 0; Chunk_X < m_config->GetLoadingChunkRange(); Chunk_X++)
	{
		for (int Chunk_Y = 0; Chunk_Y < m_config->GetLoadingChunkRange(); Chunk_Y++)
		{

		}
	}

	//更新フラグを下す
	m_isDirty = false;
}