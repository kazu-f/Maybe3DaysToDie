#pragma once

/// <summary>
/// エネミーを生成するオブジェクト。
/// </summary>
class EnemyGenerator : public IGameObject
{
public:
	/// <summary>
	/// コンストラクタ。
	/// </summary>
	EnemyGenerator();
public:
	/// <summary>
	/// スタート。
	/// </summary>
	/// <returns></returns>
	bool Start() override;
	/// <summary>
	/// デリート。
	/// </summary>
	void OnDestroy() override;
	/// <summary>
	/// 更新。
	/// </summary>
	void Update() override;
private:
	int m_currentEnemyCount = 0;		//現在、存在しているエネミーの数。
	
};

