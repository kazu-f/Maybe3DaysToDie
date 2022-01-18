#include "stdafx.h"
#include "Inventory.h"
#include "Player/Player.h"

bool Inventory::Start()
{
	m_Inbentory = NewGO<prefab::CSpriteRender>(0);
	m_Inbentory->Init("Assets/sprite/ItemUI/inbentori.dds", FRAME_BUFFER_W, FRAME_BUFFER_H);
	m_Inbentory->SetMulColor({ 1.0f, 1.0f, 1.0f, 1.0f });
	return true;
}

void Inventory::Update()
{
	if (!m_IsTriggerTab && GetAsyncKeyState(VK_TAB)) {
		if (!m_IsShow) {
			m_player->OpenInventory();
			m_Inbentory->SetMulColor({ 1.0f, 1.0f, 1.0f, 100.0f });
			m_IsShow = true;
		}
		else {
			m_player->CloseInventory();
			m_IsShow = false;
		}
	}
	if (m_player->GetState() != Player::State::Inventry) {
		m_Inbentory->SetMulColor({ 1.0f, 1.0f, 1.0f, 0.0f });
	}
	if (GetAsyncKeyState(VK_TAB)) {
		if (!m_IsTriggerTab)
			m_IsTriggerTab = true;
	}
	else {
		m_IsTriggerTab = false;
	}
}

void Inventory::OnDestroy()
{
	DeleteGO(m_Inbentory);
}
