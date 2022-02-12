#include "stdafx.h"
#include "PlayerWalk.h"
#include "Player/Player.h"

PlayerWalk::PlayerWalk(Player* pl):
	IPlayerState(pl)
{
}

void PlayerWalk::Enter()
{
	SetMulSpeed(1.0f);
}

void PlayerWalk::Update()
{
	Move();
	SwichDebugMode();
	if (GetAsyncKeyState(VK_LSHIFT) &&
		GetMoveSpeed().Length() > 0.5f &&
		GetPlayer()->UseStamina(1))
	{
		SetMulSpeed(2.0f);
	}
	else {
		SetMulSpeed(1.0f);
	}
}

void PlayerWalk::Leave()
{
}
