#pragma once

class PlacementObject:public IGameObject
{
private:
	struct RayResult :public btCollisionWorld::RayResultCallback
	{
		bool isHit = false;		//�Փ˃t���O

		//�Փ˂����Ƃ��ɌĂ΂��֐�
		virtual btScalar addSingleResult(
			btCollisionWorld::LocalRayResult& convexResult,
			bool /*normalInWorldSpace*/
		)
		{
			isHit = true;
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

	bool Start();
	void Update();
	void OnDestroy();

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
};

