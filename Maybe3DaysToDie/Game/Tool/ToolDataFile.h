#pragma once
#include "Item/GameItemTool.h"

/// <summary>
/// json�t�@�C������c�[���f�[�^��ǂݍ��ރN���X�B
/// </summary>
class ToolDataFile
{
	using json = nlohmann::json;
public:
	ToolDataFile();
	~ToolDataFile();

	void InitToolFile(const char* filePath);

private:
	//typedef std::vector<ToolInfo> ToolInfoArray;
	//ToolInfoArray m_toolInfoArray;
	typedef std::vector<GameItemTool*> ToolArray;
	ToolArray m_toolArray;
};

