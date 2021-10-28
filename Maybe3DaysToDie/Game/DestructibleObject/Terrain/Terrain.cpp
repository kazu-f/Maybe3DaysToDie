#include "stdafx.h"
#include "Terrain.h"

namespace nsTerrain {
	static const float TERRAIN_UNIT;
	static const float TERRAIN_HALF_UNIT;

	Terrain::Terrain()
	{
	}

	Terrain::~Terrain()
	{
	}

	void Terrain::SetPosition(const Vector3& pos)
	{
		m_position = pos;
	}
}
