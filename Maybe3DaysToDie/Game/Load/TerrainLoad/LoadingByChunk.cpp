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
	//ブロックを初期化
	InitChunkBlocks();
	//コライダーを初期化
	InitChunkCols();
	return true;
}

void LoadingByChunk::InitChunkCols()
{
	int Grid[2] = { 0 };
	//プレイヤーのいるチャンク
	Grid[0] = PlayerPosInGrid[0];
	Grid[1] = PlayerPosInGrid[1];
	Grid[0] -= std::floor(LoadingChunkCols / 2);
	Grid[1] -= std::floor(LoadingChunkCols / 2);
	//最大値と最小値を決めておく
	//最大値はチャンクの端からロードするチャンクの半分を引いたもの
	//最小値は0
	Grid[0] = max(min(Grid[0], MAX_CHUNK_SIDE - std::floor(LoadingChunkCols / 2)), 0);
	Grid[1] = max(min(Grid[1], MAX_CHUNK_SIDE - std::floor(LoadingChunkCols / 2)), 0);

	//現在移動中のグリッド
	int NowGrid[2];

	for (int x = 0; x < LoadingChunkCols; x++)
	{
		NowGrid[0] = Grid[0] + x;
		for (int z = 0; z < LoadingChunkCols; z++)
		{
			NowGrid[1] = Grid[1] + z;
			m_ChunkCol[x][z].SetChunkID(NowGrid);
			//対応するチャンクブロックをセット
			//チャンクブロックの真ん中9チャンクが対応している
			//todo 端っこの時にリンクがおかしくなると思うので直す
			int LinkChunk[2] = { 0 };
			LinkChunk[0] = std::floor(LoadingChunks / 2) + x;
			LinkChunk[1] = std::floor(LoadingChunks / 2) + z;
			m_ChunkCol[x][z].LinkChunkBlocks(&m_ChunkBlock[LinkChunk[0]][LinkChunk[1]]);
			//初期化
			m_ChunkCol[x][z].Init();
		}
	}

}

void LoadingByChunk::InitChunkBlocks()
{
	int Grid[2] = { 0 };
	//プレイヤーのいるチャンク
	Grid[0] = PlayerPosInGrid[0];
	Grid[1] = PlayerPosInGrid[1];
	Grid[0] -= std::floor(LoadingChunks / 2);
	Grid[1] -= std::floor(LoadingChunks / 2);
	//最大値と最小値を決めておく
	//最大値はチャンクの端からロードするチャンクの半分を引いたもの
	//最小値は0
	Grid[0] = max(min(Grid[0], MAX_CHUNK_SIDE - std::floor(LoadingChunks / 2)), 0);
	Grid[1] = max(min(Grid[1], MAX_CHUNK_SIDE - std::floor(LoadingChunks / 2)), 0);
	//現在移動中のグリッド
	int NowGrid[2];

	for (int x = 0; x < LoadingChunks; x++)
	{
		NowGrid[0] = Grid[0] + x;
		for (int z = 0; z < LoadingChunks; z++)
		{
			NowGrid[1] = Grid[1] + z;
			m_ChunkBlock[x][z].SetSaveDataFile(m_SaveDataFile);
			m_ChunkBlock[x][z].SetChunkID(NowGrid);
			//初期化
			m_ChunkBlock[x][z].Init();
		}
	}
}

void LoadingByChunk::Update()
{
	if (m_BlockManager->IsBlockDirty())
	{
		for (int Chunk_X = 0; Chunk_X < LoadingChunkCols; Chunk_X++)
		{
			for (int Chunk_Z = 0; Chunk_Z < LoadingChunkCols; Chunk_Z++)
			{
				//コライダーを更新
				m_ChunkCol[Chunk_X][Chunk_Z].UpdateCol();
			}
		}
		m_BlockManager->ResetBlockDirty();
	}


	if (m_isDirty == false)
	{
		return;
	}

	//チャンク移動
	UpdateMoveChunk();

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

void LoadingByChunk::UpdateMoveChunk()
{
	//ブロックを移動
	UpdateChunkBlocks();
	//コライダーを移動
	UpdateChunkCols();
}

void LoadingByChunk::UpdateChunkCols()
{
	int Grid[2] = { 0 };
	//プレイヤーの左下のチャンク
	Grid[0] = PlayerPosInGrid[0];
	Grid[1] = PlayerPosInGrid[1];
	Grid[0] -= std::floor(LoadingChunkCols / 2);
	Grid[1] -= std::floor(LoadingChunkCols / 2);
	//最大値と最小値を決めておく
	//最大値はチャンクの端からロードするチャンクの半分を引いたもの
	//最小値は0
	Grid[0] = max(min(Grid[0], MAX_CHUNK_SIDE - std::floor(LoadingChunkCols / 2)), 0);
	Grid[1] = max(min(Grid[1], MAX_CHUNK_SIDE - std::floor(LoadingChunkCols / 2)), 0);

	//現在移動中のグリッド
	int NowGrid[2];

	for (int x = 0; x < LoadingChunkCols; x++)
	{
		NowGrid[0] = Grid[0] + x;
		for (int z = 0; z < LoadingChunkCols; z++)
		{
			NowGrid[1] = Grid[1] + z;
			//チャンクIDをセット
			m_ChunkCol[x][z].SetChunkID(NowGrid);
			//チャンクを紐づけ
			LinkChunk();
			//チャンク移動
			m_ChunkCol[x][z].MoveChunk();
		}
	}

}

void LoadingByChunk::UpdateChunkBlocks()
{
	int Grid[2] = { 0 };
	//プレイヤーの左下のチャンク
	Grid[0] = PlayerPosInGrid[0];
	Grid[1] = PlayerPosInGrid[1];
	Grid[0] -= std::floor(LoadingChunks / 2);
	Grid[1] -= std::floor(LoadingChunks / 2);
	//最大値と最小値を決めておく
	//最大値はチャンクの端からロードするチャンクの半分を引いたもの
	//最小値は0
	Grid[0] = max(min(Grid[0], MAX_CHUNK_SIDE - std::floor(LoadingChunks / 2)), 0);
	Grid[1] = max(min(Grid[1], MAX_CHUNK_SIDE - std::floor(LoadingChunks / 2)), 0);
	//現在移動中のグリッド
	int NowGrid[2];

	for (int x = 0; x < LoadingChunks; x++)
	{
		NowGrid[0] = Grid[0] + x;
		for (int z = 0; z < LoadingChunks; z++)
		{
			NowGrid[1] = Grid[1] + z;
			//チャンクIDをセット
			m_ChunkBlock[x][z].SetChunkID(NowGrid);
			//チャンク移動
			m_ChunkBlock[x][z].MoveChunk();
		}
	}
}

void LoadingByChunk::LinkChunk()
{
	//todo リファクタリングでコード見直し
	for (int colx = 0; colx < LoadingChunkCols; colx++)
	{
		for (int colz = 0; colz < LoadingChunkCols; colz++)
		{
			int ColChunkID[2] = { 0 };
			//コライダーのチャンクIDを取得
			m_ChunkCol[colx][colz].GetChunkID(ColChunkID);
			bool Linked = false;
			for (int blockx = 0; blockx < LoadingChunks; blockx++)
			{
				Linked = false;
				for (int blockz = 0; blockz < LoadingChunks; blockz++)
				{
					int BlockChunkID[2] = { 0 };
					//ブロックのチャンクIDを取得
					m_ChunkBlock[blockx][blockz].GetChunkID(BlockChunkID);
					if (ColChunkID[0] == BlockChunkID[0])
					{
						if (ColChunkID[1] == BlockChunkID[1])
						{
							//対応しているチャンクが同じなので紐づけ
							m_ChunkCol[colx][colz].LinkChunkBlocks(&m_ChunkBlock[blockx][blockz]);
							Linked = true;
						}
					}
					if (Linked == true)
					{
						//リンクで来たのでbreak
						break;
					}
				}
				if (Linked == true)
				{
					//リンクで来たのでbreak
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