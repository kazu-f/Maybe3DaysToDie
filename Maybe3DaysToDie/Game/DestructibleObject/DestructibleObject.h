#pragma once
struct ObjectParams {
	char* BlockName = nullptr;		//���O
	int Durable = 0;		//�ϋv�l
	int ObtainAmount = 0;		//�����
	//todo [���t�@�N�^�����O] �K���c�[���̌^��int����enum�ɂ���
	int AptitudeTool = 0;		//�K���c�[��
};
class DestructibleObject
{
public:
	DestructibleObject() {}
	virtual ~DestructibleObject() {}

	/// <summary>
	/// �I�u�W�F�N�g�̊e��p�����[�^���Z�b�g
	/// </summary>
	/// <param name="param">�p�����[�^</param>
	void SetParams(ObjectParams&param)
	{
		m_params.BlockName = param.BlockName;
		m_params.Durable = param.Durable;
		m_params.ObtainAmount = param.ObtainAmount;
		m_params.AptitudeTool = param.AptitudeTool;
	}

	/// <summary>
	/// �R���C�_�[�𐶐�
	/// </summary>
	void CreateCollider(prefab::ModelRender* model)
	{
		m_StaticCol.CreateMesh(model->GetPosition(), model->GetRotation(), model->GetScale(), model);
		m_StaticCol.GetRigidBody().GetBody()->setUserIndex(ColliderUserIndex::enCollisionAttr_Ground_RayBlock);
	}

	//void Deletethis()
	//{
	//	if(m_StaticCol.GetRigidBody())
	//}
protected:
	CPhysicsStaticObject m_StaticCol;		//�ÓI�����I�u�W�F�N�g
	Vector3 m_position = Vector3::Zero;		//�|�W�V����
	Quaternion m_qrot = Quaternion::Identity;		//��]
	Vector3 m_scale = Vector3::One;		//�X�P�[��
	bool IsDestructed = false;		//�j�󂳂ꂽ���ǂ���
	ObjectParams m_params;		//�e��p�����[�^
};