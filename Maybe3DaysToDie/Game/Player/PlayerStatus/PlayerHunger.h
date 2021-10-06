#pragma once
/// <summary>
/// プレイヤーの空腹度を表すクラス
/// </summary>
class PlayerHunger : public IGameObject
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
	const void SetMaxHunger(const int maxHun) {
		m_MaxHunger = maxHun;
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

	/// <summary>
	/// 空腹アイコンを初期化する
	/// </summary>
	void IConSpriteInit();
private:
	prefab::CSpriteRender* m_CrrentSprite = nullptr;	//現在の空腹ゲージ
	prefab::CSpriteRender* m_FlameSprite = nullptr;		//空腹ゲージの枠
	prefab::CSpriteRender* m_IConSprite = nullptr;		//空腹アイコン

	float m_HungryTime = 0.0f;							//お腹が空く時間
	int m_Hunder = 100;									//空腹度
	int m_MaxHunger = 100;								//満腹量
};

