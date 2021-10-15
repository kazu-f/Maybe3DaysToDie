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
	bool Start() override;
	/// <summary>
	/// �X�V�B
	/// </summary>
	void Update() override;
	/// <summary>
	/// �p�����[�^�[�l���擾�B
	/// </summary>
	/// <returns></returns>
	EnemyParams& GetEnemyParameters() override;
private:
	Vector3 m_scale = { 3.5f, 3.5f, 3.5f };
	IEnemy::EnemyParams m_parameters;
};

