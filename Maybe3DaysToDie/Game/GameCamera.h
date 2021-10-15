#pragma once
class Player;
//配列用の定数
//なんとなくマジックナンバーが嫌だったので定数化
enum Vector {
	X, Y, Z
};
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
	const Vector3 ForwardUpdate()
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
	const Vector3 RightUpdate()
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
private:
	Player* m_Player = nullptr;					//プレイヤーポインタ

	bool m_IsChasePlayer = false;
	Vector3 m_Pos = { 0.0f, 200.0f, 500.0f };	//位置
	Quaternion m_Rot = Quaternion::Identity;	//回転
	Vector3 m_Target = Vector3::Zero;			//ターゲット
};

