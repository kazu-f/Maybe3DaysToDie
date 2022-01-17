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
	for (auto tool : jTool)
	{
		std::string itemName = tool["name"];
		std::string tkmFilePath = tool["tkmFile"];
		std::string iconDataPath = tool["iconData"];
		ToolInfo info;
		info.AttackPower = tool[damage];
		info.Durable = tool[durable];
		info.UseStamina = tool[useStamina];
		info.tool = tool[toolTypeTag];

		GameItemTool* gameItemTool = new GameItemTool(itemName, tkmFilePath, iconDataPath, info);

		m_toolArray.push_back(gameItemTool);
	}


}
