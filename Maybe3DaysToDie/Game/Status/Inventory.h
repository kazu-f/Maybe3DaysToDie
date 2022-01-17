#pragma once

#include "Item/GameItemBase.h"

class Inventory :public IGameObject
{
private:
	bool Start()override;
	void Update()override;
	void OnDestroy()override;

	prefab::CSpriteRender* m_Inbentory = nullptr;
	bool m_IsShow = false;
	
};