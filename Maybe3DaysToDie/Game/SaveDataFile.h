#pragma once

class SaveDataFile
{
public:
	struct ObjectData {
		unsigned char ObjId = -1;		//使用しているブロックの種類
		unsigned short ObjDurable = 0;		//ブロックの耐久値
		Quaternion Rotate = Quaternion::Identity;
	};

	struct  ChunkData
	{
		ObjectData ObjData[ChunkWidth][ChunkHeight][ChunkWidth];
	};
	const char* SaveDataFilePath_Terrain = "SaveData/TerrainData.dat";
	ChunkData m_ChunkData[MAX_CHUNK_SIDE][MAX_CHUNK_SIDE];
};