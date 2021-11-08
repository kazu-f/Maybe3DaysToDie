#include "stdafx.h"
#include "Terrain.h"
#include "TerrainManager/TerrainWorld.h"


namespace nsTerrain {
	namespace {
		const Vector3 TERRAIN_SIZE = { TERRAIN_UNIT ,TERRAIN_UNIT ,TERRAIN_UNIT };
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
	void Terrain::CalcVoxel()
	{
		if (m_params.Durable > 0) {
			float t = static_cast<float>(m_params.Durable / m_maxDurable);
			t = max(0.0f, min(1.0f, t));
			m_voxel = Math::Lerp(t, MIN_VOXEL, MAX_VOXEL);
		}
		else {
			m_voxel = 0.0f;
		}
		//’nŒ`‚ªXV‚³‚ê‚½B
		m_world->EnableUpdated();
	}
}
