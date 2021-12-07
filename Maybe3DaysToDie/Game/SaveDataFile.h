#pragma once

class SaveDataFile
{
public:
	struct  ChunkData
	{
		unsigned char ChunkID[2] = { 1 };		//ワールドでのチャンクの位置(2次元の座標)
		unsigned char TerrainID[ChunkWidth][ChunkHeight][ChunkWidth] = { 0 };		//使用しているブロックの種類
		unsigned short TerrainDurable[ChunkWidth][ChunkHeight][ChunkWidth] = { 0 };		//ブロックの耐久値
		ObjectType TerrainType = ObjectType::Type;
	};

	const char* SaveDataFilePath_Terrain = "SaveData/TerrainData.dat";
	ChunkData m_ChunkData[MAX_CHUNK_SIDE][MAX_CHUNK_SIDE];
};
