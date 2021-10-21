#pragma once
#include "Stage/SuperFlat/SuperFlat.h"
#include "Stage/Hill/Hill.h"

class Stage : public IGameObject
{
private:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <returns>trueを返すまでループする</returns>
	bool Start();
	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	/// <summary>
	/// deleteをすると呼ばれる関数
	/// </summary>
	void OnDestroy();

	/// <summary>
	/// コリジョン作成
	/// </summary>
	void CreatePhysics();

private:
	/// <summary>
	/// 地面を表示する
	/// </summary>
	void NewGround();
private:
	SuperFlat m_stage;
	//prefab::ModelRender* m_Model = nullptr;		//地面
	//CPhysicsStaticObject m_StaticCol;		//静的物理オブジェクト
	//Vector3 m_pos = Vector3::Zero;		//ポジション
	//Quaternion m_qrot = Quaternion::Identity;		//回転
	//Vector3 m_scale = Vector3::One;		//スケール
};

