#pragma once
#include "DestructibleObject/Block/Block.h"
#include "SaveDataFile.h"

static const int BlockKinds = 1;		//�u���b�N�̎��
static const int MaxInstanceNum = ChunkWidth * ChunkWidth * ChunkHeight;

class ChunkBlock
{
public:
	ChunkBlock() 
	{		
		//�T�C�Y�̍ő�l�Z�b�g
		BlockModel.resize(BlockKinds);
	}
	~ChunkBlock() 
	{
		OnDestroy();
	}

	void OnDestroy();
	void Init();

	void SetChunkID(int ChunkID[2])
	{
		for (int i = 0; i < 2; i++)
		{
			if (m_ChunkID[i] != ChunkID[i])
			{
				m_ChunkID[i] = ChunkID[i];
				IsMove = true;
			}
		}
	}

	void GetChunkID(int id[2])
	{
		id[0] = m_ChunkID[0];
		id[1] = m_ChunkID[1];
	}

	/// <summary>
	/// �u���b�N�̈ʒu���`�����N�ɍ��킹�Ĉړ�����
	/// </summary>
	void MoveChunk();

	/// <summary>
	/// �Z�[�u�f�[�^�t�@�C�����Z�b�g
	/// </summary>
	/// <param name="file">�Z�[�u�f�[�^�t�@�C��</param>
	void SetSaveDataFile(SaveDataFile* file)
	{
		m_SaveDataFile = file;
	}

	/// <summary>
	/// ���f���̒ǉ�
	/// </summary>
	void AddModel(ObjectParams& params, Vector3& pos, Quaternion& rot, Vector3& scale);

	/// <summary>
	/// ���f���̍폜
	/// </summary>
	void RemoveBlock(Block* blockptr);

	Block& GetBlock(Vector3 pos);

	bool IsBlockDirty()
	{
		return ChunkBlockDirty;
	}

	void ResetBlockDirty()
	{
		ChunkBlockDirty = false;
	}
public:
	Block m_Block[ChunkWidth][ChunkHeight][ChunkWidth];		//�u���b�N
private:
	int m_ChunkID[2] = { 0 };
	SaveDataFile* m_SaveDataFile = nullptr;
	bool IsMove = false;
	//todo ChunkBlock�Ń��f���\���ł���悤��BlockManager���烂�f�����폜����
	std::vector<prefab::ModelRender*>BlockModel = { nullptr };		//�u���b�N�̃��f��
	int m_modelNum = 0;
	bool ChunkBlockDirty = true;
};

