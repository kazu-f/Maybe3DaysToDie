#include "stdafx.h"
#include "ItemBar.h"

namespace {
    const Vector2 ItemBarPos( 0.0f,-250.0f );
    const float ItemOneBoxSize = 10.0f;
    const float ItemBarWidthSize = 2000.0f;
}

bool ItemBar::Start()
{
    m_ItemIcon = NewGO<prefab::CSpriteRender>(0);
    m_ItemIcon->Init("Assets/sprite/HotBar.dds", ItemOneBoxSize, ItemOneBoxSize);
    m_ItemIcon->SetPosition(ItemBarPos);

    m_SelectItemIcon = NewGO<prefab::CSpriteRender>(0);
    m_SelectItemIcon->Init("Assets/spirte/SelectBar.dds", ItemOneBoxSize, ItemOneBoxSize);
    m_SelectItemIcon->SetPosition(m_SelectPos[m_SelectNum]);

    for (int i = 0; i < SelectNum; i++) {
        m_SelectPos[i] = { -1000.0f +( 100.0f * i),-250.0f };
    }
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
