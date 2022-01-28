#pragma once

#include "TerrainManager/TerrainManager.h"
#include "Navigation/NVMGenerator.h"

class LoadingByChunk;

/// <summary>
/// 地形チャンクとブロックチャンクをまとめたチャンククラス。
/// </summary>
class WorldChunk : public IGameObject
{
//private:
//	//chunkData.
//	LoadingByChunk* m_LoadingByChunk = nullptr;	//PlaceMentObject側のチャンク。
//	nsTerrain::TerrainManager* m_Terrain;		//地形データー側のチャンク。
//	
//	//NVM.
//	using Cell = NVMGenerator::Cell;			//セル。
//	bool m_isNVMUpdate = true;					//NVMの更新が必要か。
//	Cell CellByChunk[][][]
//
//	Vector3 m_playerGrid = Vector3::Zero;		//Playerのグリッド位置。
};

