#pragma once
#include "IGameItem.h"
#include "Tool/Tool.h"

class GameItemTool : public IGameItem
{
public:
	GameItemTool(std::string& itemName, const char* tkmPath, const char* tkmIcon, const ToolInfo& toolInfo);

private:
	Tool m_tool;
};

