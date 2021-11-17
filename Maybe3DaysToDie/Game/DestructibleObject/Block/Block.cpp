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
	//���ɓo�^or�����ς݁B
	if (m_registColider == flag) return;

	//�o�^�A�����B
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
		m_BlockManager->RemoveBlock(this);
		//�ϋv�l��0�Ȃ̂ŃR���C�_�[���폜
		SetColliderEnable(false);
	}
}