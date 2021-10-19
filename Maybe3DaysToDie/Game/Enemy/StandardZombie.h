#pragma once

#include "IEnemy.h"

/// <summary>
/// 標準的なゾンビ。
/// </summary>
class StandardZombie : public IEnemy
{
public:
	/// <summary>
	/// コンストラクタ。
	/// </summary>
	StandardZombie() {};
public:
	/// <summary>
	///	スタート。
	/// </summary>
	/// <returns></returns>
	bool Start() override final;
	/// <summary>
	/// 更新。
	/// </summary>
	void Update() override final;
	/// <summary>
	/// パラメーター値を取得。
	/// </summary>
	/// <returns></returns>
	EnemyParams& GetEnemyParameters() override;
private:
	Vector3 m_scale = { 6.0f, 6.0f, 6.0f };		//拡大。
	IEnemy::EnemyParams m_parameters;			//パラメーター。
};

