#include "stdafx.h"
#include "BlockManager.h"

void BlockManager::OnDestroy()
{
	for (auto& model : BlockModel)
	{
		if (model != nullptr)
		{
			DeleteGO(model);
			model = nullptr;
		}
	}
}

bool BlockManager::Start()
{

	for (int x = 0; x < ChunkWidth; x++)
	{
		for (int y = 0; y < ChunkHeight; y++)
		{
			for (int z = 0; z < ChunkWidth; z++)
			{
				//�}�l�[�W���[���Z�b�g
				m_Block[x][y][z].SetBlockManager(this);
				Vector3 pos;
				pos.x = static_cast<float>(x) * OBJECT_UNIT;
				pos.y = static_cast<float>(y) * OBJECT_UNIT;
				pos.z = static_cast<float>(z) * OBJECT_UNIT;
				m_Block[x][y][z].SetPosition(pos);
			}
		}

	}
	return true;
}

void BlockManager::Update()
{

}

Block& BlockManager::GetBlock(const Vector3& pos)
{
	//���C�e�X�g�̊֌W��float�̒l�������Ƃ�������̂ŉ��ʂ��͂���
	Vector3 Pos = pos;
	Pos.x += OBJECT_UNIT / 2;
	Pos.y += OBJECT_UNIT / 2;
	Pos.z += OBJECT_UNIT / 2;

	int resX = static_cast<int>(std::floor(Pos.x / OBJECT_UNIT));
	int resY = static_cast<int>(std::floor(Pos.y / OBJECT_UNIT));
	int resZ = static_cast<int>(std::floor(Pos.z / OBJECT_UNIT));

	return m_Block[resX][resY][resZ];
}


void BlockManager::AddBlock(const char* BlockName, Vector3& pos, Quaternion& rot, Vector3& scale)
{
	if (m_modelNum > 0)
	{
		for (auto& model : BlockModel)
		{
			if (BlockName == model->GetInitData().m_tkmFilePath)
			{
				//�u���b�N�̖��O�����Ԃ��Ă���Ƃ�
				model->UpdateInstancingData(pos, rot, scale);
				//�R���C�_�[��L����
				GetBlock(pos).SetName(BlockName);
				return;
			}
		}
	}
	//�u���b�N�̖��O�����Ԃ��Ă��Ȃ��̂ł܂��A���̃��f�����Ȃ�
	ModelInitData InitData;
	InitData.m_tkmFilePath = BlockName;
	prefab::ModelRender* model = NewGO<prefab::ModelRender>(0);
	//�`�����N�̃T�C�Y���C���X�^���V���O�`�悷��
	model->Init(InitData, nullptr, 0, MaxInstanceNum);
	model->UpdateInstancingData(pos, rot, scale);
	BlockModel[m_modelNum] = model;
	//�R���C�_�[��L����
	GetBlock(pos).SetName(BlockName);

	m_modelNum++;
}

void BlockManager::RemoveBlock(Block* blockptr)
{
	for (auto& model : BlockModel)
	{
		const char* Name = blockptr->GetParam().BlockName;
		blockptr->ResetParams();
		//�C���X�^���V���O�f�[�^�����Z�b�g
		model->ResetInstancingDatas();
		//��������Z�b�g���Ȃ���
		for (int x = 0; x < ChunkWidth; x++)
		{
			for (int y = 0; y < ChunkHeight; y++)
			{
				for (int z = 0; z < ChunkWidth; z++)
				{
					auto& block = m_Block[x][y][z];
					if (block.GetParam().BlockName == Name)
					{
						model->UpdateInstancingData(block.GetPosition(), block.GetRotation(), block.GetScale());
					}
				}
			}
		}
	}
}