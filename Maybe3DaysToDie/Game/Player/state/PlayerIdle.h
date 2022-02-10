#pragma once
#include "Player/state/IPlayerState.h"
class PlayerIdle : public IPlayerState
{
public:
	PlayerIdle(Player* pl);
	void Enter()override final;
	void Update()override final;
	void Leave()override final;
};

