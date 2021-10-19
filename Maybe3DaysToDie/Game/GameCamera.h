#pragma once
class Player;
class GameCamera : public IGameObject
{
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
	bool Start() override final;
	/// <summary>
	/// 更新
	/// </summary>
	void Update() override final;
	/// <summary>
	/// deleteされると呼ばれる関数
	/// </summary>
	void OnDestroy() override final;
private:
	/// <summary>
	/// モデルの前方向を更新し戻り値に渡す
	/// </summary>
	///<returns>前方向</returns>
	const Vector3 ForwardUpdate()const
	{
		Matrix ModelMatrix = Matrix::Identity;
		ModelMatrix.MakeRotationFromQuaternion(m_Rot);
		//m[2]はZ軸
		Vector3 Forward = { ModelMatrix.m[Z][X],ModelMatrix.m[Z][Y],ModelMatrix.m[Z][Z] };
		//正規化して方向だけに
		Forward.Normalize();
		//前方向を返す
		return Forward;
	}
	/// <summary>
	/// モデルの右方向を更新し戻り値に渡す
	/// </summary>
	/// <returns>右方向</returns>
	const Vector3 RightUpdate()const
	{
		Matrix ModelMatrix = Matrix::Identity;
		ModelMatrix.MakeRotationFromQuaternion(m_Rot);
		ModelMatrix = MainCamera().GetCameraRotation();
		//m[0]はX軸
		Vector3 Right = { ModelMatrix.m[X][X],ModelMatrix.m[X][Y],ModelMatrix.m[X][Z] };
		//正規化して方向だけに
		Right.Normalize();
		//右方向を返す
		return Right;
	}

	/// <summary>
	/// カメラの回転をマウス操作でする
	/// </summary>
	void Rotate();

	/// <summary>
	/// カメラを移動させる
	/// </summary>
	void Move();

	/// <summary>
	/// カメラの操作を切り替える
	/// </summary>
	void IsSwichOperation();
public:
	/// <summary>
	/// 位置を設定
	/// </summary>
	/// <param name="pos">カメラ位置</param>
	void SetPosition(const Vector3& pos) {
		m_Pos = pos;
	}
	/// <summary>
	/// 位置を取得
	/// </summary>
	/// <returns>カメラ位置</returns>
	const Vector3 GetPosition() const {
		return m_Pos;
	}
	/// <summary>
	/// ターゲットを設定
	/// </summary>
	/// <param name="tar">カメラターゲット</param>
	void SetTarget(const Vector3& tar) {
		m_Target = tar;
	}
	/// <summary>
	/// ターゲットを取得
	/// </summary>
	/// <returns>カメラターゲット</returns>
	const Vector3 GetTarget() const {
		return m_Target;
	}

	void Debug()
	{
		static float OldRotAngle = m_RotAngle[X];
		if (m_RotAngle[X] != OldRotAngle) {
			int i = 0;
			i++;
			OldRotAngle = m_RotAngle[X];
		}
	}
private:
	Player* m_Player = nullptr;					//プレイヤーポインタ

	bool m_IsChasePlayer = false;
	Vector3 m_Pos = { 0.0f, 200.0f, 500.0f };	//位置
	Quaternion m_Rot = Quaternion::Identity;	//回転
	Vector3 m_Target = { 0.0f,-200.0f,-500.0f };			//ターゲット

	///マウス/////////////////////////////////////////////////////////
	float MouseRotX = 0.0f;
	float MouseRotY = 0.0f;
	int DefaultPoint[2] = { 500,300 };
	float m_SensiX = 0.00025f;
	float m_SensiY = 0.15f;
	float m_RotAngle[2] = { 0.0f,0.0f };
	///////////////////////////////////////////////////////////////////

	float rot = 0.0f;
	float AddPosY = 0.0f;
};

