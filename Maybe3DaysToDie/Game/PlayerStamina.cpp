#include "stdafx.h"
#include "PlayerStamina.h"

bool PlayerStamina::Start()
{

	return true;
}

void PlayerStamina::Update()
{
	m_nowRegeneTimer += GameTime().GetFrameDeltaTime();
	if (m_nowRegeneTimer >= m_RegeneTime) {
		m_Stamina++;
		m_nowRegeneTimer = 0.0f;
	}
}

void PlayerStamina::OnDestroy()
{
}
