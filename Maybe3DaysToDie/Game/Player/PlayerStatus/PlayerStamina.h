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
private:
	float m_RegeneTime = 1.0f;				//リジェネできる一定時間
	float m_nowRegeneTimer = 0.0f;			//一定時間以上になるとリジェネできる
	int m_Stamina = 100;					//スタミナ
	int m_MaxStamina = 100;
	prefab::CSpriteRender* m_CurrentSprite = nullptr;	
	prefab::CSpriteRender* m_FlameSprite = nullptr;
	prefab::CSpriteRender* m_IConSprite = nullptr;
};

