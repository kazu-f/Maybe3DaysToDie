#include "stdafx.h"
#include "ItemBar.h"

namespace {
    const Vector2 ItemBarPos( 0.0f,-250.0f );
    const float ItemOneBoxSize = 10.0f;
    const float ItemBarWidthSize = 100.0f;
}

bool ItemBar::Start()
{
    m_ItemIcon = NewGO<prefab::CSpriteRender>(0);
    m_ItemIcon->Init("Assets/sprite/HotBar.dds", ItemOneBoxSize, ItemOneBoxSize);
    m_ItemIcon->SetPosition(ItemBarPos);

    m_SelectItemIcon = NewGO<prefab::CSpriteRender>(0);
    m_SelectItemIcon->Init("Assets/spirte/SelectBar.dds", ItemOneBoxSize, ItemOneBoxSize);
    m_SelectItemIcon->SetPosition(m_SelectPos[m_SelectNum]);
    return true;
}

void ItemBar::Update()
{
    WPARAM wPram;
    int zDelta = GET_WHEEL_DELTA_WPARAM(wPram);
    if (zDelta < 0) {
        m_SelectNum++;
    }
    else if(zDelta > 0){
        m_SelectNum--;
    }
    m_SelectItemIcon->SetPosition(m_SelectPos[m_SelectNum]);
}