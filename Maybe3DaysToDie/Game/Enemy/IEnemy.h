#pragma once

#include "MiniEngine/NaviMesh/NaviMeshAgent.h"
#include "IEnemyState.h"

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
	virtual ~IEnemy();
	/// <summary>
	/// スタート。
	/// </summary>
	/// <returns></returns>
	virtual bool Start() override = 0;
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
	void InitNavActor(ModelInitData& initData, const char* tag, NaviMesh* mesh, AnimClipInitData animClipDatas[] = nullptr, int animSize = 0,  bool isRandMove = false);
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
	/// ジェネレーターを設定。
	/// </summary>
	/// <param name="generator">ジェネレーター。</param>
	void SetEnemyGenerator(EnemyGenerator* generator)
	{
		m_generatorPtr = generator;
	}
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
public://getter
	/// <summary>
	/// エージェントを取得。
	/// </summary>
	/// <returns></returns>
	NaviMeshAgent& GetAgent()
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
private:
	prefab::ModelRender*	m_modelRender = nullptr;	//レンダー。
	NaviMeshAgent			m_agent;					//ナビメッシュエージェント。
	EnemyGenerator*			m_generatorPtr;				//ジェネレーターのポインタ。
	IEnemyState*			m_currentState = nullptr;	//現在のステート。
};

