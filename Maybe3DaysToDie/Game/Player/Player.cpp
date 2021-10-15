#include "stdafx.h"
#include "Player.h"
#include "PlayerStatus/PlayerHp.h"
#include "PlayerStatus/PlayerStamina.h"
#include "PlayerStatus/PlayerHunger.h"
#include "PlayerStatus/PlayerWater.h"

namespace {
	const float MoveDistance = 10.0f;			//1�t���[���ɓ�������
	const float CameraTargetDistance = 500.0f;	//�v���C���[����̃^�[�Q�b�g����
	const float NeckLimitY = 80.0f;				//��≺����������E
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
	//�J�������X�V
	SetCamera();
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
	//�}�E�X�J�[�\���̈ʒu���擾
	POINT pt;
	GetCursorPos(&pt);
	int lst[] = { pt.x,pt.y };
	//�J�����̉�]�ʂ��}�E�X�J�[�\���̈ʒu�Ə����l���r���ċ��߂�
	m_RotAngle[X] = (lst[X] - DefaultPoint[X]) * m_SensiX;
	//�J�����̃|�W�V�����ɑ���Y�����̒l���}�E�X�J�[�\���̈ʒu�Ə����l���r���ċ��߂�
	m_RotAngle[Y] = (lst[Y] - DefaultPoint[Y] ) * m_SensiY;
	//�}�E�X�J�[�\���̈ʒu���Z�b�g
	SetCursorPos(DefaultPoint[X], DefaultPoint[Y]);

	//�J������X�����̉�]
	Quaternion ModelRotX;
	ModelRotX.SetRotationDegY(m_RotAngle[X]);
	m_Rot.Multiply(ModelRotX);

	//�J������������㉺�̌��E
	m_RotAngle[Y] = max(min(m_RotAngle[Y], NeckLimitY), -NeckLimitY);

	//���݂̉�]��ێ��B
	Quaternion oldRot = m_Rot;

	//�E�����v�Z
	Vector3 rightVec = RightUpdate();

	Quaternion ModelRotY = Quaternion::Identity;
	//�J������Y�����̉�]
	ModelRotY.SetRotationDeg(rightVec,m_RotAngle[Y]);
	//�J������X�����̉�]��Y�����̓������|����
	m_Rot.Multiply(ModelRotY);

	//�O�����v�Z�B
	Vector3 forwardVec = ForwardUpdate();
	//XZ���ʏ�̑O�������v�Z
	Vector3 forwardXZVec = forwardVec;
	forwardXZVec.y = 0.0f;
	forwardXZVec.Normalize();

	//���ς����B
	float dot = forwardXZVec.Dot(forwardVec);

	//�㉺�̉�]�𐧌��B
	if (dot < 0.1f)
	{
		m_Rot = oldRot;
	}
}

void Player::ModelUpdate()
{
	//��]
	Rotation();
	//�ړ�
	Move();
}