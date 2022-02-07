#include "stdafx.h"
#include "GameItemTool.h"

GameItemTool::GameItemTool(SItemDataPtr & itemData, const ToolInfo& toolInfo)
	:GameItemBase(itemData)
{
	m_tool.SetTool(toolInfo);
}
