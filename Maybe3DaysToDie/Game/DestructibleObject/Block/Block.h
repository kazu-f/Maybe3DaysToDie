#pragma once

class BlockManager;
class Block:public DestructibleObject
{
public:
	Block();
	~Block() override final;

	/// <summary>
	/// �R���C�_�[�̏������B
	/// </summary>
	void InitRayCollider();

	/// <summary>
	/// �R���C�_�[�̓o�^�A�����B
	/// </summary>
	void SetColliderEnable(bool flag);

	/// <summary>
	/// �_���[�W��^����B
	/// </summary>
	void Damage(const ToolInfo& tool)override final;

	/// <summary>
	/// �u���b�N�}�l�[�W���[���Z�b�g
	/// </summary>
	void SetBlockManager(BlockManager* manager)
	{
		m_BlockManager = manager;
	}

	//�u���b�N�̖��O���Z�b�g
	void SetName(const char* name)
	{
		param.BlockName = name;
		SetParams(param);
	}
private:
	const Vector3 BLOCK_SIZE = { OBJECT_UNIT ,OBJECT_UNIT ,OBJECT_UNIT };
	bool m_registColider = false;
	BlockManager* m_BlockManager = nullptr;
	ObjectParams param;
};

