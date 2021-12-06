#include "stdafx.h"
#include "TerrainLoad.h"

TerrainLoad::TerrainLoad()
{

}

TerrainLoad::~TerrainLoad()
{

}

void TerrainLoad::Load()
{
	if (m_SaveDataFile == nullptr)
	{
		//�Z�[�u�f�[�^�t�@�C���N���X���Q�Ƃł��܂���ł����B
		return;
	}
	FILE* fp;
	fp = fopen(m_SaveDataFile->SaveDataFilePath_Terrain, "rb");
	if (fp == NULL)
	{
		//�Z�[�u�f�[�^������܂���
		return;
	}

	fread(m_SaveDataFile->m_ChunkData, sizeof(SaveDataFile::ChunkData), MAX_CHUNK_SIDE * MAX_CHUNK_SIDE, fp);
}