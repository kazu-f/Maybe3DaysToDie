#include "stdafx.h"
#include "PlayerIdle.h"
#include "Player/Player.h"
PlayerIdle::PlayerIdle(Player* pl):
	IPlayerState::IPlayerState(pl)
{
}

void PlayerIdle::Enter()
{
	SetMulSpeed(1.0f);
	GetPlayer()->SetMoveMause(false);
}

void PlayerIdle::Update()
{
	if (GetAsyncKeyState('A') ||
		GetAsyncKeyState('W') ||
		GetAsyncKeyState('S') ||
		GetAsyncKeyState('D') ) {
		GetPlayer()->ChengeState(Player::State::Walk);
	}
	GetPlayer()->Jump();
}

void PlayerIdle::Leave()
{
}
