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
	EnemyGenerator& GetEnemyGenerator()
	{
		return m_enemyGenerator;
	}

	nsTerrain::TerrainManager* GetTerrainWorld()
	{
		return m_Terrain;
	}

private:
	EnemyGenerator m_enemyGenerator;				//エネミージェネレーター。
	nsTerrain::TerrainManager* m_Terrain;
	prefab::CSky* m_SkyCube = nullptr;
	TerrainLoad m_Load;
};

