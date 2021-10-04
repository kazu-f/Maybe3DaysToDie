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
	prefab::ModelRender* m_ObjectModel = nullptr;		//オブジェクトモデル
	Vector3 m_pos = Vector3::Zero;		//モデルのポジション
	Vector3 m_scale = Vector3::One;		//モデルのスケール
	Quaternion m_qrot = Quaternion::Identity;		//モデルの回転
};

