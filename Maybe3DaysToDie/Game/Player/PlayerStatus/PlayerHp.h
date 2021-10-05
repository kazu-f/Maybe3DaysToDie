#pragma once
class PlayerHp final : public IGameObject
{
private:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <returns>trueが返るまでループする</returns>
	bool Start()override final;

	/// <summary>
	/// 毎フレーム呼ばれる更新関数
	/// </summary>
	void Update()override final;

	/// <summary>
	/// Deleteされたフレームで呼ばれる削除関数
	/// </summary>
	void OnDestroy()override final;
public:
	/// <summary>
	/// 最大Hpを変更できる
	/// </summary>
	/// <param name="maxhp">設定したいHp</param>
	void SetMaxHp(const int maxhp) {
		m_MaxHp = maxhp;
	}

	/// <summary>
	/// 現在のHpを返す
	/// </summary>
	/// <returns>hp</returns>
	const int GetHp() {
		return m_Hp;
	}

	/// <summary>
	/// 自然回復の時間を変更できる
	/// </summary>
	/// <param name="regeneTime">自然回復の時間</param>
	void SetRegeneTime(const float regeneTime) {
		m_RegeneTime = regeneTime;
	}
private:
	/// <summary>
	/// 現在のHPスプライトを初期化
	/// </summary>
	void InitCurrentSprite();

	/// <summary>
	/// Hpフレームを初期化
	/// </summary>
	void InitFrameSprite();

	/// <summary>
	/// HpIConを初期化
	/// </summary>
	void InitIConSprite();
private:
	prefab::CSpriteRender* m_HpCurrentSprite = nullptr;	//現在のHpスプライト
	prefab::CSpriteRender* m_HpFlameSprite = nullptr;	//HPの枠
	prefab::CSpriteRender* m_HpICon = nullptr;			//Hpのアイコン
	int m_Hp = 100;										//現在のHp
	int m_MaxHp = 100;									//最大Hp
	float m_RegeneTime = 1.0f;							//自然回復時間
	float m_nowHpRegeneTime = 0.0f;						//自然回復してからの経過時間

};