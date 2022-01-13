#pragma once
class ItemBar : public IGameObject
{
public:
private:
	prefab::CSpriteRender* m_ItemIcon = nullptr;
	prefab::CSpriteRender* m_SelectItemIcon = nullptr;
};

