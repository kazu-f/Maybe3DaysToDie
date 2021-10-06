#include "stdafx.h"
#include "PlayerHp.h"
#include "SpriteInitFunction.h"

namespace {
	/////�Q�[�W�X�v���C�g�̏������f�[�^///////////////////
	const Vector2 GaugePivot = Vector2::Zero;		//�X�v���C�g�̊�_
	const Vector2 GaugePos= { -600.0f, -250.0f };	//�X�v���C�g�̈ʒu
	const UINT GaugeSize[2] = { 180,40 };			//�X�v���C�g�̏c��
	///////////////////////////////////////////////
	
	///ICon��p�̏������f�[�^////////////////////// 
	const Vector2 IConPos = { -585.0f,-250.0f };	//�A�C�R���̈ʒu
	const UINT IConSize[2] = { 40,40 };				//�A�C�R���̏c��
	/////////////////////////////////////////////// 
	
	//�X�v���C�g�̎��s�D��x
	enum SpruitePrio {
		FlamePrio,
		CurrentPrio,
		IConPrio,
		Num
	};
}

bool PlayerHp::Start()
{
	//���݂�HP�X�v���C�g��������
	InitCurrentSprite();

	//Hp�t���[����������
	InitFrameSprite();

	//HpICon��������
	InitIConSprite();
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
	m_CurrentSprite->SetScale(SpriteScale);
}

void PlayerHp::OnDestroy()
{
	//�X�v���C�g���폜
	DeleteGO(m_CurrentSprite);
	DeleteGO(m_FlameSprite);
	DeleteGO(m_ICon);
}

void PlayerHp::InitCurrentSprite()
{
	//�X�v���C�g�Ŏg���f�[�^���쐬
	SpriteData SpData;
	//�X�v���C�g�̃t�@�C���p�X
	SpData.sid.m_ddsFilePath[0] = "HpGauge.dds";
	//�V�F�[�_�[�̃t�@�C���p�X
	SpData.sid.m_fxFilePath = "Assets/shader/sprite.fx";
	//�X�v���C�g�̏c��
	SpData.sid.m_height = GaugeSize[1];
	SpData.sid.m_width = GaugeSize[0];
	//SpData�Ƀ|�W�V������ݒ�
	SpData.pos = GaugePos;
	//�D�揇�ʂ�ݒ�
	SpData.prio = CurrentPrio;
	//m_HpSprite��������
	m_CurrentSprite = SpriteInit(SpData);
}

void PlayerHp::InitFrameSprite()
{
	//�X�v���C�g�Ŏg���f�[�^���쐬
	SpriteData SpData;
	//�t�@�C���p�X��Hp�t���[���ɕύX
	SpData.sid.m_ddsFilePath[0] = "statusGauge.dds";
	//�V�F�[�_�[�̃t�@�C���p�X
	SpData.sid.m_fxFilePath = "Assets/shader/sprite.fx";
	//�X�v���C�g�̏c��
	SpData.sid.m_height = GaugeSize[1];
	SpData.sid.m_width = GaugeSize[0];
	//SpData�Ƀ|�W�V������ݒ�
	SpData.pos = GaugePos;
	//�D�揇�ʂ�ύX
	SpData.prio = FlamePrio;
	//Hp�t���[����������
	m_FlameSprite = SpriteInit(SpData);
}

void PlayerHp::InitIConSprite()
{
	//�X�v���C�g�Ŏg���f�[�^���쐬
	SpriteData SpData;
	//�t�@�C���p�X��Hp�A�C�R���ɕύX
	SpData.sid.m_ddsFilePath[0] = "HPIcon.dds";
	//�V�F�[�_�[�̃t�@�C���p�X
	SpData.sid.m_fxFilePath = "Assets/shader/sprite.fx";
	//�A�C�R���̃T�C�Y��ݒ�
	SpData.sid.m_width = IConSize[0];
	SpData.sid.m_height = IConSize[1];
	//�A�C�R���̈ʒu��ύX
	SpData.pos = IConPos;
	//�A�C�R���̊�_��ύX
	SpData.pivot = Vector2::Zero;
	//�D�揇�ʂ�ύX
	SpData.prio = IConPrio;
	//m_HpICon��������
	m_ICon = SpriteInit(SpData);
}
