#include "stdafx.h"
#include "Player.h"


bool Player::Start()
{

	return true;
}

void Player::Update()
{
	PeriodicUpdate();
	StateUpdate();
}

void Player::OnDestroy()
{
}

void Player::PeriodicUpdate()
{
	HpRegene();
	StaminaRegene();
	HungerDecrease();
	WarterDecrease();
	m_DeltaTime += GameTime().GetFrameDeltaTime();
	m_nowHpRegeneTimer += GameTime().GetFrameDeltaTime();
}

void Player::HpRegene()
{
	if (m_nowHpRegeneTimer >= m_HpRegeneTime)
	{
		hp++;
		m_nowHpRegeneTimer -= m_HpRegeneTime;
	}
}

void Player::StaminaRegene()
{
}

void Player::HungerDecrease()
{
}

void Player::WarterDecrease()
{
}

void Player::StateUpdate()
{
	ChangeState();
}

void Player::ChangeState()
{
}
