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
	//マウスで向きを変える
	Rotate();
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
	//マウスカーソルの位置を取得
	POINT pt;
	GetCursorPos(&pt);
	//このフレームでの移動量
	float lstx = pt.x - DefaultPoint[0];
	float lsty = pt.y - DefaultPoint[1];

	lstx *= SensiX;
	lsty *= SensiY;

	xrot += lstx;
	yrot += lsty;
	rot += lsty;

	yrot = min(max(yrot, -yrotLimit), yrotLimit);
	//if (yrot > yrotLimit)
	//{
	//	yrot = 180.0f - yrot;
	//}
	//else if (yrot < -yrotLimit)
	//{
	//	yrot = -180.0f - yrot;
	//}
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
	//マウスカーソルの位置を固定
	SetCursorPos(DefaultPoint[0], DefaultPoint[1]);
}