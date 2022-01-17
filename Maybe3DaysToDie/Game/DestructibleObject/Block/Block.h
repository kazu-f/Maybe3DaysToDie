#pragma once

class BlockManager;
class ChunkBlock;
class Block:public DestructibleObject
{
public:
	Block();
	~Block() override final;

	/// <summary>
	/// ダメージを与える
	/// </summary>
	/// <param name="tool">ツールの情報</param>
	void Damage(const ToolInfo& tool)override final;

	/// <summary>
	/// ブロックを追加
	/// </summary>
	/// <param name="params">パラメータ</param>
	/// <param name="pos">位置</param>
	/// <param name="rot">回転</param>
	/// <param name="scale">拡大率</param>
	void AddBlock(ObjectParams& params, Vector3& pos, Quaternion& rot, Vector3& scale)override final;

	/// <summary>
	/// ブロックマネージャーをセット
	/// </summary>
	void SetBlockManager(BlockManager* manager)
	{
		m_BlockManager = manager;
	}

	/// <summary>
	/// チャンクブロックをセット
	/// </summary>
	void SetChunkBlock(ChunkBlock* CB)
	{
		m_ChunkBlock = CB;
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
	ChunkBlock* m_ChunkBlock = nullptr;
	ObjectParams param;
};

