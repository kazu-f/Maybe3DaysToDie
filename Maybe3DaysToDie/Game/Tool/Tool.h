#pragma once
class Tool
{
public:
	Tool() {}
	~Tool() {}

private:
	ToolKinds tool = ToolKinds::DebugTool;		//ツールの種類
};