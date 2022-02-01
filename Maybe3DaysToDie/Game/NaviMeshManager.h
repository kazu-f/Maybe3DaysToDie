#pragma once

#include "TerrainManager/TerrainManager.h"
#include "Navigation/NVMGenerator.h"

class LoadingByChunk;
class Player;

/// <summary>
/// 地形チャンクとブロックチャンクをまとめたチャンククラス。
/// </summary>
class NaviMeshManager : public IGameObject
{
private:
	//pl情報。
	Player* m_playerPtr = nullptr;							//プレイヤー。
	LoadingByChunk* m_loadingByChunk = nullptr;				//チャンクローディング。
	nsTerrain::TerrainManager* m_terrainManager = nullptr;	//地形。

	int m_playerGrid[2] = { 0 };						//前フレームのPlayerのグリッド位置。
	
	//NVM.
	bool m_isUpdateNVM = false;							//nvmを更新する？

public:
	virtual ~NaviMeshManager();
	bool Start() override;
	void Update() override;

	void SetLoadingByChunk(LoadingByChunk* loadingByChunk)
	{
		m_loadingByChunk = loadingByChunk;
	}

private:
	void CalcPlayerGrid();
};

