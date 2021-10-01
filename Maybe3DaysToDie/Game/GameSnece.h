#pragma once

class Player;
class Stage;
class GameCamera;

class GameSnece : public IGameObject
{
	/// <summary>
	/// 初期化
	/// </summary>
	/// <returns>trueになるまでループする</returns>
	bool Start()override final;
	/// <summary>
	/// deleteされると呼ばれる
	/// </summary>
	void OnDestroy()override final;

private:
	Player* m_Player = nullptr;
	GameCamera* m_Camera = nullptr;
	Stage* m_Stage = nullptr;

	//Samples//
	CFontRender* m_fontRender = nullptr;	//フォントレンダー。
};