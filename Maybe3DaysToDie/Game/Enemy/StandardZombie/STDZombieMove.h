#pragma once

#include "Enemy/IEnemyState.h"

class IEnemy;

/// <summary>
/// スタンダードゾンビの移動処理。
/// </summary>
class STDZombieMove : public IEnemyState
{
public:
	/// <summary>
	/// コンストラクタ。
	/// </summary>
	/// <param name="enemy"></param>
	STDZombieMove(IEnemy* enemy) :
		IEnemyState::IEnemyState(enemy) {
		m_enemy = enemy;
	}

	void Enter() override final;
	void Leave() override final;
	void Update() override final;

private:
	IEnemy* m_enemy = nullptr;		//エネミー。
};

