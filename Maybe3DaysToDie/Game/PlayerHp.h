#pragma once
class PlayerHp final : public IGameObject
{
	/// <summary>
	/// 初期化
	/// </summary>
	/// <returns>trueが返るまでループする</returns>
	bool Start()override final;
	/// <summary>
	/// 更新
	/// </summary>
	void Update()override final;
	/// <summary>
	/// 
	/// </summary>
	void OnDestroy()override final;


};

