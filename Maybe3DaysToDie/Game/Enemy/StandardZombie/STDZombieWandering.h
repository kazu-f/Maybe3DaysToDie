#pragma once

#include "Enemy/IEnemyState.h"

class STDZombieWandering : public IEnemyState
{
public:
	STDZombieWandering(IEnemy* enemy);

public:
	//StateFunc.
	void Enter() override final;
	void Update() override final;
	void Leave() override final;

private:
	std::vector<Vector3> m_movePathList;			//�ړ��p�̃p�X���X�g�B
	Vector3 m_target = Vector3::Zero;
};

