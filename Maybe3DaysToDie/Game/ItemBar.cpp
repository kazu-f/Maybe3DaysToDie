#include "stdafx.h"
#include "ItemBar.h"

namespace {
	const Vector2 ItemBarPos = { 0.0f,-285.0f };
	const float ItemBarWidthSize = 600.0f;
}

bool ItemBar::Start()
{
	m_ItemIcon = NewGO<prefab::CSpriteRender>(0);
	m_ItemIcon->Init("Assets/sprite/ItemUI/HotBar.dds", ItemBarWidthSize, ItemOneBoxSize);
	m_ItemIcon->SetPosition(ItemBarPos);
	m_ItemIcon->SetPivot({ 0.0f,0.0f });

	for (int i = 0; i < SelectNum; i++) {
		m_SelectPos[i] = { -300.0f + (75.0f * i) ,ItemBarPos.y };
	}

	m_SelectItemIcon = NewGO<prefab::CSpriteRender>(1);
	m_SelectItemIcon->Init("Assets/sprite/ItemUI/SelectBar.dds", ItemOneBoxSize, ItemOneBoxSize);
	m_SelectItemIcon->SetPosition(m_SelectPos[0]);
	m_SelectItemIcon->SetPivot({ 0.0f,0.5 });
	return true;
}

void ItemBar::Update()
{
	//WPARAM wPram = NULL;
	//int zDelta = HIWORD(WM_MOUSEWHEEL) / 120;
	//if (zDelta > 0) {
	//	m_SelectNum++;
	//}
	//else if (zDelta < -0) {
	//	m_SelectNum--;
	//}

	int zDelta = GET_WHEEL_DELTA_WPARAM(WM_MOUSEWHEEL);
	if (zDelta > 1) {
		m_SelectNum++;
	}
	else if (zDelta < -1) {
		m_SelectNum--;
	}

	//if (GetAsyncKeyState(MK_SHIFT)) {
	//	m_SelectNum--;
	//	if (m_SelectNum < 0) {
	//		m_SelectNum = SelectNum - 1;
	//	}
	//}
	m_SelectItemIcon->SetPosition(m_SelectPos[m_SelectNum]);
}

void ItemBar::OnDestroy()
{
	DeleteGO(m_ItemIcon);
	DeleteGO(m_SelectItemIcon);
}