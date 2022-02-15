#pragma once

#include "NaviMeshManager.h"

class IEnemy;
class Stage;
class Player;

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
	/// <summary>
	/// デストラクタ。
	/// </summary>
	~EnemyGenerator();

public:
	bool Start() override;
	void Update() override;

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
	IEnemy* Create(const char* tag = "Enemy")
	{
		if (m_currentEnemyCount >= MAX_ENEMY) {
			//エネミーを設定以上に作成使用としている為、リクエストは許可しない。
			//MessageBoxA(NULL, "エネミーの許容量を超えました、このオブジェクトは削除されます。", "Warning!!", MB_OK);
			return nullptr;
		}

		//インスタンス化。
		IEnemy* enemy = NewGO<T>(0 ,tag);
		//エネミーと相対参照に。
		enemy->SetEnemyGenerator(this);
		//nvm.
		enemy->SetStage(m_stage);
		//リストに積み積み。
		m_enemyList.push_back(enemy);
		m_currentEnemyCount++;

		if (m_isActiveBloodMoon) {
			//ブラッドムーン時の処理を追加する。
		}

		return enemy;
	}

	/// <summary>
	/// プレイヤーの周りに敵を生成する。
	/// </summary>
	void SpawnEnemyAroundPlayer();

	/// <summary>
	/// エネミーの登録を解除する。
	/// </summary>
	/// <param name="enemy"></param>
	void UnRegistEnemy(IEnemy* enemy);
	
	/// /// <summary>
	/// ブラッドムーンを有効化する。
	/// <para>全ゾンビに索敵範囲に関わらず、Playerまで探査させる。</para>
	/// </summary>
	void ActivateBloodMoonHode();
	
	/// /// <summary>
	/// ブラッドムーンを無効化。
	/// </summary>
	void DisableBloodMoonHode();

	/// <summary>
	/// 死亡したエネミーの数をインクリメント。
	/// </summary>
	void AddDeadEnemyCount()
	{
		m_deadEnemyCount++;
	}

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
	static const int MAX_ENEMY = 16;				//管理できる最大エネミー数。
	Stage* m_stage = nullptr;						//ステージp
	Player* m_player = nullptr;						//プレイヤーp
	static std::map<int, int> m_indexToSign;		//インデックスから符号。

	/* EnemyManagement */
	int m_currentEnemyCount = 0;					//現在、存在しているエネミーの数。
	std::vector<IEnemy*> m_enemyList;				//エネミーのリスト。
	const float START_SPAWN_ENEMY_TIME = 10.0f;			//エネミーが沸く周期。
	const float BLOOD_MOON_SPAWN_TIME = 3.0f;
	float m_spawnEnemyTime = START_SPAWN_ENEMY_TIME;
	float m_spawnEnemyTimer = START_SPAWN_ENEMY_TIME / 2;	//エネミーが沸くタイマー。
	int m_deadEnemyCount = 0;

	static std::map<float, int> m_currentSpawnTimeToChangeSpawnTimeCount;


	/* bloodMoon */
	bool m_isActiveBloodMoon = true;				//ブラッドムーンが有効？
	
};

