#pragma once
#include "MiniEngine/physics/CollisionAttr.h"

class Tool;
//todo プレイヤー側から呼ぶようになったらIGameObjectを継承しないように
class DestroyObject:public IGameObject
{
private:
	struct RayResult :public btCollisionWorld::RayResultCallback
	{
		bool isHit = false;		//衝突フラグ
		Vector3 hitNormal = Vector3::Zero;
		Vector3 hitColPos = Vector3::Zero;
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
				return m_closestHitFraction;
			}
			return 0.0f;
		}
	};

public:
	DestroyObject();
	~DestroyObject();

	void AddObjectDamage(int damage);

	void Update();

	void SetTool(Tool* tool)
	{
		m_tool = tool;
	}

private:
	Tool* m_tool = nullptr;
};

