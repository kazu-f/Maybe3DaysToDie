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

std::map<float, int> EnemyGenerator::m_currentSpawnTimeToChangeSpawnTimeCount
{
	{ 10.0f, 1 },
	{ 9.0f,  4 },
	{ 8.0f,  10 },
	{ 7.0f,  16 },
	{ 6.0f,  24 },
	{ 5.0f,  35 }
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
	//デスポーン処理。
	//PlayerGrid.
	int playerGrid[2];
	playerGrid[0] = static_cast<int>(std::floor((m_player->GetPosition().x / OBJECT_UNIT) / ChunkWidth));// +MAX_CHUNK_SIDE / 2;
	playerGrid[1] = static_cast<int>(std::floor((m_player->GetPosition().z / OBJECT_UNIT) / ChunkWidth));// +MAX_CHUNK_SIDE / 2;
	playerGrid[0] = max(min(MAX_CHUNK_SIDE - 1, playerGrid[0]), 1);
	playerGrid[1] = max(min(MAX_CHUNK_SIDE - 1, playerGrid[1]), 1);

	std::vector<IEnemy*> deleteEnemyList;

	for (auto* enemy : m_enemyList)
	{
		//EnemyGrid.
		int enemyGrid[2];
		enemyGrid[0] = static_cast<int>(std::floor((enemy->GetPos().x / OBJECT_UNIT) / ChunkWidth));// +MAX_CHUNK_SIDE / 2;
		enemyGrid[1] = static_cast<int>(std::floor((enemy->GetPos().z / OBJECT_UNIT) / ChunkWidth));// +MAX_CHUNK_SIDE / 2;
		enemyGrid[0] = max(min(MAX_CHUNK_SIDE - 1, enemyGrid[0]), 1);
		enemyGrid[1] = max(min(MAX_CHUNK_SIDE - 1, enemyGrid[1]), 1);

		//差分グリッド。
		int E2PGrid[2];
		E2PGrid[0] = abs(enemyGrid[0] - playerGrid[0]);
		E2PGrid[1] = abs(enemyGrid[1] - playerGrid[1]);

		if (E2PGrid[0] > 1 || E2PGrid[1] > 1)
		{
			deleteEnemyList.push_back(enemy);
		}
	}

	for (auto& deleteEnemy : deleteEnemyList)
	{
		UnRegistEnemy(deleteEnemy);
	}

	m_spawnEnemyTimer += GameTime().GetFrameDeltaTime();

	if (m_isActiveBloodMoon)
	{
		for (auto& enemy : m_enemyList)
		{
			enemy->SetBloodMoon(true);
		}

		m_spawnEnemyTime = BLOOD_MOON_SPAWN_TIME;
	}
	else
	{
		//敵の撃破数に応じてスポーンタイムを変えてく。
		if (m_currentSpawnTimeToChangeSpawnTimeCount[m_spawnEnemyTime] == m_deadEnemyCount)
		{
			m_spawnEnemyTime--;
		}
	}

	if (m_spawnEnemyTimer > m_spawnEnemyTime)
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
	}
}

void EnemyGenerator::UnRegistEnemy(IEnemy* enemy)
{
	//要素を探し出して削除する。
	m_enemyList.erase(std::find(m_enemyList.begin(), m_enemyList.end(), enemy));
	DeleteGO(enemy);
	m_currentEnemyCount--;
}

void EnemyGenerator::ActivateBloodMoonHode()
{
}

void EnemyGenerator::DisableBloodMoonHode()
{
}

