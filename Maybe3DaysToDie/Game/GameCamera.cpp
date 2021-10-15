#include "stdafx.h"
#include "GameCamera.h"
#include "Player/Player.h"

namespace {

	const float MoveDistance = 10.0f;			//1�t���[���ɓ�������
	const float CameraTargetDistance = 500.0f;	//�v���C���[����̃^�[�Q�b�g����
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
		//�O�������擾
		Vector3 ForwardModel = ForwardUpdate();
		//�E�������擾
		Vector3 RightModel = RightUpdate();
		//W�L�[�������ꂽ��
		if (GetAsyncKeyState('W')) {
			MoveSpeed += ForwardModel;
		}
		//S�L�[�������ꂽ��
		if (GetAsyncKeyState('S')) {
			MoveSpeed -= ForwardModel;
		}
		//A�L�[�������ꂽ��
		if (GetAsyncKeyState('A')) {
			MoveSpeed -= RightModel;
		}
		//D�L�[�������ꂽ��
		if (GetAsyncKeyState('D')) {
			MoveSpeed += RightModel;
		}
		//���K�����ĕ���������
		MoveSpeed.Normalize();
		//1�t���[���ɓ����������|����
		MoveSpeed *= MoveDistance;
		//�ړ�������
		m_Pos += MoveSpeed;
	}
	MainCamera().SetPosition(m_Pos);
	MainCamera().SetTarget(m_Target);
	MainCamera().Update();
}

void GameCamera::OnDestroy()
{
}
