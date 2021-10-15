#pragma once
class GameCamera : public IGameObject
{
private:
	/// <summary>
	/// GameObjectに積まれると一度だけ呼ばれる初期化関数
	/// </summary>
	/// <returns>trueが返るまでループする</returns>
	bool Start();
	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	/// <summary>
	/// deleteされると呼ばれる関数
	/// </summary>
	void OnDestroy();
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
	const Vector3 GetPosition() {
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
	const Vector3 GetTarget() {
		return m_Target;
	}
private:

	Vector3 m_Pos = { 0.0f, 200.0f, 500.0f };	//位置
	Vector3 m_Target = Vector3::Zero;			//ターゲット
};

