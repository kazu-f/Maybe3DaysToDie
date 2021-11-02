#pragma once
struct ObjectParams {
	char* BlockName = nullptr;		//名前
	int Durable = 0;		//耐久値
	int ObtainAmount = 0;		//入手量
	//todo [リファクタリング] 適性ツールの型をintからenumにする
	int AptitudeTool = 0;		//適性ツール
};
class DestructibleObject
{
public:
	DestructibleObject() {}
	virtual ~DestructibleObject() {}

	/// <summary>
	/// オブジェクトの各種パラメータをセット
	/// </summary>
	/// <param name="param">パラメータ</param>
	void SetParams(ObjectParams&param)
	{
		m_params.BlockName = param.BlockName;
		m_params.Durable = param.Durable;
		m_params.ObtainAmount = param.ObtainAmount;
		m_params.AptitudeTool = param.AptitudeTool;
	}

	/// <summary>
	/// コライダーを生成
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
	CPhysicsStaticObject m_StaticCol;		//静的物理オブジェクト
	Vector3 m_position = Vector3::Zero;		//ポジション
	Quaternion m_qrot = Quaternion::Identity;		//回転
	Vector3 m_scale = Vector3::One;		//スケール
	bool IsDestructed = false;		//破壊されたかどうか
	ObjectParams m_params;		//各種パラメータ
};