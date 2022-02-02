#pragma once

#include "NaviMeshManager.h"

class IEnemy;
class Stage;

/// <summary>
/// �G�l�~�[�𐶐�����I�u�W�F�N�g�B
/// </summary>
class EnemyGenerator
{
public:
	/// <summary>
	/// �R���X�g���N�^�B
	/// </summary>
	EnemyGenerator();
	/// <summary>
	/// �f�X�g���N�^�B
	/// </summary>
	~EnemyGenerator();
public:
	/// <summary>
	/// �S�G�l�~�[������B
	/// </summary>
	void ReleaseEnemy();

	/// <summary>
	/// �G���쐬����B
	/// <para>T = Enemy�̔h���N���X�B</para>
	/// </summary>
	/// <param name="nvmGenerator">�o�H�T��������ꍇnvmGenerator�B</param>
	/// <param name="tag">IGameObject�o�^�^�O�B</param>
	template<class T>
	void Create(const char* tag = "Enemy")
	{
		if (m_currentEnemyCount >= MAX_ENEMY) {
			//�G�l�~�[��ݒ�ȏ�ɍ쐬�g�p�Ƃ��Ă���ׁA���N�G�X�g�͋����Ȃ��B
			MessageBoxA(NULL, "�G�l�~�[�̋��e�ʂ𒴂��܂����A���̃I�u�W�F�N�g�͍폜����܂��B", "Warning!!", MB_OK);
			return;
		}

		//�C���X�^���X���B
		IEnemy* enemy = NewGO<T>(0 ,tag);
		//�G�l�~�[�Ƒ��ΎQ�ƂɁB
		enemy->SetEnemyGenerator(this);
		//nvm.
		enemy->SetNVMGenerator(m_stage);
		//���X�g�ɐςݐς݁B
		m_enemyList.push_back(enemy);
		m_currentEnemyCount++;

		if (m_isActiveBloodMoon) {
			//�u���b�h���[�����̏�����ǉ�����B
		}
	}
	/// <summary>
	/// �G�l�~�[�̓o�^����������B
	/// </summary>
	/// <param name="enemy"></param>
	void UnRegistEnemy(IEnemy* enemy);
	/// <summary>
	/// �u���b�h���[����L��������B
	/// <para>�S�]���r�ɍ��G�͈͂Ɋւ�炸�APlayer�܂ŒT��������B</para>
	/// </summary>
	void ActivateBloodMoonHode();
	/// <summary>
	/// �u���b�h���[���𖳌����B
	/// </summary>
	void DisableBloodMoonHode();

	/// <summary>
	/// �X�e�[�W��ݒ�B
	/// </summary>
	/// <param name="stage"></param>
	void SetStage(Stage* stage)
	{
		m_stage = stage;
	}
private:
	/* Const */
	static const int MAX_ENEMY = 16;		//�Ǘ��ł���ő�G�l�~�[���B
	Stage* m_stage = nullptr;

	/* EnemyManagement */
	int m_currentEnemyCount = 0;			//���݁A���݂��Ă���G�l�~�[�̐��B
	std::vector<IEnemy*> m_enemyList;		//�G�l�~�[�̃��X�g�B

	/* bloodMoon */
	bool m_isActiveBloodMoon = false;		//�u���b�h���[�����L���H
	
};

