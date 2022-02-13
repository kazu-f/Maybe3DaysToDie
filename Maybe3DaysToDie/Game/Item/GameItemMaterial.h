#pragma once
#include "Item/GameItemBase.h"


class GameItemMaterial : public GameItemBase
{
public:
	GameItemMaterial(SItemDataPtr& itemData,int type);

private:
	int m_matType = -1;

};

