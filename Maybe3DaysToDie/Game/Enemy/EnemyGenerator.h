#pragma once

/// <summary>
/// �G�l�~�[�𐶐�����I�u�W�F�N�g�B
/// </summary>
class EnemyGenerator : public IGameObject
{
public:
	/// <summary>
	/// �R���X�g���N�^�B
	/// </summary>
	EnemyGenerator();
public:
	/// <summary>
	/// �X�^�[�g�B
	/// </summary>
	/// <returns></returns>
	bool Start() override;
	/// <summary>
	/// �f���[�g�B
	/// </summary>
	void OnDestroy() override;
	/// <summary>
	/// �X�V�B
	/// </summary>
	void Update() override;
private:
	int m_currentEnemyCount = 0;		//���݁A���݂��Ă���G�l�~�[�̐��B
	
};

