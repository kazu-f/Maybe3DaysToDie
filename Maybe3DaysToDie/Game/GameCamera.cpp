#include "stdafx.h"
#include "GameCamera.h"

bool GameCamera::Start()
{
	MainCamera().SetPosition( m_Pos );
	MainCamera().SetTarget(Vector3::Zero);
	return true;
}

void GameCamera::Update()
{
	MainCamera().SetPosition(m_Pos);
	MainCamera().SetTarget(m_Target);
	MainCamera().Update();
}

void GameCamera::OnDestroy()
{
}
