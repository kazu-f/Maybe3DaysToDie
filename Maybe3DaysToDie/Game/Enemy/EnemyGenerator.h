#pragma once

#include "NaviMeshManager.h"

class IEnemy;
class Stage;

/// <summary>
/// エネミーを生成するオブジェクト。
/// </summary>
class EnemyGenerator
{
public:
	/// <summary>
	/// コンストラクタ。
	/// </summary>
	EnemyGenerator();
	/// <summary>
	/// デストラクタ。
	/// </summary>
	~EnemyGenerator();
public:
	/// <summary>
	/// 全エネミーを解放。
	/// </summary>
	void ReleaseEnemy();

	/// <summary>
	/// 敵を作成する。
	/// <para>T = Enemyの派生クラス。</para>
	/// </summary>
	/// <param name="nvmGenerator">経路探査させる場合nvmGenerator。</param>
	/// <param name="tag">IGameObject登録タグ。</param>
	template<class T>
	void Create(const char* tag = "Enemy")
	{
		if (m_currentEnemyCount >= MAX_ENEMY) {
			//エネミーを設定以上に作成使用としている為、リクエストは許可しない。
			MessageBoxA(NULL, "エネミーの許容量を超えました、このオブジェクトは削除されます。", "Warning!!", MB_OK);
			return;
		}

		//インスタンス化。
		IEnemy* enemy = NewGO<T>(0 ,tag);
		//エネミーと相対参照に。
		enemy->SetEnemyGenerator(this);
		//nvm.
		enemy->SetNVMGenerator(m_stage);
		//リストに積み積み。
		m_enemyList.push_back(enemy);
		m_currentEnemyCount++;

		if (m_isActiveBloodMoon) {
			//ブラッドムーン時の処理を追加する。
		}
	}
	/// <summary>
	/// エネミーの登録を解除する。
	/// </summary>
	/// <param name="enemy"></param>
	void UnRegistEnemy(IEnemy* enemy);
	/// <summary>
	/// ブラッドムーンを有効化する。
	/// <para>全ゾンビに索敵範囲に関わらず、Playerまで探査させる。</para>
	/// </summary>
	void ActivateBloodMoonHode();
	/// <summary>
	/// ブラッドムーンを無効化。
	/// </summary>
	void DisableBloodMoonHode();

	/// <summary>
	/// ステージを設定。
	/// </summary>
	/// <param name="stage"></param>
	void SetStage(Stage* stage)
	{
		m_stage = stage;
	}
private:
	/* Const */
	static const int MAX_ENEMY = 16;		//管理できる最大エネミー数。
	Stage* m_stage = nullptr;

	/* EnemyManagement */
	int m_currentEnemyCount = 0;			//現在、存在しているエネミーの数。
	std::vector<IEnemy*> m_enemyList;		//エネミーのリスト。

	/* bloodMoon */
	bool m_isActiveBloodMoon = false;		//ブラッドムーンが有効？
	
};

