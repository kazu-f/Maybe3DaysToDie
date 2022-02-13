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
	std::vector<NVMGenerator::Cell> m_edgeCellList[LoadingChunkCols][LoadingChunkCols];


	int m_playerGrid[2] = { 0 };						//前フレームのPlayerのグリッド位置。
	
	//NVM.
	bool m_isUpdateNVM = false;							//nvmを更新する？  

	static std::map<int, Vector2> m_indexToDirection;

public:
	virtual ~NaviMeshManager();
	bool Start() override;
	void Update() override;

public:
	/// <summary>
	/// 端セルを追加。
	/// </summary>
	/// <param name="cell">セル。</param>
	void AddEdgeCellList(NVMGenerator::Cell& cell, int x, int y)
	{
		m_edgeCellList[x][y].push_back(cell);
	}

	std::vector<NVMGenerator::Cell>& GetEdgeCellList(int x, int y)
	{
		return m_edgeCellList[x][y];
	}

private:
	/// <summary>
	/// 隣接セルを見つけ出す。
	/// <para>設置ブロックと地形ブロックの隣接セル検索になるため</para>
	/// <para>普通の隣接セル計算調査とは異なるロジックになっている。</para>
	/// </summary>
	/// <param name="cell">セル。</param>
	void SerchLinkCell(NVMGenerator::Cell* cell);
};

