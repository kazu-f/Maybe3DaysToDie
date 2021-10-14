#pragma once
class DestructibleObject
{
public:
	DestructibleObject() {}
	virtual ~DestructibleObject() {}

	/// <summary>
	/// ポジションをゲット
	/// </summary>
	/// <returns>オブジェクトのポジション</returns>
	const Vector3 GetPosition()const
	{
		return m_position;
	}

	/// <summary>
	/// ローテーションをゲット
	/// </summary>
	/// <returns>オブジェクトの回転</returns>
	const Quaternion GetRotation()const
	{
		return m_qrot;
	}

	/// <summary>
	/// スケールをゲット
	/// </summary>
	/// <returns>オブジェクトのスケール</returns>
	const Vector3 GetScale()const
	{
		return m_scale;
	}


protected:
	
	Vector3 m_position = Vector3::Zero;
	Quaternion m_qrot = Quaternion::Identity;
	Vector3 m_scale = Vector3::One;
};

