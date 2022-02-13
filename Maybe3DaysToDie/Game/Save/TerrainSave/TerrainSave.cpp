#include "stdafx.h"
#include "TerrainSave.h"
#include <direct.h>

void TerrainSave::Save()
{
	if (m_SaveDataFile == nullptr)
	{
		//�Z�[�u�f�[�^�t�@�C���N���X���Q�Ƃł��܂���ł����B
		return;
	}
	FILE* fp;
	fp = fopen(m_SaveDataFile->SaveDataFilePath_Terrain, "wb");
	if (fp == NULL)
	{
		if (_mkdir("SaveData") != 0)
		{
			//�f�B���N�g�����쐬�ł��Ȃ�����
			return;
		}
		fp = fopen(m_SaveDataFile->SaveDataFilePath_Terrain, "wb");
	}

	fwrite(m_SaveDataFile->m_ChunkData, sizeof(SaveDataFile::ChunkData), MAX_CHUNK_SIDE * MAX_CHUNK_SIDE, fp);
	fclose(fp);
}