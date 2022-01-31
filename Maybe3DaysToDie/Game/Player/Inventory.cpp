#include "stdafx.h"
#include "Inventory.h"
#include "Player/Player.h"
#include <windowsx.h>

bool Inventory::Start()
{
	m_Inbentory = NewGO<prefab::CSpriteRender>(2);
	m_Inbentory->Init("Assets/sprite/ItemUI/inbentori.dds", FRAME_BUFFER_H, FRAME_BUFFER_H);
	m_Inbentory->SetActiveFlag(false);
	return true;
}

void Inventory::Update()
{
	//Tab�������Ă�����
	if (!m_IsTriggerTab && GetAsyncKeyState(VK_TAB)) {
		//�C���x���g�����J����
		SwhichInventoryState();
	}
	//�^�u�����������Ă��Ȃ����H
	TriggerTab();
}

void Inventory::OnDestroy()
{
	//��ʂ��폜
	DeleteGO(m_Inbentory);
}

void Inventory::SwhichInventoryState()
{
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
		//�}�E�X�J�[�\���̈ʒu���Œ�
		int DefaultPoint[2] = { 500,300 };
		SetCursorPos(DefaultPoint[0], DefaultPoint[1]);
		while (true) {
			int returnNo = ShowCursor(false);
			m_Inbentory->SetActiveFlag(false);
			if (returnNo < 0) {
				break;
			}
		}
	}
}

void Inventory::TriggerTab()
{
	if (GetAsyncKeyState(VK_TAB)) {
		if (!m_IsTriggerTab)
			m_IsTriggerTab = true;
	}
	else {
		m_IsTriggerTab = false;
	}
}
