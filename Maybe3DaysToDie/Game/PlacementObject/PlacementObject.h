#pragma once

class PlacementObject:public IGameObject
{
private:
	struct RayResult :public btCollisionWorld::RayResultCallback
	{
		virtual btScalar addSingleResult(
			btCollisionWorld::LocalConvexResult& convexResult,
			bool /*normalInWorldSpace*/
		)
		{

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

