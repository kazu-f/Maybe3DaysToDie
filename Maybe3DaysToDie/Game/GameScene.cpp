#include "stdafx.h"
#include "GameScene.h"
#include "GameCamera.h"
#include "Player/Player.h"
#include "Stage.h"

#include "PlacementObject/PlacementObject.h"
#include "DateTime.h"
#include "Enemy/StandardZombie/StandardZombie.h"
#include "Enemy/EnemyGenerator.h"

CGameScene::~CGameScene()
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

void CGameScene::Start()
{
	m_Camera = NewGO<GameCamera>(0, "camera");
	m_Player = NewGO<Player>(0, "player");
	m_Stage = NewGO<Stage>(0, "stage");
	m_PlacementObject = NewGO<PlacementObject>(0);
	DateTime* Data = NewGO<DateTime>(0, "dateTime");
	
	//sample//
	m_fontRender = NewGO<CFontRender>(0);
	m_fontRender->SetText(L"Press 'U' Instantiate Zombie.\nPress 'K' Delete All Zombie.\n\nR B\nE A\nO K\n  A");
	m_fontRender->SetColor({ 1.0f, 0.0f, 0.0f, 1.0f });
	m_fontRender->SetShadowParam(true, 0.5f, Vector4::Black);
	m_fontRender->SetPivot({ 0.0f, 0.5f });
	m_fontRender->SetPosition({ -630.0f, 350.0f });
	m_fontRender->SetScale(0.5f);
}

void CGameScene::Update()
{
}