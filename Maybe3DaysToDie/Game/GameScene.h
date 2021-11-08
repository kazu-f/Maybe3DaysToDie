#pragma once

class Player;
class Stage;
class GameCamera;
class PlacementObject;
class DestroyObject;

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
	//todo 後ほどプレイヤー等においてください
	PlacementObject* m_PlacementObject = nullptr;		//設置オブジェクト
	DestroyObject* m_DestroyObject = nullptr;		//オブジェクト破壊
	//Samples//
	CFontRender* m_fontRender = nullptr;			//フォントレンダー。

};