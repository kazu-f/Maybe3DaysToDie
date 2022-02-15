#include "stdafx.h"
#include "Block.h"
#include "Tool/Tool.h"
#include "Load/ChunkBlock/ChunkBlock.h"

Block::Block()
{
	param.Durable = 0;
	param.AptitudeTool = ToolKinds::DebugTool;
	SetParams(param);
}
Block::~Block()
{
}


void Block::Damage(const ToolInfo& tool)
{
	//�c�[������U���͂������Ă���
	int damage = tool.AttackPower;
	if (!(m_params.AptitudeTool & tool.tool))
	{
		//�K���c�[������Ȃ��Ƃ��_���[�W��1/3�ɂ���
		damage /= 3;
	}
	//�ϋv�l�̍Œ�l��0�ɂ���
	int durable = max(0, (m_params.Durable - damage));
	if (durable != m_params.Durable)
	{
		//�l���ς������
		m_params.Durable = durable;
	}
	if (durable == 0)
	{
		m_params.Durable = durable;
		m_ChunkBlock->RemoveBlock(this);
	}
}

void Block::AddBlock(ObjectParams& params, Vector3& pos, Quaternion& rot, Vector3& scale)
{
	//�p�����[�^���Z�b�g
	SetParams(params);
	//���f����ǉ�
	m_ChunkBlock->AddModel(params, pos, rot, scale);
}
