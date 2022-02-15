#include "stdafx.h"
#include "DestroyObject.h"
#include "TerrainManager/TerrainWorld.h"
#include "Tool/Tool.h"
#include "SaveDataFile.h"
#include "RayTest.h"
#include "Item/ItemDataFile.h"
#include "Item/GameItemPlaceObj.h"
#include "Item/BlockItem.h"
#include "Item/GameItemTerrain.h"
#include "Item/GameItemMaterial.h"

DestroyObject::DestroyObject()
{

}

DestroyObject::~DestroyObject()
{

}

void DestroyObject::Update()
{
	if (Pad(0).IsTrigger(enButtonB))
	{
		AddObjectDamage();
	}
}

std::vector<Item>& DestroyObject::AddObjectDamage()
{
	//配列クリア
	m_Item.clear();
	int damage = 0;
	int ObjectID = -1;

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
		//地形を取得
		//auto terrain = FindGO<nsTerrain::TerrainWorld>("Terrain");
		//地形にダメージを与える
		//terrain->GetTerrain(lastPos).Damage(m_tool->GetInfo());
		DestructibleObject* obj = ((DestructibleObject*)callback.ColObj->getUserPointer());
		if (obj != nullptr)
		{
			ObjectParams param = obj->GetParam();
			if (param.Durable == 0)
			{
				return m_Item;
			}
			damage = obj->Damage(m_tool->GetInfo());
			param = obj->GetParam();
			//オブジェクトのID
			ObjectID = param.BlockID;
			//設置するオブジェクトのチャンクIDを計算
			int ID[2] = { 0 };
			int x = lastPos.x / OBJECT_UNIT;
			ID[0] = static_cast<int>(x / ChunkWidth);
			int z = lastPos.z / OBJECT_UNIT;
			ID[1] = static_cast<int>(z / ChunkWidth);
			//対応するブロックを取得
			//レイテストでずれることがあるので下駄をはかす
			Vector3 Pos = lastPos;
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

			//セーブデータに直接書き込み
			if (param.Durable > 0)
			{
				chunkData.ObjData[id_x][id_y][id_z].ObjId = ObjectID;
			}
			else
			{
				chunkData.ObjData[id_x][id_y][id_z].ObjId = 0;
			}
			chunkData.ObjData[id_x][id_y][id_z].ObjDurable = param.Durable;

		}
	}
	//データファイルゲット
	auto DataFile = ItemDataFile::GetInstance();
	auto* block = DataFile->GetBlockData(ObjectID);
	auto* terrain = DataFile->GetTerrainData(ObjectID);
	if (block != nullptr)
	{
		float maxdurable = block->GetObjParams().Durable;
		float ratio = damage / maxdurable;
		//ブロック
		for (auto& item : block->GetCollectItemData())
		{
			Item i;
			auto itemData = DataFile->GetMaterialData(item.collectID);
			i.item = itemData;
			i.stack = std::round(item.collectNum * ratio);
			m_Item.push_back(i);
		}
	}
	else if (terrain != nullptr)
	{
		float maxdurable = terrain->GetObjParams().Durable;
		float ratio = damage / maxdurable;
		//テライン
		for (auto& item : terrain->GetCollectItemData())
		{
			Item i;
			auto itemData = DataFile->GetMaterialData(item.collectID);
			i.item = itemData;
			i.stack = std::round(item.collectNum * ratio);
			m_Item.push_back(i);
		}
	}

	return m_Item;
}