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
protected:
	float m_mulSpeed = 0.0f;
	Player* m_Player = nullptr;
public:
	float GetMulSpeed()const {
		return m_mulSpeed;
	}
};

