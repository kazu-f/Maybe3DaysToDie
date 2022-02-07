#pragma once
class PlayerDead : public IGameObject
{
	bool Start()override;
	void Update()override;
	void OnDestroy()override;

	prefab::CSpriteRender* InitSprite(const char* fileName);
	CFontRender* m_Font = nullptr;
	prefab::CSpriteRender* m_BottonSprite = nullptr;
	prefab::CSpriteRender* m_SelectSprite = nullptr;
	prefab::CSpriteRender* m_BackSprite = nullptr;
};

