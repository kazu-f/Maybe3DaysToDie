#include "stdafx.h"
#include "GameSnece.h"
#include "GameCamera.h"
#include "Player.h"
#include "Stage.h"


bool GameSnece::Start()
{
	m_Player = NewGO<Player>(0, "player");
	m_Camera = NewGO<GameCamera>(0, "camera");
	m_Stage = NewGO<Stage>(0, "stage");

	//sample//
	m_fontRender = NewGO<CFontRender>(0);
	m_fontRender->SetText(L"Reo is AHO.\nReo is Baka\nReo is UNKO");
	m_fontRender->SetColor({ 1.0f, 0.0f, 0.0f, 1.0f });
	m_fontRender->SetShadowParam(true, 0.5f, Vector4::Black);
	m_fontRender->SetPivot({ 0.0f, 0.5f });
	m_fontRender->SetPosition({ -630.0f, 350.0f });
	return true;
}

void GameSnece::OnDestroy()
{
	DeleteGO(m_Player); 
	DeleteGO(m_Camera);
	DeleteGO(m_Stage);

	//sample//
	DeleteGO(m_fontRender);
}
