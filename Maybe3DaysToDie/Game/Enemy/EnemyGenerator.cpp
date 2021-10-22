#include "stdafx.h"
#include "EnemyGenerator.h"
#include "IEnemy.h"


EnemyGenerator::EnemyGenerator()
{
}

EnemyGenerator::~EnemyGenerator()
{
	ReleaseEnemy();
}

void EnemyGenerator::ReleaseEnemy()
{
	//�o�^����Ă���G�l�~�[��S�ĉ���B
	for (auto* enemy : m_enemyList) {
		DeleteGO(enemy);
	}
}

void EnemyGenerator::UnRegistEnemy(IEnemy* enemy)
{
	//�v�f��T���o���č폜����B
	m_enemyList.erase(std::find(m_enemyList.begin(), m_enemyList.end(), enemy));
	m_currentEnemyCount--;
}

void EnemyGenerator::ActivateBloodMoonHode()
{
}

void EnemyGenerator::DisableBloodMoonHode()
{
}

