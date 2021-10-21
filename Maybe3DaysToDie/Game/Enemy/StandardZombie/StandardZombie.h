#pragma once

class STDZombieMove;

#include "Enemy/IEnemy.h"

/// <summary>
/// �W���I�ȃ]���r�B
/// </summary>
class StandardZombie : public IEnemy
{
public:
	/// <summary>
	/// �A�j���[�V����enum�B
	/// <para>�}�W�b�N�i���o�[�_����΁B</para>
	/// </summary>
	enum EnAnimationState {
		EnAnimationState_Idle,		//idle
		EnAnimationState_Run,		//����B
		/*-Count-*/
		EnAnimationState_Num,
		/*-Count-*/
		EnAnimationState_Walk,		//�����B
		EnAnimationState_Attack,	//�U���B
		EnAnimationState_Damage,	//�_���[�W�B
		EnAnimationState_Stun,		//�X�^���B
		EnAnimationState_Death,		//���S�B

	};
public:
	/// <summary>
	/// �R���X�g���N�^�B
	/// </summary>
	StandardZombie() {};
public:
	/// <summary>
	///	�X�^�[�g�B
	/// </summary>
	/// <returns></returns>
	bool Start() override final;
	/// <summary>
	/// �X�V�B
	/// </summary>
	void Update() override final;
	/// <summary>
	/// �p�����[�^�[�l���擾�B
	/// </summary>
	/// <returns></returns>
	EnemyParams& GetEnemyParameters() override;
private:
	Vector3 m_scale = { 6.0f, 6.0f, 6.0f };		//�g��B
	IEnemy::EnemyParams m_parameters;			//�p�����[�^�[�B

	STDZombieMove* m_moveState = nullptr;		//�ړ��p�X�e�[�g�B
};

