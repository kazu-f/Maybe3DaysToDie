#include "stdafx.h"
#include "Terrain.h"
#include "TerrainManager/TerrainWorld.h"


namespace nsTerrain {
	namespace {
		const Vector3 TERRAIN_SIZE = { TERRAIN_UNIT ,TERRAIN_UNIT ,TERRAIN_UNIT };
	}

	Terrain::Terrain()
	{
	}

	Terrain::~Terrain()
	{
	}

	void Terrain::InitRayCollider()
	{
		m_StaticCol.CreateBox(m_position, Quaternion::Identity, TERRAIN_SIZE);
		m_StaticCol.GetRigidBody().GetBody()->setUserIndex(ColliderUserIndex::enCollisionAttr_RayBlock);
		m_registColider = true;
	}
	void Terrain::SetColliderEnable(bool flag)
	{
		//Šù‚É“o˜^or‰ðœÏ‚ÝB
		if (m_registColider == flag) return;

		//“o˜^A‰ðœB
		if (flag)
		{
			PhysicsWorld().AddRigidBody(m_StaticCol.GetRigidBody());
		}
		else
		{
			PhysicsWorld().RemoveRigidBody(m_StaticCol.GetRigidBody());
		}
		m_registColider = flag;
	}
	void Terrain::CalcColliderEnable()
	{
		if (m_voxel > 0.0f)
		{
			SetColliderEnable(true);
		}
		else
		{
			SetColliderEnable(false);
		}
	}
}
