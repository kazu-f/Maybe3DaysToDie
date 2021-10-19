#pragma once

class Player;
class Stage;
class GameCamera;
class PlacementObject;

class GameScene : public IGameObject
{
private:
	/// <summary>
	/// GameObjectに積まれると一度だけ呼ばれる初期化関数
	/// </summary>
	/// <returns>trueが返るまでループする</returns>
	bool Start()override final;
	/// <summary>
	/// deleteされると呼ばれる
	/// </summary>
	void OnDestroy()override final;

private:
	Player* m_Player = nullptr;
	GameCamera* m_Camera = nullptr;
	Stage* m_Stage = nullptr;
	PlacementObject* m_PlacementObject = nullptr;		//設置オブジェクト

	//Samples//
	CFontRender* m_fontRender = nullptr;	//フォントレンダー。

};