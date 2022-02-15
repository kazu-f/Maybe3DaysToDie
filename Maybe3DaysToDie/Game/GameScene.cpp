#include "stdafx.h"
#include "GameScene.h"
#include "GameCamera.h"
#include "Player/Player.h"
#include "Stage.h"
#include "ItemBar/ItemBar.h"
#include "Player/Inventory.h"

#include "PlacementObject/PlacementObject.h"
#include "DestroyObject/DestroyObject.h"
#include "Tool/Tool.h"

#include "DateTime.h"

#include "Load/TerrainLoad/LoadingByChunk.h"



CGameScene::~CGameScene()
{
	//ゲーム終了時にセーブ
	m_TerrainSave.Save();

	DeleteGO(m_Player);
	DeleteGO(m_Camera);
	DeleteGO(m_Stage);
	DeleteGO(m_ItemBar);
	DeleteGO(m_Inventory);


	if (m_PlacementObject != nullptr)
	{
		DeleteGO(m_PlacementObject);
		m_PlacementObject = nullptr;
	}
	if (m_DestroyObject != nullptr)
	{
		DeleteGO(m_DestroyObject);
		m_DestroyObject = nullptr;
	}
	if (tool != nullptr)
	{
		delete tool;
		tool = nullptr;
	}

	//sample//
	DeleteGO(m_fontRender);
}

bool CGameScene::Start()
{

	m_Player = NewGO<Player>(0, "player");
	m_Player->SetItemBar(m_ItemBar);
	m_ItemBar = NewGO<ItemBar>(0, "itemBar");
	m_ItemBar->SetPlayer(m_Player);
	m_Camera = NewGO<GameCamera>(0, "camera");
	m_Player->SetCameraPtr(m_Camera);
	m_Stage = NewGO<Stage>(0, "stage");
	m_Inventory = NewGO<Inventory>(0, "inventory");
	m_Inventory->SetPlayer(m_Player);

	//セーブデータファイルをセット
	m_TerrainSave.SetSaveDataFile(&m_SaveDataFile);
	m_TerrainLoad.SetSaveDataFile(&m_SaveDataFile);
	m_Stage->SetSaveDataFile(&m_SaveDataFile);

	//todo プレイヤーの処理等に置くようにしてください
	m_PlacementObject = NewGO<PlacementObject>(0);
	

	m_DestroyObject = NewGO<DestroyObject>(0);
	tool = new Tool;
	m_DestroyObject->SetTool(tool);

	DateTime* Data = NewGO<DateTime>(0, "dateTime");

	//ライト。
	prefab::CDirectionLight* lig = NewGO<prefab::CDirectionLight>(0);
	lig->SetColor({ 5.0f,5.0f,5.0f,1.0f });
	lig->SetDirection({ 1.0f,-1.0f,0.0f });
	//sample//
	m_fontRender = NewGO<CFontRender>(0);
	m_fontRender->SetText(L"Press 'U' Instantiate Zombie.\nPress 'K' Delete All Zombie.\n\nR B\nE A\nO K\n  A");
	m_fontRender->SetColor({ 1.0f, 0.0f, 0.0f, 1.0f });
	m_fontRender->SetShadowParam(true, 0.5f, Vector4::Black);
	m_fontRender->SetPivot({ 0.0f, 0.5f });
	m_fontRender->SetPosition({ -630.0f, 350.0f });
	m_fontRender->SetScale(0.5f);

	m_LoadingByChunk = m_Stage->GetLoadingByChunk();
	//セーブデータファイルをセット
	m_LoadingByChunk->SetSaveDataFile(&m_SaveDataFile);
	//ワールドテーブルデータをセット
	m_Player->SetLoadingByChunk(m_LoadingByChunk);
	m_PlacementObject->SetLoadingChunk(m_LoadingByChunk);
	m_PlacementObject->SetSaveData(&m_SaveDataFile);
	m_DestroyObject->SetSaveData(&m_SaveDataFile);
	m_SaveDataFile.ObjectFilePath[0] = L"DirtModel";
	m_SaveDataFile.ObjectFilePath[1] = L"WoodBlock";
	m_SaveDataFile.ObjectFilePath[2] = L"BookBlock";
	m_SaveDataFile.ObjectFilePath[3] = L"ShelfBlock";
	m_SaveDataFile.ObjectFilePath[4] = L"CardBoard";
	m_SaveDataFile.ObjectAccessTag[0] = AccessTag::NonAccess;
	m_SaveDataFile.ObjectAccessTag[1] = AccessTag::NonAccess;
	m_SaveDataFile.ObjectAccessTag[2] = AccessTag::NonAccess;
	m_SaveDataFile.ObjectAccessTag[3] = AccessTag::NonAccess;
	m_SaveDataFile.ObjectAccessTag[4] = AccessTag::Root;
	m_SaveDataFile.ObjectType[0] = ObjectType::Terrain;
	m_SaveDataFile.ObjectType[1] = ObjectType::Block;
	m_SaveDataFile.ObjectType[2] = ObjectType::Block;
	m_SaveDataFile.ObjectType[3] = ObjectType::Block;
	m_SaveDataFile.ObjectType[4] = ObjectType::Block;


	//ワールドデータ関係を記録する
	m_ItemBar->SetWorldData(
		m_PlacementObject,
		m_DestroyObject,
		&m_SaveDataFile,
		tool,
		m_LoadingByChunk,
		&m_TerrainSave,
		&m_TerrainLoad,
		m_Stage
	);
	m_AccessObject.SetSaveData(&m_SaveDataFile);
	m_Player->SetAccessObject(&m_AccessObject);
	return true;
}

void CGameScene::Update()
{


}