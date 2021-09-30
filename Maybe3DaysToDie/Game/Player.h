#pragma once
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
	/// <summary>
	/// 初期化
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

	/// <summary>
	/// 時間によるステータスの更新
	/// </summary>
	void PeriodicUpdate();

	/// <summary>
	/// 体力を時間によって回復する
	/// </summary>
	void HpRegene();

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
private:
	prefab::ModelRender* m_Model = nullptr;		//プレイヤーモデル
	int m_Hp = 100;								//体力
	float m_Stamina = 100.0f;					//
	float m_HpRegeneTime = 1.0f;
	float m_nowHpRegeneTimer = 0.0f;
	int m_Hunger = 100;
	int m_water = 100;
	State m_State = State::Idle;
	float m_DeltaTime = 0.0f;
};

