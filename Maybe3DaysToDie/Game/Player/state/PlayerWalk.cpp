#include "stdafx.h"
#include "PlayerWalk.h"

PlayerWalk::PlayerWalk(Player* pl):
	IPlayerState(pl)
{
}

void PlayerWalk::Enter()
{
	m_mulSpeed = 1.0f;
}

void PlayerWalk::Update()
{
	Move();
}

void PlayerWalk::Leave()
{
}
