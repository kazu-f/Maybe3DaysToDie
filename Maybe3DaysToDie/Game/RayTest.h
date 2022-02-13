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

struct IKRayResult :public btCollisionWorld::RayResultCallback
{
	bool isHit = false;		//�Փ˃t���O
	Vector3 hitColPos = Vector3::Zero;
	//�Փ˂����Ƃ��ɌĂ΂��֐�
	virtual btScalar addSingleResult(
		btCollisionWorld::LocalRayResult& convexResult,
		bool /*normalInWorldSpace*/
	)
	{
		if (convexResult.m_collisionObject->getUserIndex() & ColliderUserIndex::enCollisionAttr_RayBlock)
		{
			btVector3 hitpos = convexResult.m_collisionObject->getWorldTransform().getOrigin();
			isHit = true;
			hitColPos.Set(hitpos);
			//�������߂��ق��ɍX�V
			if (m_closestHitFraction > convexResult.m_hitFraction)
			{
				m_closestHitFraction = convexResult.m_hitFraction;
			}
			return m_closestHitFraction;
		}
		return 0.0f;
	}
};
//�Փ˂����Ƃ��ɌĂ΂��֐��I�u�W�F�N�g(�n�ʗp)
struct SweepResultGround : public btCollisionWorld::ConvexResultCallback
{
	bool isHit = false;									//�Փ˃t���O�B
	Vector3 hitPos = Vector3(0.0f, -FLT_MAX, 0.0f);	//�Փ˓_�B
	Vector3 startPos = Vector3::Zero;					//���C�̎n�_�B
	float dist = FLT_MAX;								//�Փ˓_�܂ł̋����B��ԋ߂��Փ˓_�����߂邽�߁BFLT_MAX�͒P���x�̕��������_����肤��ő�̒l�B

														//�Փ˂����Ƃ��ɌĂ΂��R�[���o�b�N�֐��B
	virtual	btScalar addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace)
	{
		if (convexResult.m_hitCollisionObject->getUserIndex() & ColliderUserIndex::enCollisionAttr_RayBlock)
		{
			//�Փ˂��Ă���B
			isHit = true;
			Vector3 hitPosTmp = *(Vector3*)&convexResult.m_hitPointLocal;
			//�Փ˓_�̋��������߂�B�B
			Vector3 vDist;
			vDist.Subtract(hitPosTmp, startPos);
			float distTmp = vDist.Length();
			if (dist > distTmp) {
				//���̏Փ˓_�̕����߂��̂ŁA�ŋߖT�̏Փ˓_���X�V����B
				hitPos = hitPosTmp;
				dist = distTmp;
			}
		}
		return 0.0f;
	}
};

struct CharactorRayResult :public btCollisionWorld::RayResultCallback
{
	bool isHit = false;		//�Փ˃t���O
	Vector3 hitColPos = Vector3::Zero;
	const btCollisionObject* ColObj = nullptr;
	void* ExclusionPointer = nullptr;	//���O�������|�C���^
	//�Փ˂����Ƃ��ɌĂ΂��֐�
	virtual btScalar addSingleResult(
		btCollisionWorld::LocalRayResult& convexResult,
		bool /*normalInWorldSpace*/
	)
	{
		if (convexResult.m_collisionObject->getUserIndex() & ColliderUserIndex::enCollisionAttr_Character)
		{
			if (ExclusionPointer == convexResult.m_collisionObject->getUserPointer()) {
				return 0.0f;
			}
			btVector3 hitpos = convexResult.m_collisionObject->getWorldTransform().getOrigin();
			isHit = true;
			hitColPos.Set(hitpos);
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