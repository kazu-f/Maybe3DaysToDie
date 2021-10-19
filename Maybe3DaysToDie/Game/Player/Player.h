#pragma once
class PlayerHp;
class PlayerStamina;
class PlayerHunger;
class PlayerWater;

class Player : public IGameObject
{
	//�z��p�̒萔
	//�Ȃ�ƂȂ��}�W�b�N�i���o�[�����������̂Œ萔��
	enum Vector {
		X, Y, Z
	};
	//�v���C���[�����X�e�[�g�̎��
	enum State {
		Idle,			//�ҋ@
		Walk,			//����
		Run,			//����
		Crouch,			//���Ⴊ��
		Jump,			//�W�����v
		Attack,			//�U��
		Num				//�X�e�[�g��
	};
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

public:
	const Vector3 GetPosition() const {
		return m_Pos;
	}
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
	Vector3 ForwardUpdate()
	{
		Matrix ModelMatrix = Matrix::Identity;
		ModelMatrix.MakeRotationFromQuaternion(m_Rot);
		//m[2]��Z��
		Vector3 ForwardModel = { ModelMatrix.m[Z][X],ModelMatrix.m[Z][Y],ModelMatrix.m[Z][Z] };
		//���K�����ĕ���������
		ForwardModel.Normalize();
		//�O������Ԃ�
		return ForwardModel;
	}
	/// <summary>
	/// ���f���̉E�������X�V���߂�l�ɓn��
	/// </summary>
	/// <returns>�E����</returns>
	Vector3 RightUpdate()
	{
		Matrix ModelMatrix = Matrix::Identity;
		ModelMatrix.MakeRotationFromQuaternion(m_Rot);
		//m[0]��X��
		Vector3 RightModel = { ModelMatrix.m[X][X],ModelMatrix.m[X][Y],ModelMatrix.m[X][Z] };
		//���K�����ĕ���������
		RightModel.Normalize();

		//�E������Ԃ�
		return RightModel;
	}

private:
	////////////���f��/////////////////////////////////////////////
	prefab::ModelRender* m_Model = nullptr;		//�v���C���[���f��
	Vector3 m_Pos = { 0.0f,170.0f,500.0f };
	Quaternion m_Rot = Quaternion::Identity;
	Vector3 m_Scale = Vector3::One;
	CCharacterController m_Characon;
	///////////////////////////////////////////////////////////////

	/////�̗�//////////////////////////////////////////////////////
	PlayerHp* m_Hp = nullptr;
	///////////////////////////////////////////////////////////////

	/////�X�^�~�i/////////////////////////////////////////////////
	PlayerStamina* m_Stamina = nullptr;
	///////////////////////////////////////////////////////////////

	/////��//////////////////////////////////////////////////////
	PlayerHunger* m_Hunger = nullptr;
	///////////////////////////////////////////////////////////////

	/////����//////////////////////////////////////////////////////
	PlayerWater* m_Water = nullptr;
	///////////////////////////////////////////////////////////////
	State m_State = State::Idle;
	float m_DeltaTime = 0.0f;
};

