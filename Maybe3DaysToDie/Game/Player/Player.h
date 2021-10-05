#pragma once
class GameCamera;
class PlayerHp;
class PlayerStamina;

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
private:
	/// <summary>
	/// GameObject�ɐς܂��ƈ�x�����Ă΂�鏉�����֐�
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

private:
	/// <summary>
	/// ���Ԃɂ��X�e�[�^�X�̍X�V
	/// </summary>
	void PeriodicUpdate();

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

	/// <summary>
	/// ���f���̈ړ�����
	/// </summary>
	void Move();

	/// <summary>
	/// ���f���̉�]����
	/// </summary>
	void Rotation();

	/// <summary>
	/// ���f�����X�V
	/// </summary>
	void ModelUpdate();

	/// <summary>
	/// ���f���̑O�������X�V���߂�l�ɓn��
	/// </summary>
	///<returns>�O����</returns>
	Vector3 ForwardUpdate();
	/// <summary>
	/// ���f���̉E�������X�V���߂�l�ɓn��
	/// </summary>
	/// <returns>�E����</returns>
	Vector3 RightUpdate();

	/// <summary>
	/// �J������ݒ�
	/// </summary>
	void SetCamera();
private:
	////////////���f��/////////////////////////////////////////////
	prefab::ModelRender* m_Model = nullptr;		//�v���C���[���f��
	Vector3 m_Pos = { 0.0f,100.0f,500.0f };
	Quaternion m_Rot = Quaternion::Identity;
	Vector3 m_Scale = Vector3::One;
	///////////////////////////////////////////////////////////////
	
	/////�̗�//////////////////////////////////////////////////////
	PlayerHp* m_Hp = nullptr;
	///////////////////////////////////////////////////////////////

	/////�X�^�~�i/////////////////////////////////////////////////
	PlayerStamina* m_Stamina = nullptr;
	///////////////////////////////////////////////////////////////
	int m_Hunger = 100;
	int m_water = 100;
	State m_State = State::Idle;
	float m_DeltaTime = 0.0f;

	/// �}�E�X/////////////////////////////////////////////////////////
	float MouseRotX = 0.0f;
	float MouseRotY = 0.0f;
	int DefaultPoint[2] = { 500,300 };
	float m_SensiX = 0.02f;
	float m_SensiY = 0.02f;
	float m_RotAngle[2] = { 0.0f,0.0f };
	///////////////////////////////////////////////////////////////////
	
	///////�J����//////////////////////////////////////////////////////
	GameCamera* m_Camera = nullptr;
	///////////////////////////////////////////////////////////////////
};

