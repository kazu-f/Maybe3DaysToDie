#pragma once

#include "Item/GameItemBase.h"

class Player;
class Inventory :public IGameObject
{
public:
	void SetPlayer(Player* pp) {
		m_player = pp;
	}
private:
	bool Start()override;
	void Update()override;
	void OnDestroy()override;

	prefab::CSpriteRender* m_Inbentory = nullptr;
	bool m_IsShow = false;
	Player* m_player = nullptr;
};