#pragma once

class IEnemy;

/// <summary>
/// �G�l�~�[�̃X�e�[�g�̊��N���X�B
/// </summary>
class IEnemyState
{
public:
	/// <summary>
	/// �R���X�g���N�^�B
	/// </summary>
	/// <param name="enemy">�G�l�~�[�B</param>
	IEnemyState(IEnemy* enemy)
		:m_enemy(enemy)
	{
	}
	//virtual ~IEnemyState();
	/// <summary>
	/// �X�e�[�g���ꎞ�ɌĂ΂��B
	/// </summary>
	virtual void Enter() = 0;
	/// <summary>
	/// �X�e�[�g�ޏꎞ�ɌĂ΂��B
	/// </summary>
	virtual void Leave() = 0;
	/// <summary>
	/// �X�V�B
	/// </summary>
	virtual void Update() = 0;
protected:
	IEnemy* m_enemy = nullptr;
};

