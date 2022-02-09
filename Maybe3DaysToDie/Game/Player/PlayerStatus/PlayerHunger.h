#pragma once
class Player;
/// <summary>
/// プレイヤーの空腹度を表すクラス
/// </summary>
class PlayerHunger final : public IGameObject
{
private:
	/// <summary>
	/// Newされた時にGameObjectから呼ばれる 
	/// 初期化用関数
	/// </summary>
	/// <returns>trueが返るまでループする</returns>
	bool Start() override final;

	/// <summary>
	/// 毎フレーム呼ばれる更新関数
	/// </summary>
	void Update()override final;

	/// <summary>
	/// deleteされるとGameObjectから呼ばれる関数
	/// </summary>
	void OnDestroy()override final;

public:
	const void SetMax(const int maxHun) {
		m_MaxHunger = maxHun;
	}

	void SetPlayer(Player* pp) {
		m_Player = pp;
	}

	void Reset() {
		m_Hunder = m_MaxHunger;
	}
private:
	/// <summary>
	/// 現在の空腹ゲージを初期化する
	/// </summary>
	void CurrentSpriteInit();

	/// <summary>
	/// 空腹ゲージの枠を初期化する
	/// </summary>
	void FlameSpriteInit();
private:
	prefab::CSpriteRender* m_CurrentSprite = nullptr;	//現在の空腹ゲージ
	prefab::CSpriteRender* m_FlameSprite = nullptr;		//空腹ゲージの枠

	float m_HungeryTime = 1.0f;							//お腹が空く時間
	float m_HungeryCountTime = 0.0f;					//経過時間
	int m_Hunder = 1;									//空腹度
	int m_MaxHunger = 1;								//満腹量
	
	Player* m_Player = nullptr;							//プレイヤーのポインタ
};

