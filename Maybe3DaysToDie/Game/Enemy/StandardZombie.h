#pragma once

#include "IEnemy.h"

/// <summary>
/// �W���I�ȃ]���r�B
/// </summary>
class StandardZombie : public IEnemy
{
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
};

