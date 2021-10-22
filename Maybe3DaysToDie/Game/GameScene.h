#pragma once

#include "Enemy/EnemyGenerator.h"

class Player;
class Stage;
class GameCamera;
class PlacementObject;

/// <summary>
/// シングルトン。
/// </summary>
class CGameScene
{
private:
	CGameScene() {};
	~CGameScene();
public:
	/// <summary>
	/// スタート。
	/// </summary>
	void Start();
	/// <summary>
	/// 更新。
	/// </summary>
	void Update();
public:
	/// <summary>
	/// インスタンス化。
	/// </summary>
	void Instantiate()
	{
		if (m_instance == nullptr) {
			//インスタンスされてないので作成。
			m_instance = new CGameScene;
		}
	}
	/// <summary>
	/// インスタンスを削除。
	/// </summary>
	void DeleteInstance()
	{
		if (m_instance != nullptr) {
			//削除。
			delete m_instance;
		}
	}
public://Getter.
	/// <summary>
	/// インスタンスを取得。
	/// </summary>
	/// <returns></returns>
	static CGameScene* GetInstance()
	{
		return m_instance;
	}
	/// <summary>
	/// プレイヤーを取得。FindGOのオーバーヘッドないぜ？ｗ
	/// </summary>
	/// <returns></returns>
	Player* GetPlayer() const 
	{
		return m_Player;
	}
	/// <summary>
	/// エネミージェネレーターを取得。
	/// </summary>
	/// <returns></returns>
	EnemyGenerator& GetEnemyGenerator()
	{
		return m_enemyGenerator;
	}
private:
	static CGameScene* m_instance;					//シングルトンインスタンス。
	Player* m_Player = nullptr;
	GameCamera* m_Camera = nullptr;
	Stage* m_Stage = nullptr;
	PlacementObject* m_PlacementObject = nullptr;		//設置オブジェクト
	EnemyGenerator m_enemyGenerator;				//エネミージェネレーター。
	//Samples//
	CFontRender* m_fontRender = nullptr;			//フォントレンダー。

};

/// <summary>
/// ゲームシーンを取得。
/// </summary>
/// <returns></returns>
static inline CGameScene* GameScene()
{
	return CGameScene::GetInstance();
}