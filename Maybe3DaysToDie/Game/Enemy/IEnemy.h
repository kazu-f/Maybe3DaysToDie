#pragma once

#include "IEnemyState.h"
#include "Navigation/NavigationAgent.h"
#include "IK/FootIK.h"

class Player;
class EnemyGenerator;

/// <summary>
/// 敵キャラの基底クラス。
/// </summary>
/// <remarks>
/// 敵キャラを作成する際は、このクラスを継承して作成していくこと。
/// サンプルコードはStandardZombieにある。
/// 尚、パラメーターは派生先のクラスで保持、初期化を行うこと。
/// </remarks>
class IEnemy : public IGameObject
{
public:
	/// <summary>
	/// エネミーの初期化パラメーター。
	/// </summary>
	/// <remarks>
	/// 派生クラスで保持させて、各パラメータを初期化して使用すること。
	/// </remarks>
	struct EnemyParams
	{
		//Status
		unsigned int Attack = 20;		//攻撃力。		
		unsigned int Deffence = 5;		//防御力。		
		unsigned int EXP = 500;			//収得経験値。	
		float MoveSpeed = 3.0f;			//移動速度。	

		int Hp = 100;					//体力。

		//体格
		float Hight  = 90.0f;
		float Radius = 50.0f;

		//move(cm)
		float AttackRange = 150.0f;		//攻撃範囲。	
		float SearchRange = 20000.0f;	//索敵範囲。	
	};
public:
	/// <summary>
	/// コンストラクタ。
	/// </summary>
	IEnemy();

	/// <summary>
	/// デストラクタ。
	/// </summary>
	virtual ~IEnemy() {};
	
	void OnDestroy() override final;
	/// <summary>
	/// スタート。
	/// </summary>
	/// <returns></returns>
	virtual bool Start() override;
	/// <summary>
	/// 更新。
	/// </summary>
	virtual void Update() override = 0;
	/// <summary>
	/// エネミーのパラメーターを取得。
	/// <para>派生クラスでパラメーターを返す処理を実装すること。</para>
	/// </summary>
	/// <returns></returns>
	virtual EnemyParams& GetEnemyParameters() = 0;
public:
	/// <summary>
	/// エージェント付きモデル初期化。
	/// </summary>
	/// <param name="initData">初期化データー。</param>
	/// <param name="tag">タグ。</param>
	/// <param name="mesh">ナビメッシュ。</param>
	/// <param name="animClipDatas">アニメーションクリップ。</param>
	/// <param name="isRandMove">ランダム移動するか。</param>
	//void InitNavActor(ModelInitData& initData, const char* tag, NaviMesh* mesh, AnimClipInitData animClipDatas[] = nullptr, int animSize = 0,  bool isRandMove = false);
public://なんかtripleTrashオカピー。
	/// <summary>
	/// アクター初期化。
	/// <para>エージェントは含まない。</para>
	/// </summary>
	/// <param name="initData">モデルの初期化データー。</param>
	/// <param name="tag">タグ。</param>
	/// <param name="animClipDatas">アニメーションデーター。</param>
	void InitActor(ModelInitData& initData, const char* tag, AnimClipInitData animClipDatas[] = nullptr, int animSize = 0);
public://setter
	/// <summary>
	/// ステートを変更。
	/// </summary>
	/// <param name="state"></param>
	void ChangeState(IEnemyState* state)
	{
		if (m_currentState == state) {
			//一緒の場合は特に何も行わない。
			return;
		}

		//ステートを変更の際に関数を呼び出し。
		if (m_currentState != nullptr) {
			m_currentState->Leave();
		}
		m_currentState = state;
		m_currentState->Enter();
	}

	/// <summary>
	/// ジェネレーターを設定。
	/// </summary>
	/// <param name="generator">ジェネレーター。</param>
	void SetEnemyGenerator(EnemyGenerator* generator)
	{
		m_generatorPtr = generator;
	}

	/// <summary>
	/// NVMジェネレーターを取得。
	/// </summary>
	/// <returns></returns>
	EnemyGenerator* GetEnemyGenerator()
	{
		return m_generatorPtr;
	}

	/// <summary>
	/// NVMジェネレーターを設定。
	/// </summary>
	/// <param name="generator"></param>
	void SetStage(Stage* stage)
	{
		m_stage = stage;
	}

	/// <summary>
	/// 位置を設定。
	/// </summary>
	/// <param name="pos"></param>
	void SetPos(const Vector3& pos)
	{
		m_pos = pos;
	}

	void SetRot(const Quaternion rot)
	{
		m_rot = rot;
	}

public://getter
	/// <summary>
	/// エージェントを取得。
	/// </summary>
	/// <returns></returns>
	NavigationAgent& GetAgent()
	{
		return m_agent;
	}
	/// <summary>
	/// モデルレンダーを取得。
	/// </summary>
	/// <returns></returns>
	prefab::ModelRender* GetModelRender() const
	{
		return m_modelRender;
	}
	/// <summary>
	/// 現在のステートを取得。
	/// </summary>
	/// <returns></returns>
	IEnemyState* GetCurrentState() const 
	{
		return m_currentState;
	}
	/// <summary>
	/// 位置を取得。
	/// </summary>
	/// <returns></returns>
	Vector3& GetPos()
	{
		return m_pos;
	}
	/// <summary>
	/// 回転を取得。
	/// </summary>
	/// <returns></returns>
	Quaternion& GetRot()
	{
		return m_rot;
	}

	FootIK& GetIK()
	{
		return m_footIK;
	}

	/// <summary>
	/// プレイヤーを取得。
	/// </summary>
	/// <returns></returns>
	Player* GetPlayer()
	{
		return m_playerPtr;
	}

	/// <summary>
	/// ステージを取得。
	/// </summary>
	/// <returns></returns>
	Stage* GetStage()
	{
		return m_stage;
	}
public:	//Hp関係
	virtual void HitDamage(int attack) = 0;
protected:
	prefab::ModelRender*	m_modelRender = nullptr;	//レンダー。
	EnemyGenerator*			m_generatorPtr;				//ジェネレーターのポインタ。
	IEnemyState*			m_currentState = nullptr;	//現在のステート。
	Vector3					m_pos = g_vec3Zero;			//座標。
	Quaternion				m_rot = g_quatIdentity;		//回転。
	NavigationAgent			m_agent;					//エージェント。
	FootIK					m_footIK;
	Player*					m_playerPtr;				//プレイヤー。
	Stage*					m_stage = nullptr;

	CCapsuleCollider		m_capsuleCollider;			//カプセルコライダー。
	CRigidBody				m_rigidBody;				//剛体。
};

