#include "stdafx.h"
#include "GameCamera.h"
#include "Player/Player.h"

namespace {
	const float MoveDistance = 10.0f;			//1フレームに動く距離
	const float CameraTargetDistance = 500.0f;	//プレイヤーからのターゲット距離
	const float NeckLimitY = 80.0f;				//上や下を向ける限界
}

bool GameCamera::Start()
{
	MainCamera().SetPosition(m_Pos);
	MainCamera().SetTarget(m_Target);
	MainCamera().Update();
	m_Rot.SetRotation(m_Pos, m_Target);
	m_Player = FindGO<Player>("player");
	return true;
}

void GameCamera::Update()
{
	//操作を切り替える？
	IsSwichOperation();

	//マウスで向きを変える
	Rotate();
	//どちらの操作？
	if (m_IsChasePlayer) {
		Vector3 CameraPos = m_Player->GetPosition();
		CameraPos.y += 100.0f;
		m_Pos = CameraPos;
	}
	else {
		//マウス操作で回転
		Move();
	}
	Vector3 Forward = ForwardUpdate();
	m_Target = Forward * CameraTargetDistance;

	MainCamera().Update();
}

void GameCamera::OnDestroy()
{
}

void GameCamera::Rotate()
{
	////マウスカーソルの位置を取得
	//POINT pt;
	//GetCursorPos(&pt);
	//int lst[] = { pt.x,pt.y };
	////カメラの回転量をマウスカーソルの位置と初期値を比較して求める
	//m_RotAngle[X] = (lst[X] - DefaultPoint[X]) * m_SensiX;
	////カメラのポジションに足すY方向の値をマウスカーソルの位置と初期値を比較して求める
	//m_RotAngle[Y] = (lst[Y] - DefaultPoint[Y]) * m_SensiY;
	////マウスカーソルの位置をセット
	//SetCursorPos(DefaultPoint[X], DefaultPoint[Y]);

	////カメラのX方向の回転
	//Quaternion ModelRotX;
	//ModelRotX.SetRotationDegY(m_RotAngle[X]);
	//m_Rot.Multiply(ModelRotX);

	//Debug();
	//////カメラが向ける上下の限界
	////m_RotAngle[Y] = max(min(m_RotAngle[Y], NeckLimitY), -NeckLimitY);

	////現在の回転を保持。
	//Quaternion oldRot = m_Rot;

	////右方向計算
	//Vector3 rightVec = RightUpdate();

	//Quaternion ModelRotY = Quaternion::Identity;
	////カメラのY方向の回転
	//ModelRotY.SetRotationDeg(rightVec, m_RotAngle[Y]);
	////カメラのX方向の回転にY方向の動きを掛ける
	//m_Rot.Multiply(ModelRotY);

	////前方向計算。
	//Vector3 forwardVec = ForwardUpdate();
	////XZ平面上の前方向を計算
	//Vector3 forwardXZVec = forwardVec;
	//forwardXZVec.y = 0.0f;
	//forwardXZVec.Normalize();

	////内積を取る。
	//float dot = forwardXZVec.Dot(forwardVec);
	
	//マウスカーソルの位置を取得
	POINT pt;
	GetCursorPos(&pt);
	int lstx = pt.x;
	int lsty = pt.y;

	//カメラの回転量をマウスカーソルの位置と初期値を比較して求める
	rot += (DefaultPoint[0] - lstx) * m_SensiX;
	//最終的なカメラのポジション
	Vector3 m_pos = m_Player->GetPosition();
	//最終的なカメラのターゲットのポジション
	Vector3 targetPos = m_Player->GetPosition();
	//最低限の高さの確保
	targetPos.y = 100.0f;

	//カメラのポジションに足すY方向の値をマウスカーソルの位置と初期値を比較して求める
	AddPosY += (DefaultPoint[1] - lsty) * m_SensiY;

	//AddPosY = min(max(NeckLimitY, AddPosY), NeckLimitY);
	//カメラのポジションに足すベクトル
	Vector3 addPos = Vector3::Zero;
	//rotからカメラのターゲットの位置を決める
	addPos.x -= sinf(rot) * CameraTargetDistance;
	addPos.y += AddPosY;
	addPos.z = cosf(rot) * CameraTargetDistance;
	targetPos += addPos;

	m_pos.y += 100.0f;
	Vector3 AddPos = MainCamera().GetForward();
	AddPos.y = 0.0f;
	AddPos.Normalize();
	m_pos += AddPos * 15.0f;
	//マウスカーソルの位置をセット
	SetCursorPos(DefaultPoint[0], DefaultPoint[1]);

	MainCamera().SetPosition(m_pos);
	MainCamera().SetTarget(targetPos);
	////カメラにセット
	//g_camera3D->SetPosition(m_pos);
	//g_camera3D->SetTarget(targetPos);
	////上下の回転を制限。
	//if (dot < 0.099f)
	//{
	//	m_Rot = oldRot;
	//}
	//if (GetAsyncKeyState('O')) {
	//	m_Rot.SetRotationDegX(180.0f);
	//}
}

void GameCamera::Move()
{
	Vector3 MoveSpeed = Vector3::Zero;
	//前方向を取得
	Vector3 Forward = ForwardUpdate();
	//右方向を取得
	Vector3 Right = RightUpdate();
	//Wキーが押されたら
	if (GetAsyncKeyState('W')) {
		MoveSpeed += Forward;
	}
	//Sキーが押されたら
	if (GetAsyncKeyState('S')) {
		MoveSpeed -= Forward;
	}
	//Aキーが押されたら
	if (GetAsyncKeyState('A')) {
		MoveSpeed -= Right;
	}
	//Dキーが押されたら
	if (GetAsyncKeyState('D')) {
		MoveSpeed += Right;
	}
	//正規化して方向だけに
	MoveSpeed.Normalize();
	//1フレームに動く距離を掛ける
	MoveSpeed *= MoveDistance;
	//移動させる
	m_Pos += MoveSpeed;
}

void GameCamera::IsSwichOperation()
{
	if (GetAsyncKeyState('G')) {
		m_IsChasePlayer = !m_IsChasePlayer;
	}
}
