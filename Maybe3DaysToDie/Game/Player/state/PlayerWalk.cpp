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
	GetPlayer()->SetMoveMause(false);
}

void PlayerWalk::Update()
{
	SwichDebugMode();
	float Len = GetMoveSpeed().Length();
	if (Len > 0.1f) {
		if (GetAsyncKeyState(VK_LSHIFT) &&
			GetPlayer()->UseStamina(1))
		{
			SetMulSpeed(2.0f);
		}
	}
	else {
		SetMulSpeed(1.0f);
	}
	if (GetPlayer()->IsDebugMode()) {
		SetMulSpeed(2.0f);
	}
	Move();
	GetPlayer()->Jump();
}

void PlayerWalk::Leave()
{
}
