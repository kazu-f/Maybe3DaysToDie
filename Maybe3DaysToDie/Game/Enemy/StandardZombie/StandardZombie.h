#pragma once

class STDZombieMove;
class STDZombieTracking;
class STDZombieAttack;

#include "Enemy/IEnemy.h"

/// <summary>
/// 標準的なゾンビ。
/// </summary>
class StandardZombie : public IEnemy
{
public:
	/// <summary>
	/// アニメーションenum。
	/// <para>マジックナンバーダメ絶対。</para>
	/// </summary>
	enum EnAnimationState {
		EnAnimationState_Idle,		//idle
		EnAnimationState_Run,		//走り。
		EnAnimationState_Attack,	//攻撃。
		/*-Count-*/
		EnAnimationState_Num,
		/*-Count-*/
		EnAnimationState_Walk,		//歩き。
		EnAnimationState_Damage,	//ダメージ。
		EnAnimationState_Stun,		//スタン。
		EnAnimationState_Death,		//死亡。

	};
public:
	/// <summary>
	/// コンストラクタ。
	/// </summary>
	StandardZombie() {};
public:
	/// <summary>
	///	スタート。
	/// </summary>
	/// <returns></returns>
	bool Start() override;
	/// <summary>
	/// 更新。
	/// </summary>
	void Update() override;

	/// <summary>
	/// 遅延更新。
	/// </summary>
	void PostUpdate() override;
	/// <summary>
	/// パラメーター値を取得。
	/// </summary>
	/// <returns></returns>
	EnemyParams& GetEnemyParameters() override;
public://HP関係
	void HitDamage(int attack)
	{
		int Damage = attack - m_parameters.Deffence;
		m_parameters.Hp = max(m_parameters.Hp - Damage, 0);
	}
private:
	Vector3 m_scale = { 6.0f, 6.0f, 6.0f };		//拡大。
	IEnemy::EnemyParams m_parameters;			//パラメーター。

	STDZombieTracking*	m_trackingState = nullptr;	//追跡用ステート。
	STDZombieAttack* m_attackState = nullptr;		//攻撃用ステート。
};

