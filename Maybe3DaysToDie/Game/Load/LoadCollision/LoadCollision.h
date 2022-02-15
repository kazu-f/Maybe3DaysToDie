#pragma once
#include "TerrainManager/TerrainWorld.h"
#include "SaveDataFile.h"

class ChunkBlock;
class LoadCollision
{
public:
	LoadCollision() {}
	~LoadCollision() {}

	/// <summary>
	/// ������
	/// </summary>
	void Init();
	/// <summary>
	/// �`�����N�u���b�N�ƃ����N������
	/// </summary>
	/// <param name="ptr">�|�C���^</param>
	/// <param name="ChunkX">�v���C���[�𒆐S�Ƃ���3*3�̃`�����N��X</param>
	/// <param name="ChunkZ">�v���C���[�𒆐S�Ƃ���3*3�̃`�����N��Z</param>
	void LinkChunk(ChunkBlock* ptr, int ChunkX, int ChunkZ)
	{
		m_ChunkBlocks[ChunkX][ChunkZ] = ptr;
	}

	/// <summary>
	/// �e���C���`�����N�f�[�^�ƃ����N������
	/// </summary>
	/// <param name="ptr">�|�C���^</param>
	/// <param name="ChunkX">�v���C���[�𒆐S�Ƃ���3*3�̃`�����N��X</param>
	/// <param name="ChunkZ">�v���C���[�𒆐S�Ƃ���3*3�̃`�����N��Z</param>
	void LinkTerrainWorld(nsTerrain::TerrainChunkData* ptr,int ChunkX,int ChunkZ)
	{
		m_TerrainData[ChunkX][ChunkZ] = ptr;
	}

	/// <summary>
	/// �v���C���[�̈ʒu���Z�b�g
	/// </summary>
	/// <param name="pos">�v���C���[�̈ʒu</param>
	void SetPlayerPos(const Vector3& pos)
	{
		m_PlayerPos = pos;
	}

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �Z�[�u�f�[�^�t�@�C�����Z�b�g
	/// </summary>
	void SetSaveDataFile(SaveDataFile* ptr)
	{
		m_SaveDataFile = ptr;
	}

private:
	/// <summary>
	/// �R���C�_�[���쐬
	/// </summary>
	void NewCol();

	/// <summary>
	/// �R���C�_�[���u���b�N�p�ɍX�V
	/// </summary>
	void UpdateColForBlock();

private:
	static const int Cols = PlayerRange * 2 + 1;
	const Vector3 BLOCK_SIZE = { OBJECT_UNIT ,OBJECT_UNIT ,OBJECT_UNIT };
	CPhysicsStaticObject m_StaticCol[Cols][Cols][Cols];		//�T�C�Y�̓v���C���[�̃|�W�V����������̂�2�{+1
	ChunkBlock* m_ChunkBlocks[LoadingChunkCols][LoadingChunkCols] = { nullptr };		//�v���C���[�𒆐S��3*3�̃`�����N���K�v(�ړ��ɂ���ă`�����N�܂����\��������̂�)
	nsTerrain::TerrainChunkData* m_TerrainData[LoadingChunkCols][LoadingChunkCols] = { nullptr };
	Vector3 m_PlayerPos = Vector3::Zero;
	Vector3Int m_PosInChunk = { 0,0,0 };
	SaveDataFile* m_SaveDataFile = nullptr;
};