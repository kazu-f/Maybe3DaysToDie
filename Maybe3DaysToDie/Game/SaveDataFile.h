#pragma once

class SaveDataFile
{
public:
	struct  ChunkData
	{
		unsigned char ChunkID[2] = { 0 };		//ワールドでのチャンクの位置(2次元の座標)
		unsigned char ObjId[ChunkWidth][ChunkHeight][ChunkWidth] = { 0 };		//使用しているブロックの種類
		unsigned short ObjDurable[ChunkWidth][ChunkHeight][ChunkWidth] = { 0 };		//ブロックの耐久値
		ObjectType TerrainType = ObjectType::Type;
	};

	const char* SaveDataFilePath_Terrain = "SaveData/TerrainData.dat";
	ChunkData m_ChunkData[MAX_CHUNK_SIDE][MAX_CHUNK_SIDE];
};
