#include "stdafx.h"
#include "LoadingByChunk.h"

LoadingByChunk::~LoadingByChunk()
{

}

bool LoadingByChunk::Start()
{
	//���f����������
	InitModels();
	SetPlayerPos(Vector3::Zero);
	//�u���b�N��������
	InitChunkBlocks();
	//�R���C�_�[��������
	InitChunkCols();
	LinkChunk();
	return true;
}

void LoadingByChunk::OnDestroy()
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

void LoadingByChunk::InitChunkCols()
{
	int Grid[2] = { 0 };
	//�v���C���[�̂���`�����N
	Grid[0] = PlayerPosInGrid[0];
	Grid[1] = PlayerPosInGrid[1];
	Grid[0] -= std::floor(LoadingChunkCols / 2);
	Grid[1] -= std::floor(LoadingChunkCols / 2);
	//�ő�l�ƍŏ��l�����߂Ă���
	//�ő�l�̓`�����N�̒[���烍�[�h����`�����N�̔���������������
	//�ŏ��l��0
	Grid[0] = max(min(Grid[0], MAX_CHUNK_SIDE - std::floor(LoadingChunkCols / 2)), 0);
	Grid[1] = max(min(Grid[1], MAX_CHUNK_SIDE - std::floor(LoadingChunkCols / 2)), 0);

	//���݈ړ����̃O���b�h
	int NowGrid[2];

	for (int x = 0; x < LoadingChunkCols; x++)
	{
		NowGrid[0] = Grid[0] + x;
		for (int z = 0; z < LoadingChunkCols; z++)
		{
			NowGrid[1] = Grid[1] + z;
			m_ChunkCol[x][z].SetChunkID(NowGrid);
			//�Ή�����`�����N�u���b�N���Z�b�g
			//�`�����N�u���b�N�̐^��9�`�����N���Ή����Ă���
			//todo �[�����̎��Ƀ����N�����������Ȃ�Ǝv���̂Œ���
			int LinkChunk[2] = { 0 };
			LinkChunk[0] = std::floor(LoadingChunks / 2) + x;
			LinkChunk[1] = std::floor(LoadingChunks / 2) + z;
			m_ChunkCol[x][z].LinkChunkBlocks(&m_ChunkBlock[LinkChunk[0]][LinkChunk[1]]);
			//������
			m_ChunkCol[x][z].Init();
		}
	}

}

void LoadingByChunk::InitChunkBlocks()
{
	int Grid[2] = { 0 };
	//�v���C���[�̂���`�����N
	Grid[0] = PlayerPosInGrid[0];
	Grid[1] = PlayerPosInGrid[1];
	Grid[0] -= std::floor(LoadingChunks / 2);
	Grid[1] -= std::floor(LoadingChunks / 2);
	//�ő�l�ƍŏ��l�����߂Ă���
	//�ő�l�̓`�����N�̒[���烍�[�h����`�����N�̔���������������
	//�ŏ��l��0
	Grid[0] = max(min(Grid[0], MAX_CHUNK_SIDE - std::floor(LoadingChunks / 2)), 0);
	Grid[1] = max(min(Grid[1], MAX_CHUNK_SIDE - std::floor(LoadingChunks / 2)), 0);
	//���݈ړ����̃O���b�h
	int NowGrid[2];

	for (int x = 0; x < LoadingChunks; x++)
	{
		NowGrid[0] = Grid[0] + x;
		for (int z = 0; z < LoadingChunks; z++)
		{
			NowGrid[1] = Grid[1] + z;
			m_ChunkBlock[x][z].SetSaveDataFile(m_SaveDataFile);
			m_ChunkBlock[x][z].SetChunkID(NowGrid);
			//������
			m_ChunkBlock[x][z].Init();
		}
	}
}

void LoadingByChunk::InitModels()
{
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

void LoadingByChunk::Update()
{
	//���f���̍X�V
	UpdateModels();

	for (int Chunk_X = 0; Chunk_X < LoadingChunkCols; Chunk_X++)
	{
		for (int Chunk_Z = 0; Chunk_Z < LoadingChunkCols; Chunk_Z++)
		{
			//�R���C�_�[���X�V
			m_ChunkCol[Chunk_X][Chunk_Z].UpdateCol();
		}
	}


	if (m_isDirty == false)
	{
		return;
	}

	//�`�����N�ړ�
	UpdateMoveChunk();

	////////////////////////////////////////////
	/////�������牺�͍X�V����K�v������Ƃ�/////
	////////////////////////////////////////////
	for (int Chunk_X = 0; Chunk_X < m_config->GetLoadingChunkRange(); Chunk_X++)
	{
		for (int Chunk_Y = 0; Chunk_Y < m_config->GetLoadingChunkRange(); Chunk_Y++)
		{
			//�v���C���[�𒆐S�Ƀ��[�h����
			int LoadingGrid[2] = { 0 };
			for (int i = 0; i < 2; i++)
			{
				LoadingGrid[i] = PlayerPosInGrid[i];
				LoadingGrid[i] -= m_config->GetLoadingChunkRange() / 2;
			}
			LoadingGrid[0] += Chunk_X;
			LoadingGrid[1] += Chunk_Y;

			//���[�h����
		}
	}

	//�X�V�t���O������
	m_isDirty = false;
}

void LoadingByChunk::UpdateMoveChunk()
{
	//�u���b�N���ړ�
	UpdateChunkBlocksAndTerrains();
	//�R���C�_�[���ړ�
	UpdateChunkCols();
}

void LoadingByChunk::UpdateChunkCols()
{
	int Grid[2] = { 0 };
	//�v���C���[�̍����̃`�����N
	Grid[0] = PlayerPosInGrid[0];
	Grid[1] = PlayerPosInGrid[1];
	Grid[0] -= std::floor(LoadingChunkCols / 2);
	Grid[1] -= std::floor(LoadingChunkCols / 2);
	//�ő�l�ƍŏ��l�����߂Ă���
	//�ő�l�̓`�����N�̒[���烍�[�h����`�����N�̔���������������
	//�ŏ��l��0
	Grid[0] = max(min(Grid[0], MAX_CHUNK_SIDE - std::floor(LoadingChunkCols / 2)), 0);
	Grid[1] = max(min(Grid[1], MAX_CHUNK_SIDE - std::floor(LoadingChunkCols / 2)), 0);

	//���݈ړ����̃O���b�h
	int NowGrid[2];

	for (int x = 0; x < LoadingChunkCols; x++)
	{
		NowGrid[0] = Grid[0] + x;
		for (int z = 0; z < LoadingChunkCols; z++)
		{
			NowGrid[1] = Grid[1] + z;
			//�`�����NID���Z�b�g
			m_ChunkCol[x][z].SetChunkID(NowGrid);
			//�`�����N��R�Â�
			LinkChunk();
			//�`�����N�ړ�
			m_ChunkCol[x][z].MoveChunk();
		}
	}

}

void LoadingByChunk::UpdateChunkBlocksAndTerrains()
{
	int Grid[2] = { 0 };
	//�v���C���[�̍����̃`�����N
	Grid[0] = PlayerPosInGrid[0];
	Grid[1] = PlayerPosInGrid[1];
	Grid[0] -= std::floor(LoadingChunks / 2);
	Grid[1] -= std::floor(LoadingChunks / 2);
	//�ő�l�ƍŏ��l�����߂Ă���
	//�ő�l�̓`�����N�̒[���烍�[�h����`�����N�̔���������������
	//�ŏ��l��0
	Grid[0] = max(min(Grid[0], MAX_CHUNK_SIDE - std::floor(LoadingChunks / 2)), 0);
	Grid[1] = max(min(Grid[1], MAX_CHUNK_SIDE - std::floor(LoadingChunks / 2)), 0);
	//���݈ړ����̃O���b�h
	int NowGrid[2];

	for (int x = 0; x < LoadingChunks; x++)
	{
		NowGrid[0] = Grid[0] + x;
		for (int z = 0; z < LoadingChunks; z++)
		{
			NowGrid[1] = Grid[1] + z;
			//�`�����NID���Z�b�g
			m_ChunkBlock[x][z].SetChunkID(NowGrid);
			//�`�����N�ړ�
			m_ChunkBlock[x][z].MoveChunk();

			const auto& terrainWorld = m_TerrainManager->GetTerrainWorld(x, z);
			//�e���C�����[���h�Ƀ`�����N�f�[�^���Z�b�g
			if (terrainWorld->SetTerrainChunkData(&m_TerrainManager->GetTerrainChunkData(NowGrid[0], NowGrid[1])))
			{
				//�e���C�����[���h�̑Ή����Ă���`�����N�ɕύX����������
				//�e���C�����[���h�̈ʒu���Z�b�g
				Vector3 terrainPos = Vector3::Zero;
				terrainPos.x = static_cast<float>(NowGrid[0] * ChunkWidth * OBJECT_UNIT);
				terrainPos.z = static_cast<float>(NowGrid[1] * ChunkWidth * OBJECT_UNIT);
				terrainWorld->SetTerrainPosition(terrainPos);
			}
		}
	}
}

void LoadingByChunk::UpdateTerains()
{

}

void LoadingByChunk::LinkChunk()
{
	//todo ���t�@�N�^�����O�ŃR�[�h������
	for (int colx = 0; colx < LoadingChunkCols; colx++)
	{
		for (int colz = 0; colz < LoadingChunkCols; colz++)
		{
			int ColChunkID[2] = { 0 };
			//�R���C�_�[�̃`�����NID���擾
			m_ChunkCol[colx][colz].GetChunkID(ColChunkID);
			bool Linked = false;
			for (int blockx = 0; blockx < LoadingChunks; blockx++)
			{
				Linked = false;
				for (int blockz = 0; blockz < LoadingChunks; blockz++)
				{
					int BlockChunkID[2] = { 0 };
					//�u���b�N�̃`�����NID���擾
					m_ChunkBlock[blockx][blockz].GetChunkID(BlockChunkID);
					if (ColChunkID[0] == BlockChunkID[0])
					{
						if (ColChunkID[1] == BlockChunkID[1])
						{
							//�Ή����Ă���`�����N�������Ȃ̂ŕR�Â�
							m_ChunkCol[colx][colz].LinkChunkBlocks(&m_ChunkBlock[blockx][blockz]);
							//�Ή����Ă���`�����N�f�[�^���Z�b�g
							//�`�����N�f�[�^�͑��݂���`�����N������������̂Ń`�����NID����擾
							m_ChunkCol[colx][colz].LinkTerrainWorld(&m_TerrainManager->GetTerrainChunkData(ColChunkID[0], ColChunkID[1]));
							Linked = true;
						}
					}
					if (Linked == true)
					{
						//�����N�ŗ����̂�break
						break;
					}
				}
				if (Linked == true)
				{
					//�����N�ŗ����̂�break
					break;
				}
			}
		}
	}
}

ChunkBlock& LoadingByChunk::GetChunkBlocks(int ID[2])
{
	for (int x = 0; x < LoadingChunks; x++)
	{
		for (int z = 0; z < LoadingChunks; z++)
		{
			int chunkID[2] = { 0 };
			m_ChunkBlock[x][z].GetChunkID(chunkID);
			if (chunkID[0] == ID[0] && chunkID[1] == ID[1])
			{
				return m_ChunkBlock[x][z];
			}
		}
	}
}

void LoadingByChunk::UpdateModels()
{
	bool Dirty = false;
	for (int x = 0; x < LoadingChunks; x++)
	{
		for (int z = 0; z < LoadingChunks; z++)
		{
			if (m_ChunkBlock[x][z].IsModelUpdated())
			{
				//�X�V����
				Dirty = true;
			}
			if (Dirty)
			{
				break;
			}
		}
		if (Dirty)
		{
			break;
		}
	}

	if (Dirty == false)
	{
		//�X�V�����Ƃ�return
		return;
	}

	for (int BlockID = 0; BlockID < BlockKinds; BlockID++)
	{
		//�C���X�^���V���O�f�[�^�����Z�b�g
		BlockModel[BlockID]->ResetInstancingDatas();
		for (int x = 0; x < LoadingChunks; x++)
		{
			for (int z = 0; z < LoadingChunks; z++)
			{
				auto& Datas = m_ChunkBlock[x][z].GetInstancingData(BlockID);
				for (auto& data : Datas)
				{
					//�C���X�^���V���O�f�[�^��ǉ�
					BlockModel[BlockID]->UpdateInstancingData(data.pos,data.rot,data.scale);
				}
			}
		}
	}
}