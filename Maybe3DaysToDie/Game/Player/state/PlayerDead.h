#pragma once
#include "IPlayerState.h"
class PlayerDead : public IPlayerState
{
public:
	PlayerDead(Player* pl); 
	~PlayerDead();
	void Enter()override final;
	void Update()override final;
	void Leave()override final;

private:
	prefab::CSpriteRender* InitSprite(const char* fileName);
	CFontRender* m_Font = nullptr;
	prefab::CSpriteRender* m_BottonSprite = nullptr;
	prefab::CSpriteRender* m_SelectSprite = nullptr;
	prefab::CSpriteRender* m_BackSprite = nullptr;

	float m_ReSpownTime = 2.0f;
	RECT m_MainRt;				//�E�B���h�E���
	RECT m_DeskRt;				//�f�X�N�g�b�v���
};