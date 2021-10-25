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
	//�}�E�X�Ō�����ς���
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
	//�}�E�X�J�[�\���̈ʒu���擾
	POINT pt;
	GetCursorPos(&pt);
	//���̃t���[���ł̈ړ���
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

	//�J�����̉E��������̉�]
	Quaternion yqrot = Quaternion::Identity;
	yqrot.SetRotationDegX(yrot);
	//Y������̉�]
	Quaternion xqrot = Quaternion::Identity;
	xqrot.SetRotationDegY(xrot);
	//��]�̉��Z
	//�E�������肩����Z����
	yqrot.Multiply(xqrot);
	Quaternion rot = Quaternion::Identity;
	rot.Multiply(yqrot);

	m_qrot = rot;
	//�}�E�X�J�[�\���̈ʒu���Œ�
	SetCursorPos(DefaultPoint[0], DefaultPoint[1]);
}