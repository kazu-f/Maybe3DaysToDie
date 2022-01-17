#pragma once
#include "Load/TerrainLoad/LoadingByChunk.h"

class PlayerHp;
class PlayerStamina;
class PlayerHunger;
class PlayerWater;
class GameCamera;
class ItemBar;
class Player : public IGameObject
{
	//配列用の定数
	//なんとなくマジックナンバーが嫌だったので定数化
	enum Vector {
		X, Y, Z
	};
	//プレイヤーが持つステートの種類
	enum State {
		Idle,			//待機
		Walk,			//歩く
		Run,			//走る
		Jump,			//ジャンプ
		Attack,			//攻撃
		Inventry,		//インベントリを開く
		Damage,			//攻撃に当たった
		Dead,			//死にました
		Num				//ステート数
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
		cameraptr = ptr;
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

private:
	/// <summary>
	/// 時間によるステータスの更新
	/// </summary>
	void PeriodicUpdate();

	/// <summary>
	/// IPlayerStateのUpdateを呼ぶ
	/// </summary>
	void StateUpdate();

	/// <summary>
	/// IPlayerStateを更新
	/// </summary>
	void ChangeState();

	/// <summary>
	/// モデルの移動処理
	/// </summary>
	void Move();

	/// <summary>
	/// モデルの回転処理
	/// </summary>
	void Rotation();

	/// <summary>
	/// モデルを更新
	/// </summary>
	void ModelUpdate();
private:
	////////////モデル/////////////////////////////////////////////
	//prefab::ModelRender* m_Model = nullptr;		//プレイヤーモデル
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
	State m_CurrentState = State::Idle;				//現在のステート
	State m_NextState = State::Idle;				//次に変わるステート
	float m_DeltaTime = 0.0f;

	bool m_IsChasePlayer = false;
	GameCamera* cameraptr = nullptr;

	float m_mulSpeed = 1.0f;			//移動速度(バフ、デバフ用）

	CFontRender* m_Font = nullptr;
	LoadingByChunk* m_LoadingByChunk = nullptr;
};

