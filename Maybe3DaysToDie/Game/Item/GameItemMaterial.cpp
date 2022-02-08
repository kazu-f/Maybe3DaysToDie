#include "stdafx.h"
#include "GameItemMaterial.h"

GameItemMaterial::GameItemMaterial(SItemDataPtr& itemData, int type)
	:GameItemBase(itemData)
{
	m_matType = type;
}
