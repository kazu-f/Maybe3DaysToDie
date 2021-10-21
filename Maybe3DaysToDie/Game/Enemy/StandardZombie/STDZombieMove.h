#pragma once

#include "Enemy/IEnemyState.h"

class IEnemy;

/// <summary>
/// �X�^���_�[�h�]���r�̈ړ������B
/// </summary>
class STDZombieMove : public IEnemyState
{
public:
	/// <summary>
	/// �R���X�g���N�^�B
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
	IEnemy* m_enemy = nullptr;		//�G�l�~�[�B
};

