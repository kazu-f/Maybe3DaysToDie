#include "stdafx.h"
#include "GameCamera.h"
#include "Player/Player.h"

bool GameCamera::Start()
{
	MainCamera().SetPosition(m_Pos);
	MainCamera().SetTarget(m_Target);
	MainCamera().Update();
	return true;
}

void GameCamera::Update()
{
	if (!m_IsMovingMouse) {
		//マウスで向きを変える
		Rotate();
	}
	m_Pos.y += CameraHeight;
	m_Target = m_Pos + ForwardUpdate() * m_CameraDist;
	MainCamera().SetPosition(m_Pos);
	MainCamera().SetTarget(m_Target);
	MainCamera().Update();
}

void GameCamera::OnDestroy()
{
}

void GameCamera::Rotate()
{
	xrot += MauseInfo::GetInstance()->GetMauseMove().x * SensiX;
	yrot += MauseInfo::GetInstance()->GetMauseMove().y * SensiY;

	yrot = min(max(yrot, -yrotLimit), yrotLimit);
	if (xrot > xrotLimit)
	{
		xrot -= xrotLimit;
	}
	else if (xrot < -xrotLimit)
	{
		xrot += xrotLimit;
	}

	//カメラの右方向周りの回転
	Quaternion yqrot = Quaternion::Identity;
	yqrot.SetRotationDegX(yrot);
	//Y軸周りの回転
	Quaternion xqrot = Quaternion::Identity;
	xqrot.SetRotationDegY(xrot);
	//回転の加算
	//右方向周りから加算する
	yqrot.Multiply(xqrot);
	Quaternion rot = Quaternion::Identity;
	rot.Multiply(yqrot);

	m_qrot = rot;
	MauseInfo::GetInstance()->SetMauseCursor(
		{
		MauseInfo::IntialMausePos().x,
		MauseInfo::IntialMausePos().y
		}
	);
}