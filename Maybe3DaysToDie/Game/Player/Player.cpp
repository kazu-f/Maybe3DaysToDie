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

	AnimClipInitData AnInitData[State::Num];
	AnInitData[State::Idle].tkaFilePath = "Assets/animData/PlayerIdle.tka";
	AnInitData[State::Idle].isLoop = true;
	AnInitData[State::Walk].tkaFilePath = "Assets/animData/PlayerWalk.tka";
	AnInitData[State::Walk].isLoop = true;
	AnInitData[State::Attack].tkaFilePath = "Assets/animData/PlayerIdle.tka";
	//m_Model = NewGO<prefab::ModelRender>(0);
	//m_Model->Init(PlayerModel, AnInitData,State::Num);
	//m_Model->SetPosition(m_Pos);
	//m_Model->SetRotation(m_Rot);
	//m_Model->SetScale(m_Scale);
	m_Characon.Init(radius, hight, m_Pos);
	m_Characon.GetBody()->GetBody()->setUserPointer(this);
	m_NextState = State::Idle;
	return true;
}

void Player::Update()
{
	//�X�e�[�g���X�V
	ChangeState();

	if (m_PlayerState != nullptr) {
		m_PlayerState->Update();
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
		start.setValue(PlayerPos.x, PlayerPos.y, PlayerPos.z);
		Vector3 RayEnd = PlayerPos;
		RayEnd += MainCamera().GetForward() * PlayerRange * OBJECT_UNIT;
		end.setValue(RayEnd.x, RayEnd.y, RayEnd.z);

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
	m_PlayerState->Leave();
	m_PlayerState = nullptr;
	m_NextState = State::Idle;
	while (true) {
		int returnNo = ShowCursor(false);
		if (returnNo <= 0) {
			break;
		}
	}
}

bool Player::UseStamina(int useCost)
{
	return m_Stamina->IsUseStamina(useCost);
}

void Player::SetMoveMause(bool isMove)
{
	m_Camera->SetMovingMouse(isMove);
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
		if (m_PlayerState != nullptr) {
			m_PlayerState->Leave();
		}
		switch (m_CurrentState)
		{
		case State::Idle:
			m_PlayerState = &m_Idle;
			m_PlayerState->Enter();
			break;
		case State::Menu:
			m_PlayerState = &m_Menu;
			m_PlayerState->Enter();
			break;
		case State::Dead:
			m_PlayerState = &m_Dead;
			m_PlayerState->Enter();
			break;
		case State::Walk:
			m_PlayerState = &m_Walk;
			m_PlayerState->Enter();
			break;
		default:
			break;
		}
	}

}

void Player::Jump()
{
	static float gravity = 0.0f;
	gravity -= GameTime().GetFrameDeltaTime();

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
			m_PlayerState->SetMoveSpeedY(m_PlayerState->GetMoveSpeed().y + 1.0f);
		}
	}
	if (IsJump)
	{
		NowTime += GameTime().GetFrameDeltaTime();
		const float JumpTime = 0.3f;
		float f = NowTime - JumpTime;
		const float JumpPower = 0.8f;
		float Jump = gravity * pow(f, 2.0f) + JumpPower;
		m_PlayerState->SetMoveSpeedY(Jump);
		if (IsJumping && m_Characon.IsOnGround())
		{
			//�W�����v���ɒn�ʂɂ����̂ŃW�����v�I��
			IsJump = false;
			IsJumping = false;
			NowTime = 0.0f;
			m_PlayerState->SetMoveSpeedY(0.0f);
		}
		else
		{
			IsJumping = true;
		}
	}
	if (m_Characon.IsOnGround()||
		m_IsDebugMode) {
		gravity = 0.0f;
	}
	m_PlayerState->SetMoveSpeedY(m_PlayerState->GetMoveSpeed().y + gravity);
	m_PlayerState->ExcuteMove();
}

const bool Player::IsDubug() const
{
	return m_IsDebugMode;
}

void Player::SetMulSpeed(const float mulSp)
{
	m_PlayerState->SetMulSpeed(mulSp);
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
	MauseInfo::GetInstance()->SetMauseCursor(MauseInfo::GetInstance()->IntialMausePos());
}