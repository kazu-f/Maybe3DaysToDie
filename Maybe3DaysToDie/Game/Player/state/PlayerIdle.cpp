#include "stdafx.h"
#include "PlayerIdle.h"
#include "Player/Player.h"
PlayerIdle::PlayerIdle(Player* pl):
	IPlayerState::IPlayerState(pl)
{
}

void PlayerIdle::Enter()
{
	SetMulSpeed(0.0f);
}

void PlayerIdle::Update()
{
	if (GetAsyncKeyState('A') ||
		GetAsyncKeyState('W') ||
		GetAsyncKeyState('S') ||
		GetAsyncKeyState('D') ) {
		GetPlayer()->ChengeState(Player::State::Walk);
	}
}

void PlayerIdle::Leave()
{
}
