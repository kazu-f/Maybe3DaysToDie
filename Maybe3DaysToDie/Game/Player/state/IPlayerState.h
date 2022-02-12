#pragma once
class Player;
class IPlayerState
{
public:
	IPlayerState(Player* pl) :m_Player(pl) {}
	virtual ~IPlayerState() {}
	virtual void Enter() = 0;
	virtual	void Update() = 0;
	virtual void Leave() = 0;
	void Move();
	void ExcuteMove();
	/// <summary>
	/// �f�o�b�O���[�h��؂�ւ���֐�
	/// </summary>
	void SwichDebugMode();

	/// <summary>
	/// �ړ����x��ݒ�
	/// </summary>
	/// <param name="mul">�ړ����x</param>
	void SetMulSpeed(float mul) {
		m_mulSpeed = mul;
	}

	/// <summary>
	/// �ړ����x���擾
	/// </summary>
	/// <returns>�ړ����x</returns>
	float GetMulSpeed()const {
		return m_mulSpeed;
	}

	/// <summary>
	/// �v���C���[�̃|�C���^���擾
	/// </summary>
	/// <returns>�v���C���[�̃|�C���^</returns>
	Player* GetPlayer() const {
		return m_Player;
	}

	/// <summary>
	/// �ړ��ʂ�ݒ�
	/// </summary>
	/// <param name="Move">�����������x�N�g��</param>
	void SetMoveSpeed(const Vector3& Move) {
		m_MoveSpeed = Move;
	}

	/// <summary>
	/// �ړ��ʂ�Y�����݂̂�ݒ肷��
	/// </summary>
	/// <param name="MoveSpeed">�ړ���Y</param>
	void SetMoveSpeedY(float MoveSpeed) {
		m_MoveSpeed.y = MoveSpeed;
	}

	Vector3 GetMoveSpeed()const {
		return m_MoveSpeed;
	}
private:
	float m_mulSpeed = 0.0f;
	Player* m_Player = nullptr;
	Vector3 m_MoveSpeed = Vector3::Zero;
};

