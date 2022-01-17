#pragma once

class BlockManager;
class ChunkBlock;
class Block:public DestructibleObject
{
public:
	Block();
	~Block() override final;

	/// <summary>
	/// �_���[�W��^����
	/// </summary>
	/// <param name="tool">�c�[���̏��</param>
	void Damage(const ToolInfo& tool)override final;

	/// <summary>
	/// �u���b�N��ǉ�
	/// </summary>
	/// <param name="params">�p�����[�^</param>
	/// <param name="pos">�ʒu</param>
	/// <param name="rot">��]</param>
	/// <param name="scale">�g�嗦</param>
	void AddBlock(ObjectParams& params, Vector3& pos, Quaternion& rot, Vector3& scale)override final;

	/// <summary>
	/// �u���b�N�}�l�[�W���[���Z�b�g
	/// </summary>
	void SetBlockManager(BlockManager* manager)
	{
		m_BlockManager = manager;
	}

	/// <summary>
	/// �`�����N�u���b�N���Z�b�g
	/// </summary>
	void SetChunkBlock(ChunkBlock* CB)
	{
		m_ChunkBlock = CB;
	}

	//�u���b�N�̖��O���Z�b�g
	void SetName(const char* name)
	{
		param.BlockName = name;
		SetParams(param);
	}
private:
	const Vector3 BLOCK_SIZE = { OBJECT_UNIT ,OBJECT_UNIT ,OBJECT_UNIT };
	BlockManager* m_BlockManager = nullptr;
	ChunkBlock* m_ChunkBlock = nullptr;
	ObjectParams param;
};

