#pragma once
#include "Load/ChunkCollision/ChunkCollision.h"
#include "Load/ChunkBlock/ChunkBlock.h"
#include "TerrainManager/TerrainManager.h"

class ItemDataFile;

class LoadingByChunk :public IGameObject
{
private:

public:
	LoadingByChunk();
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
		int Limit = static_cast<int>(LoadingChunks / 2);
		int GridPos[2] = { 0 };
		GridPos[0] = static_cast<int>(std::floor((pos.x / OBJECT_UNIT) / ChunkWidth));// +MAX_CHUNK_SIDE / 2;
		GridPos[1] = static_cast<int>(std::floor((pos.z / OBJECT_UNIT) / ChunkWidth));// +MAX_CHUNK_SIDE / 2;
		GridPos[0] = max(min(MAX_CHUNK_SIDE - Limit, GridPos[0]), Limit);
		GridPos[1] = max(min(MAX_CHUNK_SIDE - Limit, GridPos[1]), Limit);
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
	bool IsNvmDirty(int x,int z)
	{
		return m_IsUpdatedChunk[x][z];
	}

	/// <summary>
	/// �i�r���b�V���X�V�̃t���O����
	/// </summary>
	void NvmDirtyFlagDown(int x,int z)
	{
		m_IsUpdatedChunk[x][z] = false;
	}

	/// <summary>
	/// �i�r���b�V���X�V�̃t���O�𗧂Ă�
	/// </summary>
	void NvmDirtyFlagUp(int x,int z)
	{
		m_IsUpdatedChunk[x][z] = true;
	}

	ChunkBlock* GetChunkBlock(int x, int z)
	{
		return &m_ChunkBlock[x][z];
	}
 private:
	 ItemDataFile* m_itemDatas = nullptr;
	SaveDataFile* m_SaveDataFile = nullptr;
	int PlayerPosInGrid[2] = { 0 };
	bool m_isDirty = true;		//�X�V���邩�ǂ���
	ChunkCollision m_ChunkCol[LoadingChunkCols][LoadingChunkCols];		//�`�����N���Ƃ̃u���b�N
	ChunkBlock m_ChunkBlock[LoadingChunks][LoadingChunks];
	nsTerrain::TerrainManager* m_TerrainManager = nullptr;		//�e���C���}�l�[�W���[
	std::vector<prefab::ModelRender*>BlockModel = { nullptr };		//�u���b�N�̃��f��
	bool m_IsUpdatedChunk[LoadingChunks][LoadingChunks];
};