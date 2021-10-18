#include "stdafx.h"
#include "GameSnece.h"
#include "GameCamera.h"
#include "Player/Player.h"
#include "Stage.h"

#include "PlacementObject/PlacementObject.h"
#include "DateTime.h"
#include "Enemy/StandardZombie.h"
bool GameSnece::Start()
{
	m_Player = NewGO<Player>(0, "player");
	m_Camera = NewGO<GameCamera>(0, "camera");
	m_Stage = NewGO<Stage>(0, "stage");
	m_PlacementObject = NewGO<PlacementObject>(1);
	DateTime* Data = NewGO<DateTime>(0, "dateTime");
	
	//sample//
	m_fontRender = NewGO<CFontRender>(0);
	m_fontRender->SetText(L"Reo is AHO.\nReo is Baka\nReo is UNKO\nHima is Neet");
	m_fontRender->SetColor({ 1.0f, 0.0f, 0.0f, 1.0f });
	m_fontRender->SetShadowParam(true, 0.5f, Vector4::Black);
	m_fontRender->SetPivot({ 0.0f, 0.5f });
	m_fontRender->SetPosition({ -630.0f, 350.0f });
	NewGO<StandardZombie>(0);

	return true;
}

void GameSnece::OnDestroy()
{
	DeleteGO(m_Player); 
	DeleteGO(m_Camera);
	DeleteGO(m_Stage);
	if (m_PlacementObject != nullptr)
	{
		DeleteGO(m_PlacementObject);
		m_PlacementObject = nullptr;
	}

	//sample//
	DeleteGO(m_fontRender);
}
