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
	Vector3 Move();
	
	Vector3 GetMoveSpeed()const {
		return m_MoveSpeed;
	}
	
	void SetMoveSpeed(Vector3& MoveSpeed) {
		m_MoveSpeed = MoveSpeed;
	}

	float GetMulSpeed()const {
		return m_mulSpeed;
	}

protected:
	float m_mulSpeed = 0.0f;
	Player* m_Player = nullptr;
	Vector3 m_MoveSpeed = Vector3::Zero;
};

