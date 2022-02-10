#include "stdafx.h"
#include "Player.h"
#include "PlayerStatus/PlayerHp.h"
#include "PlayerStatus/PlayerStamina.h"
#include "PlayerStatus/PlayerHunger.h"
#include "PlayerStatus/PlayerWater.h"
#include "GameCamera.h"
#include "AccessObject/AccessObject.h"
#include "Player/State/PlayerDead.h"
#include "Player/State/IPlayerState.h"

namespace {
	const float MoveDistance = 1000.0f;			//1�t���[���ɓ�������
	const float CameraTargetDistance = 500.0f;	//�v���C���[����̃^�[�Q�b�g����
	const float NeckLimitY = 10.0f;				//��≺����������E
}

bool Player::Start()
{
	//Hp�����
	m_Hp = NewGO<PlayerHp>(0, "playerHp");

	//�X�^�~�i�����
	m_Stamina = NewGO<PlayerStamina>(0, "playerStamina");

	//�󕠓x�����
	m_Hunger = NewGO<PlayerHunger>(0, "playerHunger");
	m_Hunger->SetPlayer(this);

	//���������
	m_Water = NewGO<PlayerWater>(0, "playerWater");
	m_Water->SetPlayer(this);

	ModelInitData PlayerModel;
	PlayerModel.m_tkmFilePath = "Assets/modelData/Player.tkm";

	AnimClipInitData AnInitData[State::Num];
	AnInitData[State::Idle].tkaFilePath = "Assets/animData/PlayerIdle.tka";
	AnInitData[State::Idle].isLoop = true;
	AnInitData[State::Walk].tkaFilePath = "Assets/animData/PlayerWalk.tka";
	AnInitData[State::Walk].isLoop = true;
	AnInitData[State::Attack].tkaFilePath = "Assets/animData/PlayerIdle.tka";
	AnInitData[State::Jump].tkaFilePath = "Assets/animData/PlayerIdle.tka";
	AnInitData[State::Run].tkaFilePath = "Assets/animData/PlayerIdle.tka";
	//m_Model = NewGO<prefab::ModelRender>(0);
	//m_Model->Init(PlayerModel, AnInitData,State::Num);
	//m_Model->SetPosition(m_Pos);
	//m_Model->SetRotation(m_Rot);
	//m_Model->SetScale(m_Scale);
	m_Characon.Init(50.0f, 90.0f, m_Pos);

	return true;
}

void Player::Update()
{
	//�X�e�[�g���X�V
	ChangeState();

	if (PlayerState != nullptr) {
		PlayerState->Update();

	}
	if (GetAsyncKeyState('e')) {
		m_AccessObject->Access();
	}
	if (GetAsyncKeyState('r')) {
		m_AccessObject->EndAccess();
	}

	Run();


	//���Ԍo�߂ɂ���
	PeriodicUpdate();
	//�J�����Ƀ|�W�V������n��
	m_Camera->SetPosition(m_Pos);
	//���f�������X�V
	ModelUpdate();

	m_LoadingByChunk->SetPlayerPos(m_Pos);
}

void Player::OnDestroy()
{
	//���f�����폜
	//DeleteGO(m_Model);
	//Hp���폜
	DeleteGO(m_Hp);
	//�X�^�~�i���폜
	DeleteGO(m_Stamina);
}

void Player::ReStart()
{
	m_Characon.SetPosition(m_RespownPoint);
	m_Hp->Reset();
	m_Stamina->Reset();
	m_Hunger->Reset();
	m_Water->Reset();
	PlayerState->Leave();
	PlayerState = nullptr;
	m_NextState = State::Idle;
	while (true) {
		int returnNo = ShowCursor(false);
		if (returnNo <= 0) {
			break;
		}
	}
}

void Player::PeriodicUpdate()
{
	//�X�e�[�^�X�������Ԃ𐔂���
	m_DeltaTime += GameTime().GetFrameDeltaTime();
}

void Player::ChangeState()
{
	if (m_CurrentState != m_NextState) {
		m_CurrentState = m_NextState;
	}
	switch (m_CurrentState)
	{
	case State::Menu:
		m_Camera->SetMovingMouse(true);
		break;
	case State::Dead:
		PlayerState = &m_Dead;
		PlayerState->Enter();
		m_Camera->SetMovingMouse(true);
		break;
	case State::Run:
		m_mulSpeed = 1.0f;
		//�ړ�����
		Move();
		SwichDebugMode();
		m_Camera->SetMovingMouse(false);
		break;
	case Debug:
		m_mulSpeed = 2.0f;
		//�ړ�����
		Move();
		SwichDebugMode();
		m_Camera->SetMovingMouse(false);
		break;
	default:
		//�ړ�����
		Move();
		SwichDebugMode();
		m_Camera->SetMovingMouse(false);
		break;
	}
}


void Player::Rotation()
{
}

void Player::ModelUpdate()
{
	//��]
	Rotation();
	//m_Model->PlayAnimation(State::Idle,GameTime().GetFrameDeltaTime());
}

void Player::SwichDebugMode()
{
	static bool IsPush = false;
	if (GetAsyncKeyState('G')) {
		if (!IsPush) {
			static State BuckUpState = State::Idle;
			if (m_CurrentState == State::Debug) {
				m_NextState = BuckUpState;
			}
			else {
				m_NextState = State::Debug;
				BuckUpState = m_CurrentState;
			}
		}
		IsPush = true;
	}
	else {
		IsPush = false;
	}
}

void Player::Run()
{
	{
		if (GetAsyncKeyState(VK_LSHIFT) &&
			PlayerState->GetMoveSpeed().Length() > 0.5f &&
			m_Stamina->IsUseStamina(1))
		{
			m_NextState = State::Run;
		}
	}
}

void Player::Jump()
{
	{
		static float gravity = 0.0f;
		gravity -= GameTime().GetFrameDeltaTime();
		if (IsDubug()) {
			gravity = 0.0f;
		}

		/////////�W�����v����/////////////////////////////////////////////
		{
			if (GetAsyncKeyState(VK_SPACE)) {
				//�n�ʂɐݒu���Ă���Ƃ�����
				//�W�����v����
				if (m_Characon.IsOnGround())
				{
					IsJump = true;
				}
				//�_���_�̎��̓W�����v��������
				if (IsDubug()) {
					IsJump = false;
					Vector3 MoveY = {
						PlayerState->GetMoveSpeed().x,
						PlayerState->GetMoveSpeed().y + 1.0f,
						PlayerState->GetMoveSpeed().z };
					PlayerState->SetMoveSpeed(MoveY);
				}
				//if (m_IsChasePlayer) {
				//	if (m_Characon.IsOnGround()) {
				//		MoveSpeed.y = 10.0f;
				//	}
				//}
				//else {
				//	MoveSpeed.y = 10.0f;
				//}
			}
		}
		if (IsJump)
		{
			NowTime += GameTime().GetFrameDeltaTime();
			const float JumpTime = 0.3f;
			float f = NowTime - JumpTime;
			const float JumpPower = 0.8f;
			MoveSpeed.y = ((gravity)*pow(f, 2.0f)) + JumpPower;
			if (IsJumping && m_Characon.IsOnGround())
			{
				//�W�����v���ɒn�ʂɂ����̂ŃW�����v�I��
				IsJump = false;
				IsJumping = false;
				NowTime = 0.0f;
				MoveSpeed.y = 0.0f;
			}
			else
			{
				IsJumping = true;
			}
		}

		/////////////////////
		if (m_Characon.IsOnGround()) {
			gravity = 0.0f;
		}
		MoveSpeed.y += gravity;
	}
}

const bool Player::IsDubug() const
{
	if (m_CurrentState == State::Debug) {
		return true;
	}
	return false;
}

void Player::HitDamage(float damage) {
	float PlayerHp = m_Hp->GetHp() - damage;
	if (PlayerHp <= 0) {
		m_NextState = State::Dead;
	}
	m_Hp->HitDamage(damage);
}

bool Player::OpenInventory()
{
	if (State::Dead != m_CurrentState) {
		m_NextState = State::Menu;
		return true;
	}
	return false;
}

void Player::CloseInventory()
{
	m_NextState = State::Idle;
}