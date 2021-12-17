#pragma once

class BlockManager;
class Block:public DestructibleObject
{
public:
	Block();
	~Block() override final;

	/// <summary>
	/// ダメージを与える。
	/// </summary>
	void Damage(const ToolInfo& tool)override final;

	/// <summary>
	/// ブロックマネージャーをセット
	/// </summary>
	void SetBlockManager(BlockManager* manager)
	{
		m_BlockManager = manager;
	}

	//ブロックの名前をセット
	void SetName(const char* name)
	{
		param.BlockName = name;
		SetParams(param);
	}
private:
	const Vector3 BLOCK_SIZE = { OBJECT_UNIT ,OBJECT_UNIT ,OBJECT_UNIT };
	BlockManager* m_BlockManager = nullptr;
	ObjectParams param;
};

