#pragma once
#include "MiniEngine/physics/CollisionAttr.h"

//todo �v���C���[������ĂԂ悤�ɂȂ�����IGameObject���p�����Ȃ��悤��
class DestroyObject:public IGameObject
{
private:
	struct RayResult :public btCollisionWorld::RayResultCallback
	{
		//�Փ˂����Ƃ��ɌĂ΂��֐�
		virtual btScalar addSingleResult(
			btCollisionWorld::LocalRayResult& convexResult,
			bool /*normalInWorldSpace*/
		)
		{
			if (convexResult.m_collisionObject->getUserIndex() != enCollisionAttr_Character)
			{
				//���C�����������t���O�𗧂Ă�
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

