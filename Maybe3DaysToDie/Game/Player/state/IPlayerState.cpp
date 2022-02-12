#include "stdafx.h"
#include "IPlayerState.h"
#include "Player/Player.h"

namespace {
	const float MoveDistance = 1000.0f;			//1�t���[���ɓ�������
}

void IPlayerState::Move() {

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

	MoveSpeed *= MoveDistance * m_mulSpeed;
	if (MoveSpeed.Length() > 1.0f) {
		int a;
		a = 1;
	}
	m_Player->CharaMove(MoveSpeed);
}

void IPlayerState::SwichDebugMode()
{
	static bool IsPush = false;
	if (GetAsyncKeyState('G')) {
		if (!IsPush) {
			static Player::State BuckUpState = Player::State::Idle;
			if (m_Player->GetCurrentState() == Player::State::Debug) {
				m_Player->ChengeState(BuckUpState);
			}
			else {
				m_Player->ChengeState(Player::State::Debug);
				BuckUpState = m_Player->GetCurrentState();
			}
		}
		IsPush = true;
	}
	else {
		IsPush = false;
	}
}
