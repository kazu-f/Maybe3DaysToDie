#pragma once

class SaveDataFile
{
public:
	struct  ChunkData
	{
		unsigned char ChunkID[2] = { 1 };		//���[���h�ł̃`�����N�̈ʒu(2�����̍��W)
		unsigned char TerrainID[ChunkWidth][ChunkHeight][ChunkWidth] = { 0 };		//�g�p���Ă���u���b�N�̎��
		unsigned short TerrainDurable[ChunkWidth][ChunkHeight][ChunkWidth] = { 0 };		//�u���b�N�̑ϋv�l
		ObjectType TerrainType = ObjectType::Type;
	};

	const char* SaveDataFilePath_Terrain = "SaveData/TerrainData.dat";
	ChunkData m_ChunkData[MAX_CHUNK_SIDE][MAX_CHUNK_SIDE];
};
