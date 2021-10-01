#include "stdafx.h"
#include "StandardZombie.h"

bool StandardZombie::Start()
{
	//StatusInit
	m_enemyParameters.Attack = 20;
	m_enemyParameters.AttackRange = 150.0f;
	m_enemyParameters.Deffence = 5;
	m_enemyParameters.EXP = 500.0f;
	m_enemyParameters.MoveSpeed = 2.0f;
	m_enemyParameters.SearchRange = 20000.0f;


	

	return true;
}

void StandardZombie::Update()
{

}
