#pragma once

class Player;
class PlayerWater final : public IGameObject
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
	/// 現在の水分スプライトを初期化
	/// </summary>
	void CurretSpriteInit();

	/// <summary>
	/// 水分フレームを初期化
	/// </summary>
	void FlameSpriteInit();

public:
	void SetPlayer(Player* pp){
		m_Player = pp;
	}
private:
	prefab::CSpriteRender* m_CurrentWaterSprite = nullptr;	//現在の水分のスプライト
	prefab::CSpriteRender* m_FlameWaterSprite = nullptr;	//水分の枠のスプライト
	float m_WaterCountTime = 0.0f;							//経過時間
	float m_DecWaterTime = 1.0f;							//喉が乾く時間
	int m_Water = 100;										//水分
	int m_MaxWater = 100;									//水分の最大量
	Player* m_Player = nullptr;
};

