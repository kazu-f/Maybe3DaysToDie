#pragma once
class Player;
class IPlayerState
{
public:
	//プレイヤーが持つステートの種類
	enum State {
		Idle,			//待機
		Walk,			//歩く
		Run,			//走る
		Attack,			//攻撃
		Menu,			//メニュー画面中
		//Damage,			//攻撃に当たった
		Dead,			//死にました
		Debug,			//デバッグモード
		Num				//ステート数
	};
	IPlayerState(Player* pl) :m_Player(pl) {}
	virtual ~IPlayerState() {}
	virtual void Enter() = 0;
	virtual	void Update() = 0;
	virtual void Leave() = 0;
	void Move();
	
	Vector3 GetMoveSpeed()const {
		return m_MoveSpeed;
	}
	
	void SetMoveSpeedY(float MoveSpeed) {
		m_MoveSpeed.y = MoveSpeed;
	}

	float GetMulSpeed()const {
		return m_mulSpeed;
	}

	/// <summary>
	/// デバッグモードを切り替える関数
	/// </summary>
	void SwichDebugMode();
protected:
	float m_mulSpeed = 0.0f;
	Player* m_Player = nullptr;
	Vector3 m_MoveSpeed = Vector3::Zero;
};

