#include "stdafx.h"
#include "PhysicsGhostobject.h"

namespace Engine {
	void CPhysicsGhostObject::Release()
	{
		//�R���W�����̓o�^�������B
		if (m_isRegistPhysicsWorld == true) {
			PhysicsWorld().RemoveCollisionObject(m_ghostObject);
			m_isRegistPhysicsWorld = false;
		}
	}
	void CPhysicsGhostObject::CreateCommon(const Vector3& pos, const Quaternion& rot)
	{
		m_ghostObject.setCollisionShape(m_sphere->GetBody());
		btTransform btTrans;
		btTrans.setOrigin({ pos.x,pos.y,pos.z });
		btTrans.setRotation({ rot.x,rot.y,rot.z,rot.w });
		m_ghostObject.setWorldTransform(btTrans);

		//�����G���W���ɓo�^�B
		PhysicsWorld().AddCollisionObject(m_ghostObject);
		m_isRegistPhysicsWorld = true;
	}
}