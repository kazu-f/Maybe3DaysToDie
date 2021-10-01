#include "stdafx.h"
#include "Player.h"
#include "GameCamera.h"

namespace {
	const float MoveDistance = 10.0f;			//1フレームに動く距離
	const float CameraTargetDistance = 500.0f;	//プレイヤーからのターゲット距離
	const float NeckLimitY = 80.0f;				//上や下を向ける限界
	//配列用の定数
	//なんとなくマジックナンバーが嫌だったので定数化
	const int X = 0;
	const int Y = 1;
	const int Z = 2;
}

bool Player::Start()
{
	//カメラを探す
	m_Camera = FindGO<GameCamera>("camera");
	return true;
}

void Player::Update()
{
	//時間経過による回復
	PeriodicUpdate();
	//ステートを回復
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
}

void Player::PeriodicUpdate()
{
	//HPを自然回復
	HpRegene();
	//スタミナを自然回復
	StaminaRegene();
	//空腹値を減少
	HungerDecrease();
	//水分を減少
	WarterDecrease();
	//ステータス減少時間を数える
	m_DeltaTime += GameTime().GetFrameDeltaTime();
	m_nowHpRegeneTimer += GameTime().GetFrameDeltaTime();
}

void Player::HpRegene()
{
	if (m_nowHpRegeneTimer >= m_HpRegeneTime)
	{
		m_nowHpRegeneTimer -= m_HpRegeneTime;
	}
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
	Vector3 MoveSpeed = Vector3::Zero;
	//前方向を取得
	Vector3 ForwardModel = ForwardUpdate();
	//右方向を取得
	Vector3 RightModel = RightUpdate();
	//Wキーが押されたら
	if (GetAsyncKeyState('W')) {
		MoveSpeed += ForwardModel;
	}
	//Sキーが押されたら
	if (GetAsyncKeyState('S')) {
		MoveSpeed -= ForwardModel;
	}
	//Aキーが押されたら
	if (GetAsyncKeyState('A')) {
		MoveSpeed -= RightModel;
	}
	//Dキーが押されたら
	if (GetAsyncKeyState('D')) {
		MoveSpeed += RightModel;
	}
	//正規化して方向だけに
	MoveSpeed.Normalize();
	//1フレームに動く距離を掛ける
	MoveSpeed *= MoveDistance;
	//移動させる
	m_Pos += MoveSpeed;
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

Vector3 Player::ForwardUpdate()
{
	Matrix ModelMatrix = Matrix::Identity;
	ModelMatrix.MakeRotationFromQuaternion(m_Rot);
	//m[2]はZ軸
	Vector3 ForwardModel = { ModelMatrix.m[Z][X],ModelMatrix.m[Z][Y],ModelMatrix.m[Z][Z] };
	//正規化して方向だけに
	ForwardModel.Normalize();
	//前方向を返す
	return ForwardModel;
}

Vector3 Player::RightUpdate()
{
	Matrix ModelMatrix = Matrix::Identity;
	ModelMatrix.MakeRotationFromQuaternion(m_Rot);
	//m[0]はX軸
	Vector3 RightModel = { ModelMatrix.m[X][X],ModelMatrix.m[X][Y],ModelMatrix.m[X][Z] };
	//正規化して方向だけに
	RightModel.Normalize();
	//右方向を返す
	return RightModel;
}

void Player::SetCamera()
{
	//カメラポジションを設定
	m_Camera->SetPosition(m_Pos);
	//カメラターゲットを設定
	Vector3 CaneraTarget = Vector3::Zero;
	CaneraTarget = m_Pos;
	//フォワード方向を取得
	Vector3 Forward = ForwardUpdate();
	//カメラターゲットは前方向とカメラターゲット用の距離を掛けた位置になる
	CaneraTarget += Forward* CameraTargetDistance;
	//カメラターゲットを設定
	m_Camera->SetTarget(CaneraTarget);
}
