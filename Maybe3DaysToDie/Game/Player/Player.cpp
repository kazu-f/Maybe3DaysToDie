#include "stdafx.h"
#include "Player.h"
#include "PlayerStatus/PlayerHp.h"
#include "PlayerStatus/PlayerStamina.h"
#include "PlayerStatus/PlayerHunger.h"
#include "PlayerStatus/PlayerWater.h"
#include "GameCamera.h"
#include "AccessObject/AccessObject.h"
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
	StateUpdate();

	switch (m_CurrentState)
	{
	case State::Menu:
		m_Camera->SetMovingMouse(true);
		break;
	case State::Dead:
	case State::Run:
		m_mulSpeed = 1.0f;
	case Debug:
		m_mulSpeed *= 2.0f;
	default:
		//�ړ�����
		Move();
		SwichDebugMode();
		m_Camera->SetMovingMouse(false);
		break;
	}

	if (GetAsyncKeyState('e')) {

	}
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

void Player::PeriodicUpdate()
{
	//�X�e�[�^�X�������Ԃ𐔂���
	m_DeltaTime += GameTime().GetFrameDeltaTime();
}

void Player::StateUpdate()
{
	ChangeState();
}

void Player::ChangeState()
{
	m_CurrentState = m_NextState;
}

void Player::Move()
{
	Vector3 Forward = MainCamera().GetForward();
	Forward.y = 0.0f;

	Vector3 MoveSpeed = Vector3::Zero;
	//W�L�[�������ꂽ��
	if (GetAsyncKeyState('W')) {
		if (m_IsDebugPlayer) {
			MoveSpeed += Forward;
		}
		else {
			MoveSpeed += MainCamera().GetForward();
		}
	}
	//S�L�[�������ꂽ��
	if (GetAsyncKeyState('S')) {
		if (m_IsDebugPlayer) {
			MoveSpeed -= Forward;
		}
		else {
			MoveSpeed -= MainCamera().GetForward();
		}
	}
	//A�L�[�������ꂽ��
	if (GetAsyncKeyState('A')) {
		MoveSpeed -= MainCamera().GetRight();
	}
	//D�L�[�������ꂽ��
	if (GetAsyncKeyState('D')) {
		MoveSpeed += MainCamera().GetRight();
	}
	
	//////�ړ����x//////////////////////////
	{
		m_mulSpeed = 0.5f;
		///�_�b�V���@�\////////////////////////
		if (GetAsyncKeyState(VK_LSHIFT) &&
			MoveSpeed.Length() > 0.5f &&
			m_Stamina->IsUseStamina(1))
		{
			m_NextState = State::Run;
		}
	}
	///////////////////////////////////////////////
	
	/////�d�͏���////////////////////////
	{
		static float gravity = 0.0f;
		gravity -= GameTime().GetFrameDeltaTime();
		if (!m_IsDebugPlayer) {
			gravity = 0.0f;
		}

		/////////�W�����v����/////////////////////////////////////////////
		{
			if (GetAsyncKeyState(VK_SPACE)) {
				//�_���_�̎��̓W�����v��������
				if (m_Characon.IsOnGround())
				{
					IsJump = true;
				}
				if (m_IsDebugPlayer) {
					IsJump = false;
					MoveSpeed.y += 1.0f;
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
			const float JumpPower = 0.5f;
			MoveSpeed.y = ((gravity)*pow(f, 2)) + JumpPower;
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
	////////////////////////////////////////


	MoveSpeed *= MoveDistance * m_mulSpeed;
	m_Pos = m_Characon.Execute(MoveSpeed);

	//m_Model->SetPosition(Vector3::Zero);
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
			static State BuckUpState=State::Idle;
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

bool Player::IsDubug()
{
	return false;
}

void Player::HitDamage(float damage) {
	float PlayerHp = m_Hp->GetHp() - damage;
	if (PlayerHp < 0) {
		m_NextState = State::Dead;
	}
	else {
		m_NextState = State::Damage;
	}
}

void Player::OpenInventory()
{
	if (State::Dead != m_CurrentState) {
		m_NextState = State::Menu;
	}
}

void Player::CloseInventory()
{
	m_NextState = State::Idle;
}