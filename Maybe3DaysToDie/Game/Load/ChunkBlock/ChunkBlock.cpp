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
	int m_modelNum = 0;
	for (int ObjectID = 0; ObjectID < BlockKinds; ObjectID++)
	{
		//���f����������
		//�u���b�N�̖��O�����Ԃ��Ă��Ȃ��̂ł܂��A���̃��f�����Ȃ�
		ModelInitData InitData;
		InitData.m_tkmFilePath = m_SaveDataFile->ObjectFilePath[ObjectID];
		prefab::ModelRender* model = NewGO<prefab::ModelRender>(0);
		//�`�����N�̃T�C�Y���C���X�^���V���O�`�悷��
		model->Init(InitData, nullptr, 0, MaxInstanceNum);
		BlockModel[m_modelNum] = model;
		m_modelNum++;
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
	for (auto& model : BlockModel)
	{
		//�C���X�^���V���O�f�[�^�����Z�b�g
		model->ResetInstancingDatas();
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
				int BlockID = static_cast<int>(param.BlockID);
				param.BlockName = m_SaveDataFile->ObjectFilePath[BlockID];
				//�p�����[�^���Z�b�g
				m_Block[x][y][z].SetParams(param);

				if (param.Durable > 0)
				{
					//�u���b�N�̖��O�����Ԃ��Ă���Ƃ�
					//�C���X�^���V���O�f�[�^���X�V
					Quaternion rot = Quaternion::Identity;
					Vector3 scale = Vector3::One;
					BlockModel[BlockID]->UpdateInstancingData(pos, rot, scale);
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
	int BlockID = static_cast<int>(params.BlockID);
	//�u���b�N�ɖ��O���Z�b�g
	params.BlockName = m_SaveDataFile->ObjectFilePath[BlockID];
	//�C���X�^���V���O�f�[�^���X�V
	BlockModel[BlockID]->UpdateInstancingData(pos, rot, scale);
}

void ChunkBlock::RemoveBlock(Block* blockptr)
{
	ChunkBlockDirty = true;
	int BlockID = static_cast<int>(blockptr->GetParam().BlockID);
	if (BlockID < 0 || BlockID > BlockKinds)
	{
		//�u���b�NID���}�C�i�X���ő�l���傫���Ƃ�return
		return;
	}

	//�폜����u���b�N�̒l�����Z�b�g
	blockptr->ResetParams();
	//�C���X�^���V���O�f�[�^�����Z�b�g
	BlockModel[BlockID]->ResetInstancingDatas();
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
					BlockModel[BlockID]->UpdateInstancingData(block.GetPosition(), block.GetRotation(), block.GetScale());
				}
			}
		}
	}

}