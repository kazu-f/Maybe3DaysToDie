#include "stdafx.h"
#include "PlacementObject.h"
#include "Load/TerrainLoad/LoadingByChunk.h"
#include "SaveDataFile.h"
#include "RayTest.h"
#include "Item/ItemDataFile.h"
#include "Item/GameItemPlaceObj.h"
#include "Item/BlockItem.h"
#include "Item/GameItemTerrain.h"

PlacementObject::PlacementObject()
{
	m_itemDataFile = ItemDataFile::GetInstance();
}

PlacementObject::~PlacementObject()
{

}

void PlacementObject::OnDestroy()
{
	if (m_ObjectModel != nullptr)
	{
		DeleteGO(m_ObjectModel);
		m_ObjectModel = nullptr;
	}
	for (auto model : m_model)
	{
		delete model;
	}
}

bool PlacementObject::Start()
{
	m_ObjectModel = NewGO<prefab::ModelRender>(0);
	m_modelInitData.m_shaderData.vsFxFilePath = L"Assets/shader/model.fx";
	m_modelInitData.m_shaderData.vsEntryPointFunc = "VSMain";
	m_modelInitData.m_shaderData.psFxFilePath = L"Assets/shader/ObjectPreview.fx";
	m_modelInitData.m_shaderData.psEntryPointFunc = "PSMain";
	m_ObjectModel->SetForwardRenderFlag(true);
	m_ObjectModel->SetShadowCasterFlag(true);
	//アクティブを切る
	m_ObjectModel->SetActiveFlag(false);

	m_TerrainManager = FindGO<nsTerrain::TerrainManager>("Terrain");

	return true;
}

void PlacementObject::Update()
{
	ObjID = static_cast<int>(objParam.BlockID);
	auto* block = m_itemDataFile->GetBlockData(ObjID);
	auto* terrain = m_itemDataFile->GetTerrainData(ObjID);
	if (block == nullptr && terrain == nullptr) {
		//ブロックIDがマイナスか最大値より大きいときreturn
		CanPlace = false;
		return;	
	}

	////オブジェクトを設置する位置を計算
	//ObjID = static_cast<int>(objParam.BlockID);
	//if (ObjID < 0 || ObjID >= BlockKinds)
	//{
	//	//ブロックIDがマイナスか最大値より大きいときreturn
	//	CanPlace = false;
	//	return;
	//}
	CalcObjectPos();
	//各種セット
	m_ObjectModel->SetPosition(m_pos);
	m_ObjectModel->SetRotation(m_qrot);
	m_ObjectModel->SetScale(m_scale);
}

void PlacementObject::CalcObjectPos()
{
	//視点の位置
	Vector3 m_Start = MainCamera().GetPosition();
	//視線方向にポジションを加算
	Vector3 m_End = m_Start;
	m_End += MainCamera().GetForward() * PlayerRange * OBJECT_UNIT;
	Vector3 cpos = MainCamera().GetPosition();
	Vector3 ctgt = MainCamera().GetTarget();
	Vector3 forward = cpos - ctgt;
	forward.Normalize();
	//レイテストで使用するベクトルを作成
	btVector3 start, end;
	start.setValue(m_Start.x, m_Start.y, m_Start.z);
	end.setValue(m_End.x, m_End.y, m_End.z);

	//レイテスト
	RayResult callback;
	PhysicsWorld().RayTest(start, end, callback);
	//最終的な位置
	Vector3 lastPos;
	lastPos.Set(end);
	//レイが衝突しているとき
	if (callback.isHit)
	{
		lastPos = callback.hitColPos;
		lastPos += callback.hitNormal * 100.0f;
		m_hitObj = ((DestructibleObject*)callback.ColObj->getUserPointer());
	}
	m_pos.Set(lastPos);
	CanPlace = false;
	if (m_pos.x >= 0.0f && m_pos.x <= (ChunkWidth - 1) * OBJECT_UNIT * MAX_CHUNK_SIDE)
	{
		if (m_pos.z >= 0.0f && m_pos.z <= (ChunkWidth - 1) * OBJECT_UNIT * MAX_CHUNK_SIDE)
		{
			if (m_pos.y >= 0.0f && m_pos.y <= (ChunkHeight - 1) * OBJECT_UNIT)
			{
				//位置が範囲内の時
				CanPlace = callback.isHit;
			}
		}
	}
}

bool PlacementObject::SetModelParams()
{
	ObjID = static_cast<int>(objParam.BlockID);
	auto* block = m_itemDataFile->GetBlockData(ObjID);
	auto* terrain = m_itemDataFile->GetTerrainData(ObjID);
	if (block == nullptr && terrain == nullptr)return false;

	const char* filePath = nullptr;
	if (block != nullptr)
	{
		filePath = block->GetItemData()->tkmPath.c_str();
	}
	if (terrain != nullptr)
	{
		filePath = terrain->GetItemData()->tkmPath.c_str();
	}

	if (filePath == nullptr) return false;

	m_modelInitData.m_tkmFilePath = filePath;

	return true;

	//const auto& dataFile = ItemDataFile::GetInstance();
	////todo ItemDataFileから取得してくる
	//if (ObjID < 0 || ObjID >= BlockKinds)
	//{
	//	//ブロックIDがマイナスか最大値より大きいときreturn
	//	return false;
	//}
	//else
	//{
	//	//ファイルパス作成。
	//	wchar_t filePath[256];
	//	swprintf_s(filePath, L"Assets/modelData/CubeBlock/%s.tkm", m_SaveData->ObjectFilePath[ObjID].c_str());

	//	size_t oriSize = wcslen(filePath) + 1;
	//	size_t convertedChars = 0;
	//	char strConcat[] = "";
	//	size_t strConcatSize = (strlen(strConcat) + 1) * 2;
	//	const size_t newSize = oriSize * 2;
	//	char* nString = new char[newSize + strConcatSize];
	//	wcstombs_s(&convertedChars, nString, newSize, filePath, _TRUNCATE);
	//	_mbscat_s((unsigned char*)nString, newSize + strConcatSize, (unsigned char*)strConcat);

	//	m_modelInitData.m_tkmFilePath = nString;
	//	return true;
	//}
}

//todo [最適化]後で処理見直せ
void PlacementObject::PlaceObject()
{
	if (CanPlace)
	{
		if (m_hitObj != nullptr)
		{
			//設置可能な時
			Quaternion rot = Quaternion::Identity;
			Vector3 scale = Vector3::One;
			//ヒットしているオブジェクトの位置にブロックを追加
			//m_hitObj->AddBlock(params, m_pos, rot, scale);

			//設置するオブジェクトのチャンクIDを計算
			int ID[2] = { 0 };
			int x = m_pos.x / OBJECT_UNIT;
			ID[0] = static_cast<int>(x / ChunkWidth);
			int z = m_pos.z / OBJECT_UNIT;
			ID[1] = static_cast<int>(z / ChunkWidth);
			//対応するブロックを取得
			//レイテストでずれることがあるので下駄をはかす
			Vector3 Pos = m_pos;
			Pos.x += OBJECT_UNIT / 4;
			Pos.y += OBJECT_UNIT / 4;
			Pos.z += OBJECT_UNIT / 4;

			Pos.x = abs(Pos.x);
			Pos.y = abs(Pos.y);
			Pos.z = abs(Pos.z);

			//セーブデータファイルからチャンクの情報を取得
			auto& chunkData = m_SaveData->m_ChunkData[ID[0]][ID[1]];
			//ポジションに対応するブロックを取得
			int id_x = Pos.x / OBJECT_UNIT;
			id_x = static_cast<int>(id_x % ChunkWidth);
			int id_y = Pos.y / OBJECT_UNIT;
			id_y = static_cast<int>(id_y % ChunkHeight);
			int id_z = Pos.z / OBJECT_UNIT;
			id_z = static_cast<int>(id_z % ChunkWidth);

			auto* datas = ItemDataFile::GetInstance();

			auto blockData = datas->GetBlockData(objParam.BlockID);
			if (blockData != nullptr) {
				auto* block = m_LoadingChunk->GetChunkBlocks(ID).GetBlock(Pos);
				//セーブデータに直接書き込み
				chunkData.ObjData[id_x][id_y][id_z].ObjId = objParam.BlockID;
				chunkData.ObjData[id_x][id_y][id_z].ObjDurable = objParam.Durable;
				block->AddBlock(objParam, m_pos, rot, scale);
			}
			auto terrainData = datas->GetTerrainData(objParam.BlockID);
			if (terrainData != nullptr) {
				auto* terrain = m_TerrainManager->GetTerrainChunkData(ID[0], ID[1]).GetTerrainData(id_x, id_y, id_z);
				terrain->AddBlock(objParam, m_pos, rot, scale);
			}

			//switch (m_SaveData->ObjectType[objParam.BlockID])
			//{
			//case ObjectType::Block:
			//{
			//	auto* block = m_LoadingChunk->GetChunkBlocks(ID).GetBlock(Pos);
			//	//セーブデータに直接書き込み
			//	chunkData.ObjData[id_x][id_y][id_z].ObjId = objParam.BlockID;
			//	chunkData.ObjData[id_x][id_y][id_z].ObjDurable = objParam.Durable;
			//	block->AddBlock(objParam, m_pos, rot, scale);
			//	break;
			//}
			//case ObjectType::Terrain:
			//{
			//	auto* terrain = m_TerrainManager->GetTerrainChunkData(ID[0], ID[1]).GetTerrainData(id_x, id_y, id_z);
			//	terrain->AddBlock(objParam, m_pos, rot, scale);
			//	break;
			//}
			//}
		}
	}
}