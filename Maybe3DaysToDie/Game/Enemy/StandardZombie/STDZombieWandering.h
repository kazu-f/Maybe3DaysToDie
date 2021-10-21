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
	/// �ړ��p�̃p�X��ǉ��B
	/// </summary>
	/// <param name="pos"></param>
	void AddMovePath(Vector3& pos)
	{
		m_movePathList.push_back(pos);
	}
private:
	std::vector<Vector3> m_movePathList;	//�ړ��p�̃p�X���X�g�B
};

