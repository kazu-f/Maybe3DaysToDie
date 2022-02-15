#pragma once

#include "Save/TerrainSave/TerrainSave.h"
#include "Save/TerrainSave/TerrainLoad.h"
#include "Save/ChestSave/ChestSave.h"
#include "Save/ChestSave/ChestLoad.h"
#include "AccessObject/AccessObject.h"

class Player;
class Stage;
class GameCamera;

class PlacementObject;
class DestroyObject;
class Tool;

class LoadingByChunk;
class NaviMeshManager;

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

	//仮置き//
	//Samples//
	CFontRender* m_fontRender = nullptr;			//フォントレンダー。
	TerrainSave m_TerrainSave;		//地形セーブ用のクラス
	TerrainLoad m_TerrainLoad;
	ChestSave m_ChestSave;		//チェストセーブ用のクラス
	ChestLoad m_ChestLoad;		//チェストロード用のクラス
	SaveDataFile m_SaveDataFile;
	ChestDataFile m_ChestDataFile;
	LoadingByChunk* m_LoadingByChunk = nullptr;
	AccessObject m_AccessObject;		//設置物にアクセスするためのクラス
};