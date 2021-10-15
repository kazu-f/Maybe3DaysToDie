#include "stdafx.h"
#include "Player.h"
#include "PlayerStatus/PlayerHp.h"
#include "PlayerStatus/PlayerStamina.h"
#include "PlayerStatus/PlayerHunger.h"
#include "PlayerStatus/PlayerWater.h"

namespace {
	const float MoveDistance = 10.0f;			//1フレームに動く距離
	const float CameraTargetDistance = 500.0f;	//プレイヤーからのターゲット距離
	const float NeckLimitY = 80.0f;				//上や下を向ける限界
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
	//カメラを更新
	SetCamera();
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
	//マウスカーソルの位置を取得
	POINT pt;
	GetCursorPos(&pt);
	int lst[] = { pt.x,pt.y };
	//カメラの回転量をマウスカーソルの位置と初期値を比較して求める
	m_RotAngle[X] = (lst[X] - DefaultPoint[X]) * m_SensiX;
	//カメラのポジションに足すY方向の値をマウスカーソルの位置と初期値を比較して求める
	m_RotAngle[Y] = (lst[Y] - DefaultPoint[Y] ) * m_SensiY;
	//マウスカーソルの位置をセット
	SetCursorPos(DefaultPoint[X], DefaultPoint[Y]);

	//カメラのX方向の回転
	Quaternion ModelRotX;
	ModelRotX.SetRotationDegY(m_RotAngle[X]);
	m_Rot.Multiply(ModelRotX);

	//カメラが向ける上下の限界
	m_RotAngle[Y] = max(min(m_RotAngle[Y], NeckLimitY), -NeckLimitY);

	//現在の回転を保持。
	Quaternion oldRot = m_Rot;

	//右方向計算
	Vector3 rightVec = RightUpdate();

	Quaternion ModelRotY = Quaternion::Identity;
	//カメラのY方向の回転
	ModelRotY.SetRotationDeg(rightVec,m_RotAngle[Y]);
	//カメラのX方向の回転にY方向の動きを掛ける
	m_Rot.Multiply(ModelRotY);

	//前方向計算。
	Vector3 forwardVec = ForwardUpdate();
	//XZ平面上の前方向を計算
	Vector3 forwardXZVec = forwardVec;
	forwardXZVec.y = 0.0f;
	forwardXZVec.Normalize();

	//内積を取る。
	float dot = forwardXZVec.Dot(forwardVec);

	//上下の回転を制限。
	if (dot < 0.1f)
	{
		m_Rot = oldRot;
	}
}

void Player::ModelUpdate()
{
	//回転
	Rotation();
	//移動
	Move();
}