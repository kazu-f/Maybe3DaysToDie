#pragma once

#include "Save/TerrainSave/TerrainSave.h"
#include "Load/TerrainLoad/TerrainLoad.h"
#include "AccessObject/AccessObject.h"

class Player;
class Stage;
class GameCamera;
class ItemBar;
class Inventory;

class PlacementObject;
class DestroyObject;
class Tool;

class LoadingByChunk;

class CGameScene : public IGameObject
{
public:
	CGameScene() {};
	~CGameScene();
public:
	/// <summary>
	/// スタート。
	/// </summary>
	bool Start()override final;
	/// <summary>
	/// 更新。
	/// </summary>
	void Update()override final;
private:
	Player* m_Player = nullptr;
	GameCamera* m_Camera = nullptr;
	Stage* m_Stage = nullptr;
	ItemBar* m_ItemBar = nullptr;
	Inventory* m_Inventory = nullptr;

	//仮置き//
	//todo 後ほどプレイヤー等においてください
	PlacementObject* m_PlacementObject = nullptr;		//設置オブジェクト
	DestroyObject* m_DestroyObject = nullptr;		//オブジェクト破壊
	Tool* tool = nullptr;
	//Samples//
	CFontRender* m_fontRender = nullptr;			//フォントレンダー。
	TerrainSave m_TerrainSave;		//地形セーブ用のクラス
	TerrainLoad m_TerrainLoad;
	SaveDataFile m_SaveDataFile;
	LoadingByChunk* m_LoadingByChunk = nullptr;
	AccessObject m_AccessObject;		//設置物にアクセスするためのクラス
};