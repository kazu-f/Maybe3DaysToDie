#pragma once

class PlacementObject:public IGameObject
{
private:
	struct RayResult :public btCollisionWorld::RayResultCallback
	{
		bool isHit = false;		//衝突フラグ

		//衝突したときに呼ばれる関数
		virtual btScalar addSingleResult(
			btCollisionWorld::LocalRayResult& convexResult,
			bool /*normalInWorldSpace*/
		)
		{
			isHit = true;
			//距離が近いほうに更新
			if (m_closestHitFraction > convexResult.m_hitFraction)
			{
				m_closestHitFraction = convexResult.m_hitFraction;
			}
			return m_closestHitFraction;
		}
	};
public:
	PlacementObject();
	~PlacementObject();

	bool Start();
	void Update();
	void OnDestroy();

	/// <summary>
	/// 設置するオブジェクトの位置を計算
	/// </summary>
	void CalcObjectPos();

private:
	prefab::ModelRender* m_ObjectModel = nullptr;		//オブジェクトモデル
	Vector3 m_pos = Vector3::Zero;		//モデルのポジション
	Vector3 m_scale = Vector3::One;		//モデルのスケール
	Quaternion m_qrot = Quaternion::Identity;		//モデルの回転
	const float m_SetRange = 500.0f;		//設置範囲
};

