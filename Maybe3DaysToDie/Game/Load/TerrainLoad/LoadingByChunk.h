#pragma once
#include "Block/ChunkBlock/ChunkBlock.h"

class SaveDataFile;
class WorldConfig;
class LoadingByChunk :public IGameObject
{
private:

public:
	LoadingByChunk();
	~LoadingByChunk();

	/// <summary>
	/// �Z�[�u�f�[�^�t�@�C�����Z�b�g
	/// </summary>
	/// <param name="file">�Z�[�u�f�[�^�t�@�C��</param>
	void SetSaveDataFile(SaveDataFile* file)
	{
		m_SaveDataFile = file;
	}

	/// <summary>
	/// ���[���h�ݒ���Z�b�g
	/// </summary>
	/// <param name="config">���[���h�ݒ�</param>
	void SetWorldConfig(WorldConfig* config)
	{
		m_config = config;
	}

	/// <summary>
	/// �v���C���[�̃|�W�V�������Z�b�g���ēǂݍ��ރ`�����N���w��
	/// </summary>
	/// <param name="pos">�v���C���[�̃|�W�V����</param>
	void SetPlayerPos(const Vector3& pos)
	{
		int GridPos[2] = { 0 };
		GridPos[0] = static_cast<int>(std::floor(pos.x / OBJECT_UNIT)) + MAX_CHUNK_SIDE / 2;
		GridPos[1] = static_cast<int>(std::floor(pos.z / OBJECT_UNIT)) + MAX_CHUNK_SIDE / 2;
		for (int i = 0; i < 2; i++)
		{
			if (PlayerPosInGrid[i] != GridPos[i])
			{
				PlayerPosInGrid[i] = GridPos[i];
				m_isDirty = true;
			}
		}
	}

	bool Start();

	void Update();
private:
	WorldConfig* m_config = nullptr;
	SaveDataFile* m_SaveDataFile = nullptr;
	int PlayerPosInGrid[2] = { 0 };
	bool m_isDirty = false;		//�X�V���邩�ǂ���
	ChunkBlock m_ChunkBlock[16][16];		//�`�����N���Ƃ̃u���b�N
};