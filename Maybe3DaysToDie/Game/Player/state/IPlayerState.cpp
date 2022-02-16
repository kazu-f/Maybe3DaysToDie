#include "stdafx.h"
#include "IPlayerState.h"
#include "Player/Player.h"

namespace {
	const float MoveDistance = 500.0f;			//1フレームに動く距離
}

void IPlayerState::Move() {

	Vector3 Forward = MainCamera().GetForward();
	Forward.y = 0.0f;

	//Wキーが押されたら
	if (GetAsyncKeyState('W')) {
		if (m_Player->IsDubug()) {
			m_MoveSpeed += MainCamera().GetForward();
		}
		else {
			m_MoveSpeed += Forward;
		}
	}
	//Sキーが押されたら
	if (GetAsyncKeyState('S')) {
		if (m_Player->IsDubug()) {
			m_MoveSpeed -= MainCamera().GetForward();
		}
		else {
			m_MoveSpeed -= Forward;
		}
	}

	Vector3 RightMoveSpeed = MainCamera().GetRight();
	RightMoveSpeed.y = 0.0f;
	//Aキーが押されたら
	if (GetAsyncKeyState('A')) {
		if (m_Player->IsDubug()) {
			m_MoveSpeed -= MainCamera().GetRight();
		}
		else {
			m_MoveSpeed -= RightMoveSpeed;
		}
	}
	//Dキーが押されたら
	if (GetAsyncKeyState('D')) {
		if (m_Player->IsDubug()) {
			m_MoveSpeed += MainCamera().GetRight();
		}
		else {
			m_MoveSpeed += RightMoveSpeed;
		}
	}

}

void IPlayerState::ExcuteMove()
{
	if (m_Player->IsDebugMode()) {
	m_MoveSpeed *= MoveDistance * m_mulSpeed;
	}
	else {
		m_MoveSpeed.x *= MoveDistance * m_mulSpeed;
		m_MoveSpeed.y *= MoveDistance;
		m_MoveSpeed.z *= MoveDistance * m_mulSpeed;
	}
	m_Player->CharaMove(m_MoveSpeed);
	m_MoveSpeed = Vector3::Zero;
}

void IPlayerState::SwichDebugMode()
{
	static bool IsPush = false;
	if (GetAsyncKeyState('G')) {
		if (!IsPush) {
			m_Player->SetDebugMode(!m_Player->IsDebugMode());
		}
		IsPush = true;
	}
	else {
		IsPush = false;
	}
}
