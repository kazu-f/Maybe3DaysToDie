#include "stdafx.h"
#include "IPlayerState.h"
#include "Player/Player.h"

Vector3 IPlayerState::Move() {

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
