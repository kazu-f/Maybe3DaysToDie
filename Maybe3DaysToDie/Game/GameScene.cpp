#include "stdafx.h"
#include "GameScene.h"
#include "GameCamera.h"
#include "Player/Player.h"
#include "Stage.h"
#include "ItemBar.h"

#include "PlacementObject/PlacementObject.h"
#include "DestroyObject/DestroyObject.h"
#include "Tool/Tool.h"

#include "DateTime.h"

#include "Load/TerrainLoad/LoadingByChunk.h"


CGameScene::~CGameScene()
{
	DeleteGO(m_Player);
	DeleteGO(m_Camera);
	DeleteGO(m_Stage);
	
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
	m_Camera = NewGO<GameCamera>(0, "camera");
	m_Player->SetCameraPtr(m_Camera);
	m_Stage = NewGO<Stage>(0, "stage");

	//セーブデータファイルをセット
	m_TerrainSave.SetSaveDataFile(&m_SaveDataFile);
	m_TerrainLoad.SetSaveDataFile(&m_SaveDataFile);
	
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

	//動的にワールドを読み込むLoadingByChunkをNewGO
	m_LoadingByChunk = NewGO<LoadingByChunk>(0);
	//ワールド設定をセット
	m_LoadingByChunk->SetWorldConfig(&m_WorldConfig);
	//セーブデータファイルをセット
	m_LoadingByChunk->SetSaveDataFile(&m_SaveDataFile);
	m_Player->SetLoadingByChunk(m_LoadingByChunk);
	m_PlacementObject->SetLoadingChunk(m_LoadingByChunk);
	m_PlacementObject->SetSaveData(&m_SaveDataFile);
	m_DestroyObject->SetSaveData(&m_SaveDataFile);

	return true;
}

void CGameScene::Update()
{
	if (GetAsyncKeyState(VK_SPACE))
	{
		//テラインをセットしているけど、ここでセットしているのはテラインが作られるのが遅いため。
		m_TerrainSave.SetTerrainWorld(m_Stage->GetTerrainWorld());
		m_TerrainSave.Save();
	}
}