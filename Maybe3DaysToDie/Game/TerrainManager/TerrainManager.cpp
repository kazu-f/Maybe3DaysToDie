#include "stdafx.h"
#include "TerrainManager.h"
#include "DestructibleObject/Terrain/Terrain.h"

namespace nsTerrain {
	Terrain* TerrainManager::CreateTerrain(const Vector3& pos)
	{
		//�쐬�B
		auto ptr = std::make_unique<Terrain>();
		//���W�ݒ�B
		ptr->SetPosition(pos);
		//���_�\�z�B
		ptr->BuildVertex();

		//�o�^�B
		m_terrainPtrs.push_back(std::move(ptr));

		if (m_terrainPtrs.size() > MAX_TERRAIN_NUM)
		{
			ENGINE_ASSERT(false, "�n�`�u���b�N�̐����ő�l���z�����B");
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