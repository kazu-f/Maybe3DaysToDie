#pragma once

class Player;
class Stage;
class GameCamera;
class PlacementObject;

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
	PlacementObject* m_PlacementObject = nullptr;		//設置オブジェクト
	//Samples//
	CFontRender* m_fontRender = nullptr;			//フォントレンダー。

};