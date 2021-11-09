#pragma once
static const int BlockKinds = 1;		//�u���b�N�̎��
class BlockManager :public IGameObject
{
public:
	BlockManager() 
	{
		//�T�C�Y�̍ő�l�Z�b�g
		BlockModel.resize(BlockKinds);
	}
	~BlockManager() {}

	void OnDestroy()override final;
	bool Start()override final;
	void Update()override final;
	void AddBlock(const char* BlockName, Vector3& pos, Quaternion& rot, Vector3& scale);
private:
	std::vector<prefab::ModelRender*>(BlockModel) = { nullptr };		//�u���b�N�̃��f��
	int m_modelNum = 0;
};

