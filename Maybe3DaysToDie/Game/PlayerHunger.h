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

private:
	prefab::CSpriteRender* m_CrrentSprite = nullptr;
	prefab::CSpriteRender* m_FrameSprite = nullptr;

};

