#pragma once
#include "MiniEngine/physics/CollisionAttr.h"

//todo プレイヤー側から呼ぶようになったらIGameObjectを継承しないように
class DestroyObject:public IGameObject
{
private:
	struct RayResult :public btCollisionWorld::RayResultCallback
	{
		//衝突したときに呼ばれる関数
		virtual btScalar addSingleResult(
			btCollisionWorld::LocalRayResult& convexResult,
			bool /*normalInWorldSpace*/
		)
		{
			if (convexResult.m_collisionObject->getUserIndex() != enCollisionAttr_Character)
			{
				//レイが当たったフラグを立てる
				//convexResult.m_collisionObject->SetIsRayHit(true);
			}
			return 0.0f;
		}
	};

public:
	DestroyObject();
	~DestroyObject();

	void AddObjectDamage();

};

