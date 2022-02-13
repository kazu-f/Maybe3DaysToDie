#pragma once

struct RayResult :public btCollisionWorld::RayResultCallback
{
	bool isHit = false;		//衝突フラグ
	Vector3 hitNormal = Vector3::Zero;
	Vector3 hitColPos = Vector3::Zero;
	const btCollisionObject* ColObj = nullptr;
	//衝突したときに呼ばれる関数
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
			//距離が近いほうに更新
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
	bool isHit = false;		//衝突フラグ
	Vector3 hitColPos = Vector3::Zero;
	//衝突したときに呼ばれる関数
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
			//距離が近いほうに更新
			if (m_closestHitFraction > convexResult.m_hitFraction)
			{
				m_closestHitFraction = convexResult.m_hitFraction;
			}
			return m_closestHitFraction;
		}
		return 0.0f;
	}
};
//衝突したときに呼ばれる関数オブジェクト(地面用)
struct SweepResultGround : public btCollisionWorld::ConvexResultCallback
{
	bool isHit = false;									//衝突フラグ。
	Vector3 hitPos = Vector3(0.0f, -FLT_MAX, 0.0f);	//衝突点。
	Vector3 startPos = Vector3::Zero;					//レイの始点。
	float dist = FLT_MAX;								//衝突点までの距離。一番近い衝突点を求めるため。FLT_MAXは単精度の浮動小数点が取りうる最大の値。

														//衝突したときに呼ばれるコールバック関数。
	virtual	btScalar addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace)
	{
		if (convexResult.m_hitCollisionObject->getUserIndex() & ColliderUserIndex::enCollisionAttr_RayBlock)
		{
			//衝突している。
			isHit = true;
			Vector3 hitPosTmp = *(Vector3*)&convexResult.m_hitPointLocal;
			//衝突点の距離を求める。。
			Vector3 vDist;
			vDist.Subtract(hitPosTmp, startPos);
			float distTmp = vDist.Length();
			if (dist > distTmp) {
				//この衝突点の方が近いので、最近傍の衝突点を更新する。
				hitPos = hitPosTmp;
				dist = distTmp;
			}
		}
		return 0.0f;
	}
};

struct CharactorRayResult :public btCollisionWorld::RayResultCallback
{
	bool isHit = false;		//衝突フラグ
	Vector3 hitColPos = Vector3::Zero;
	const btCollisionObject* ColObj = nullptr;
	void* ExclusionPointer = nullptr;	//除外したいポインタ
	//衝突したときに呼ばれる関数
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
			//距離が近いほうに更新
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