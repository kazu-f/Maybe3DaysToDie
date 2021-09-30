#pragma once
enum State {
	Idle,			//�ҋ@
	Walk,			//����
	Run,			//����
	Crouch,			//���Ⴊ��
	Jump,			//�W�����v
	Attack,			//�U��
	Num				//�X�e�[�g��
};
class Player : public IGameObject
{
	/// <summary>
	/// ������
	/// </summary>
	/// <returns>true���Ԃ�܂Ń��[�v����</returns>
	bool Start()override final;

	/// <summary>
	/// �X�V
	/// </summary>
	void Update()override final;

	/// <summary>
	/// delete�����ƌĂ΂��֐�
	/// </summary>
	void OnDestroy()override final;

	/// <summary>
	/// ���Ԃɂ��X�e�[�^�X�̍X�V
	/// </summary>
	void PeriodicUpdate();

	/// <summary>
	/// �̗͂����Ԃɂ���ĉ񕜂���
	/// </summary>
	void HpRegene();

	/// <summary>
	/// �X�^�~�i�����Ԃɂ���ĉ񕜂���
	/// </summary>
	void StaminaRegene();

	/// <summary>
	/// �������󂢂�
	/// </summary>
	void HungerDecrease();

	/// <summary>
	/// �A��������
	/// </summary>
	void WarterDecrease();

	/// <summary>
	/// IPlayerState��Update���Ă�
	/// </summary>
	void StateUpdate();

	/// <summary>
	/// IPlayerState���X�V
	/// </summary>
	void ChangeState();
private:
	prefab::ModelRender* m_Model = nullptr;		//�v���C���[���f��
	int m_Hp = 100;								//�̗�
	float m_Stamina = 100.0f;					//
	float m_HpRegeneTime = 1.0f;
	float m_nowHpRegeneTimer = 0.0f;
	int m_Hunger = 100;
	int m_water = 100;
	State m_State = State::Idle;
	float m_DeltaTime = 0.0f;
};

