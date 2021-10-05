#pragma once
class PlacementObject:public IGameObject
{
public:
	PlacementObject();
	~PlacementObject();

	bool Start();
	void Update();
	void OnDestroy();
	/// <summary>
	/// �����I�u�W�F�N�g���쐬
	/// </summary>
	void CreatePhysics();
private:
	prefab::ModelRender* m_ObjectModel = nullptr;		//�I�u�W�F�N�g���f��
	CPhysicsStaticObject m_StaticCol;		//�ÓI�����I�u�W�F�N�g
	Vector3 m_pos = Vector3::Zero;		//���f���̃|�W�V����
	Vector3 m_scale = Vector3::One;		//���f���̃X�P�[��
	Quaternion m_qrot = Quaternion::Identity;		//���f���̉�]
};

