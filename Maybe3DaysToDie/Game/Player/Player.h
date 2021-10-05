#pragma once
class GameCamera;
class PlayerHp;
class PlayerStamina;

enum State {
	Idle,			//待機
	Walk,			//歩く
	Run,			//走る
	Crouch,			//しゃがみ
	Jump,			//ジャンプ
	Attack,			//攻撃
	Num				//ステート数
};
class Player : public IGameObject
{
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

private:
	/// <summary>
	/// 時間によるステータスの更新
	/// </summary>
	void PeriodicUpdate();

	/// <summary>
	/// スタミナを時間によって回復する
	/// </summary>
	void StaminaRegene();

	/// <summary>
	/// お腹が空いた
	/// </summary>
	void HungerDecrease();

	/// <summary>
	/// 喉が乾いた
	/// </summary>
	void WarterDecrease();

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

	/// <summary>
	/// モデルの前方向を更新し戻り値に渡す
	/// </summary>
	///<returns>前方向</returns>
	Vector3 ForwardUpdate();
	/// <summary>
	/// モデルの右方向を更新し戻り値に渡す
	/// </summary>
	/// <returns>右方向</returns>
	Vector3 RightUpdate();

	/// <summary>
	/// カメラを設定
	/// </summary>
	void SetCamera();
private:
	////////////モデル/////////////////////////////////////////////
	prefab::ModelRender* m_Model = nullptr;		//プレイヤーモデル
	Vector3 m_Pos = { 0.0f,100.0f,500.0f };
	Quaternion m_Rot = Quaternion::Identity;
	Vector3 m_Scale = Vector3::One;
	///////////////////////////////////////////////////////////////
	
	/////体力//////////////////////////////////////////////////////
	PlayerHp* m_Hp = nullptr;
	///////////////////////////////////////////////////////////////

	/////スタミナ/////////////////////////////////////////////////
	PlayerStamina* m_Stamina = nullptr;
	///////////////////////////////////////////////////////////////
	int m_Hunger = 100;
	int m_water = 100;
	State m_State = State::Idle;
	float m_DeltaTime = 0.0f;

	/// マウス/////////////////////////////////////////////////////////
	float MouseRotX = 0.0f;
	float MouseRotY = 0.0f;
	int DefaultPoint[2] = { 500,300 };
	float m_SensiX = 0.02f;
	float m_SensiY = 0.02f;
	float m_RotAngle[2] = { 0.0f,0.0f };
	///////////////////////////////////////////////////////////////////
	
	///////カメラ//////////////////////////////////////////////////////
	GameCamera* m_Camera = nullptr;
	///////////////////////////////////////////////////////////////////
};

