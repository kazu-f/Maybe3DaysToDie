#include "stdafx.h"
#include "GameCamera.h"
#include "Player/Player.h"

namespace {
	const float MoveDistance = 10.0f;			//1�t���[���ɓ�������
	const float CameraTargetDistance = 500.0f;	//�v���C���[����̃^�[�Q�b�g����
	const float NeckLimitY = 360.0f;				//��≺����������E
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
	//�����؂�ւ���H
	IsSwichOperation();

	//�}�E�X�Ō�����ς���
	Rotate();
	//�ǂ���̑���H
	Vector3 CameraPos = m_Player->GetPosition();
	CameraPos.y += 100.0f;
	m_Pos = CameraPos;
	Vector3 Forward = ForwardUpdate();
	m_Target = Forward * CameraTargetDistance;
	MainCamera().SetPosition(m_Pos);
	MainCamera().Update();
}

void GameCamera::OnDestroy()
{
}

void GameCamera::Rotate()
{
	////�}�E�X�J�[�\���̈ʒu���擾
	//POINT pt;
	//GetCursorPos(&pt);
	//int lst[] = { pt.x,pt.y };
	////�J�����̉�]�ʂ��}�E�X�J�[�\���̈ʒu�Ə����l���r���ċ��߂�
	//m_RotAngle[X] = (lst[X] - DefaultPoint[X]) * m_SensiX;
	////�J�����̃|�W�V�����ɑ���Y�����̒l���}�E�X�J�[�\���̈ʒu�Ə����l���r���ċ��߂�
	//m_RotAngle[Y] = (lst[Y] - DefaultPoint[Y]) * m_SensiY;
	////�}�E�X�J�[�\���̈ʒu���Z�b�g
	//SetCursorPos(DefaultPoint[X], DefaultPoint[Y]);

	////�J������X�����̉�]
	//Quaternion ModelRotX;
	//ModelRotX.SetRotationDegY(m_RotAngle[X]);
	//m_Rot.Multiply(ModelRotX);

	//Debug();
	//////�J������������㉺�̌��E
	////m_RotAngle[Y] = max(min(m_RotAngle[Y], NeckLimitY), -NeckLimitY);

	////���݂̉�]��ێ��B
	//Quaternion oldRot = m_Rot;

	////�E�����v�Z
	//Vector3 rightVec = RightUpdate();

	//Quaternion ModelRotY = Quaternion::Identity;
	////�J������Y�����̉�]
	//ModelRotY.SetRotationDeg(rightVec, m_RotAngle[Y]);
	////�J������X�����̉�]��Y�����̓������|����
	//m_Rot.Multiply(ModelRotY);

	////�O�����v�Z�B
	//Vector3 forwardVec = ForwardUpdate();
	////XZ���ʏ�̑O�������v�Z
	//Vector3 forwardXZVec = forwardVec;
	//forwardXZVec.y = 0.0f;
	//forwardXZVec.Normalize();

	////���ς����B
	//float dot = forwardXZVec.Dot(forwardVec);

	//�}�E�X�J�[�\���̈ʒu���擾
	POINT pt;
	GetCursorPos(&pt);
	float lstx = DefaultPoint[X]-pt.x;
	float lsty = DefaultPoint[Y]-pt.y;
	
	m_RotAngle[0] += lsty * m_SensiY;
	m_RotAngle[1] += lstx * m_SensiX;

	lstx = Math::DegToRad(lstx);
	Quaternion RotX;
	RotX.SetRotationY(-lstx);
	m_TargetRot.Multiply(RotX);
	Quaternion RotY = Quaternion::Identity;
	Vector3 Right = RightUpdate();
	lsty = Math::DegToRad(lsty);
	RotY.SetRotationDeg(Right, lsty);
	m_TargetRot.Multiply(RotY);
	Vector3 Target = { 0.0f,0.0,500.0 };
	Target += m_Pos;
	Target.Normalize();
	m_TargetRot.Apply(Target);
	Target *= CameraTargetDistance;
	MainCamera().SetTarget(Target);

	////�J�����̉�]�ʂ��}�E�X�J�[�\���̈ʒu�Ə����l���r���ċ��߂�
	//rot += (DefaultPoint[0] - lstx) * m_SensiX;
	////�ŏI�I�ȃJ�����̃^�[�Q�b�g�̃|�W�V����
	//Vector3 targetPos = m_Player->GetPosition();
	////�Œ���̍����̊m��
	//targetPos.y = 100.0f;

	////�J�����̃|�W�V�����ɑ���Y�����̒l���}�E�X�J�[�\���̈ʒu�Ə����l���r���ċ��߂�
	//AddPosY += (DefaultPoint[1] - lsty) * m_SensiY;

	//AddPosY = min(max(-NeckLimitY, AddPosY), NeckLimitY);
	////�J�����̃|�W�V�����ɑ����x�N�g��
	//Vector3 addPos = Vector3::Zero;
	////rot����J�����̃^�[�Q�b�g�̈ʒu�����߂�
	//addPos.x -= sinf(rot) * CameraTargetDistance;
	//addPos.y += AddPosY;
	//addPos.z = cosf(rot) * CameraTargetDistance;
	//targetPos += addPos;
	//�}�E�X�J�[�\���̈ʒu���Z�b�g
	SetCursorPos(DefaultPoint[0], DefaultPoint[1]);

	////�J�����ɃZ�b�g
	//g_camera3D->SetPosition(m_pos);
	//g_camera3D->SetTarget(targetPos);
	////�㉺�̉�]�𐧌��B
	//if (dot < 0.099f)
	//{
	//	m_Rot = oldRot;
	//}
	//O�{�^���������Ǝ��_�����Z�b�g����
	if (GetAsyncKeyState('O')) {
		m_Rot.SetRotationDegX(180.0f);
	}
}

void GameCamera::Move()
{
	//�ŏI�I�ȃJ�����̃|�W�V����
	Vector3 m_pos = m_Player->GetPosition();
	Vector3 MoveSpeed = Vector3::Zero;
	//�O�������擾
	Vector3 Forward = ForwardUpdate();
	//�E�������擾
	Vector3 Right = RightUpdate();
	//W�L�[�������ꂽ��
	if (GetAsyncKeyState('W')) {
		MoveSpeed += Forward;
	}
	//S�L�[�������ꂽ��
	if (GetAsyncKeyState('S')) {
		MoveSpeed -= Forward;
	}
	//A�L�[�������ꂽ��
	if (GetAsyncKeyState('A')) {
		MoveSpeed -= Right;
	}
	//D�L�[�������ꂽ��
	if (GetAsyncKeyState('D')) {
		MoveSpeed += Right;
	}
	//���K�����ĕ���������
	MoveSpeed.Normalize();
	//1�t���[���ɓ����������|����

	//�ړ�������
	m_pos += MoveSpeed * MoveDistance;
	MainCamera().SetPosition(m_pos);
}

void GameCamera::IsSwichOperation()
{
	if (GetAsyncKeyState('G')) {
		m_IsChasePlayer = !m_IsChasePlayer;
	}
}
