#include "stdafx.h"
#include "GameItemTool.h"

GameItemTool::GameItemTool(std::string& itemName, const char* tkmPath, const char* tkmIcon, const ToolInfo& toolInfo)
	:IGameItem(itemName,tkmPath, tkmIcon)
{
	m_tool.SetTool(toolInfo);
}
