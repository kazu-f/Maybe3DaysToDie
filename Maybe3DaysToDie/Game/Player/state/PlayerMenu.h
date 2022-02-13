#pragma once
#include "IPlayerState.h"
class Player;
class PlayerMenu : public IPlayerState
{
public:
	PlayerMenu(Player* pl);
	~PlayerMenu() {}

	void Enter()override final;
	void Update()override final;
	void Leave()override final;
};

