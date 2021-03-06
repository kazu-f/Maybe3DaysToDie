#include "MiniEngine.h"
#include "PhysicsStaticObject.h"


namespace Engine {
	void CPhysicsStaticObject::Release()
	{
		m_rigidBody.Release();
	}
	void CPhysicsStaticObject::CreateCommon(const Vector3& pos, const Quaternion& rot)
	{
		//剛体を作成。
		RigidBodyInfo rbInfo;
		rbInfo.collider = m_sphere.get();
		rbInfo.mass = 0.0f;
		rbInfo.pos = pos;
		rbInfo.rot = rot;
		m_rigidBody.Create(rbInfo);
		m_rigidBody.GetBody()->setUserIndex(ColliderUserIndex::enCollisionAttr_Ground);
	}
}

