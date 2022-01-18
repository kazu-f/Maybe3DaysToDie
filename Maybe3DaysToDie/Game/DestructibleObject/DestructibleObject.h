#pragma once
struct ToolInfo;

static const float OBJECT_UNIT = 100.0f;
static const float OBJECT_HALF_UNIT = 50.0f;

struct ObjectParams {
	const char* BlockName = nullptr;		//名前
	unsigned char BlockID = 0;
	unsigned short Durable = 0;		//耐久値
	unsigned char ObtainAmount = 0;		//入手量
	ToolKinds AptitudeTool = ToolKinds::DebugTool;		//適性ツール
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
	/// オブジェクトの各種パラメータをセット
	/// </summary>
	/// <param name="param">パラメータ</param>
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
	///// コライダーを生成
	///// </summary>
	//void CreateCollider(prefab::ModelRender* model)
	//{
	//	m_StaticCol.CreateMesh(model->GetPosition(), model->GetRotation(), model->GetScale(), model);
	//	m_StaticCol.GetRigidBody().GetBody()->setUserIndex(ColliderUserIndex::enCollisionAttr_Ground_RayBlock);
	//}

	///// <summary>
	///// コライダーの座標と回転をセット
	///// </summary>
	///// <param name="pos">座標</param>
	///// <param name="rot">回転</param>
	//void SetColPos(const Vector3& pos,const Quaternion&rot)
	//{
	//	m_StaticCol.SetPosAndRot(pos, rot);
	//}

	/// <summary>
	/// ダメージを与える。
	/// </summary>
	virtual void Damage(const ToolInfo& tool) = 0;

	/// <summary>
	/// ブロックの追加
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
	/// 座標を設定。
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
	/// 物理オブジェクトの座標と回転を設定。
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
	//CPhysicsStaticObject m_StaticCol;		//静的物理オブジェクト
	Vector3 m_position = Vector3::Zero;		//ポジション
	Quaternion m_qrot = Quaternion::Identity;		//回転
	Vector3 m_scale = Vector3::One;		//スケール
	bool IsDestructed = false;		//破壊されたかどうか
	ObjectParams m_params;		//各種パラメータ
	int m_maxDurable = 0;
};