#pragma once
#include "Load/ChunkCollision/ChunkCollision.h"
#include "Load/ChunkBlock/ChunkBlock.h"
#include "TerrainManager/TerrainManager.h"
#include "GameConfig/WorldConfig/WorldConfig.h"

class SaveDataFile;
class WorldConfig;
class LoadingByChunk :public IGameObject
{
private:

public:
	LoadingByChunk()
	{
		//�T�C�Y�̍ő�l�Z�b�g
		BlockModel.resize(BlockKinds);
	}
	~LoadingByChunk();


	void OnDestroy();

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

	void SetTerrainManager(nsTerrain::TerrainManager* manager)
	{
		m_TerrainManager = manager;
	}

	/// <summary>
	/// �v���C���[�̃|�W�V�������Z�b�g���ēǂݍ��ރ`�����N���w��
	/// </summary>
	/// <param name="pos">�v���C���[�̃|�W�V����</param>
	void SetPlayerPos(const Vector3& pos)
	{
		int GridPos[2] = { 0 };
		GridPos[0] = static_cast<int>(std::floor((pos.x / OBJECT_UNIT) / ChunkWidth));// +MAX_CHUNK_SIDE / 2;
		GridPos[1] = static_cast<int>(std::floor((pos.z / OBJECT_UNIT) / ChunkWidth));// +MAX_CHUNK_SIDE / 2;
		GridPos[0] = max(min(MAX_CHUNK_SIDE - 1, GridPos[0]), 1);
		GridPos[1] = max(min(MAX_CHUNK_SIDE - 1, GridPos[1]), 1);
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

	/// <summary>
	/// �R���C�_�[�̏�����
	/// </summary>
	void InitChunkCols();

	/// <summary>
	/// �u���b�N�̏�����
	/// </summary>
	void InitChunkBlocks();

	/// <summary>
	/// ���f���̏�����
	/// </summary>
	void InitModels();

	void Update();

	/// <summary>
	/// �`�����N���ړ������Ƃ��̍X�V
	/// </summary>
	void UpdateMoveChunk();

	/// <summary>
	/// �R���C�_�[�̍X�V
	/// </summary>
	void UpdateChunkCols();

	/// <summary>
	/// �u���b�N�̍X�V
	/// </summary>
	void UpdateChunkBlocksAndTerrains();

	/// <summary>
	/// �e���C���̍X�V
	/// </summary>
	void UpdateTerains();

	/// <summary>
	/// �`�����N�u���b�N���`�����N�R���C�_�[�ƕR�Â�����
	/// </summary>
	void LinkChunk();

	/// <summary>
	/// �|�W�V��������Ή�����`�����N�u���b�N���擾
	/// </summary>
	ChunkBlock& GetChunkBlocks(int ID[2]);

	/// <summary>
	/// ���f���̍X�V
	/// </summary>
	void UpdateModels();

 private:
	WorldConfig* m_config = nullptr;
	SaveDataFile* m_SaveDataFile = nullptr;
	int PlayerPosInGrid[2] = { 0 };
	bool m_isDirty = true;		//�X�V���邩�ǂ���
	ChunkCollision m_ChunkCol[LoadingChunkCols][LoadingChunkCols];		//�`�����N���Ƃ̃u���b�N
	ChunkBlock m_ChunkBlock[LoadingChunks][LoadingChunks];
	nsTerrain::TerrainManager* m_TerrainManager = nullptr;		//�e���C���}�l�[�W���[
	std::vector<prefab::ModelRender*>BlockModel = { nullptr };		//�u���b�N�̃��f��
};