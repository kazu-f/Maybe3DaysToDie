#pragma once
#include "SaveDataFile.h"

class MapLoad
{
public:
	MapLoad() {}
	~MapLoad() {}

	void SetChunkID(int ChunkX, int ChunkZ)
	{
		ChunkID[0] = ChunkX;
		ChunkID[1] = ChunkZ;
	}
	/// <summary>
	/// ���x���̏�����
	/// </summary>
	/// <param name="filePath">�t�@�C���p�X</param>
	void Init(const char* filePath);

	void SetSaveDataFile(SaveDataFile* ptr)
	{
		m_SaveDataFile = ptr;
	}
private:
	/// <summary>
	/// �{�[���s��̍\�z�B
	/// </summary>
	void BuildBoneMatrices();

	SaveDataFile::ObjectData& GetObjectArrange(Vector3& pos);
private:
	CTklFile m_tklFile;		//tkl�t�@�C��
	using BonePtr = std::unique_ptr<Bone>;
	std::vector<BonePtr> m_bones;		//�{�[���̔z��
	std::unique_ptr<Matrix[]> m_boneMatrixs;	//�{�[���s��
	bool m_isInited = false;			//�������ς݂��ǂ���
	SaveDataFile::ObjectData m_objData[ChunkWidth][ChunkHeight][ChunkWidth];
	struct SObjData {
		Vector3 position;
		Quaternion rotation;
		Vector3 scale;
	};
	SaveDataFile* m_SaveDataFile = nullptr;
	int ChunkID[2] = { -1 };
};