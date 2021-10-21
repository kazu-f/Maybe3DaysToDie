#pragma once

class STDZombieMove;

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
		/*-Count-*/
		EnAnimationState_Num,
		/*-Count-*/
		EnAnimationState_Walk,		//歩き。
		EnAnimationState_Attack,	//攻撃。
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
	bool Start() override final;
	/// <summary>
	/// 更新。
	/// </summary>
	void Update() override final;
	/// <summary>
	/// パラメーター値を取得。
	/// </summary>
	/// <returns></returns>
	EnemyParams& GetEnemyParameters() override;
private:
	Vector3 m_scale = { 6.0f, 6.0f, 6.0f };		//拡大。
	IEnemy::EnemyParams m_parameters;			//パラメーター。

	STDZombieMove* m_moveState = nullptr;		//移動用ステート。
};

