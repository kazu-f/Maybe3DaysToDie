#include "stdafx.h"
#include "Block.h"

Block::~Block()
{
}

void Block::InitRayCollider()
{
	//m_StaticCol.CreateBox(m_position, Quaternion::Identity, TERRAIN_SIZE);
	//m_StaticCol.GetRigidBody().GetBody()->setUserIndex(ColliderUserIndex::enCollisionAttr_RayBlock);
	//m_registColider = true;
	//DestructibleObject* obj = this;
	//m_StaticCol.GetRigidBody().GetBody()->setUserPointer((void*)obj);
}