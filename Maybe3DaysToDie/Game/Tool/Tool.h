#pragma once

struct ToolInfo {
	ToolKinds tool = ToolKinds::DebugTool;		//�c�[���̎��
	int AttackPower = 100;		//�c�[���̍U����
	int UseStamina = 0;		//�X�^�~�i�̌�����
	int Durable = 1000000;		//�ϋv�l
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