#pragma once
class Player;
class GameCamera : public IGameObject
{
	//�z��p�̒萔
	//�Ȃ�ƂȂ��}�W�b�N�i���o�[�����������̂Œ萔��
	enum Vector {
		X, Y, Z
	};
private:
	/// <summary>
	/// GameObject�ɐς܂��ƈ�x�����Ă΂�鏉�����֐�
	/// </summary>
	/// <returns>true���Ԃ�܂Ń��[�v����</returns>
	bool Start() override final;
	/// <summary>
	/// �X�V
	/// </summary>
	void Update() override final;
	/// <summary>
	/// delete�����ƌĂ΂��֐�
	/// </summary>
	void OnDestroy() override final;
private:
	/// <summary>
	/// ���f���̑O�������X�V���߂�l�ɓn��
	/// </summary>
	///<returns>�O����</returns>
	const Vector3 ForwardUpdate()const
	{
		Matrix ModelMatrix = Matrix::Identity;
		ModelMatrix.MakeRotationFromQuaternion(m_Rot);
		//m[2]��Z��
		Vector3 Forward = { ModelMatrix.m[Z][X],ModelMatrix.m[Z][Y],ModelMatrix.m[Z][Z] };
		//���K�����ĕ���������
		Forward.Normalize();
		//�O������Ԃ�
		return Forward;
	}
	/// <summary>
	/// ���f���̉E�������X�V���߂�l�ɓn��
	/// </summary>
	/// <returns>�E����</returns>
	const Vector3 RightUpdate()const
	{
		Matrix ModelMatrix = Matrix::Identity;
		ModelMatrix.MakeRotationFromQuaternion(m_Rot);
		ModelMatrix = MainCamera().GetCameraRotation();
		//m[0]��X��
		Vector3 Right = { ModelMatrix.m[X][X],ModelMatrix.m[X][Y],ModelMatrix.m[X][Z] };
		//���K�����ĕ���������
		Right.Normalize();
		//�E������Ԃ�
		return Right;
	}

	/// <summary>
	/// �J�����̉�]���}�E�X����ł���
	/// </summary>
	void Rotate();

	/// <summary>
	/// �J�������ړ�������
	/// </summary>
	void Move();

	/// <summary>
	/// �J�����̑����؂�ւ���
	/// </summary>
	void IsSwichOperation();
public:
	/// <summary>
	/// �ʒu��ݒ�
	/// </summary>
	/// <param name="pos">�J�����ʒu</param>
	void SetPosition(const Vector3& pos) {
		m_Pos = pos;
	}
	/// <summary>
	/// �ʒu���擾
	/// </summary>
	/// <returns>�J�����ʒu</returns>
	const Vector3 GetPosition() const {
		return m_Pos;
	}
	/// <summary>
	/// �^�[�Q�b�g��ݒ�
	/// </summary>
	/// <param name="tar">�J�����^�[�Q�b�g</param>
	void SetTarget(const Vector3& tar) {
		m_Target = tar;
	}
	/// <summary>
	/// �^�[�Q�b�g���擾
	/// </summary>
	/// <returns>�J�����^�[�Q�b�g</returns>
	const Vector3 GetTarget() const {
		return m_Target;
	}

	void Debug()
	{
		static float OldRotAngle = m_RotAngle[X];
		if (m_RotAngle[X] != OldRotAngle) {
			int i = 0;
			i++;
			OldRotAngle = m_RotAngle[X];
		}
	}
private:
	Player* m_Player = nullptr;					//�v���C���[�|�C���^

	bool m_IsChasePlayer = false;
	Vector3 m_Pos = { 0.0f, 200.0f, 500.0f };	//�ʒu
	Quaternion m_Rot = Quaternion::Identity;	//��]
	Vector3 m_Target = { 0.0f,-200.0f,-500.0f };			//�^�[�Q�b�g

	///�}�E�X/////////////////////////////////////////////////////////
	float MouseRotX = 0.0f;
	float MouseRotY = 0.0f;
	int DefaultPoint[2] = { 500,300 };
	float m_SensiX = 0.00025f;
	float m_SensiY = 0.15f;
	float m_RotAngle[2] = { 0.0f,0.0f };
	///////////////////////////////////////////////////////////////////

	float rot = 0.0f;
	float AddPosY = 0.0f;
};

