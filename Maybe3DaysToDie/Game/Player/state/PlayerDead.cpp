#include "stdafx.h"
#include "PlayerDead.h"
#include <windows.h>
#include"Player/Player.h"

namespace
{
	const Vector2 BottonPos = { 0.0f,0.0f };
}
PlayerDead::PlayerDead(Player* pl):
	IPlayerState::IPlayerState(pl)
{
}
void PlayerDead::Enter()
{
	while (true) {
		int returnNo = ShowCursor(true);
		if (returnNo >= 0) {
			break;
		}
	}
	m_Font = NewGO<CFontRender>(0);
	m_Font->SetText(L"Ž€‚ñ‚¾");
	m_Font->SetColor(Vector4::Red);
	m_Font->SetShadowParam(true, 0.5f, Vector4::White);

	m_BackSprite = InitSprite("Assets/sprite/BackColor.dds");
	m_SelectSprite = InitSprite("Assets/sprite/SelectBotton.dds");
	m_BottonSprite = InitSprite("Assets/sprite/respownBotton.dds");
	m_mulSpeed = 0.0f;
}

void PlayerDead::Update()
{
	ReSpownTime -= GameTime().GetFrameDeltaTime();
    if (ReSpownTime < 0.0) {
		m_Player->ReStart();
    }
}

void PlayerDead::Leave()
{
	DeleteGO(m_Font);
	DeleteGO(m_BottonSprite);
	DeleteGO(m_BackSprite);
	DeleteGO(m_SelectSprite);
}

prefab::CSpriteRender* PlayerDead::InitSprite(const char* fileName)
{
	static int layer = 0;
	prefab::CSpriteRender* render = NewGO<prefab::CSpriteRender>(layer++);
	render->Init(fileName, 500.0f, 200.0f);
	render->SetPosition(BottonPos);
	return render;
}