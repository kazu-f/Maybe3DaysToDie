#include "stdafx.h"
#include "Block.h"
#include "Tool/Tool.h"
#include "Block/BlockManager/BlockManager.h"

Block::Block()
{
	param.BlockName = nullptr;
	param.Durable = 0;
	param.ObtainAmount = 0;
	param.AptitudeTool = ToolKinds::DebugTool;
	param.Type = ObjectType::Block;
	SetParams(param);
}
Block::~Block()
{
}


void Block::Damage(const ToolInfo& tool)
{
	//ツールから攻撃力を持ってくる
	int damage = tool.AttackPower;
	if (!(m_params.AptitudeTool & tool.tool))
	{
		//適性ツールじゃないときダメージを1/3にする
		damage /= 3;
	}
	//耐久値の最低値を0にする
	int durable = max(0, (m_params.Durable - damage));
	if (durable != m_params.Durable)
	{
		//値が変わった時
		m_params.Durable = durable;
	}
	if (durable == 0)
	{
		m_BlockManager->RemoveBlock(this);
	}
}

void Block::AddBlock(ObjectParams& params, Vector3& pos, Quaternion& rot, Vector3& scale)
{
	//パラメータをセット
	SetParams(params);
	//モデルを追加
	m_BlockManager->AddModel(params, pos, rot, scale);
}
