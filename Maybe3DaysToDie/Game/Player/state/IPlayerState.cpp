#include "stdafx.h"
#include "IPlayerState.h"
#include "Player/Player.h"

Vector3 IPlayerState::Move() {

	Vector3 Forward = MainCamera().GetForward();
	Forward.y = 0.0f;

	Vector3 MoveSpeed = Vector3::Zero;
	//W�L�[�������ꂽ��
	if (GetAsyncKeyState('W')) {
		if (m_Player->IsDubug()) {
			MoveSpeed += MainCamera().GetForward();
		}
		else {
			MoveSpeed += Forward;
		}
	}
	//S�L�[�������ꂽ��
	if (GetAsyncKeyState('S')) {
		if (m_Player->IsDubug()) {
			MoveSpeed -= MainCamera().GetForward();
		}
		else {
			MoveSpeed -= Forward;
		}
	}

	Vector3 RightMoveSpeed = MainCamera().GetRight();
	RightMoveSpeed.y = 0.0f;
	//A�L�[�������ꂽ��
	if (GetAsyncKeyState('A')) {
		if (m_Player->IsDubug()) {
			MoveSpeed -= MainCamera().GetRight();
		}
		else {
			MoveSpeed -= RightMoveSpeed;
		}
	}
	//D�L�[�������ꂽ��
	if (GetAsyncKeyState('D')) {
		if (m_Player->IsDubug()) {
			MoveSpeed += MainCamera().GetRight();
		}
		else {
			MoveSpeed += RightMoveSpeed;
		}
	}

	if (PlayerState == nullptr) {
		MoveSpeed *= MoveDistance * m_mulSpeed;
	}
	else {
		MoveSpeed *= MoveDistance * PlayerState->GetMulSpeed();
	}
	m_Pos = m_Characon.Execute(MoveSpeed);

	//m_Model->SetPosition(Vector3::Zero);
	return Vector3();
}
