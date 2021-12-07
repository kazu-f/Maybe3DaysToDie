#include "stdafx.h"
#include "ToolDataFile.h"

namespace {
	const char* damage = "damage";
	const char* durable = "durable";
	const char* useStamina = "useStamina";
	const char* toolTypeTag = "tool";
}

ToolDataFile::ToolDataFile()
{
}

ToolDataFile::~ToolDataFile()
{
}

void ToolDataFile::InitToolFile(const char* filePath)
{
	std::ifstream ifs;
	ifs.open(filePath);
	if (!ifs) {
		ENGINE_MESSAGE_BOX(
			"Toolファイルのオープンに失敗しました。\n"
			"%s", filePath
		);
		return;
	}

	//jsonファイルに読み込んでいく。
	json jTool;
	ifs >> jTool;
	ifs.close();			//ファイルは閉じておく。

	//ツールの種類ごとに読み込む。
	for (auto toolType : jTool["ToolName"])
	{
		std::string toolTypeStr = toolType;
		//ツールの名前ごとに読み込む。
		for (auto& toolName : jTool[toolTypeStr]["ObjName"])
		{
			std::string toolNameStr = toolName;

			ToolInfo info;
			info.AttackPower = jTool[toolTypeStr][toolNameStr][damage];
			info.Durable = jTool[toolTypeStr][toolNameStr][durable];
			info.UseStamina = jTool[toolTypeStr][toolNameStr][useStamina];
			info.tool = jTool[toolTypeStr][toolNameStr][toolTypeTag];

			m_toolInfoArray.push_back(info);
		}
	}


}
