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
	/////�������牺�͍X�V����K�v������Ƃ�/////
	////////////////////////////////////////////
	for (int Chunk_X = 0; Chunk_X < m_config->GetLoadingChunkRange(); Chunk_X++)
	{
		for (int Chunk_Y = 0; Chunk_Y < m_config->GetLoadingChunkRange(); Chunk_Y++)
		{

		}
	}

	//�X�V�t���O������
	m_isDirty = false;
}