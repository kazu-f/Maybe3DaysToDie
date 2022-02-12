#pragma once
class Player;
class IPlayerState
{
public:
	IPlayerState(Player* pl) :m_Player(pl) {}
	virtual ~IPlayerState() {}
	virtual void Enter() = 0;
	virtual	void Update() = 0;
	virtual void Leave() = 0;
	void Move();
	void ExcuteMove();
	/// <summary>
	/// デバッグモードを切り替える関数
	/// </summary>
	void SwichDebugMode();

	/// <summary>
	/// 移動速度を設定
	/// </summary>
	/// <param name="mul">移動速度</param>
	void SetMulSpeed(float mul) {
		m_mulSpeed = mul;
	}

	/// <summary>
	/// 移動速度を取得
	/// </summary>
	/// <returns>移動速度</returns>
	float GetMulSpeed()const {
		return m_mulSpeed;
	}

	/// <summary>
	/// プレイヤーのポインタを取得
	/// </summary>
	/// <returns>プレイヤーのポインタ</returns>
	Player* GetPlayer() const {
		return m_Player;
	}

	/// <summary>
	/// 移動量を設定
	/// </summary>
	/// <param name="Move">動かしたいベクトル</param>
	void SetMoveSpeed(const Vector3& Move) {
		m_MoveSpeed = Move;
	}

	/// <summary>
	/// 移動量のY成分のみを設定する
	/// </summary>
	/// <param name="MoveSpeed">移動量Y</param>
	void SetMoveSpeedY(float MoveSpeed) {
		m_MoveSpeed.y = MoveSpeed;
	}

	Vector3 GetMoveSpeed()const {
		return m_MoveSpeed;
	}
private:
	float m_mulSpeed = 0.0f;
	Player* m_Player = nullptr;
	Vector3 m_MoveSpeed = Vector3::Zero;
};

