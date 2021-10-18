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
	/// �|�W�V�������Q�b�g
	/// </summary>
	/// <returns>�I�u�W�F�N�g�̃|�W�V����</returns>
	const Vector3 GetPosition()const
	{
		return m_model->GetPosition();
	}

	/// <summary>
	/// ���[�e�[�V�������Q�b�g
	/// </summary>
	/// <returns>�I�u�W�F�N�g�̉�]</returns>
	const Quaternion GetRotation()const
	{
		return m_model->GetRotation();
	}

	/// <summary>
	/// �X�P�[�����Q�b�g
	/// </summary>
	/// <returns>�I�u�W�F�N�g�̃X�P�[��</returns>
	const Vector3 GetScale()const
	{
		return m_model->GetScale();
	}

	/// <summary>
	/// ���f�����Z�b�g
	/// </summary>
	/// <param name="model">���f�������_�[�̃|�C���^</param>
	void SetModel(prefab::ModelRender* model)
	{
		m_model = model;
	}

	/// <summary>
	/// �R���C�_�[�𐶐�
	/// </summary>
	void CreateCollider()
	{
		if (m_model != nullptr)
		{
			m_StaticCol.CreateMesh(m_model->GetPosition(), m_model->GetRotation(), m_model->GetScale(), m_model);
		}
	}

	/// <summary>
	/// ���f���̎擾
	/// </summary>
	/// <returns>���f�������_�[</returns>
	const prefab::ModelRender* GetModel()const
	{
		return m_model;
	}
protected:
	prefab::ModelRender* m_model = nullptr;		//���f��
	CPhysicsStaticObject m_StaticCol;		//�ÓI�����I�u�W�F�N�g
	Vector3 m_position = Vector3::Zero;		//�|�W�V����
	Quaternion m_qrot = Quaternion::Identity;		//��]
	Vector3 m_scale = Vector3::One;		//�X�P�[��
	bool IsDestructed = false;		//�j�󂳂ꂽ���ǂ���
	ObjectParams m_params;		//�e��p�����[�^
};