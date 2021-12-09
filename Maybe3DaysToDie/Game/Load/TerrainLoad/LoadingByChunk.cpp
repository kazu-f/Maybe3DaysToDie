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
		//BlockManagerをセットしてください。
		std::abort();
	}
	SetPlayerPos(Vector3::Zero);
	for (int Chunk_X = 0; Chunk_X < LoadingChunks; Chunk_X++)
	{
		for (int Chunk_Z = 0; Chunk_Z < LoadingChunks; Chunk_Z++)
		{
			//IDをセット
			int ChunkID[2] = { 0 };
			ChunkID[0] += PlayerPosInGrid[0] + Chunk_X - 1 ;
			ChunkID[1] += PlayerPosInGrid[1] + Chunk_Z - 1 ;
			m_ChunkBlock[Chunk_X][Chunk_Z].SetChunkID(ChunkID);
			//初期化
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
				//コライダーを更新
				m_ChunkBlock[Chunk_X][Chunk_Z].UpdateCol();
			}
		}
		m_BlockManager->ResetBlockDirty();
	}


	if (m_isDirty == false)
	{
		return;
	}

	//todo めちゃくちゃ汚いコードなので後から見直し
	for (int i = 0; i < 2; i++)
	{
		if (IsChunkMove[i] == true)
		{
			if (i == 0)
			{
				//X軸方向に移動
				if (IsMoveUp[i] == true)
				{
					//プラス方向に移動
					for (int Chunk_X = 0; Chunk_X < LoadingChunks; Chunk_X++)
					{
						for (int Chunk_Z = 0; Chunk_Z < LoadingChunks; Chunk_Z++)
						{
							int ChunkID[2] = { 0 };
							//現在のチャンクIDを取得
							m_ChunkBlock[Chunk_X][Chunk_Z].GetChunkID(ChunkID);
							if (ChunkID[0] <= PlayerPosInGrid[0] - 2)
							{
								//Xが現在の位置より2低いとき移動
								ChunkID[0] = PlayerPosInGrid[0] + 1;
								m_ChunkBlock[Chunk_X][Chunk_Z].MoveChunk(ChunkID);
							}
						}
					}
				}
				else
				{
					//マイナス方向に移動
					for (int Chunk_X = 0; Chunk_X < LoadingChunks; Chunk_X++)
					{
						for (int Chunk_Z = 0; Chunk_Z < LoadingChunks; Chunk_Z++)
						{
							int ChunkID[2] = { 0 };
							//現在のチャンクIDを取得
							m_ChunkBlock[Chunk_X][Chunk_Z].GetChunkID(ChunkID);
							if (ChunkID[0] >= PlayerPosInGrid[0] + 2)
							{
								//Xが現在の位置より2大きいとき移動
								ChunkID[0] = PlayerPosInGrid[0] - 1;
								m_ChunkBlock[Chunk_X][Chunk_Z].MoveChunk(ChunkID);
							}
						}
					}
				}
			}
			else if (i == 1)
			{
				//Z軸方向に移動
				if (IsMoveUp[i] == true)
				{
					//プラス方向に移動
					for (int Chunk_X = 0; Chunk_X < LoadingChunks; Chunk_X++)
					{
						for (int Chunk_Z = 0; Chunk_Z < LoadingChunks; Chunk_Z++)
						{
							int ChunkID[2] = { 0 };
							//現在のチャンクIDを取得
							m_ChunkBlock[Chunk_X][Chunk_Z].GetChunkID(ChunkID);
							if (ChunkID[1] <= PlayerPosInGrid[1] - 2)
							{
								//Zが現在の位置より2低いとき移動
								ChunkID[1] = PlayerPosInGrid[1] + 1;
								m_ChunkBlock[Chunk_X][Chunk_Z].MoveChunk(ChunkID);
							}
						}
					}
				}
				else
				{
					//マイナス方向に移動
					for (int Chunk_X = 0; Chunk_X < LoadingChunks; Chunk_X++)
					{
						for (int Chunk_Z = 0; Chunk_Z < LoadingChunks; Chunk_Z++)
						{
							int ChunkID[2] = { 0 };
							//現在のチャンクIDを取得
							m_ChunkBlock[Chunk_X][Chunk_Z].GetChunkID(ChunkID);
							if (ChunkID[1] >= PlayerPosInGrid[1] + 2)
							{
								//Zが現在の位置より2大きいとき移動
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
	/////ここから下は更新する必要があるとき/////
	////////////////////////////////////////////
	for (int Chunk_X = 0; Chunk_X < m_config->GetLoadingChunkRange(); Chunk_X++)
	{
		for (int Chunk_Y = 0; Chunk_Y < m_config->GetLoadingChunkRange(); Chunk_Y++)
		{
			//プレイヤーを中心にロードする
			int LoadingGrid[2] = { 0 };
			for (int i = 0; i < 2; i++)
			{
				LoadingGrid[i] = PlayerPosInGrid[i];
				LoadingGrid[i] -= m_config->GetLoadingChunkRange() / 2;
			}
			LoadingGrid[0] += Chunk_X;
			LoadingGrid[1] += Chunk_Y;

			//ロードする
		}
	}

	//更新フラグを下す
	m_isDirty = false;
}