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
class IPlayerState;
class IEnemy;
class Player : public IGameObject
{
public :
	Player():
		m_Dead(this),
		m_Idle(this)
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
	const Vector3 GetPosition() const {
		return m_Pos;
	}

	void SetCameraPtr(GameCamera* ptr)
	{
		m_Camera = ptr;
	}

	/// <summary>
	/// 移動速度を変更する関数
	/// ダッシュとかデバフとかに使う
	/// </summary>
	/// <param name="mulSp">速度に掛けたい値</param>
	void SetMulSpeed(const float mulSp) {
		m_mulSpeed = mulSp;
	}

	void SetLoadingByChunk(LoadingByChunk* lbc)
	{
		m_LoadingByChunk = lbc;
	}

	void SetItemBar(ItemBar* itemBar) {
		m_ItemBar = itemBar;
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

	void CloseInventory();

	/// <summary>
	/// 現在のステートを取得
	/// </summary>
	/// <returns>現在のステート</returns>
	IPlayerState::State GetState() const {
		return m_CurrentState;
	}

	void SetAccessObject(AccessObject* AOp) {
		m_AccessObject = AOp;
	}

	void ReStart();

	/// <summary>
	/// デバッグモード化を判定する
	/// </summary>
	/// <returns>デバッグモードならtrue</returns>
	const bool IsDubug()const;

	void CharaMove(Vector3& move) {
		m_Characon.Execute(move);
	}

	void ChengeState(IPlayerState::State nextState) {
		m_NextState = nextState;
	}

	IPlayerState::State GetCurrentState() const {
		return m_CurrentState;
	}
private:
	/// <summary>
	/// 時間によるステータスの更新
	/// </summary>
	void PeriodicUpdate();

	/// <summary>
	/// IPlayerStateを更新
	/// </summary>
	void ChangeState();


	/// <summary>
	/// ダッシュ機能
	/// </summary>
	void Dash();

	/// <summary>
	/// 重力処理
	/// </summary>
	void Jump();
private:
	////////////モデル/////////////////////////////////////////////
	Vector3 m_Pos = { 0.0f,500.0f,500.0f };
	Quaternion m_Rot = Quaternion::Identity;
	Vector3 m_Scale = Vector3::One;
	CCharacterController m_Characon;
	///////////////////////////////////////////////////////////////

	/////体力//////////////////////////////////////////////////////
	PlayerHp* m_Hp = nullptr;
	///////////////////////////////////////////////////////////////

	/////スタミナ/////////////////////////////////////////////////
	PlayerStamina* m_Stamina = nullptr;
	///////////////////////////////////////////////////////////////

	/////空腹//////////////////////////////////////////////////////
	PlayerHunger* m_Hunger = nullptr;
	///////////////////////////////////////////////////////////////

	/////水分//////////////////////////////////////////////////////
	PlayerWater* m_Water = nullptr;
	///////////////////////////////////////////////////////////////

	/////ホットバー//////////////////////////////////////////////
	ItemBar* m_ItemBar = nullptr;
	/// ////////////////////////////////////////////////////////
	IPlayerState::State m_CurrentState = IPlayerState::State::Num;				//現在のステート
	IPlayerState::State m_NextState = IPlayerState::State::Num;				//次に変わるステート
	float m_DeltaTime = 0.0f;

	GameCamera* m_Camera = nullptr;
	bool IsJump = false;
	bool IsJumping = false;
	float NowTime = 0.0f;
	float m_mulSpeed = 1.0f;			//移動速度(バフ、デバフ用）

	LoadingByChunk* m_LoadingByChunk = nullptr; 

	bool m_IsUseItem = true;
	AccessObject* m_AccessObject = nullptr;

	IPlayerState* PlayerState = nullptr;
	PlayerIdle m_Idle;
	PlayerDead m_Dead;
	PlayerWalk m_Walk;
	Vector3 m_RespownPoint = { 100.0f,100.0f,100.0f };
	IEnemy* m_Enemy = nullptr;
};

