#pragma once
#include "TerrainManager/TerrainWorld.h"

class TerrainSave
{
private:
	struct  ChunkData
	{
		unsigned char ChunkID[2] = { 0 };		//ワールドでのチャンクの位置(2次元の座標)
		unsigned char TerrainID[ChunkWidth][ChunkHeight][ChunkWidth] = { 0 };		//使用しているブロックの種類
		unsigned short TerrainDurable[ChunkWidth][ChunkHeight][ChunkWidth] = { 0 };		//ブロックの耐久値
		ObjectType TerrainType = ObjectType::Type;
		//void Reset()
		//{
		//	for (int i = 0; i < 2; i++)
		//	{
		//		ChunkID[i] = 0;
		//	}
		//	for (int x = 0; x < ChunkWidth; x++)
		//	{
		//		for (int y = 0; y < ChunkWidth; y++)0
		//		{
		//			for (int z = 0; z < ChunkWidth; z++)
		//			{
		//				TerrainID[x][y][z] = 0;
		//				TerrainDurable[x][y][z] = 0;
		//			}
		//		}
		//	}
		//}
	};
public:
	TerrainSave() {}
	~TerrainSave() {}

	void Save();
	void Load();
	void SetTerrainWorld(nsTerrain::TerrainWorld*terrain)
	{
		m_TerrainWorld = terrain;
	}
private:
	ChunkData m_ChunkData[MAX_CHUNK_SIDE][MAX_CHUNK_SIDE];
	nsTerrain::TerrainWorld* m_TerrainWorld = nullptr;
};