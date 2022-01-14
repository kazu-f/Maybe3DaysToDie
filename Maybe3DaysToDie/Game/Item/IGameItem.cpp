#include "stdafx.h"
#include "IGameItem.h"

IGameItem::IGameItem(std::string& itemName, const char* tkmPath, const char* iconPath)
{
	m_itemName = itemName;
}
