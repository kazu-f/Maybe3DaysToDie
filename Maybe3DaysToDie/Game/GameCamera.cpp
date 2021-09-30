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
}

void GameCamera::OnDestroy()
{
}
