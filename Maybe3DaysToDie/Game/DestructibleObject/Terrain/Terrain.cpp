#include "stdafx.h"
#include "Terrain.h"
#include "TerrainManager/TerrainChunkData.h"
#include "Tool/Tool.h"


namespace nsTerrain {
	namespace {
		const Vector3 TERRAIN_SIZE = { OBJECT_UNIT ,OBJECT_UNIT ,OBJECT_UNIT };
		const float MIN_VOXEL = 0.5f;
		const float MAX_VOXEL = 1.0f;
	}

	Terrain::Terrain()
	{
		m_params.Durable = 500;
		m_maxDurable = 500;
	}

	Terrain::~Terrain()
	{
	}

	void Terrain::Damage(const ToolInfo& tool)
	{
		int damage = tool.AttackPower;
		if (!(m_params.AptitudeTool & tool.tool))
		{
			damage /= 3;
		}
		int durable = max(0, (m_params.Durable - damage));
		if (durable != m_params.Durable)
		{
			m_params.Durable = durable;
			CalcVoxel();
		}
	}
	void Terrain::CalcVoxel()
	{
		if (m_params.Durable > 0) {
			float t = static_cast<float>(m_params.Durable) / static_cast<float>(m_maxDurable);
			t = max(0.0f, min(1.0f, t));
			m_voxel = Math::Lerp(t, MIN_VOXEL, MAX_VOXEL);
		}
		else {
			m_voxel = 0.0f;
		}

		//地形が更新された。
		m_chunkData->EnableUpdated();
	}
}
