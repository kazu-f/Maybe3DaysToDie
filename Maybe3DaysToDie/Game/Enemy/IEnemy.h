#pragma once

/// <summary>
/// 敵キャラの基底クラス。
/// </summary>
/// <remarks>
/// 敵キャラを作成する際は、このクラスを継承して作成していくこと。
/// </remarks>
class IEnemy : public IGameObject
{
protected:
	/// <summary>
	/// エネミーの初期化パラメーター。
	/// </summary>
	struct EnemyParams
	{
		//Status
		unsigned int Attack = 20;		//攻撃力。		
		unsigned int Deffence = 5;		//防御力。		
		unsigned int EXP = 500;			//収得経験値。	
		float MoveSpeed = 3.0f;			//移動速度。	

		//move(cm)
		float AttackRange = 150.0f;		//攻撃範囲。	
		float SearchRange = 20000.0f;	//索敵範囲。	
	};
public:
	/// <summary>
	/// デストラクタ。
	/// </summary>
	virtual ~IEnemy();
	/// <summary>
	/// スタート。
	/// </summary>
	/// <returns></returns>
	virtual bool Start() override = 0;
	/// <summary>
	/// 更新。
	/// </summary>
	virtual void Update() override = 0;

private:
	//NVM
};

