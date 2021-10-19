#include "stdafx.h"
#include "Player.h"
#include "PlayerStatus/PlayerHp.h"
#include "PlayerStatus/PlayerStamina.h"
#include "PlayerStatus/PlayerHunger.h"
#include "PlayerStatus/PlayerWater.h"

namespace {
	const float MoveDistance = 10.0f;			//1フレームに動く距離
	const float CameraTargetDistance = 500.0f;	//プレイヤーからのターゲット距離
	const float NeckLimitY = 10.0f;				//上や下を向ける限界
}

bool Player::Start()
{
	//Hpを作る
	m_Hp = NewGO<PlayerHp>(0, "playerHp");

	//スタミナを作る
	m_Stamina = NewGO<PlayerStamina>(0, "playerStamina");

	//空腹度を作る
	m_Hunger = NewGO<PlayerHunger>(0, "playerHunger");

	//水分を作る
	m_Water = NewGO<PlayerWater>(0,"playerWater");

	MainCamera().SetPosition(m_Pos);
	//Vector3 m_Target = { 0.0f,-200.0f,-500.0f };			//ターゲット
	//MainCamera().SetTarget(m_Target);
	//MainCamera().Update();
	return true;
}

void Player::Update()
{
	//時間経過による回復
	PeriodicUpdate();
	//ステートを更新
	StateUpdate();
	//モデル情報を更新
	ModelUpdate();
}

void Player::OnDestroy()
{
	//モデルを削除
	DeleteGO(m_Model);
	//Hpを削除
	DeleteGO(m_Hp);
	//スタミナを削除
	DeleteGO(m_Stamina);
}

void Player::PeriodicUpdate()
{
	//スタミナを自然回復
	StaminaRegene();
	//空腹値を減少
	HungerDecrease();
	//水分を減少
	WarterDecrease();
	//ステータス減少時間を数える
	m_DeltaTime += GameTime().GetFrameDeltaTime();
}

void Player::StaminaRegene()
{
}

void Player::HungerDecrease()
{
}

void Player::WarterDecrease()
{
}

void Player::StateUpdate()
{
	ChangeState();
}

void Player::ChangeState()
{
}

void Player::Move()
{
}

void Player::Rotation()
{
}

void Player::ModelUpdate()
{
	//回転
	Rotation();
	//移動
	Move();
}