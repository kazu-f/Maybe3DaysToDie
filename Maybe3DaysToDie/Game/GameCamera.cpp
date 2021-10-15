#include "stdafx.h"
#include "GameCamera.h"
#include "Player/Player.h"

namespace {

	const float MoveDistance = 10.0f;			//1フレームに動く距離
	const float CameraTargetDistance = 500.0f;	//プレイヤーからのターゲット距離
}

bool GameCamera::Start()
{
	MainCamera().SetPosition(m_Pos);
	MainCamera().SetTarget(Vector3::Zero);
	m_Player = FindGO<Player>("player");
	return true;
}

void GameCamera::Update()
{
	if (m_IsChasePlayer) {
		Vector3 CameraPos=m_Player->GetPosition();
		CameraPos.y += 100.0f;
		m_Pos = CameraPos;
	}
	else {
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
	MainCamera().SetPosition(m_Pos);
	MainCamera().SetTarget(m_Target);
	MainCamera().Update();
}

void GameCamera::OnDestroy()
{
}
