#pragma once

#include "Enemy/IEnemyState.h"

class STDZombieWandering : public IEnemyState
{
public:
	//StateFunc.
	void Enter() override final;
	void Update() override final;
	void Leave() override final;
public:
	/// <summary>
	/// 移動用のパスを追加。
	/// </summary>
	/// <param name="pos"></param>
	void AddMovePath(Vector3& pos)
	{
		m_movePathList.push_back(pos);
	}
private:
	std::vector<Vector3> m_movePathList;	//移動用のパスリスト。
};

