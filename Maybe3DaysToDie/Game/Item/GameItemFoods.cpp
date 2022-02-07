#include "stdafx.h"
#include "GameItemFoods.h"

GameItemFoods::GameItemFoods(SItemDataPtr& itemData, const SFoodParams& params)
	:GameItemBase(itemData)
{
	m_foodParams = params;
}
