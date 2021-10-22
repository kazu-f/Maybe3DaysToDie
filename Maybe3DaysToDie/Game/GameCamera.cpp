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

	rot += lsty;

	//Y軸周りの回転
	Quaternion xrot = Quaternion::Identity;
	xrot.SetRotationDegY(lstx);
	//カメラの右方向周りの回転
	Quaternion yrot = Quaternion::Identity;
	//回転が限界まで達していなかったら回転する
	if (std::abs(rot) < rotLimit)
	{
		yrot.SetRotationDeg(RightUpdate(), lsty);
	}
	rot = min(max(rot, -rotLimit), rotLimit);
	//回転の加算
	xrot.Multiply(yrot);
	m_qrot.Multiply(xrot);

	//マウスカーソルの位置を固定
	SetCursorPos(DefaultPoint[0], DefaultPoint[1]);
}