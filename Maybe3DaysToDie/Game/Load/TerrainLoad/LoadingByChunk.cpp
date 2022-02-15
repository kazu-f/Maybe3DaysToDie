#include "stdafx.h"
#include "LoadingByChunk.h"
#include "Item/ItemDataFile.h"
#include "Item/GameItemPlaceObj.h"
#include "Item/BlockItem.h"
#include "Item/GameItemTerrain.h"

LoadingByChunk::LoadingByChunk()
{
	m_itemDatas = ItemDataFile::GetInstance();
	int modelSize = m_itemDatas->GetBlockArraySize() + m_itemDatas->GetPlaceArraySize();
	//サイズの最大値セット
	BlockModel.resize(modelSize);
}

LoadingByChunk::~LoadingByChunk()
{

}

bool LoadingByChunk::Start()
{
	//モデルを初期化
	InitModels();
	SetPlayerPos(Vector3::Zero);
	//ブロックを初期化
	InitChunkBlocks();
	//コライダーを初期化
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
	//最大値はチャンクの端からロードするチャンクを引いたもの
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
			m_ChunkBlock[x][z].SetLoadingByChunk(this);
			//初期化
			m_ChunkBlock[x][z].Init();
		}
	}
}

void LoadingByChunk::InitModels()
{
	int m_modelNum = 0;
	for (int blockID = 0; blockID < m_itemDatas->GetBlockArraySize(); blockID++)
	{
		//モデルを初期化
		//ブロックの名前がかぶっていないのでまだ、そのモデルがない
		ModelInitData InitData;
		auto* block = m_itemDatas->GetBlockDataTypeID(blockID);
		if (block == nullptr)
		{
			m_modelNum++;
			continue;
		}
		InitData.m_tkmFilePath = block->GetItemData()->tkmPath.c_str();

		prefab::ModelRender* model = NewGO<prefab::ModelRender>(0);
		//model->SetActiveFlag(false);
		//チャンクのサイズ分インスタンシング描画する
		model->Init(InitData, nullptr, 0, MaxInstanceNum);
		BlockModel[m_modelNum] = model;
		m_modelNum++;
	}
	for (int ObjectID = 0; ObjectID < m_itemDatas->GetPlaceArraySize(); ObjectID++)
	{
		//モデルを初期化
		//ブロックの名前がかぶっていないのでまだ、そのモデルがない
		ModelInitData InitData;
		auto* place = m_itemDatas->GetPlaceObjTypeID(ObjectID);
		if (place == nullptr)
		{
			m_modelNum++;
			continue;
		}
		InitData.m_tkmFilePath = place->GetItemData()->tkmPath.c_str();

		prefab::ModelRender* model = NewGO<prefab::ModelRender>(0);
		//model->SetActiveFlag(false);
		//チャンクのサイズ分インスタンシング描画する
		model->Init(InitData, nullptr, 0, MaxInstanceNum);
		BlockModel[m_modelNum] = model;
		m_modelNum++;
	}
}

void LoadingByChunk::Update()
{
	//モデルの更新
	UpdateModels();

	for (int Chunk_X = 0; Chunk_X < LoadingChunkCols; Chunk_X++)
	{
		for (int Chunk_Z = 0; Chunk_Z < LoadingChunkCols; Chunk_Z++)
		{
			//コライダーを更新
			m_ChunkCol[Chunk_X][Chunk_Z].UpdateCol();
		}
	}


	if (m_isDirty == false)
	{
		return;
	}

	////////////////////////////////////////////
	/////ここから下は更新する必要があるとき/////
	////////////////////////////////////////////
	for (int x = 0; x < LoadingChunks; x++)
	{
		for (int z = 0; z < LoadingChunks; z++)
		{
			//移動したのですべてのNVMの更新フラグを立てる
			m_IsUpdatedChunk[x][z] = true;
		}
	}
	//チャンク移動
	UpdateMoveChunk();

	//更新フラグを下す
	m_isDirty = false;
}

void LoadingByChunk::UpdateMoveChunk()
{
	//ブロックを移動
	UpdateChunkBlocksAndTerrains();
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
	//最大値はチャンクの端からロードするチャンクを引いたもの
	//最小値は0
	Grid[0] = max(min(Grid[0], MAX_CHUNK_SIDE - LoadingChunkCols), 0);
	Grid[1] = max(min(Grid[1], MAX_CHUNK_SIDE - LoadingChunkCols), 0);

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

void LoadingByChunk::UpdateChunkBlocksAndTerrains()
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
	Grid[0] = max(min(Grid[0], MAX_CHUNK_SIDE - LoadingChunks), 0);
	Grid[1] = max(min(Grid[1], MAX_CHUNK_SIDE - LoadingChunks), 0);
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

			const auto& terrainWorld = m_TerrainManager->GetTerrainWorld(x, z);
			//テラインワールドにチャンクデータをセット
			if (terrainWorld->SetTerrainChunkData(&m_TerrainManager->GetTerrainChunkData(NowGrid[0], NowGrid[1])))
			{
				//テラインワールドの対応しているチャンクに変更があった時
				//テラインワールドの位置をセット
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

void LoadingByChunk::UpdateWorldTableData()
{

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
							//対応しているチャンクデータをセット
							//チャンクデータは存在するチャンク数分だけあるのでチャンクIDから取得
							m_ChunkCol[colx][colz].LinkTerrainWorld(&m_TerrainManager->GetTerrainChunkData(ColChunkID[0], ColChunkID[1]));
							m_ChunkBlock[colx][colz].SetLoadChunkID(blockx, blockz);
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

void LoadingByChunk::UpdateModels()
{
	bool Dirty = false;
	for (int x = 0; x < LoadingChunks; x++)
	{
		for (int z = 0; z < LoadingChunks; z++)
		{
			if (m_ChunkBlock[x][z].IsModelUpdated())
			{
				//todo 更新フラグを下す
				//更新あり
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
		//更新無いときreturn
		return;
	}
	int modelID = 0;
	for (int BlockID = 0; BlockID < m_itemDatas->GetBlockArraySize(); BlockID++)
	{
		auto* block = m_itemDatas->GetBlockDataTypeID(BlockID);
		if (block == nullptr) {
			modelID++;
			continue;
		}

		//インスタンシングデータをリセット
		BlockModel[modelID]->ResetInstancingDatas();
		for (int x = 0; x < LoadingChunks; x++)
		{
			for (int z = 0; z < LoadingChunks; z++)
			{
				auto& Datas = m_ChunkBlock[x][z].GetInstancingData(modelID);
				for (auto& data : Datas)
				{
					//インスタンシングデータを追加
 					BlockModel[modelID]->UpdateInstancingData(data.pos,data.rot,data.scale);
				}
				m_ChunkBlock[x][z].ResetModelUpdated();
			}
		}
		modelID++;
	}
	for (int ObjID = 0; ObjID < m_itemDatas->GetPlaceArraySize(); ObjID++)
	{
		auto* block = m_itemDatas->GetPlaceObjTypeID(ObjID);
		if (block == nullptr) {
			modelID++;
			continue;
		}

		//インスタンシングデータをリセット
		BlockModel[modelID]->ResetInstancingDatas();
		for (int x = 0; x < LoadingChunks; x++)
		{
			for (int z = 0; z < LoadingChunks; z++)
			{
				auto& Datas = m_ChunkBlock[x][z].GetInstancingData(modelID);
				for (auto& data : Datas)
				{
					//インスタンシングデータを追加
 					BlockModel[modelID]->UpdateInstancingData(data.pos,data.rot,data.scale);
				}
				m_ChunkBlock[x][z].ResetModelUpdated();
			}
		}
		modelID++;
	}
}