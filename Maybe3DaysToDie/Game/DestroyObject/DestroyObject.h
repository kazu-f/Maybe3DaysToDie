#pragma once
#include "MiniEngine/physics/CollisionAttr.h"

class Tool;
//todo �v���C���[������ĂԂ悤�ɂȂ�����IGameObject���p�����Ȃ��悤��
class DestroyObject:public IGameObject
{
private:
	struct RayResult :public btCollisionWorld::RayResultCallback
	{
		bool isHit = false;		//�Փ˃t���O
		Vector3 hitNormal = Vector3::Zero;
		Vector3 hitColPos = Vector3::Zero;
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

