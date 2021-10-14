#pragma once
class DestructibleObject
{
public:
	DestructibleObject() {}
	virtual ~DestructibleObject() {}

	/// <summary>
	/// �|�W�V�������Q�b�g
	/// </summary>
	/// <returns>�I�u�W�F�N�g�̃|�W�V����</returns>
	const Vector3 GetPosition()const
	{
		return m_position;
	}

	/// <summary>
	/// ���[�e�[�V�������Q�b�g
	/// </summary>
	/// <returns>�I�u�W�F�N�g�̉�]</returns>
	const Quaternion GetRotation()const
	{
		return m_qrot;
	}

	/// <summary>
	/// �X�P�[�����Q�b�g
	/// </summary>
	/// <returns>�I�u�W�F�N�g�̃X�P�[��</returns>
	const Vector3 GetScale()const
	{
		return m_scale;
	}


protected:
	
	Vector3 m_position = Vector3::Zero;
	Quaternion m_qrot = Quaternion::Identity;
	Vector3 m_scale = Vector3::One;
};

