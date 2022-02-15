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
		m_enemyList.push_back(enemy);
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

