#pragma once
class GameCamera : public IGameObject
{
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
		ModelMatrix.MakeRotationFromQuaternion(m_qrot);
		//m[2]はZ軸
		Vector3 Forward = { ModelMatrix.m[2][0],ModelMatrix.m[2][1],ModelMatrix.m[2][2] };
		//正規化して方向だけに
		Forward.Normalize();
		//前方向を返す
		return Forward;
	}

	/// <summary>
	/// カメラの回転をマウス操作でする
	/// </summary>
	void Rotate();

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
	/// マウスを動かしたいときの関数
	/// trueでマウスを動かせる
	/// </summary>
	/// <param name="isMoving">動かしますか？</param>
	void SetMovingMouse(const bool isMoving) {
		m_IsMovingMouse = isMoving;
	}
private:
	Vector3 m_Pos = { 0.0f, 1000.0f, 0.0f };	//位置
	Vector3 m_Target = { 0.0f,1000.0f,100.0f};			//ターゲット
	Quaternion m_qrot = Quaternion::Identity;
	const float m_CameraDist = 100.0f;

	//センシ
	float SensiX = 0.1f;
	float SensiY = 0.1f;
	//カメラの制限
	const float xrotLimit = 360.0f;
	const float yrotLimit = 85.0f;
	//現在の回転
	float xrot = 0.0f;
	float yrot = 0.0f;
	//カメラの高さ
	float CameraHeight = 170.0f;

	bool m_IsMovingMouse = false;	//マウスが動かせるか
};

