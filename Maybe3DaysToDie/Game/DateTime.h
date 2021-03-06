#pragma once
/// <summary>
/// 時間を計測し、１日を数えるクラス
/// １分ごとのカウント等はcpp側の名前空間内にあるよ〜
/// </summary>
class DateTime final : public IGameObject
{
private:
	/// <summary>
	/// GameObjectに積まれると一度だけ呼ばれる初期化関数
	/// </summary>
	/// <returns>trueが返るまでループする</returns>
	bool Start()override final;

	/// <summary>
	/// 毎フレーム呼ばれる更新関数
	/// </summary>
	void Update()override final;

	/// <summary>
	/// Deleteされたときに呼ばれる関数
	/// </summary>
	void OnDestroy()override final;
public:
	int GetDay() {
		return m_Day;
	}

	/// <summary>
	/// ホードかどうか
	/// </summary>
	/// <returns>ホードですか？</returns>
	bool GetHode() const {
		return m_IsHode;
	}

	/// <summary>
	/// ホードを終了させる
	/// </summary>
	void FinishHode();
private:
	int m_minit = 0;		//分
	int m_Hours = 0;		//時
	int m_Day = 0;			//日
	float m_Second = 0.0f;	//秒
	CFontRender* m_TimeFont = nullptr;
	bool m_IsHode = false;
};

