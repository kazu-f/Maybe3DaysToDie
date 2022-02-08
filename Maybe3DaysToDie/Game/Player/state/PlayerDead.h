#pragma once
#include "IPlayerState.h"
class PlayerDead : public IPlayerState
{
	void Init()override;
	void Update()override;
	void Delete()override;

	prefab::CSpriteRender* InitSprite(const char* fileName);
	CFontRender* m_Font = nullptr;
	prefab::CSpriteRender* m_BottonSprite = nullptr;
	prefab::CSpriteRender* m_SelectSprite = nullptr;
	prefab::CSpriteRender* m_BackSprite = nullptr;
	int ReSpownTime = 1.0f;
};