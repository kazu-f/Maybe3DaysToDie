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
			"Tool�t�@�C���̃I�[�v���Ɏ��s���܂����B\n"
			"%s", filePath
		);
		return;
	}

	//json�t�@�C���ɓǂݍ���ł����B
	json jTool;
	ifs >> jTool;
	ifs.close();			//�t�@�C���͕��Ă����B

	//�c�[���̎�ނ��Ƃɓǂݍ��ށB
	for (auto toolType : jTool["ToolName"])
	{
		std::string toolTypeStr = toolType;
		//�c�[���̖��O���Ƃɓǂݍ��ށB
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
