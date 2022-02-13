#include "stdafx.h"
#include "PlayerMenu.h"
#include "Player/Player.h"

PlayerMenu::PlayerMenu(Player* pl):
	IPlayerState(pl)
{
}

void PlayerMenu::Enter()
{
	SetMulSpeed(1.0f);
	GetPlayer()->SetMoveMause(true);
}

void PlayerMenu::Update()
{

}

void PlayerMenu::Leave()
{
}
