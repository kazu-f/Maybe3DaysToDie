#pragma once

/// <summary>
/// �G�L�����̊��N���X�B
/// </summary>
/// <remarks>
/// �G�L�������쐬����ۂ́A���̃N���X���p�����č쐬���Ă������ƁB
/// </remarks>
class IEnemy : public IGameObject
{
protected:
	/// <summary>
	/// �G�l�~�[�̏������p�����[�^�[�B
	/// </summary>
	struct EnemyParams
	{
		//Status
		unsigned int Attack = 20;		//�U���́B		
		unsigned int Deffence = 5;		//�h��́B		
		unsigned int EXP = 500;			//�����o���l�B	
		float MoveSpeed = 3.0f;			//�ړ����x�B	

		//move(cm)
		float AttackRange = 150.0f;		//�U���͈́B	
		float SearchRange = 20000.0f;	//���G�͈́B	
	};
public:
	/// <summary>
	/// �f�X�g���N�^�B
	/// </summary>
	virtual ~IEnemy();
	/// <summary>
	/// �X�^�[�g�B
	/// </summary>
	/// <returns></returns>
	virtual bool Start() override = 0;
	/// <summary>
	/// �X�V�B
	/// </summary>
	virtual void Update() override = 0;

private:
	//NVM
};

