#pragma once
class GameCamera : public IGameObject
{
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
		ModelMatrix.MakeRotationFromQuaternion(m_qrot);
		//m[2]��Z��
		Vector3 Forward = { ModelMatrix.m[2][0],ModelMatrix.m[2][1],ModelMatrix.m[2][2] };
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
		ModelMatrix.MakeRotationFromQuaternion(m_qrot);
		ModelMatrix = MainCamera().GetCameraRotation();
		//m[0]��X��
		Vector3 Right = { ModelMatrix.m[0][0],ModelMatrix.m[0][1],ModelMatrix.m[0][2] };
		//���K�����ĕ���������
		Right.Normalize();
		//�E������Ԃ�
		return Right;
	}

	/// <summary>
	/// �J�����̉�]���}�E�X����ł���
	/// </summary>
	void Rotate();

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

private:
	Vector3 m_Pos = { 0.0f, 1000.0f, 0.0f };	//�ʒu
	Vector3 m_Target = { 0.0f,1000.0f,100.0f};			//�^�[�Q�b�g
	Quaternion m_qrot = Quaternion::Identity;
	const float m_CameraDist = 100.0f;
	///�}�E�X/////////////////////////////////////////////////////////
	float MouseRotX = 0.0f;
	float MouseRotY = 0.0f;
	int DefaultPoint[2] = { 500,300 };
	///////////////////////////////////////////////////////////////////
	//�Z���V
	float SensiX = 0.1f;
	float SensiY = 0.1f;
	//�J�����̐���
	const float rotLimit = 90.0f;
	//���݂̉�]
	float rot = 0.0f;
};

