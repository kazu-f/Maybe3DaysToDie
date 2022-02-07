#pragma once

#include "TerrainManager/TerrainManager.h"

class LoadingByChunk;
class Player;

/// <summary>
/// 地形チャンクとブロックチャンクをまとめたチャンククラス。
/// </summary>
class NaviMeshManager : public IGameObject
{
private:
	enum VERTEX
	{
		VERTEX_BackLeft,
		VERTEX_BackRight,
		VERTEX_FrontLeft,
		VERTEX_FrontRight,
	};

private:
	LoadingByChunk* m_loadingByChunk = nullptr;				//チャンクローディング。
	nsTerrain::TerrainManager* m_terrainManager = nullptr;	//地形。

	int m_playerGrid[2] = { 0 };						//前フレームのPlayerのグリッド位置。
	
	//NVM.
	bool m_isUpdateNVM = false;							//nvmを更新する？  

public:
	virtual ~NaviMeshManager();
	bool Start() override;
	void Update() override;

private:
	/// <summary>
	/// 隣接セルを見つけ出す。
	/// <para>設置ブロックと地形ブロックの隣接セル検索になるため</para>
	/// <para>普通の隣接セル計算調査とは異なるロジックになっている。</para>
	/// </summary>
	/// <param name="cell">セル。</param>
	void SerchLinkCell(NVMGenerator::Cell* cell);
};

