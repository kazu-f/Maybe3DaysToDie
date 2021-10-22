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

	rot += lsty;

	//Y������̉�]
	Quaternion xrot = Quaternion::Identity;
	xrot.SetRotationDegY(lstx);
	//�J�����̉E��������̉�]
	Quaternion yrot = Quaternion::Identity;
	//��]�����E�܂ŒB���Ă��Ȃ��������]����
	if (std::abs(rot) < rotLimit)
	{
		yrot.SetRotationDeg(RightUpdate(), lsty);
	}
	rot = min(max(rot, -rotLimit), rotLimit);
	//��]�̉��Z
	xrot.Multiply(yrot);
	m_qrot.Multiply(xrot);

	//�}�E�X�J�[�\���̈ʒu���Œ�
	SetCursorPos(DefaultPoint[0], DefaultPoint[1]);
}