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
	const float radius = 50.0f;
	const float hight = 90.0f;
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

	AnimClipInitData AnInitData[IPlayerState::State::Num];
	AnInitData[IPlayerState::State::Idle].tkaFilePath = "Assets/animData/PlayerIdle.tka";
	AnInitData[IPlayerState::State::Idle].isLoop = true;
	AnInitData[IPlayerState::State::Walk].tkaFilePath = "Assets/animData/PlayerWalk.tka";
	AnInitData[IPlayerState::State::Walk].isLoop = true;
	AnInitData[IPlayerState::State::Attack].tkaFilePath = "Assets/animData/PlayerIdle.tka";
	AnInitData[IPlayerState::State::Run].tkaFilePath = "Assets/animData/PlayerIdle.tka";
	//m_Model = NewGO<prefab::ModelRender>(0);
	//m_Model->Init(PlayerModel, AnInitData,State::Num);
	//m_Model->SetPosition(m_Pos);
	//m_Model->SetRotation(m_Rot);
	//m_Model->SetScale(m_Scale);
	m_Characon.Init(radius, hight, m_Pos);
	m_Characon.GetBody()->GetBody()->setUserPointer(this);
	m_NextState = IPlayerState::State::Idle;
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
	if (GetAsyncKeyState(MK_RBUTTON)) {
		//���C�e�X�g�Ŏg�p����x�N�g�����쐬
		btVector3 start, end;
		Vector3 PlayerPos = m_Pos;
		PlayerPos.y = m_Pos.y + 90.0f;
		start.setValue(PlayerPos.x, PlayerPos.y + 90.0f, PlayerPos.z);
		float Range = 5000.0f;
		Vector3 RayEnd = PlayerPos;
		RayEnd += MainCamera().GetForward() * Range;
		end.setValue(RayEnd.x, RayEnd.y + 90.0f, RayEnd.z);

		//���C�e�X�g
		CharactorRayResult callback;
		callback.ExclusionPointer = this;
		PhysicsWorld().RayTest(start, end, callback);
		//���C���Փ˂��Ă���Ƃ�
		if (callback.isHit)
		{
			m_Enemy = ((IEnemy*)callback.ColObj->getUserPointer());
			//�I�u�W�F�N�g��ID����K�؂ȃA�N�V�������N����
			int Attck = 105;
			m_Enemy->HitDamage(Attck);
		}
	}
	//����H
	Dash();

	//�W�����v
	Jump();

	//���Ԍo�߂ɂ���
	PeriodicUpdate();
	//�J�����Ƀ|�W�V������n��
	m_Camera->SetPosition(m_Pos);

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
	m_NextState = IPlayerState::State::Idle;
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
		if (PlayerState != nullptr) {
			PlayerState->Leave();
		}
		switch (m_CurrentState)
		{
		case IPlayerState::State::Idle:
			PlayerState = &m_Idle;
			PlayerState->Enter();
			m_Camera->SetMovingMouse(false);
			break;
		case IPlayerState::State::Menu:
			m_Camera->SetMovingMouse(true);
			break;
		case IPlayerState::State::Dead:
			PlayerState = &m_Dead;
			PlayerState->Enter();
			m_Camera->SetMovingMouse(true);
			break;
		case IPlayerState::State::Run:
			PlayerState = &m_Walk;
			PlayerState->Leave();
			m_Camera->SetMovingMouse(false);
			break;
		case IPlayerState::State::Debug:
			m_mulSpeed = 2.0f;
			IPlayerState::SwichDebugMode();
			m_Camera->SetMovingMouse(false);
			break;
		default:
			m_Camera->SetMovingMouse(false);
			break;
		}
	}

}

void Player::Dash()
{
	{
		if (GetAsyncKeyState(VK_LSHIFT) &&
			PlayerState->GetMoveSpeed().Length() > 0.5f &&
			m_Stamina->IsUseStamina(1))
		{
			m_NextState = IPlayerState::State::Run;
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
	if (m_CurrentState == IPlayerState::State::Debug) {
		return true;
	}
	return false;
}

void Player::HitDamage(float damage) {
	float PlayerHp = m_Hp->GetHp() - damage;
	if (PlayerHp <= 0) {
		m_NextState = IPlayerState::State::Dead;
	}
	m_Hp->HitDamage(damage);
}

bool Player::OpenInventory()
{
	if (IPlayerState::State::Dead != m_CurrentState) {
		m_NextState = IPlayerState::State::Menu;
		return true;
	}
	return false;
}

void Player::CloseInventory()
{
	m_NextState = IPlayerState::State::Idle;
}