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
	/// レベルの初期化
	/// </summary>
	/// <param name="filePath">ファイルパス</param>
	void Init(const char* filePath);

	void SetSaveDataFile(SaveDataFile* ptr)
	{
		m_SaveDataFile = ptr;
	}
private:
	/// <summary>
	/// ボーン行列の構築。
	/// </summary>
	void BuildBoneMatrices();

	SaveDataFile::ObjectData& GetObjectArrange(Vector3& pos);
private:
	CTklFile m_tklFile;		//tklファイル
	using BonePtr = std::unique_ptr<Bone>;
	std::vector<BonePtr> m_bones;		//ボーンの配列
	std::unique_ptr<Matrix[]> m_boneMatrixs;	//ボーン行列
	bool m_isInited = false;			//初期化済みかどうか
	SaveDataFile::ObjectData m_objData[ChunkWidth][ChunkHeight][ChunkWidth];
	struct SObjData {
		Vector3 position;
		Quaternion rotation;
		Vector3 scale;
	};
	SaveDataFile* m_SaveDataFile = nullptr;
	int ChunkID[2] = { -1 };
};