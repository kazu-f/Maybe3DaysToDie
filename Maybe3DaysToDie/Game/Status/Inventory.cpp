#include "stdafx.h"
#include "Inventory.h"
#include "Player/Player.h"

bool Inventory::Start()
{
	m_Inbentory = NewGO<prefab::CSpriteRender>(0);
	m_Inbentory->Init("Assets/sprite/ItemUI/inbentori.dds", FRAME_BUFFER_W, FRAME_BUFFER_H);
	m_Inbentory->SetMulColor({ 1.0f, 1.0f, 1.0f, 0.0f });
	return true;
}

void Inventory::Update()
{
	if (GetAsyncKeyState(VK_TAB)) {
		m_player.
	}
}

void Inventory::OnDestroy()
{
	DeleteGO(m_Inbentory);
}
