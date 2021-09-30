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
	return true;
}

void GameSnece::OnDestroy()
{
	DeleteGO(m_Player); 
	DeleteGO(m_Camera);
	DeleteGO(m_Stage);
}
