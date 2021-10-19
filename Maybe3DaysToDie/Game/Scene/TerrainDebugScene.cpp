#include "stdafx.h"
#include "TerrainDebugScene.h"
#include "DestructibleObject/Terrain/Terrain.h"
#include "terrainManager/TerrainManager.h"


bool TerrainDebugScene::Start()
{
	//instance作成。
	nsTerrain::TerrainManager::CreateInstance();
	//instance取得。
	auto* manager = nsTerrain::TerrainManager::GetInstance();

	//一つ作成。
	auto* a = manager->CreateTerrain({ 0.0f,0.0f,0.0f });

	auto* b = manager->CreateTerrain({ 100.0f,0.0f,0.0f });

	a->SetRelatedTerrain(b, nsTerrain::en_terrainOnRight);
	b->SetRelatedTerrain(a, nsTerrain::en_terrainOnLeft);

	return true;
}

void TerrainDebugScene::Update()
{
}

