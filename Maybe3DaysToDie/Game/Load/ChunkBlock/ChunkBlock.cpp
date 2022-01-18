#include "stdafx.h"
#include "ChunkBlock.h"

void ChunkBlock::OnDestroy()
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

void ChunkBlock::Init()
{
	for (int x = 0; x < ChunkWidth; x++)
	{
		for (int y = 0; y < ChunkHeight; y++)
		{
			for (int z = 0; z < ChunkWidth; z++)
			{
				m_Block[x][y][z].SetChunkBlock(this);
				Vector3 pos;
				pos.x = static_cast<float>(x) * OBJECT_UNIT;
				pos.y = static_cast<float>(y) * OBJECT_UNIT;
				pos.z = static_cast<float>(z) * OBJECT_UNIT;
				//�`�����N�̈ʒu�����Z
				float geta = 0;
				geta = OBJECT_UNIT * ChunkWidth;
				pos.x += geta * m_ChunkID[0];
				pos.z += geta * m_ChunkID[1];
				//�|�W�V�������Z�b�g
				m_Block[x][y][z].SetPosAndRot(pos, Quaternion::Identity);
			}
		}
	}
}

void ChunkBlock::MoveChunk()
{
	if (IsMove == false)
	{
		//�`�����N�ړ����Ȃ�
		return;
	}
	//�Z�[�u�f�[�^�t�@�C������`�����N�̏����擾
	auto& chunkData = m_SaveDataFile->m_ChunkData[m_ChunkID[0]][m_ChunkID[1]];
	if (m_modelNum > 0)
	{
		for (auto& model : BlockModel)
		{
			//�C���X�^���V���O�f�[�^�����Z�b�g
			model->ResetInstancingDatas();
		}
	}
	for (int x = 0; x < ChunkWidth; x++)
	{
		for (int y = 0; y < ChunkHeight; y++)
		{
			for (int z = 0; z < ChunkWidth; z++)
			{
				Vector3 pos;
				pos.x = static_cast<float>(x) * OBJECT_UNIT;
				pos.y = static_cast<float>(y) * OBJECT_UNIT;
				pos.z = static_cast<float>(z) * OBJECT_UNIT;
				//�`�����N�̈ʒu�����Z
				float geta = 0;
				geta = OBJECT_UNIT * ChunkWidth;
				pos.x += geta * m_ChunkID[0];
				pos.z += geta * m_ChunkID[1];
				//�|�W�V�������Z�b�g
				m_Block[x][y][z].SetPosAndRot(pos, Quaternion::Identity);
				//�p�����[�^
				ObjectParams param;
				param.BlockID = chunkData.ObjId[x][y][z];
				param.Durable = chunkData.ObjDurable[x][y][z];
				int id = static_cast<int>(param.BlockID);
				param.BlockName = m_SaveDataFile->ObjectFilePath[id];
				//�p�����[�^���Z�b�g
				m_Block[x][y][z].SetParams(param);

				if (param.Durable > 0)
				{
					bool InitedModel = false;
					if (m_modelNum > 0)
					{
						for (auto& model : BlockModel)
						{
							//���̓��f��1��ނ���������t�@�C���p�X�Œ�
							if (param.BlockName == model->GetInitData().m_tkmFilePath)
							{
								//�u���b�N�̖��O�����Ԃ��Ă���Ƃ�
								//�C���X�^���V���O�f�[�^���X�V
								Quaternion rot = Quaternion::Identity;
								Vector3 scale = Vector3::One;
								model->UpdateInstancingData(pos, rot, scale);
								InitedModel = true;
								break;
							}

						}
					}
					if (InitedModel == false)
					{
						//�u���b�N�̖��O�����Ԃ��Ă��Ȃ��̂ł܂��A���̃��f�����Ȃ�
						ModelInitData InitData;
						Quaternion rot = Quaternion::Identity;
						Vector3 scale = Vector3::One;
						InitData.m_tkmFilePath = param.BlockName;
						prefab::ModelRender* model = NewGO<prefab::ModelRender>(0);
						//�`�����N�̃T�C�Y���C���X�^���V���O�`�悷��
						model->Init(InitData, nullptr, 0, MaxInstanceNum);
						model->UpdateInstancingData(pos, rot, scale);
						BlockModel[m_modelNum] = model;
						m_modelNum++;
					}
				}
			}
		}
	}
	IsMove = false;
}

Block& ChunkBlock::GetBlock(Vector3 pos)
{
	//�|�W�V�����ɑΉ�����u���b�N���擾
	int x = pos.x / OBJECT_UNIT;
	x = static_cast<int>(x % ChunkWidth);
	int y = pos.y / OBJECT_UNIT;
	y = static_cast<int>(y % ChunkHeight);
	int z = pos.z / OBJECT_UNIT;
	z = static_cast<int>(z % ChunkWidth);

	return m_Block[x][y][z];
}

void ChunkBlock::AddModel(ObjectParams& params, Vector3& pos, Quaternion& rot, Vector3& scale)
{
	ChunkBlockDirty = true;
	if (m_modelNum > 0)
	{
		for (auto& model : BlockModel)
		{
			if (params.BlockName == model->GetInitData().m_tkmFilePath)
			{
				//�u���b�N�̖��O�����Ԃ��Ă���Ƃ�
				//�C���X�^���V���O�f�[�^���X�V
				model->UpdateInstancingData(pos, rot, scale);
				return;
			}
		}
	}
	//�u���b�N�̖��O�����Ԃ��Ă��Ȃ��̂ł܂��A���̃��f�����Ȃ�
	ModelInitData InitData;
	InitData.m_tkmFilePath = params.BlockName;
	prefab::ModelRender* model = NewGO<prefab::ModelRender>(0);
	//�`�����N�̃T�C�Y���C���X�^���V���O�`�悷��
	model->Init(InitData, nullptr, 0, MaxInstanceNum);
	model->UpdateInstancingData(pos, rot, scale);
	BlockModel[m_modelNum] = model;
	m_modelNum++;
}

void ChunkBlock::RemoveBlock(Block* blockptr)
{
	ChunkBlockDirty = true;
	const char* Name = blockptr->GetParam().BlockName;
	if (Name == nullptr)
	{
		//���O���Z�b�g����Ă��Ȃ��̂ŉ���������Ȃ����̂��󂻂��Ƃ��Ă���
		return;
	}
	for (auto& model : BlockModel)
	{
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
					if (block.GetParam().Durable > 0)
					{
						if (block.GetParam().BlockName == Name)
						{
							model->UpdateInstancingData(block.GetPosition(), block.GetRotation(), block.GetScale());
						}
					}
				}
			}
		}
	}
}