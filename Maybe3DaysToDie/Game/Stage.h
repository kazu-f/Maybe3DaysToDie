#pragma once
#include "Stage/SuperFlat/SuperFlat.h"
#include "Stage/Hill/Hill.h"
#include "Enemy/EnemyGenerator.h"
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
	/// <summary>
	/// 地面を表示する
	/// </summary>
	void NewGround();
public:
	/// <summary>
	/// エネミージェネレーターを取得。
	/// </summary>
	/// <returns></returns>
	EnemyGenerator& GetEnemyGenerator()
	{
		return m_enemyGenerator;
	}
private:
	SuperFlat m_stage;
	EnemyGenerator m_enemyGenerator;				//エネミージェネレーター。
	//prefab::ModelRender* m_Model = nullptr;		//地面
	//CPhysicsStaticObject m_StaticCol;		//静的物理オブジェクト
	//Vector3 m_pos = Vector3::Zero;		//ポジション
	//Quaternion m_qrot = Quaternion::Identity;		//回転
	//Vector3 m_scale = Vector3::One;		//スケール
};

