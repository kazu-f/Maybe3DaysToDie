#include "stdafx.h"
#include "PlayerHp.h"

namespace {
	/////HpCurrent�̏������f�[�^///////////////////
	const Vector2 SpPivot = Vector2::Zero;		//�X�v���C�g�̊�_
	const Vector2 SpPos= { -600.0f, -250.0f };	//�X�v���C�g�̈ʒu
	const UINT SpSize[2] = { 180,40 };			//�X�v���C�g�̏c��
	const int HpCurrentPrio = 1;				//���s�D��x
	///////////////////////////////////////////////
	
	//Hp�t���[����p�̏������f�[�^/////////////////
	const int HpFlarmPrio = 0;					//���s�D��x
	///////////////////////////////////////////////

	///ICon��p�̏������f�[�^////////////////
	const Vector2 IConPos = { -580.0f,-245.0f };	//�A�C�R���̈ʒu
	const Vector2 IConPivot = { 0.0f,0.0f };		//�A�C�R���̊�_
	const UINT IConSize[2] = { 30,30 };				//�A�C�R���̏c��
	const int IConPrio = 2;							//���s�D��x
	////////////////////////////////////////////
}

bool PlayerHp::Start()
{
	//�X�v���C�g�Ŏg���f�[�^��ݒ�
	SpriteData SpData;
	SpData.sid.m_ddsFilePath[0] = "HpGauge.dds";
	SpData.sid.m_fxFilePath = "Assets/shader/sprite.fx";
	//�X�v���C�g�̏c��
	SpData.sid.m_height = SpSize[1];
	SpData.sid.m_width = SpSize[0];
	//SpData�Ƀ|�W�V������ݒ�
	SpData.pos = SpPos;
	//�D�揇�ʂ�ݒ�
	SpData.prio = HpCurrentPrio;
	//m_HpSprite��������
	m_HpCurrentSprite = SpriteInit(SpData);

	//�t�@�C���p�X��Hp�t���[���ɕύX
	SpData.sid.m_ddsFilePath[0] = "statusGauge.dds";
	//�D�揇�ʂ�ύX
	SpData.prio = HpFlarmPrio;
	//Hp�t���[����������
	m_HpFlameSprite = SpriteInit(SpData);
	
	//�t�@�C���p�X��Hp�A�C�R���ɕύX
	SpData.sid.m_ddsFilePath[0] = "HPIcon.dds";
	//�A�C�R���̃T�C�Y��ݒ�
	SpData.sid.m_width = IConSize[0];
	SpData.sid.m_height = IConSize[1];
	//�A�C�R���̈ʒu��ύX
	SpData.pos = IConPos;
	//�A�C�R���̊�_��ύX
	SpData.pivot = IConPivot;
	//�D�揇�ʂ�ύX
	SpData.prio = IConPrio;
	//m_HpICon��������
	m_HpICon = SpriteInit(SpData);
	return true;
}

void PlayerHp::Update()
{
	//���Ԃ��v��
	m_nowHpRegeneTime += GameTime().GetFrameDeltaTime();
	//���R�񕜂���܂Ŏ��Ԃ������Ă��邩
	if (m_nowHpRegeneTime >= m_RegeneTime) {
		//���R�񕜂�����
		m_Hp--;
		m_Hp = min(m_MaxHp, m_Hp);
		m_nowHpRegeneTime = 0;
	}
	//�X�v���C�g�̑傫���̕ϐ�
	Vector3 SpriteScale = Vector3::One;
	//Hp�̊������v�Z����
	SpriteScale.x = (float)m_Hp / (float)m_MaxHp;
	//�傫�����X�v���C�g�ɐݒ�
	m_HpCurrentSprite->SetScale(SpriteScale);
}

void PlayerHp::OnDestroy()
{
	//�X�v���C�g���폜
	DeleteGO(m_HpCurrentSprite);
	DeleteGO(m_HpFlameSprite);
	DeleteGO(m_HpICon);
}