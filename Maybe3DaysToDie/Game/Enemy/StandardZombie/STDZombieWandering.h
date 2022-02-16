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
	std::vector<Vector3> m_movePathList;			//移動用のパスリスト。
	Vector3 m_target = Vector3::Zero;
	const float SUCCESS_TIME = 0.5f;
	const float FAILED_TIME = 2.0f;
	float m_serchTime = SUCCESS_TIME;
};

