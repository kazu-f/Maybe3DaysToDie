#pragma once
#include "Item/GameItemTool.h"

/// <summary>
/// json�t�@�C������c�[���f�[�^��ǂݍ��ރN���X�B
/// </summary>
class ItemDataFile
{
	using json = nlohmann::json;
public:
	ItemDataFile();
	~ItemDataFile();

	void InitItemData(const char* filePath);

private:
	typedef std::vector<GameItemTool*> ToolArray;
	ToolArray m_toolArray;
	typedef std::vector<GameItemBase*> ItemArray;
	ItemArray m_itemArray;
};

