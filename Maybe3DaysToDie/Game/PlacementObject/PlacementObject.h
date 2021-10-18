#pragma once
#include "DestructibleObject/Block/Block.h"

class PlacementObject:public IGameObject
{
private:
	struct RayResult :public btCollisionWorld::RayResultCallback
	{
		bool isHit = false;		//�Փ˃t���O
		Vector3 hitNormal = Vector3::Zero;
		//�Փ˂����Ƃ��ɌĂ΂��֐�
		virtual btScalar addSingleResult(
			btCollisionWorld::LocalRayResult& convexResult,
			bool /*normalInWorldSpace*/
		)
		{
			isHit = true;
			hitNormal.Set(convexResult.m_hitNormalLocal);
			//�������߂��ق��ɍX�V
			if (m_closestHitFraction > convexResult.m_hitFraction)
			{
				m_closestHitFraction = convexResult.m_hitFraction;
			}
			return m_closestHitFraction;
		}
	};
public:
	PlacementObject();
	~PlacementObject();

	bool Start()override final;
	void Update()override final;
	void OnDestroy()override final;

	/// <summary>
	/// �I�u�W�F�N�g��ݒu
	/// </summary>
	void PlaceObject();

	/// <summary>
	/// �ݒu����I�u�W�F�N�g�̈ʒu���v�Z
	/// </summary>
	void CalcObjectPos();

private:
	prefab::ModelRender* m_ObjectModel = nullptr;		//�I�u�W�F�N�g���f��
	Vector3 m_pos = Vector3::Zero;		//���f���̃|�W�V����
	Vector3 m_scale = Vector3::One;		//���f���̃X�P�[��
	Quaternion m_qrot = Quaternion::Identity;		//���f���̉�]
	const float m_SetRange = 500.0f;		//�ݒu�͈�
	std::vector<Block*> m_model;
	bool CanPlace = false;
};

