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
		//ƒ}ƒEƒX‚ÅŒü‚«‚ð•Ï‚¦‚é
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

	//ƒJƒƒ‰‚Ì‰E•ûŒüŽü‚è‚Ì‰ñ“]
	Quaternion yqrot = Quaternion::Identity;
	yqrot.SetRotationDegX(yrot);
	//YŽ²Žü‚è‚Ì‰ñ“]
	Quaternion xqrot = Quaternion::Identity;
	xqrot.SetRotationDegY(xrot);
	//‰ñ“]‚Ì‰ÁŽZ
	//‰E•ûŒüŽü‚è‚©‚ç‰ÁŽZ‚·‚é
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