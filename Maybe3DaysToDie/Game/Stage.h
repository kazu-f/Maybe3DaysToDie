#pragma once
class Stage : public IGameObject
{
	/// <summary>
	/// 初期化
	/// </summary>
	/// <returns>trueを返すまでループする</returns>
	bool Start();
	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	/// <summary>
	/// deleteをすると呼ばれる関数
	/// </summary>
	void OnDestroy();

	/// <summary>
	/// 地面を表示する
	/// </summary>
	void NewGround();
private:
	prefab::ModelRender* m_Model = nullptr;		//地面
};

