#include "stdafx.h"
#include "GameItemTool.h"

GameItemTool::GameItemTool(std::string& itemName, std::string& tkmPath, std::string& tkmIcon, const ToolInfo& toolInfo)
	:GameItemBase(itemName,tkmPath, tkmIcon)
{
	m_tool.SetTool(toolInfo);
}
