#pragma once
class GameCamera : public IGameObject
{
private:
	/// <summary>
	/// GameObject�ɐς܂��ƈ�x�����Ă΂�鏉�����֐�
	/// </summary>
	/// <returns>true���Ԃ�܂Ń��[�v����</returns>
	bool Start();
	/// <summary>
	/// �X�V
	/// </summary>
	void Update();
	/// <summary>
	/// delete�����ƌĂ΂��֐�
	/// </summary>
	void OnDestroy();
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
	const Vector3 GetPosition() {
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
	const Vector3 GetTarget() {
		return m_Target;
	}
private:

	Vector3 m_Pos = { 0.0f, 200.0f, 500.0f };	//�ʒu
	Vector3 m_Target = Vector3::Zero;			//�^�[�Q�b�g
};

