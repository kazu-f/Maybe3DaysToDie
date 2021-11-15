#pragma once
#include "TerrainManager/TerrainWorld.h"

class TerrainSave
{
private:
	struct  ChunkData
	{
		unsigned char ChunkID[2] = { 0 };		//���[���h�ł̃`�����N�̈ʒu(2�����̍��W)
		unsigned char TerrainID[ChunkWidth][ChunkHeight][ChunkWidth] = { 0 };		//�g�p���Ă���u���b�N�̎��
		unsigned short TerrainDurable[ChunkWidth][ChunkHeight][ChunkWidth] = { 0 };		//�u���b�N�̑ϋv�l
	};
public:
	TerrainSave() {}
	~TerrainSave() {}

	void Save();

	void SetTerrainWorld(nsTerrain::TerrainWorld*terrain)
	{
		m_TerrainWorld = terrain;
	}
private:
	ChunkData m_ChunkData[MAX_CHUNK_SIDE][MAX_CHUNK_SIDE];
	nsTerrain::TerrainWorld* m_TerrainWorld = nullptr;
};