#pragma once
//ツールの種類
enum ToolKinds {
	axe = 0,		//斧
	Pickaxe = 1 << 0,		//ツルハシ
	shovel = 1 << 1,		//ショベル
	others = 1 << 2,		//その他
	DebugTool = 0xffffffff		//デバッグ用ツール
};

struct ToolInfo {
	ToolKinds tool = ToolKinds::DebugTool;		//ツールの種類
	int AttackPower = 1000000;		//ツールの攻撃力
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