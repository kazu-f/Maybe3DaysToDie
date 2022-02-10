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
#include "RayTest.h"
#include "Enemy/IEnemy.h"

namespace {
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
	//���C�e�X�g�Ŏg�p����x�N�g�����쐬
	btVector3 start, end;
	Vector3 PlayerPos = m_Pos;
	PlayerPos.y += 90.0f;
	start.setValue(PlayerPos.x, PlayerPos.y + 90.0f, PlayerPos.z);
	float Range = 50.0f;
	Vector3 RayEnd = PlayerPos;
	RayEnd += MainCamera().GetForward()* Range;
	end.setValue(RayEnd.x, RayEnd.y + 90.0f, RayEnd.z);

	//���C�e�X�g
	CharactorRayResult callback;
	PhysicsWorld().RayTest(start, end, callback);
	//���C���Փ˂��Ă���Ƃ�
	if (callback.isHit)
	{
		m_Enemy = ((IEnemy*)callback.ColObj->getUserPointer());
		//�I�u�W�F�N�g��ID����K�؂ȃA�N�V�������N����
		auto& param = m_Enemy->();
	}
	//����H
	Dash();

	//�W�����v
	Jump();

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
		SwichDebugMode();
		m_Camera->SetMovingMouse(false);
		break;
	case Debug:
		m_mulSpeed = 2.0f;
		SwichDebugMode();
		m_Camera->SetMovingMouse(false);
		break;
	default:
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

void Player::Dash()
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
				PlayerState->SetMoveSpeedY(PlayerState->GetMoveSpeed().y + 1.0f);
			}
		}
	}
	if (IsJump)
	{
		NowTime += GameTime().GetFrameDeltaTime();
		const float JumpTime = 0.3f;
		float f = NowTime - JumpTime;
		const float JumpPower = 0.8f;
		PlayerState->SetMoveSpeedY(gravity * pow(f, 2.0f) + JumpPower);
		if (IsJumping && m_Characon.IsOnGround())
		{
			//�W�����v���ɒn�ʂɂ����̂ŃW�����v�I��
			IsJump = false;
			IsJumping = false;
			NowTime = 0.0f;
			PlayerState->SetMoveSpeedY(0.0f);
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
	PlayerState->SetMoveSpeedY(PlayerState->GetMoveSpeed().y + gravity);
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