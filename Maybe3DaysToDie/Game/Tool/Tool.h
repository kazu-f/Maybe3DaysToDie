#pragma once
//�c�[���̎��
enum ToolKinds {
	axe = 0,		//��
	Pickaxe = 1 << 0,		//�c���n�V
	shovel = 1 << 1,		//�V���x��
	others = 1 << 2,		//���̑�
	DebugTool = 0xffffffff		//�f�o�b�O�p�c�[��
};

struct ToolInfo {
	ToolKinds tool = ToolKinds::DebugTool;		//�c�[���̎��
	int AttackPower = 1000000;		//�c�[���̍U����
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