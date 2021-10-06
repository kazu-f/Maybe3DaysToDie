#pragma once
/// <summary>
/// 時間を計測し、１日を数えるクラス
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
private:
	int m_minit = 0;		//分
	int m_Hours = 0;		//時
	int m_Day = 0;			//日
	float m_Second = 0.0f;	//秒
	CFontRender* m_TimeFont = nullptr;
};

