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
	
	Vector3 GetMoveSpeed()const {
		return m_MoveSpeed;
	}
	
	void SetMoveSpeedY(float MoveSpeed) {
		m_MoveSpeed.y = MoveSpeed;
	}

	float GetMulSpeed()const {
		return m_mulSpeed;
	}
protected:
	float m_mulSpeed = 0.0f;
	Player* m_Player = nullptr;
	Vector3 m_MoveSpeed = Vector3::Zero;
};

