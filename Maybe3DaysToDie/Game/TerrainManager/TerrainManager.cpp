#include "stdafx.h"
#include "TerrainManager.h"
#include "DestructibleObject/Terrain/Terrain.h"

namespace nsTerrain {
	Terrain* TerrainManager::CreateTerrain(const Vector3& pos)
	{
		//作成。
		auto ptr = std::make_unique<Terrain>();
		//座標設定。
		ptr->SetPosition(pos);
		//頂点構築。
		ptr->BuildVertex();

		//登録。
		m_terrainPtrs.push_back(std::move(ptr));

		if (m_terrainPtrs.size() > MAX_TERRAIN_NUM)
		{
			ENGINE_ASSERT(false, "地形ブロックの数が最大値を越えた。");
			return nullptr;
		}

		return m_terrainPtrs.back().get();
	}
	void TerrainManager::Update()
	{

	}
	void TerrainManager::PostUpdate()
	{
		m_terrainPtrs


	}
}