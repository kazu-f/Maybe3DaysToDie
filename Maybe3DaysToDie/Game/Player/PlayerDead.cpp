#include "stdafx.h"
#include "PlayerDead.h"

namespace
{
	const Vector2 BottonPos = { 0.0f,0.0f };
}

bool PlayerDead::Start()
{
	m_Font = NewGO<CFontRender>(0);
	m_Font->SetText(L"Ž€‚ñ‚¾");
	m_Font->SetColor(Vector4::Red);
	m_Font->SetShadowParam(true, 0.5f, Vector4::White);
	m_BottonSprite = InitSprite("Assets/sprite/respownBotton.dds");

	m_BackSprite = InitSprite("Assets/sprite/BackColor.dds");

	m_SelectSprite = InitSprite("Assets/sprite/SelectBotton.dds");
    return true;
}

void PlayerDead::Update()
{
	POINT MausePoint;
	GetCursorPos(&MausePoint);
	if (fabsf(MausePoint.x) > 150.0f && fabsf(MausePoint.y) > 50.0f) {
		DeleteGO(this);
	}
}

void PlayerDead::OnDestroy()
{
	DeleteGO(m_Font);
	DeleteGO(m_BottonSprite);
	DeleteGO(m_BackSprite);
	DeleteGO(m_SelectSprite);
}

prefab::CSpriteRender* PlayerDead::InitSprite(const char* fileName)
{
	prefab::CSpriteRender* render = NewGO<prefab::CSpriteRender>(0);
	render->Init(fileName, 500.0f, 200.0f);
	render->SetPosition(BottonPos);
	return render;
}
