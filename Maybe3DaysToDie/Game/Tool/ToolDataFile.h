#pragma once
#include "Tool.h"

/// <summary>
/// jsonファイルからツールデータを読み込むクラス。
/// </summary>
class ToolDataFile
{
	using json = nlohmann::json;
public:
	ToolDataFile();
	~ToolDataFile();

	void InitToolFile(const char* filePath);

private:
	typedef std::vector<ToolInfo> ToolInfoArray;
	ToolInfoArray m_toolInfoArray;
};

