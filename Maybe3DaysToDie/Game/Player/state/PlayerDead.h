#pragma once
#include "IPlayerState.h"
class PlayerDead : public IPlayerState
{
	PlayerDead(Player* pl);
	PlayerDead();
	void Enter()override final;
	void Update()override final;
	void Leave()override final;

	prefab::CSpriteRender* InitSprite(const char* fileName);
	CFontRender* m_Font = nullptr;
	prefab::CSpriteRender* m_BottonSprite = nullptr;
	prefab::CSpriteRender* m_SelectSprite = nullptr;
	prefab::CSpriteRender* m_BackSprite = nullptr;

	int ReSpownTime = 1.0f;
};