#pragma once
class PlayerStamina final : public IGameObject
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

private:
	/// <summary>
	/// 現在のスタミナスプライトを初期化
	/// </summary>
	void CurrentSpriteInit();
	/// <summary>
	/// スタミナフレームを初期化
	/// </summary>
	void FlameSpriteInit();

	/// <summary>
	/// アイコンを初期化
	/// </summary>
	void IConSpriteInit();

	/// <summary>
	/// フォントを初期化
	/// </summary>
	void InitStaminaFont();
	/// <summary>
	/// フォントを更新
	/// </summary>
	void UpdateStaminaFont();

public:
	const bool IsUseStamina(const int cost) {
		static float DownTime = 0.0f;
		DownTime += GameTime().GetFrameDeltaTime();
		if (m_Stamina >= cost) {
			if (DownTime > 0.5000f) {
				DownTime = 0.0f;
				m_Stamina -= cost;
			}
			return true;
		}
		return false;
	}
	void Reset() {
		m_Stamina = m_MaxStamina;
	}
	void SetMax(int maxSt) {
		m_MaxStamina = maxSt;
	}
private:
	float m_RegeneTime = 2.0f;				//リジェネできる一定時間
	float m_nowRegeneTimer = 0.0f;			//一定時間以上になるとリジェネできる
	int m_Stamina = 100;					//スタミナ
	int m_MaxStamina = 100;					//最大スタミナ
	prefab::CSpriteRender* m_CurrentSprite = nullptr;	//現在のスタミナを表すスプライト
	prefab::CSpriteRender* m_FlameSprite = nullptr;		//スタミナの枠
	prefab::CSpriteRender* m_IConSprite = nullptr;		//アイコンのスプライト
	CFontRender* m_StaminaFont = nullptr;				//スタミナのフォント
};

