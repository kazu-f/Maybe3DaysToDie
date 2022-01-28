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
	AccessTag ObjectAccessTag[BlockKinds] = { AccessTag::NonAccess};
};

class WorldTableData {
public:
	//�u���b�N�P�ʂ̃f�[�^
	struct TableData {
		//�����ɃI�u�W�F�N�g�����邩�ǂ���
		bool OnObject = { false };
		//�אڃu���b�N�����邩�ǂ���
		bool IsAdjacentObject[4] = { false };
	};
	//�`�����N�ɂ܂Ƃ߂�����
	struct ChunkTableData {
		TableData Data[ChunkWidth][ChunkHeight][ChunkWidth];
	};
	//�S�̂̃f�[�^�͓ǂݍ���ł���͈͂̃f�[�^
	ChunkTableData m_ChunkTableData[LoadingChunks][LoadingChunks];
};