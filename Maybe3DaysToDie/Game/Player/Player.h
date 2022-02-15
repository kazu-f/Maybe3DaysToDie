#pragma once
#include "Load/TerrainLoad/LoadingByChunk.h"

class PlayerHp;
class PlayerStamina;
class PlayerHunger;
class PlayerWater;
class GameCamera;
class ItemBar;
class AccessObject;
#include "state/PlayerDead.h"
#include "state/PlayerIdle.h"
#include "state/PlayerWalk.h"
#include "state/PlayerMenu.h"
class IPlayerState;
class IEnemy;
class Inventory;
class Stage;
class PlacementObject;
class DestroyObject;
class Tool;
class SaveDataFile;
class Player : public IGameObject
{
public :
	//プレイヤーが持つステートの種類
	enum State {
		Idle,			//待機
		Walk,			//歩く
		Attack,			//攻撃
		Menu,			//メニュー画面中
		//Damage,			//攻撃に当たった
		Dead,			//死にました
		Num				//ステート数
	};
	/// <summary>
	/// コンストラクタ
	/// ステートパターンで使用する変数のコンストラクタの為にある
	/// </summary>
	Player():
		m_Dead(this),
		m_Idle(this),
		m_Walk(this),
		m_Menu(this)
	{}
private:
	//配列用の定数
	//なんとなくマジックナンバーが嫌だったので定数化
	enum Vector {
		X, Y, Z
	};

private:
	/// <summary>
	/// GameObjectに積まれると一度だけ呼ばれる初期化関数
	/// </summary>
	/// <returns>trueが返るまでループする</returns>
	bool Start()override final;

	/// <summary>
	/// 更新
	/// </summary>
	void Update()override final;

	/// <summary>
	/// deleteされると呼ばれる関数
	/// </summary>
	void OnDestroy()override final;

public:
	/// <summary>
	/// プレイヤーの位置を取得
	/// </summary>
	/// <returns></returns>
	const Vector3 GetPosition() const {
		return m_Pos;
	}

	/// <summary>
	/// カメラのポインタを設定する
	/// </summary>
	/// <param name="ptr">カメラのポインタ</param>
	void SetCameraPtr(GameCamera* ptr)
	{
		m_Camera = ptr;
	}

	/// <summary>
	/// 移動速度を変更する関数
	/// ダッシュとかデバフとかに使う
	/// </summary>
	/// <param name="mulSp">速度に掛けたい値</param>
	void SetMulSpeed(const float mulSp);

	void SetLoadingByChunk(LoadingByChunk* lbc)
	{
		m_LoadingByChunk = lbc;
	}

	/// <summary>
	/// プレイヤーが攻撃をくらった際に入る関数。
	/// プレイヤーへの当たり判定はしてないです。
	/// </summary>
	/// <param name="Damage">ダメージ量</param>
	void HitDamage(const float Damage);

	/// <summary>
	/// インベントリを表示する
	/// </summary>
	bool OpenInventory();

	/// <summary>
	/// インベントリを閉じる
	/// </summary>
	void CloseInventory();

	/// <summary>
	/// 現在のステートを取得
	/// </summary>
	/// <returns>現在のステート</returns>
	State GetState() const {
		return m_CurrentState;
	}

	void SetAccessObject(AccessObject* AOp) {
		m_AccessObject = AOp;
	}

	/// <summary>
	/// 死んだ時に呼ばれる関数
	///	ステータスを現在の最大値に設定しなおす
	/// </summary>
	void ReStart();

	/// <summary>
	/// デバッグモード化を判定する
	/// </summary>
	/// <returns>デバッグモードならtrue</returns>
	const bool IsDubug()const;

	/// <summary>
	/// プレイヤーが動く関数
	/// </summary>
	/// <param name="move">移動量</param>
	void CharaMove(Vector3& move) {
		m_Pos = m_Characon.Execute(move);
	}

	/// <summary>
	/// ステートを変更するときに呼ぶ関数
	/// </summary>
	/// <param name="nextState">次のステート</param>
	void ChengeState(State nextState) {
		m_NextState = nextState;
	}

	/// <summary>
	/// 現在のステートを取得
	/// </summary>
	/// <returns>現在のステート</returns>
	State GetCurrentState() const {
		return m_CurrentState;
	}

	/// <summary>
	/// プレイヤーがスタミナを使うときに呼ぶ関数
	/// </summary>
	/// <param name="usenum">使用消費量</param>
	bool UseStamina(int useCost);

	/// <summary>
	/// 視点を動かすかどうかを決める関数
	/// </summary>
	/// <param name="isMove">動かすならfalse</param>
	void SetMoveMause(bool isMove);

	/// <summary>
	/// デバッグモードかどうかを取得する関数
	/// </summary>
	/// <returns></returns>
	bool IsDebugMode()const {
		return m_IsDebugMode;
	}

	/// <summary>
	/// デバッグモードを設定する関数
	/// </summary>
	/// <param name="mode"></param>
	void SetDebugMode(bool mode) {
		m_IsDebugMode = mode;
	}

	/// <summary>
	/// 重力処理
	/// </summary>
	void Jump();

	/// <summary>
	/// Hpのポインタを取得
	/// </summary>
	/// <returns>Hpポインタ</returns>
	PlayerHp* GetHp() const {
		return m_Hp;
	}

	/// <summary>
	/// スタミナのポインタを取得
	/// </summary>
	/// <returns>スタミナポインタ</returns>
	PlayerStamina* GetStamina() const {
		return m_Stamina;
	}

	/// <summary>
	/// 空腹度のポインタを取得
	/// </summary>
	/// <returns>空腹度のぽいんた</returns>
	PlayerHunger* GetHunger()const {
		return m_Hunger;
	}

	/// <summary>
	/// 水分のポインタを取得
	/// </summary>
	/// <returns>水分のポインタ</returns>
	PlayerWater* GetWater()const {
		return m_Water;
	}

	Inventory* GetInventory() {
		return m_Inventory;
	}

	void ItemDetaInit(
		SaveDataFile* Sf,
		Stage* s);
private:
	/// <summary>
	/// 時間によるステータスの更新
	/// </summary>
	void PeriodicUpdate();

	/// <summary>
	/// IPlayerStateを更新
	/// </summary>
	void ChangeState();

private:
	////////////モデル/////////////////////////////////////////////
	Vector3 m_Pos = { 500.0f,500.0f,500.0f };
	Quaternion m_Rot = Quaternion::Identity;
	Vector3 m_Scale = Vector3::One;
	CCharacterController m_Characon;
	///////////////////////////////////////////////////////////////

	/////ステータス//////////////////////////////////////////////////////
	PlayerHp* m_Hp = nullptr;
	PlayerStamina* m_Stamina = nullptr;
	PlayerHunger* m_Hunger = nullptr;
	PlayerWater* m_Water = nullptr;
	///////////////////////////////////////////////////////////////

	/////UI//////////////////////////////////////////////
	ItemBar* m_ItemBar = nullptr;
	Inventory* m_Inventory = nullptr;
	/// ////////////////////////////////////////////////////////
	float m_DeltaTime = 0.0f;

	GameCamera* m_Camera = nullptr;			//カメラのポインタ
	bool IsJump = false;
	bool IsJumping = false;

	float NowTime = 0.0f;
	LoadingByChunk* m_LoadingByChunk = nullptr; 

	bool m_IsUseItem = true;
	AccessObject* m_AccessObject = nullptr;

	/////ステート//////////////////////////////////
	State m_CurrentState = State::Num;				//現在のステート
	State m_NextState = State::Num;				//次に変わるステート
	IPlayerState* m_PlayerState = nullptr;
	PlayerIdle m_Idle;
	PlayerDead m_Dead;
	PlayerWalk m_Walk;
	PlayerMenu m_Menu;
	////////////////////////////////////////////////

	Vector3 m_RespownPoint = { 100.0f,100.0f,100.0f };
	IEnemy* m_Enemy = nullptr;

	bool m_IsDebugMode = false;
	float m_Gravity = 0.0f;

	//todo 後ほどプレイヤー等においてください
	PlacementObject* m_PlacementObject = nullptr;		//設置オブジェクト
	DestroyObject* m_DestroyObject = nullptr;		//オブジェクト破壊
	Tool* tool = nullptr;

	SaveDataFile* m_SaveData;
	Stage* m_Stage;
};

