#pragma once
class PlayerHp;
class PlayerStamina;
class PlayerHunger;
class PlayerWater;

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
		Crouch,			//しゃがみ
		Jump,			//ジャンプ
		Attack,			//攻撃
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
	Vector3 ForwardUpdate()
	{
		Matrix ModelMatrix = Matrix::Identity;
		ModelMatrix.MakeRotationFromQuaternion(m_Rot);
		//m[2]はZ軸
		Vector3 ForwardModel = { ModelMatrix.m[Z][X],ModelMatrix.m[Z][Y],ModelMatrix.m[Z][Z] };
		//正規化して方向だけに
		ForwardModel.Normalize();
		//前方向を返す
		return ForwardModel;
	}
	/// <summary>
	/// モデルの右方向を更新し戻り値に渡す
	/// </summary>
	/// <returns>右方向</returns>
	Vector3 RightUpdate()
	{
		Matrix ModelMatrix = Matrix::Identity;
		ModelMatrix.MakeRotationFromQuaternion(m_Rot);
		//m[0]はX軸
		Vector3 RightModel = { ModelMatrix.m[X][X],ModelMatrix.m[X][Y],ModelMatrix.m[X][Z] };
		//正規化して方向だけに
		RightModel.Normalize();

		//右方向を返す
		return RightModel;
	}

private:
	////////////モデル/////////////////////////////////////////////
	prefab::ModelRender* m_Model = nullptr;		//プレイヤーモデル
	Vector3 m_Pos = { 0.0f,170.0f,500.0f };
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
	State m_State = State::Idle;
	float m_DeltaTime = 0.0f;
};

