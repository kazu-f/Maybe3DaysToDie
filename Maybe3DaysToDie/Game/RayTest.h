#pragma once

struct RayResult :public btCollisionWorld::RayResultCallback
{
	bool isHit = false;		//�Փ˃t���O
	Vector3 hitNormal = Vector3::Zero;
	Vector3 hitColPos = Vector3::Zero;
	const btCollisionObject* ColObj = nullptr;
	//�Փ˂����Ƃ��ɌĂ΂��֐�
	virtual btScalar addSingleResult(
		btCollisionWorld::LocalRayResult& convexResult,
		bool /*normalInWorldSpace*/
	)
	{
		if (convexResult.m_collisionObject->getUserIndex() & ColliderUserIndex::enCollisionAttr_RayBlock)
		{
			btVector3 colPos = convexResult.m_collisionObject->getWorldTransform().getOrigin();
			isHit = true;
			hitNormal.Set(convexResult.m_hitNormalLocal);
			hitColPos.Set(colPos);
			//�������߂��ق��ɍX�V
			if (m_closestHitFraction > convexResult.m_hitFraction)
			{
				m_closestHitFraction = convexResult.m_hitFraction;
			}
			ColObj = convexResult.m_collisionObject;
			return m_closestHitFraction;
		}
		return 0.0f;
	}
};