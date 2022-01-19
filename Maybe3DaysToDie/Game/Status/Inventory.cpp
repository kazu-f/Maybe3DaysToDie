#include "stdafx.h"
#include "Inventory.h"
#include "Player/Player.h"

bool Inventory::Start()
{
	m_Inbentory = NewGO<prefab::CSpriteRender>(2);
	m_Inbentory->Init("Assets/sprite/ItemUI/inbentori.dds", FRAME_BUFFER_H, FRAME_BUFFER_H);
	return true;
}

void Inventory::Update()
{
	if (!m_IsTriggerTab && GetAsyncKeyState(VK_TAB)) {
		if (!m_IsShow) {
			m_player->OpenInventory();
			m_IsShow = true;
			while (true) {
				int returnNo = ShowCursor(true);
				if (returnNo >= 0) {
					break;
				}
			}
			m_Inbentory->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
			m_Inbentory->SetScale(Vector3::One);
		}
		else {
			m_player->CloseInventory();
			m_IsShow = false;
			while (true) {
				int returnNo = ShowCursor(false);
				if (returnNo < 0) {
					break;
				}
			}
		}
	}
	if (m_player->GetState() != Player::State::Inventry) {
		m_Inbentory->SetMulColor({ 1.0f,1.0f,1.0f,0.0f });
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
