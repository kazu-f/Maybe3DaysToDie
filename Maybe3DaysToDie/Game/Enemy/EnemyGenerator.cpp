#include "stdafx.h"
#include "EnemyGenerator.h"
#include "IEnemy.h"

//唯一のインスタンス。
EnemyGenerator* EnemyGenerator::m_instance = nullptr;

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
	if (m_currentEnemyCount == 0) {
		//設定以上作成した時の削除処理はここに入る。
		//特に何もRegist側で行ってないため、こちらも何も行わない。
		return;
	}

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

