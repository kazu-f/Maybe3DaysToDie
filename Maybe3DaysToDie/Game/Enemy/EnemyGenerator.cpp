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
	//登録されているエネミーを全て解放。
	for (auto* enemy : m_enemyList) {
		DeleteGO(enemy);
	}
}

void EnemyGenerator::UnRegistEnemy(IEnemy* enemy)
{
	//要素を探し出して削除する。
	m_enemyList.erase(std::find(m_enemyList.begin(), m_enemyList.end(), enemy));
	m_currentEnemyCount--;
}

void EnemyGenerator::ActivateBloodMoonHode()
{
}

void EnemyGenerator::DisableBloodMoonHode()
{
}

