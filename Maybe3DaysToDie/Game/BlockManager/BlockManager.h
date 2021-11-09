#pragma once
static const int BlockKinds = 1;		//ブロックの種類
class BlockManager :public IGameObject
{
public:
	BlockManager() 
	{
		//サイズの最大値セット
		BlockModel.resize(BlockKinds);
	}
	~BlockManager() {}

	void OnDestroy()override final;
	bool Start()override final;
	void Update()override final;
	void AddBlock(const char*BlockName);
private:
	std::vector<prefab::ModelRender*>(BlockModel) = { nullptr };		//ブロックのモデル
};

