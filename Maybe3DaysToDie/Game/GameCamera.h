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

	/// <summary>
	/// �}�E�X�𓮂��������Ƃ��̊֐�
	/// true�Ń}�E�X�𓮂�����
	/// </summary>
	/// <param name="isMoving">�������܂����H</param>
	void SetMovingMouse(const bool isMoving) {
		m_IsMovingMouse = isMoving;
	}
private:
	Vector3 m_Pos = { 0.0f, 1000.0f, 0.0f };	//�ʒu
	Vector3 m_Target = { 0.0f,1000.0f,100.0f};			//�^�[�Q�b�g
	Quaternion m_qrot = Quaternion::Identity;
	const float m_CameraDist = 100.0f;

	//�Z���V
	float SensiX = 0.1f;
	float SensiY = 0.1f;
	//�J�����̐���
	const float xrotLimit = 360.0f;
	const float yrotLimit = 85.0f;
	//���݂̉�]
	float xrot = 0.0f;
	float yrot = 0.0f;
	//�J�����̍���
	float CameraHeight = 170.0f;

	bool m_IsMovingMouse = false;	//�}�E�X���������邩
};

