#include "stdafx.h"
#include "IPlayerState.h"
#include "Player/Player.h"

namespace {
	const float MoveDistance = 1000.0f;			//1フレームに動く距離
}

void IPlayerState::Move() {

	Vector3 Forward = MainCamera().GetForward();
	Forward.y = 0.0f;

	Vector3 MoveSpeed = Vector3::Zero;
	//Wキーが押されたら
	if (GetAsyncKeyState('W')) {
		if (m_Player->IsDubug()) {
			MoveSpeed += MainCamera().GetForward();
		}
		else {
			MoveSpeed += Forward;
		}
	}
	//Sキーが押されたら
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
	//Aキーが押されたら
	if (GetAsyncKeyState('A')) {
		if (m_Player->IsDubug()) {
			MoveSpeed -= MainCamera().GetRight();
		}
		else {
			MoveSpeed -= RightMoveSpeed;
		}
	}
	//Dキーが押されたら
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
