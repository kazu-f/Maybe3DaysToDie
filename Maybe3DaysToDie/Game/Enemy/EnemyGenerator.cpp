#include "stdafx.h"
#include "EnemyGenerator.h"
#include "IEnemy.h"

//�B��̃C���X�^���X�B
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
	//�o�^����Ă���G�l�~�[��S�ĉ���B
	for (auto* enemy : m_enemyList) {
		DeleteGO(enemy);
	}
}

void EnemyGenerator::UnRegistEnemy(IEnemy* enemy)
{
	if (m_currentEnemyCount == 0) {
		//�ݒ�ȏ�쐬�������̍폜�����͂����ɓ���B
		//���ɉ���Regist���ōs���ĂȂ����߁A������������s��Ȃ��B
		return;
	}

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

