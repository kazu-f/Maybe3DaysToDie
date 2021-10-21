#pragma once

class IEnemy;

/// <summary>
/// エネミーのステートの基底クラス。
/// </summary>
class IEnemyState
{
public:
	/// <summary>
	/// コンストラクタ。
	/// </summary>
	/// <param name="enemy">エネミー。</param>
	IEnemyState(IEnemy* enemy)
		:m_enemy(enemy)
	{
	}
	//virtual ~IEnemyState();
	/// <summary>
	/// ステート入場時に呼ばれる。
	/// </summary>
	virtual void Enter() = 0;
	/// <summary>
	/// ステート退場時に呼ばれる。
	/// </summary>
	virtual void Leave() = 0;
	/// <summary>
	/// 更新。
	/// </summary>
	virtual void Update() = 0;
protected:
	IEnemy* m_enemy = nullptr;
};

