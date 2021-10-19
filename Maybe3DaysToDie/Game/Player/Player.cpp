#include "stdafx.h"
#include "Player.h"
#include "PlayerStatus/PlayerHp.h"
#include "PlayerStatus/PlayerStamina.h"
#include "PlayerStatus/PlayerHunger.h"
#include "PlayerStatus/PlayerWater.h"

namespace {
	const float MoveDistance = 10.0f;			//1�t���[���ɓ�������
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
	m_Water = NewGO<PlayerWater>(0,"playerWater");

	MainCamera().SetPosition(m_Pos);
	//Vector3 m_Target = { 0.0f,-200.0f,-500.0f };			//�^�[�Q�b�g
	//MainCamera().SetTarget(m_Target);
	//MainCamera().Update();
	return true;
}

void Player::Update()
{
	//���Ԍo�߂ɂ���
	PeriodicUpdate();
	//�X�e�[�g���X�V
	StateUpdate();
	//���f�������X�V
	ModelUpdate();
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