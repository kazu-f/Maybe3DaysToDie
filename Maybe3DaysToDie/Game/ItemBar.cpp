#include "stdafx.h"
#include "ItemBar.h"

namespace {
    const Vector2 ItemBarPos( 0.0f,-285.0f );
    const float ItemBarWidthSize = 600.0f;
}

bool ItemBar::Start()
{
    m_ItemIcon = NewGO<prefab::CSpriteRender>(0);
    m_ItemIcon->Init("Assets/sprite/HotBar.dds", ItemBarWidthSize, ItemOneBoxSize);
    m_ItemIcon->SetPosition(ItemBarPos);

    for (int i = 0; i < SelectNum; i++) {
        m_SelectPos[i] = { -1000.0f +( 100.0f * i),ItemBarPos.y };
    }
    m_SelectItemIcon = NewGO<prefab::CSpriteRender>(0);
    m_SelectItemIcon->Init("Assets/sprite/SelectBar.dds", ItemOneBoxSize, ItemOneBoxSize);
    m_SelectItemIcon->SetPosition(m_SelectPos[m_SelectNum]);

    return true;
}

void ItemBar::Update()
{
    WPARAM wPram=NULL;
    int zDelta = GET_WHEEL_DELTA_WPARAM(wPram);
    if (zDelta > 120) {
        m_SelectNum++;
    }
    else if(zDelta < -120){
        m_SelectNum--;
    }
    m_SelectItemIcon->SetPosition(m_SelectPos[m_SelectNum]);
}

void ItemBar::OnDestroy()
{
    DeleteGO(m_ItemIcon);
    DeleteGO(m_SelectItemIcon);
}
