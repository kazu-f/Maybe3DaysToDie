#pragma once
struct ToolInfo;

static const float OBJECT_UNIT = 100.0f;
static const float OBJECT_HALF_UNIT = 50.0f;

struct ObjectParams {
	const char* BlockName = nullptr;		//���O
	unsigned char BlockID = 0;
	unsigned short Durable = 0;		//�ϋv�l
	unsigned char ObtainAmount = 0;		//�����
	ToolKinds AptitudeTool = ToolKinds::DebugTool;		//�K���c�[��
	ObjectType Type = ObjectType::Type;
};
class DestructibleObject
{
public:
	DestructibleObject() {}
	virtual ~DestructibleObject() {}

	DestructibleObject* GetPointer()
	{
		return this;
	}

	/// <summary>
	/// �I�u�W�F�N�g�̊e��p�����[�^���Z�b�g
	/// </summary>
	/// <param name="param">�p�����[�^</param>
	void SetParams(ObjectParams&param)
	{
		m_params.BlockName = param.BlockName;
		m_params.BlockID = param.BlockID;
		m_params.Durable = param.Durable;
		m_maxDurable = param.Durable;
		m_params.ObtainAmount = param.ObtainAmount;
		m_params.AptitudeTool = param.AptitudeTool;
	}

	const ObjectParams& GetParam()const
	{
		return m_params;
	}
	///// <summary>
	///// �R���C�_�[�𐶐�
	///// </summary>
	//void CreateCollider(prefab::ModelRender* model)
	//{
	//	m_StaticCol.CreateMesh(model->GetPosition(), model->GetRotation(), model->GetScale(), model);
	//	m_StaticCol.GetRigidBody().GetBody()->setUserIndex(ColliderUserIndex::enCollisionAttr_Ground_RayBlock);
	//}

	///// <summary>
	///// �R���C�_�[�̍��W�Ɖ�]���Z�b�g
	///// </summary>
	///// <param name="pos">���W</param>
	///// <param name="rot">��]</param>
	//void SetColPos(const Vector3& pos,const Quaternion&rot)
	//{
	//	m_StaticCol.SetPosAndRot(pos, rot);
	//}

	/// <summary>
	/// �_���[�W��^����B
	/// </summary>
	virtual void Damage(const ToolInfo& tool) = 0;

	/// <summary>
	/// �u���b�N�̒ǉ�
	/// </summary>
	/// <param name="params"></param>
	/// <param name="pos"></param>
	/// <param name="rot"></param>
	/// <param name="scale"></param>
	virtual void AddBlock(ObjectParams& params, Vector3& pos, Quaternion& rot, Vector3& scale) = 0;

	//void Deletethis()
	//{
	//	if(m_StaticCol.GetRigidBody())
	//}

	/// <summary>
	/// ���W��ݒ�B
	/// </summary>
	void SetPosition(const Vector3& pos)
	{
		m_position = pos;
	}

	const Vector3& GetPosition()const
	{
		return m_position;
	}

	void SetRotation(const Quaternion& rot)
	{
		m_qrot = rot;
	}

	const Quaternion& GetRotation()const
	{
		return m_qrot;
	}

	void SetScale(const Vector3& scale)
	{
		m_scale = scale;
	}

	const Vector3& GetScale()const
	{
		return m_scale;
	}

	/// <summary>
	/// �����I�u�W�F�N�g�̍��W�Ɖ�]��ݒ�B
	/// </summary>
	void SetPosAndRot(const Vector3& pos, const Quaternion& rot)
	{
		m_position = pos;
		m_qrot = rot;
	}

	void ResetParams()
	{
		m_params.BlockName = nullptr;
		m_params.Durable = 0;
		m_params.ObtainAmount = 0;
		m_params.AptitudeTool = ToolKinds::DebugTool;
	}
protected:
	//CPhysicsStaticObject m_StaticCol;		//�ÓI�����I�u�W�F�N�g
	Vector3 m_position = Vector3::Zero;		//�|�W�V����
	Quaternion m_qrot = Quaternion::Identity;		//��]
	Vector3 m_scale = Vector3::One;		//�X�P�[��
	bool IsDestructed = false;		//�j�󂳂ꂽ���ǂ���
	ObjectParams m_params;		//�e��p�����[�^
	int m_maxDurable = 0;
};