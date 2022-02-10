#include "stdafx.h"
#include "PlayerIdle.h"

PlayerIdle::PlayerIdle(Player* pl):
	IPlayerState::IPlayerState(pl)
{
}

void PlayerIdle::Enter()
{
	m_mulSpeed = 0.0f;
}

void PlayerIdle::Update()
{
	if (GetAsyncKeyState('A') ||
		GetAsyncKeyState('W') ||
		GetAsyncKeyState('S') ||
		GetAsyncKeyState('D') ) {

	}
}

void PlayerIdle::Leave()
{
}
