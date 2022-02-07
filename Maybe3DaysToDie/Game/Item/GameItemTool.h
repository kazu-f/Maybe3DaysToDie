#pragma once
#include "GameItemBase.h"
#include "Tool/Tool.h"

class GameItemTool : public GameItemBase
{
public:
	GameItemTool(SItemDataPtr & itemData, const ToolInfo& toolInfo);

private:
	Tool m_tool;
};

