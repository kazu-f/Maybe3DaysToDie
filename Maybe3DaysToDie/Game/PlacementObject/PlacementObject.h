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
	/// 物理オブジェクトを作成
	/// </summary>
	void CreatePhysics();
private:
	prefab::ModelRender* m_ObjectModel = nullptr;		//オブジェクトモデル
	CPhysicsStaticObject m_StaticCol;		//静的物理オブジェクト
	Vector3 m_pos = Vector3::Zero;		//モデルのポジション
	Vector3 m_scale = Vector3::One;		//モデルのスケール
	Quaternion m_qrot = Quaternion::Identity;		//モデルの回転
};

