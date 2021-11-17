#include "stdafx.h"
#include "Block.h"
#include "Tool/Tool.h"
#include "BlockManager/BlockManager.h"

Block::Block()
{
	param.BlockName = nullptr;
	param.Durable = 500;
	param.ObtainAmount = 0;
	param.AptitudeTool = ToolKinds::DebugTool;
	param.Type = ObjectType::Block;
	SetParams(param);
}
Block::~Block()
{
}

void Block::InitRayCollider()
{
	m_StaticCol.CreateBox(m_position, Quaternion::Identity, BLOCK_SIZE);
	m_StaticCol.GetRigidBody().GetBody()->setUserIndex(ColliderUserIndex::enCollisionAttr_Ground_RayBlock);
	m_registColider = true;
	DestructibleObject* obj = this;
	m_StaticCol.GetRigidBody().GetBody()->setUserPointer((void*)obj);
}

void Block::SetColliderEnable(bool flag)
{
	//既に登録or解除済み。
	if (m_registColider == flag) return;

	//登録、解除。
	if (flag)
	{
		PhysicsWorld().AddRigidBody(m_StaticCol.GetRigidBody());
	}
	else
	{
		PhysicsWorld().RemoveRigidBody(m_StaticCol.GetRigidBody());
	}
	m_registColider = flag;
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
		//耐久値が0なのでコライダーを削除
		SetColliderEnable(false);
	}
}