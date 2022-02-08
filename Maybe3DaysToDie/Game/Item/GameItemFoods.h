#pragma once

#include "Item/GameItemBase.h"

struct SFoodParams
{
	int hp = 0;
	int water = 0;
	int food = 0;
	int stamina = 0;
};

class GameItemFoods : public GameItemBase
{
public:
	GameItemFoods(SItemDataPtr& itemData, const SFoodParams& params);

private:
	SFoodParams m_foodParams;
};

