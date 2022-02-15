#include "stdafx.h"
#include "EnemyGenerator.h"
#include "IEnemy.h"
#include "Player/Player.h"
#include "Stage.h"
#include "StandardZombie/StandardZombie.h"

std::map<int, int> EnemyGenerator::m_indexToSign
{
	{ 0, 1},
	{ 1, -1}
};

EnemyGenerator::EnemyGenerator()
{
}

EnemyGenerator::~EnemyGenerator()
{
	ReleaseEnemy();
}

bool EnemyGenerator::Start()
{
	m_player = FindGO<Player>("player");
	return true;
}

void EnemyGenerator::Update()
{
	m_spawnEnemyTimer += GameTime().GetFrameDeltaTime();

	if (m_spawnEnemyTimer > SPAWN_ENEMY_TIME)
	{
		SpawnEnemyAroundPlayer();
		m_spawnEnemyTimer = 0.0f;
	}

}

void EnemyGenerator::ReleaseEnemy()
{
	//登録されているエネミーを全て解放。
	for (auto* enemy : m_enemyList) {
		DeleteGO(enemy);
	}
}

void EnemyGenerator::SpawnEnemyAroundPlayer()
{
	int playerGrid[2] = { 1, 1 };

	//playerから1~2チャンク離れた場所にエネミーを生成。
	int sign = m_indexToSign[rand() % 2];
	playerGrid[0] += sign;
	sign = m_indexToSign[rand() % 2];
	playerGrid[1] += sign;

	//現在のチャンクから適当にセルを引っ張って生成位置を決定。
	auto& cellList = m_stage->GetTerrainWorld()->GetTerrainWorld(playerGrid[0], playerGrid[1])->GetCellList();
	int cellIndex = rand() % cellList.size();
	Vector3 spawnPoint = cellList[cellIndex].m_CenterPos;

	//todo:生成するZombieの種類（Enemyの種類）を選ぶロジックを追加。

	//生成！
	IEnemy* enemy = Create<StandardZombie>("Zombie");
	if (enemy != nullptr)
	{
		enemy->SetPos(spawnPoint);
		m_enemyList.push_back(enemy);
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

