#pragma once
class PlacementObject:public IGameObject
{
public:
	PlacementObject();
	~PlacementObject();

	void Awake();
	bool Start();
	void Update();
	void OnDestroy();
private:
	prefab::ModelRender* m_ObjectModel = nullptr;		//�I�u�W�F�N�g���f��
	Vector3 m_pos = Vector3::Zero;		//���f���̃|�W�V����
	Vector3 m_scale = Vector3::One;		//���f���̃X�P�[��
	Quaternion m_qrot = Quaternion::Identity;		//���f���̉�]
};

