#pragma once
#include "GameItemBase.h"
#include "Tool/Tool.h"

class GameItemTool : public GameItemBase
{
public:
	GameItemTool(std::string& itemName, std::string& tkmPath, std::string& tkmIcon, const ToolInfo& toolInfo);

private:
	Tool m_tool;
};

