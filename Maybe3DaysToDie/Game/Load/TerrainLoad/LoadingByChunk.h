#pragma once
#include "Load/ChunkCollision/ChunkCollision.h"
#include "Load/ChunkBlock/ChunkBlock.h"
#include "TerrainManager/TerrainManager.h"

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
	/// ���[���h�f�[�^�̃|�C���^���Z�b�g
	/// </summary>
	/// <param name="ptr">���[���h�e�[�u���f�[�^</param>
	void SetWorldTableData(WorldTableData* ptr)
	{
		m_WorldTableData = ptr;
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
	/// ���[���h�e�[�u���f�[�^�̍X�V
	/// </summary>
	void UpdateWorldTableData();

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

	/// <summary>
	/// �i�r���b�V�����X�V���邩�ǂ���
	/// </summary>
	bool IsNvmDirty()
	{
		return m_IsUpdated;
	}

	/// <summary>
	/// �i�r���b�V���X�V�̃t���O����
	/// </summary>
	void NvmDirtyFlagDown()
	{
		m_IsUpdated = false;
	}

	/// <summary>
	/// �i�r���b�V���X�V�̃t���O�𗧂Ă�
	/// </summary>
	void NvmDirtyFlagUp()
	{
		m_IsUpdated = true;
	}

 private:
	SaveDataFile* m_SaveDataFile = nullptr;
	WorldTableData* m_WorldTableData = nullptr;
	int PlayerPosInGrid[2] = { 0 };
	bool m_isDirty = true;		//�X�V���邩�ǂ���
	ChunkCollision m_ChunkCol[LoadingChunkCols][LoadingChunkCols];		//�`�����N���Ƃ̃u���b�N
	ChunkBlock m_ChunkBlock[LoadingChunks][LoadingChunks];
	nsTerrain::TerrainManager* m_TerrainManager = nullptr;		//�e���C���}�l�[�W���[
	std::vector<prefab::ModelRender*>BlockModel = { nullptr };		//�u���b�N�̃��f��
	bool m_IsUpdated = false;
};