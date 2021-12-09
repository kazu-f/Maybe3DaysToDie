#include "stdafx.h"
#include "LoadingByChunk.h"

LoadingByChunk::LoadingByChunk()
{

}

LoadingByChunk::~LoadingByChunk()
{

}

bool LoadingByChunk::Start()
{
	if (IsBlockManagerSet == false)
	{
		//BlockManager���Z�b�g���Ă��������B
		std::abort();
	}
	SetPlayerPos(Vector3::Zero);
	for (int Chunk_X = 0; Chunk_X < LoadingChunks; Chunk_X++)
	{
		for (int Chunk_Z = 0; Chunk_Z < LoadingChunks; Chunk_Z++)
		{
			//ID���Z�b�g
			int ChunkID[2] = { 0 };
			ChunkID[0] += PlayerPosInGrid[0] + Chunk_X - 1 ;
			ChunkID[1] += PlayerPosInGrid[1] + Chunk_Z - 1 ;
			m_ChunkBlock[Chunk_X][Chunk_Z].SetChunkID(ChunkID);
			//������
			m_ChunkBlock[Chunk_X][Chunk_Z].Init();
		}
	}
	return true;
}

void LoadingByChunk::Update()
{
	if (m_BlockManager->IsBlockDirty())
	{
		for (int Chunk_X = 0; Chunk_X < LoadingChunks; Chunk_X++)
		{
			for (int Chunk_Z = 0; Chunk_Z < LoadingChunks; Chunk_Z++)
			{
				//�R���C�_�[���X�V
				m_ChunkBlock[Chunk_X][Chunk_Z].UpdateCol();
			}
		}
		m_BlockManager->ResetBlockDirty();
	}


	if (m_isDirty == false)
	{
		return;
	}

	//todo �߂��Ⴍ���ቘ���R�[�h�Ȃ̂Ōォ�猩����
	for (int i = 0; i < 2; i++)
	{
		if (IsChunkMove[i] == true)
		{
			if (i == 0)
			{
				//X�������Ɉړ�
				if (IsMoveUp[i] == true)
				{
					//�v���X�����Ɉړ�
					for (int Chunk_X = 0; Chunk_X < LoadingChunks; Chunk_X++)
					{
						for (int Chunk_Z = 0; Chunk_Z < LoadingChunks; Chunk_Z++)
						{
							int ChunkID[2] = { 0 };
							//���݂̃`�����NID���擾
							m_ChunkBlock[Chunk_X][Chunk_Z].GetChunkID(ChunkID);
							if (ChunkID[0] <= PlayerPosInGrid[0] - 2)
							{
								//X�����݂̈ʒu���2�Ⴂ�Ƃ��ړ�
								ChunkID[0] = PlayerPosInGrid[0] + 1;
								m_ChunkBlock[Chunk_X][Chunk_Z].MoveChunk(ChunkID);
							}
						}
					}
				}
				else
				{
					//�}�C�i�X�����Ɉړ�
					for (int Chunk_X = 0; Chunk_X < LoadingChunks; Chunk_X++)
					{
						for (int Chunk_Z = 0; Chunk_Z < LoadingChunks; Chunk_Z++)
						{
							int ChunkID[2] = { 0 };
							//���݂̃`�����NID���擾
							m_ChunkBlock[Chunk_X][Chunk_Z].GetChunkID(ChunkID);
							if (ChunkID[0] >= PlayerPosInGrid[0] + 2)
							{
								//X�����݂̈ʒu���2�傫���Ƃ��ړ�
								ChunkID[0] = PlayerPosInGrid[0] - 1;
								m_ChunkBlock[Chunk_X][Chunk_Z].MoveChunk(ChunkID);
							}
						}
					}
				}
			}
			else if (i == 1)
			{
				//Z�������Ɉړ�
				if (IsMoveUp[i] == true)
				{
					//�v���X�����Ɉړ�
					for (int Chunk_X = 0; Chunk_X < LoadingChunks; Chunk_X++)
					{
						for (int Chunk_Z = 0; Chunk_Z < LoadingChunks; Chunk_Z++)
						{
							int ChunkID[2] = { 0 };
							//���݂̃`�����NID���擾
							m_ChunkBlock[Chunk_X][Chunk_Z].GetChunkID(ChunkID);
							if (ChunkID[1] <= PlayerPosInGrid[1] - 2)
							{
								//Z�����݂̈ʒu���2�Ⴂ�Ƃ��ړ�
								ChunkID[1] = PlayerPosInGrid[1] + 1;
								m_ChunkBlock[Chunk_X][Chunk_Z].MoveChunk(ChunkID);
							}
						}
					}
				}
				else
				{
					//�}�C�i�X�����Ɉړ�
					for (int Chunk_X = 0; Chunk_X < LoadingChunks; Chunk_X++)
					{
						for (int Chunk_Z = 0; Chunk_Z < LoadingChunks; Chunk_Z++)
						{
							int ChunkID[2] = { 0 };
							//���݂̃`�����NID���擾
							m_ChunkBlock[Chunk_X][Chunk_Z].GetChunkID(ChunkID);
							if (ChunkID[1] >= PlayerPosInGrid[1] + 2)
							{
								//Z�����݂̈ʒu���2�傫���Ƃ��ړ�
								ChunkID[1] = PlayerPosInGrid[1] - 1;
								m_ChunkBlock[Chunk_X][Chunk_Z].MoveChunk(ChunkID);
							}
						}
					}
				}
			}
		}
		IsChunkMove[i] = false;
		IsMoveUp[i] = false;
	}


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