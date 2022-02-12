#pragma once
#include "Enemy/EnemyGenerator.h"
#include "TerrainManager/TerrainManager.h"
#include "SaveDataFile.h"
#include "Save/TerrainSave/TerrainLoad.h"

class NaviMeshManager;

class Stage : public IGameObject
{
public:
	Stage();
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
	EnemyGenerator& GetEnemyGenerator()
	{
		return m_enemyGenerator;
	}

	nsTerrain::TerrainManager* GetTerrainWorld()
	{
		return m_Terrain;
	}

private:
	EnemyGenerator m_enemyGenerator;				//�G�l�~�[�W�F�l���[�^�[�B
	nsTerrain::TerrainManager* m_Terrain;
	prefab::CSky* m_SkyCube = nullptr;
	TerrainLoad m_Load;
};

