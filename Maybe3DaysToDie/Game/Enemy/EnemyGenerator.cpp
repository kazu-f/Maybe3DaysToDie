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
	//�f�X�|�[�������B
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

		//�����O���b�h�B
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
		//�G�̌��j���ɉ����ăX�|�[���^�C����ς��Ă��B
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
	//�o�^����Ă���G�l�~�[��S�ĉ���B
	for (auto* enemy : m_enemyList) {
		DeleteGO(enemy);
	}
}

void EnemyGenerator::SpawnEnemyAroundPlayer()
{
	int playerGrid[2] = { 1, 1 };

	//player����1~2�`�����N���ꂽ�ꏊ�ɃG�l�~�[�𐶐��B
	int sign = m_indexToSign[rand() % 2];
	playerGrid[0] += sign;
	sign = m_indexToSign[rand() % 2];
	playerGrid[1] += sign;

	//���݂̃`�����N����K���ɃZ�������������Đ����ʒu������B
	auto& cellList = m_stage->GetTerrainWorld()->GetTerrainWorld(playerGrid[0], playerGrid[1])->GetCellList();

	int cellIndex = rand() % cellList.size();
	Vector3 spawnPoint = cellList[cellIndex].m_CenterPos;

	//todo:��������Zombie�̎�ށiEnemy�̎�ށj��I�ԃ��W�b�N��ǉ��B

	//�����I
	IEnemy* enemy = Create<StandardZombie>("Zombie");
	if (enemy != nullptr)
	{
		enemy->SetPos(spawnPoint);
	}
}

void EnemyGenerator::UnRegistEnemy(IEnemy* enemy)
{
	//�v�f��T���o���č폜����B
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

