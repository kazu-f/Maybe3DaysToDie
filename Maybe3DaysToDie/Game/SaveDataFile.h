#pragma once

class SaveDataFile
{
public:
	struct ObjectData {
		unsigned char ObjId = 0;		//�g�p���Ă���u���b�N�̎��
		unsigned short ObjDurable = 0;		//�u���b�N�̑ϋv�l
	};

	struct  ChunkData
	{
		ObjectData ObjData[ChunkWidth][ChunkHeight][ChunkWidth];
	};
	const char* SaveDataFilePath_Terrain = "SaveData/TerrainData.dat";
	ChunkData m_ChunkData[MAX_CHUNK_SIDE][MAX_CHUNK_SIDE];
	//�c�[�����g���Ȃ��̂ŉ��u��
	const char* ObjectFilePath[BlockKinds] = { nullptr };
};
