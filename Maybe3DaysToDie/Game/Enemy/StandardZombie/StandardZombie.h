#pragma once

class STDZombieMove;
class STDZombieTracking;
class STDZombieAttack;

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
		EnAnimationState_Attack,	//�U���B
		/*-Count-*/
		EnAnimationState_Num,
		/*-Count-*/
		EnAnimationState_Walk,		//�����B
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
	bool Start() override;
	/// <summary>
	/// �X�V�B
	/// </summary>
	void Update() override;

	/// <summary>
	/// �x���X�V�B
	/// </summary>
	void PostUpdate() override;
	/// <summary>
	/// �p�����[�^�[�l���擾�B
	/// </summary>
	/// <returns></returns>
	EnemyParams& GetEnemyParameters() override;
public://HP�֌W
	void HitDamage(int attack)
	{
		int Damage = attack - m_parameters.Deffence;
		m_parameters.Hp = max(m_parameters.Hp - Damage, 0);
	}
private:
	Vector3 m_scale = { 6.0f, 6.0f, 6.0f };		//�g��B
	IEnemy::EnemyParams m_parameters;			//�p�����[�^�[�B

	STDZombieTracking*	m_trackingState = nullptr;	//�ǐ՗p�X�e�[�g�B
	STDZombieAttack* m_attackState = nullptr;		//�U���p�X�e�[�g�B
};

