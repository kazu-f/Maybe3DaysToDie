#pragma once
#include "Enemy/EnemyGenerator.h"
#include "TerrainManager/TerrainManager.h"
#include "SaveDataFile.h"
#include "Save/TerrainSave/TerrainLoad.h"
#include "Save/TerrainSave/TerrainSave.h"
#include "MapLoad/MapLoad.h"
#include "SaveDataFile.h"

class NaviMeshManager;

class Stage : public IGameObject
{
public:
	Stage();
	~Stage();
private:
	/// <summary>
	/// ������
	/// </summary>
	/// <returns>true��Ԃ��܂Ń��[�v����</returns>
	bool Start();
	/// <summary>
	/// �X�V
	/// </summary>
	void Update();
	/// <summary>
	/// delete������ƌĂ΂��֐�
	/// </summary>
	void OnDestroy();
	/// <summary>
	/// �n�ʂ�\������
	/// </summary>
	void NewGround();

public:
	/// <summary>
	/// �G�l�~�[�W�F�l���[�^�[���擾�B
	/// </summary>
	/// <returns></returns>
	EnemyGenerator* GetEnemyGenerator()
	{
		return m_enemyGenerator;
	}

	nsTerrain::TerrainManager* GetTerrainWorld()
	{
		return m_Terrain;
	}

	void SetSaveDataFile(SaveDataFile* ptr)
	{
		m_SaveDataFile = ptr;
	}

	LoadingByChunk* GetLoadingByChunk()
	{
		return m_LoadingByChunk;
	}

private:
	EnemyGenerator* m_enemyGenerator = nullptr;				//�G�l�~�[�W�F�l���[�^�[�B
	nsTerrain::TerrainManager* m_Terrain = nullptr;
	prefab::CSky* m_SkyCube = nullptr;
	TerrainLoad m_Load;
	MapLoad m_Map;
	SaveDataFile* m_SaveDataFile = nullptr;
	LoadingByChunk* m_LoadingByChunk = nullptr;
};

