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
	prefab::CSpriteRender* m_StaminaCurrentSprite = nullptr;
	prefab::CSpriteRender* m_StaminaFlameSprite = nullptr;
	prefab::CSpriteRender* m_StaminaIConSprite = nullptr;

	float m_RegeneTime = 0.0f;				//リジェネできる一定時間
	float m_nowRegeneTimer = 0.0f;			//一定時間以上になるとリジェネできる
	int m_Stamina = 100;					//スタミナ
	int m_MaxStamina = 100;					//スタミナ最大値
											//変更するかもしれないので定数にはしない
};

