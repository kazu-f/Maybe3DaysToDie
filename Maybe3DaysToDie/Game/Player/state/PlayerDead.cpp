#include "stdafx.h"
#include "PlayerDead.h"
#include <windows.h>
#include"Player/Player.h"

namespace
{
	const Vector2 BottonPos = { 0.0f,0.0f };
}
PlayerDead::PlayerDead(Player* pl) :
	IPlayerState::IPlayerState(pl)
{
	m_Font = NewGO<CFontRender>(0);
	m_Font->SetText(L"死んだ");
	m_Font->SetColor(Vector4::Red);
	m_Font->SetShadowParam(true, 0.5f, Vector4::White);
	m_Font->SetActiveFlag(false);

	m_BackSprite = InitSprite("Assets/sprite/BackColor.dds");
	m_BackSprite->SetActiveFlag(false);
	m_SelectSprite = InitSprite("Assets/sprite/SelectBotton.dds");
	m_SelectSprite->SetActiveFlag(false);
	m_BottonSprite = InitSprite("Assets/sprite/respownBotton.dds");
	m_BottonSprite->SetActiveFlag(false);
	SetMulSpeed(0.0f);
}
PlayerDead::~PlayerDead()
{
	DeleteGO(m_Font);
	DeleteGO(m_BottonSprite);
	DeleteGO(m_BackSprite);
	DeleteGO(m_SelectSprite);
}
void PlayerDead::Enter()
{
	while (true) {
		int returnNo = ShowCursor(true);
		if (returnNo >= 0) {
			break;
		}
	}
	m_Font->SetActiveFlag(true);
	m_BackSprite->SetActiveFlag(true);
	m_SelectSprite->SetActiveFlag(true);
	m_BottonSprite->SetActiveFlag(true);
	GetPlayer()->SetMoveMause(true);
	SystemParametersInfo(SPI_GETWORKAREA, 0, &m_DeskRt, 0);
}

void PlayerDead::Update()
{
	// いろいろと計算
	GetWindowRect(g_hWnd, &m_MainRt);
	float sx = (m_MainRt.right - m_MainRt.left); // ウインドウの横幅
	float sy = (m_MainRt.bottom - m_MainRt.top); // ウインドウの高さ
	float cx = sx / 2 + m_MainRt.left;    // 横方向の中央座標軸
	float cy = sy / 2 + m_MainRt.top;     // 縦方向の中央座標軸
	float SpriteSizeX = ((sx) / FRAME_BUFFER_W) * 250.0f;
	float SpriteSizeY = ((sy) / FRAME_BUFFER_H) * 100.0f;
	if (MauseInfo::GetInstance()->GetMauseState() ==
		MauseInfo::State::MauseLClick) {
		int cyCaption = GetSystemMetrics(SM_CYCAPTION);     // タイトルバーの高さ
		float diffX = fabsf(MauseInfo::GetInstance()->GetMausePos().x - cx);
		float diffY = fabsf(MauseInfo::GetInstance()->GetMausePos().y - (cy + cyCaption));
		if (diffX < SpriteSizeX &&
			diffY < SpriteSizeY) {
			GetPlayer()->ReStart();
		}
	}
}

void PlayerDead::Leave()
{
	m_Font->SetActiveFlag(false);
	m_BackSprite->SetActiveFlag(false);
	m_SelectSprite->SetActiveFlag(false);
	m_BottonSprite->SetActiveFlag(false);
}

prefab::CSpriteRender* PlayerDead::InitSprite(const char* fileName)
{
	static int layer = 0;
	prefab::CSpriteRender* render = NewGO<prefab::CSpriteRender>(layer++);
	render->Init(fileName, 500.0f, 200.0f);
	render->SetPosition(BottonPos);
	return render;
}