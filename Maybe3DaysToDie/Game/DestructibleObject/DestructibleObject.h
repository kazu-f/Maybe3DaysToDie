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
	/// ポジションをゲット
	/// </summary>
	/// <returns>オブジェクトのポジション</returns>
	const Vector3 GetPosition()const
	{
		return m_model->GetPosition();
	}

	/// <summary>
	/// ローテーションをゲット
	/// </summary>
	/// <returns>オブジェクトの回転</returns>
	const Quaternion GetRotation()const
	{
		return m_model->GetRotation();
	}

	/// <summary>
	/// スケールをゲット
	/// </summary>
	/// <returns>オブジェクトのスケール</returns>
	const Vector3 GetScale()const
	{
		return m_model->GetScale();
	}

	/// <summary>
	/// モデルをセット
	/// </summary>
	/// <param name="model">モデルレンダーのポインタ</param>
	void SetModel(prefab::ModelRender* model)
	{
		m_model = model;
	}

	/// <summary>
	/// コライダーを生成
	/// </summary>
	void CreateCollider()
	{
		if (m_model != nullptr)
		{
			m_StaticCol.CreateMesh(m_model->GetPosition(), m_model->GetRotation(), m_model->GetScale(), m_model);
		}
	}

	/// <summary>
	/// モデルの取得
	/// </summary>
	/// <returns>モデルレンダー</returns>
	const prefab::ModelRender* GetModel()const
	{
		return m_model;
	}
protected:
	prefab::ModelRender* m_model = nullptr;		//モデル
	CPhysicsStaticObject m_StaticCol;		//静的物理オブジェクト
	Vector3 m_position = Vector3::Zero;		//ポジション
	Quaternion m_qrot = Quaternion::Identity;		//回転
	Vector3 m_scale = Vector3::One;		//スケール
	bool IsDestructed = false;		//破壊されたかどうか
	ObjectParams m_params;		//各種パラメータ
};