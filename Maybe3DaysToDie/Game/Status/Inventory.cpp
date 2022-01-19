#include "stdafx.h"
#include "Inventory.h"
#include "Player/Player.h"

bool Inventory::Start()
{
	m_Inbentory = NewGO<prefab::CSpriteRender>(2);
	m_Inbentory->Init("Assets/sprite/ItemUI/inbentori.dds", FRAME_BUFFER_H, FRAME_BUFFER_H);
	m_Inbentory->SetActiveFlag(false);
	return true;
}

void Inventory::Update()
{
	if (!m_IsTriggerTab && GetAsyncKeyState(VK_TAB)) {
		if (!m_IsShow) {
			m_player->OpenInventory();
			m_Inbentory->SetActiveFlag(true);
			m_IsShow = true;
			while (true) {
				int returnNo = ShowCursor(true);
				if (returnNo >= 0) {
					break;
				}
			}
		}
		else {
			m_player->CloseInventory();
			m_IsShow = false;
			while (true) {
				int returnNo = ShowCursor(false);
				m_Inbentory->SetActiveFlag(false);
				if (returnNo < 0) {
					break;
				}
			}
		}
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
