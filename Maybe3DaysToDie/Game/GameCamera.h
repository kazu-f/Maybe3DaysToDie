#pragma once
class Player;
//�z��p�̒萔
//�Ȃ�ƂȂ��}�W�b�N�i���o�[�����������̂Œ萔��
enum Vector {
	X, Y, Z
};
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
	const Vector3 ForwardUpdate()
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
	const Vector3 RightUpdate()
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
private:
	Player* m_Player = nullptr;					//�v���C���[�|�C���^

	bool m_IsChasePlayer = false;
	Vector3 m_Pos = { 0.0f, 200.0f, 500.0f };	//�ʒu
	Quaternion m_Rot = Quaternion::Identity;	//��]
	Vector3 m_Target = Vector3::Zero;			//�^�[�Q�b�g
};

