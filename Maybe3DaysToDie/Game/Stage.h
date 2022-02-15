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
	/// 初期化
	/// </summary>
	/// <returns>trueを返すまでループする</returns>
	bool Start();
	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	/// <summary>
	/// deleteをすると呼ばれる関数
	/// </summary>
	void OnDestroy();
	/// <summary>
	/// 地面を表示する
	/// </summary>
	void NewGround();

public:
	/// <summary>
	/// エネミージェネレーターを取得。
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
	EnemyGenerator* m_enemyGenerator = nullptr;				//エネミージェネレーター。
	nsTerrain::TerrainManager* m_Terrain = nullptr;
	prefab::CSky* m_SkyCube = nullptr;
	TerrainLoad m_Load;
	MapLoad m_Map;
	SaveDataFile* m_SaveDataFile = nullptr;
	LoadingByChunk* m_LoadingByChunk = nullptr;
};

