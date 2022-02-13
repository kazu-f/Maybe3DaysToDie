#pragma once
#include "Player/state/IPlayerState.h"
class PlayerWalk : public IPlayerState
{
public:
	PlayerWalk(Player* pl);

	void Enter()override final;
	void Update()override final;
	void Leave()override final;
};

