#include "stdafx.h"
#include "Player.h"
#include "GameCamera.h"

namespace {
	const float MoveDistance = 10.0f;			//1�t���[���ɓ�������
	const float CameraTargetDistance = 500.0f;	//�v���C���[����̃^�[�Q�b�g����
	const float NeckLimitY = 80.0f;				//��≺����������E
	//�z��p�̒萔
	//�Ȃ�ƂȂ��}�W�b�N�i���o�[�����������̂Œ萔��
	const int X = 0;
	const int Y = 1;
	const int Z = 2;
}

bool Player::Start()
{
	//�J������T��
	m_Camera = FindGO<GameCamera>("camera");
	return true;
}

void Player::Update()
{
	//���Ԍo�߂ɂ���
	PeriodicUpdate();
	//�X�e�[�g����
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
}

void Player::PeriodicUpdate()
{
	//HP�����R��
	HpRegene();
	//�X�^�~�i�����R��
	StaminaRegene();
	//�󕠒l������
	HungerDecrease();
	//����������
	WarterDecrease();
	//�X�e�[�^�X�������Ԃ𐔂���
	m_DeltaTime += GameTime().GetFrameDeltaTime();
	m_nowHpRegeneTimer += GameTime().GetFrameDeltaTime();
}

void Player::HpRegene()
{
	if (m_nowHpRegeneTimer >= m_HpRegeneTime)
	{
		m_nowHpRegeneTimer -= m_HpRegeneTime;
	}
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
	Vector3 MoveSpeed = Vector3::Zero;
	//�O�������擾
	Vector3 ForwardModel = ForwardUpdate();
	//�E�������擾
	Vector3 RightModel = RightUpdate();
	//W�L�[�������ꂽ��
	if (GetAsyncKeyState('W')) {
		MoveSpeed += ForwardModel;
	}
	//S�L�[�������ꂽ��
	if (GetAsyncKeyState('S')) {
		MoveSpeed -= ForwardModel;
	}
	//A�L�[�������ꂽ��
	if (GetAsyncKeyState('A')) {
		MoveSpeed -= RightModel;
	}
	//D�L�[�������ꂽ��
	if (GetAsyncKeyState('D')) {
		MoveSpeed += RightModel;
	}
	//���K�����ĕ���������
	MoveSpeed.Normalize();
	//1�t���[���ɓ����������|����
	MoveSpeed *= MoveDistance;
	//�ړ�������
	m_Pos += MoveSpeed;
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

Vector3 Player::ForwardUpdate()
{
	Matrix ModelMatrix = Matrix::Identity;
	ModelMatrix.MakeRotationFromQuaternion(m_Rot);
	//m[2]��Z��
	Vector3 ForwardModel = { ModelMatrix.m[Z][X],ModelMatrix.m[Z][Y],ModelMatrix.m[Z][Z] };
	//���K�����ĕ���������
	ForwardModel.Normalize();
	//�O������Ԃ�
	return ForwardModel;
}

Vector3 Player::RightUpdate()
{
	Matrix ModelMatrix = Matrix::Identity;
	ModelMatrix.MakeRotationFromQuaternion(m_Rot);
	//m[0]��X��
	Vector3 RightModel = { ModelMatrix.m[X][X],ModelMatrix.m[X][Y],ModelMatrix.m[X][Z] };
	//���K�����ĕ���������
	RightModel.Normalize();
	//�E������Ԃ�
	return RightModel;
}

void Player::SetCamera()
{
	//�J�����|�W�V������ݒ�
	m_Camera->SetPosition(m_Pos);
	//�J�����^�[�Q�b�g��ݒ�
	Vector3 CaneraTarget = Vector3::Zero;
	CaneraTarget = m_Pos;
	//�t�H���[�h�������擾
	Vector3 Forward = ForwardUpdate();
	//�J�����^�[�Q�b�g�͑O�����ƃJ�����^�[�Q�b�g�p�̋������|�����ʒu�ɂȂ�
	CaneraTarget += Forward* CameraTargetDistance;
	//�J�����^�[�Q�b�g��ݒ�
	m_Camera->SetTarget(CaneraTarget);
}
