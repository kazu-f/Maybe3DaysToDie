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
	void SetMax(const int maxhp) {
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

	const int HitDamage(const int damage) {
		m_Hp -= damage;
		m_Hp = max(m_Hp, 0);
		if (m_Hp == 0) {
			m_IsRegene = false;
		}
		return m_Hp;
	}

	void Reset() {
		m_Hp = m_MaxHp;
		m_IsRegene = true;
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

	/// <summary>
	/// フォントを初期化
	/// </summary>
	void InitHpFont();
	/// <summary>
	/// フォントを更新
	/// </summary>
	void UpdateHpFont();
private:
	prefab::CSpriteRender* m_CurrentSprite = nullptr;	//現在のHpスプライト
	prefab::CSpriteRender* m_FlameSprite = nullptr;	//HPの枠
	prefab::CSpriteRender* m_ICon = nullptr;			//Hpのアイコン
	int m_Hp = 100;										//現在のHp
	int m_MaxHp = 100;									//最大Hp
	float m_RegeneTime = 5.0f;							//自然回復時間
	float m_nowHpRegeneTime = 0.0f;						//自然回復してからの経過時間
	CFontRender* m_HpFont = nullptr;					//Hpを表すフォント
	bool m_IsRegene = true;
};