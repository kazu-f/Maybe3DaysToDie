#pragma once

struct ToolInfo {
	ToolKinds tool = ToolKinds::DebugTool;		//ツールの種類
	int AttackPower = 100;		//ツールの攻撃力
	int UseStamina = 0;		//スタミナの減少量
	int Durable = 1000000;		//耐久値
};

class Tool
{
public:
	Tool() {}
	~Tool() {}

	void SetTool(ToolInfo T_Info)
	{
		info = T_Info;
	}

	ToolInfo& GetInfo()
	{
		return info;
	}
private:
	ToolInfo info;
};