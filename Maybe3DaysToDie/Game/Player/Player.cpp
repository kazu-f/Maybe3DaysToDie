#include "stdafx.h"
#include "Player.h"
#include "PlayerStatus/PlayerHp.h"
#include "PlayerStatus/PlayerStamina.h"
#include "PlayerStatus/PlayerHunger.h"
#include "PlayerStatus/PlayerWater.h"
#include "GameCamera.h"

namespace {
	const float MoveDistance = 100.0f;			//1�t���[���ɓ�������
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

	//���������
	m_Water = NewGO<PlayerWater>(0, "playerWater");

	m_Characon.Init(100.0f, 100.0f, m_Pos);
	return true;
}

void Player::Update()
{
	if (GetAsyncKeyState('G')) {
		m_IsChasePlayer = !m_IsChasePlayer;
	}
	//���Ԍo�߂ɂ���
	PeriodicUpdate();
	//�X�e�[�g���X�V
	StateUpdate();
	//���f�������X�V
	ModelUpdate();

	Vector3 Forward = MainCamera().GetForward();
	Forward.y = 0.0f;

	Vector3 MoveSpeed = Vector3::Zero;
	//W�L�[�������ꂽ��
	if (GetAsyncKeyState('W')) {
		if (m_IsChasePlayer) {
			MoveSpeed += Forward;
		}
		else {
			MoveSpeed += MainCamera().GetForward();
		}
	}
	//S�L�[�������ꂽ��
	if (GetAsyncKeyState('S')) {
		if (m_IsChasePlayer) {
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
	MoveSpeed.y -= 0.1f;
	MoveSpeed *= MoveDistance;
	m_Pos = m_Characon.Execute(MoveSpeed);

	//�J�����Ƀ|�W�V������n��
	cameraptr->SetPosition(m_Pos);
}

void Player::OnDestroy()
{
	//���f�����폜
	DeleteGO(m_Model);
	//Hp���폜
	DeleteGO(m_Hp);
	//�X�^�~�i���폜
	DeleteGO(m_Stamina);
}

void Player::PeriodicUpdate()
{
	//�X�^�~�i�����R��
	StaminaRegene();
	//�󕠒l������
	HungerDecrease();
	//����������
	WarterDecrease();
	//�X�e�[�^�X�������Ԃ𐔂���
	m_DeltaTime += GameTime().GetFrameDeltaTime();
}

void Player::StaminaRegene()
{
}

void Player::HungerDecrease()
{
}

void Player::WarterDecrease()
{
}

void Player::StateUpdate()
{
	ChangeState();
}

void Player::ChangeState()
{
}

void Player::Move()
{
}

void Player::Rotation()
{
}

void Player::ModelUpdate()
{
	//��]
	Rotation();
	//�ړ�
	Move();
}