#include "stdafx.h"
#include "ChunkBlock.h"
#include "Load/TerrainLoad/LoadingByChunk.h"
#include "Item/ItemDataFile.h"
#include "Item/GameItemPlaceObj.h"
#include "Item/BlockItem.h"
#include "Item/GameItemTerrain.h"

void ChunkBlock::Init()
{
	m_itemDataFile = ItemDataFile::GetInstance();
	int modelSize = m_itemDataFile->GetBlockArraySize() + m_itemDataFile->GetPlaceArraySize();
	m_InstancingData.resize(modelSize);
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
	ChunkBlockDirty = true;
	m_IsModelUpdated = true;

	//�Z�[�u�f�[�^�t�@�C������`�����N�̏����擾
	auto& chunkData = m_SaveDataFile->m_ChunkData[m_ChunkID[0]][m_ChunkID[1]];

	//�C���X�^���V���O�f�[�^�����Z�b�g
	for (auto& data : m_InstancingData)
	{
		data.clear();
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
				param.BlockID = chunkData.ObjData[x][y][z].ObjId;
				param.Durable = chunkData.ObjData[x][y][z].ObjDurable;
				int DataID = static_cast<int>(param.BlockID);
				m_Block[x][y][z].SetParams(param);

				auto* block = m_itemDataFile->GetBlockData(DataID);
				auto* place = m_itemDataFile->GetPlaceData(DataID);
				if (block == nullptr && place == nullptr) {
					m_Block[x][y][z].ResetParams();
					continue;
				}

				//�C���X�^���V���O�f�[�^ID���v�Z����B
				int modelID = 0;
				if (block != nullptr)modelID = block->GetItemData()->itemTypeID;
				if (place != nullptr)modelID = place->GetItemData()->itemTypeID + m_itemDataFile->GetBlockArraySize();


				if (param.Durable > 0)
				{
					//�C���X�^���V���O�f�[�^���X�V
					Quaternion rot = Quaternion::Identity;
					Vector3 scale = Vector3::One;
					//�f�[�^���쐬
					InstancingData data;
					data.pos = pos;
					data.rot = rot;
					data.scale = scale;
					//�z��ɒǉ�
					m_InstancingData[modelID].push_back(data);
				}
			}
		}
	}
	
	IsMove = false;
}

Block* ChunkBlock::GetBlock(Vector3 pos)
{
	//�|�W�V�����ɑΉ�����u���b�N���擾
	int x = pos.x / OBJECT_UNIT;
	x = static_cast<int>(x % ChunkWidth);
	int y = pos.y / OBJECT_UNIT;
	y = static_cast<int>(y % ChunkHeight);
	int z = pos.z / OBJECT_UNIT;
	z = static_cast<int>(z % ChunkWidth);

	return &m_Block[x][y][z];
}

void ChunkBlock::AddModel(ObjectParams& params, Vector3& pos, Quaternion& rot, Vector3& scale)
{
	int DataID = static_cast<int>(params.BlockID);

	auto* block = m_itemDataFile->GetBlockData(DataID);
	auto* place = m_itemDataFile->GetPlaceData(DataID);
	if (block == nullptr && place == nullptr) return;

	//�C���X�^���V���O�f�[�^ID���v�Z����B
	int modelID = 0;
	if (block != nullptr)modelID = block->GetItemData()->itemTypeID;
	if (place != nullptr)modelID = place->GetItemData()->itemTypeID + m_itemDataFile->GetBlockArraySize();

	ChunkBlockDirty = true;
	m_IsModelUpdated = true;

	//�f�[�^���쐬
	InstancingData data;
	data.pos = pos;
	data.rot = rot;
	data.scale = scale;
	//�z��ɒǉ�
	m_InstancingData[modelID].push_back(data);
	//�i�r���b�V���X�V�̃t���O�𗧂Ă�B
	m_LoadingByChunk->NvmDirtyFlagUp(m_LoadID[0], m_LoadID[1]);
}

void ChunkBlock::RemoveBlock(Block* blockptr)
{
	int DataID = static_cast<int>(blockptr->GetParam().BlockID);

	auto* block = m_itemDataFile->GetBlockData(DataID);
	auto* place = m_itemDataFile->GetPlaceData(DataID);
	if (block == nullptr && place == nullptr) return;

	//�C���X�^���V���O�f�[�^ID���v�Z����B
	int modelID = 0;
	if (block != nullptr)modelID = block->GetItemData()->itemTypeID;
	if (place != nullptr)modelID = place->GetItemData()->itemTypeID + m_itemDataFile->GetBlockArraySize();

	ChunkBlockDirty = true;
	m_IsModelUpdated = true;

	//�폜����u���b�N�̒l�����Z�b�g
	blockptr->ResetParams();
	//�C���X�^���V���O�f�[�^���N���A
	m_InstancingData[modelID].clear();
	//�C���X�^���V���O�f�[�^�����Z�b�g
	//��������Z�b�g���Ȃ���
	for (int x = 0; x < ChunkWidth; x++)
	{
		for (int y = 0; y < ChunkHeight; y++)
		{
			for (int z = 0; z < ChunkWidth; z++)
			{
				auto& block = m_Block[x][y][z];
				if (block.GetParam().BlockID != blockptr->GetParam().BlockID)
				{
					continue;
				}
				if (static_cast<int>(block.GetParam().Durable) > 0)
				{
					//�f�[�^���쐬
					InstancingData data;
					data.pos = block.GetPosition();
					data.rot = block.GetRotation();
					data.scale = block.GetScale();
					//�z��ɒǉ�
					m_InstancingData[modelID].push_back(data);
				}
			}
		}
	}
	//�i�r���b�V���X�V�̃t���O�𗧂Ă�B
	m_LoadingByChunk->NvmDirtyFlagUp(m_LoadID[0], m_LoadID[1]);
}