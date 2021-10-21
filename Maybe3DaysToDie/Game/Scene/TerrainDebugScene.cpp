#include "stdafx.h"
#include "TerrainDebugScene.h"
#include "DestructibleObject/Terrain/Terrain.h"
#include "terrainManager/TerrainManager.h"
#include "terrainManager/TerrainWorld.h"


bool TerrainDebugScene::Start()
{
	////instance�쐬�B
	//nsTerrain::TerrainManager::CreateInstance();
	////instance�擾�B
	//auto* manager = nsTerrain::TerrainManager::GetInstance();

	////��쐬�B
	//auto* a = manager->CreateTerrain({ 0.0f,0.0f,0.0f });

	//auto* b = manager->CreateTerrain({ 100.0f,0.0f,0.0f });

	//a->SetRelatedTerrain(b, nsTerrain::en_terrainOnRight);
	//b->SetRelatedTerrain(a, nsTerrain::en_terrainOnLeft);

	NewGO<nsTerrain::TerrainWorld>(0,"world");

	return true;
}

void TerrainDebugScene::Update()
{
}

