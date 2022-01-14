#include "stdafx.h"
#include "PlacementObject.h"
#include "Block/BlockManager/BlockManager.h"
#include "Load/TerrainLoad/LoadingByChunk.h"
#include "SaveDataFile.h"

PlacementObject::PlacementObject()
{
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

	ModelInitData m_modelInitData;
	m_modelInitData.m_tkmFilePath = "Assets/modelData/CubeBlock/woodBlock.tkm";
	m_modelInitData.m_shaderData.vsFxFilePath = L"Assets/shader/model.fx";
	m_modelInitData.m_shaderData.vsEntryPointFunc = "VSMain";
	m_modelInitData.m_shaderData.psFxFilePath = L"Assets/shader/ObjectPreview.fx";
	m_modelInitData.m_shaderData.psEntryPointFunc = "PSMain";
	m_ObjectModel->Init(m_modelInitData);
	m_ObjectModel->SetForwardRenderFlag(true);
	m_ObjectModel->SetShadowCasterFlag(true);
	return true;
}

void PlacementObject::Update()
{
	//オブジェクトを設置する位置を計算
	CalcObjectPos();
	//各種セット
	m_ObjectModel->SetPosition(m_pos);
	m_ObjectModel->SetRotation(m_qrot);
	m_ObjectModel->SetScale(m_scale);

	if (Pad(0).IsTrigger(enButtonA))
	{
		//パラメータ
		ObjectParams param;
		param.Durable = 500;
		auto name = "Assets/modelData/CubeBlock/woodBlock.tkm";
		param.BlockName = name;
		PlaceObject(param);
	}
}

void PlacementObject::CalcObjectPos()
{
	//視点の位置
	Vector3 m_Start = MainCamera().GetPosition();
	//視線方向にポジションを加算
	Vector3 m_End = m_Start;
	m_End += MainCamera().GetForward() * SetRange;
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
	CanPlace = callback.isHit;
	//レイが衝突しているとき
	if (callback.isHit)
	{
		lastPos = callback.hitColPos;
		lastPos += callback.hitNormal * 100.0f;
		m_hitObj = ((DestructibleObject*)callback.ColObj->getUserPointer());
	}
	m_pos.Set(lastPos);
}

//todo [最適化]後で処理見直せ
void PlacementObject::PlaceObject(ObjectParams& params)
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

			//セーブデータに直接書き込み
			chunkData.ObjId[id_x][id_y][id_z] = params.BlockID;
			chunkData.ObjDurable[id_x][id_y][id_z] = params.Durable;
			auto& block = m_LoadingChunk->GetChunkBlocks(ID).GetBlock(Pos);
			block.AddBlock(params, m_pos, rot, scale);
		}
	}
}