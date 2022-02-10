#pragma once
#include "DestructibleObject/Block/Block.h"
#include "SaveDataFile.h"

static const int MaxInstanceNum = ChunkWidth * ChunkWidth * ChunkHeight;
struct InstancingData {
	Vector3 pos = Vector3::Zero;
	Quaternion rot = Quaternion::Identity;
	Vector3 scale = Vector3::One;
};

class LoadingByChunk;
class ChunkBlock
{
public:
	ChunkBlock() 
	{		
		//�T�C�Y�̍ő�l�Z�b�g
		//BlockModel.resize(BlockKinds);
	}
	~ChunkBlock() 
	{
	}

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

	Block* GetBlock(Vector3 pos);

	bool IsBlockDirty()
	{
		return ChunkBlockDirty;
	}

	void ResetBlockDirty()
	{
		ChunkBlockDirty = false;
	}

	bool IsModelUpdated()
	{
		return m_IsModelUpdated;
	}

	void ResetModelUpdated()
	{
		m_IsModelUpdated = false;
	}
	/// <summary>
	/// ���̃`�����N�ɂ��郂�f���̃C���X�^���V���O�f�[�^���擾
	/// </summary>
	/// <param name="BlockID">�u���b�NID</param>
	/// <returns>�C���X�^���V���O�f�[�^</returns>
	std::vector<InstancingData>& GetInstancingData(int BlockID)
	{
		return m_InstancingData[BlockID];
	}

	/// <summary>
	/// LoadingByChunk�̃|�C���^���Z�b�g
	/// </summary>
	void SetLoadingByChunk(LoadingByChunk* ptr)
	{
		m_LoadingByChunk = ptr;
	}

	/// <summary>
	/// ���[�h���Ă���`�����N�ɑΉ������邽��ID��������
	/// </summary>
	void SetLoadChunkID(int x, int z)
	{
		m_LoadID[0] = x;
		m_LoadID[1] = z;
	}
public:
	Block m_Block[ChunkWidth][ChunkHeight][ChunkWidth];		//�u���b�N
private:
	int m_ChunkID[2] = { 0 };
	SaveDataFile* m_SaveDataFile = nullptr;
	bool IsMove = false;
	bool ChunkBlockDirty = true;
	//�C���X�^���V���O�f�[�^
	std::vector<InstancingData> m_InstancingData[BlockKinds];
	bool m_IsModelUpdated = false;
	LoadingByChunk* m_LoadingByChunk = nullptr;
	int m_LoadID[2] = { 0 };

};