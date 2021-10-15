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
	const Vector2 IConPos = { -570.0f,-230.0f };	//�A�C�R���̈ʒu
	const Vector2 IConPivot = { 0.5f,0.5f };		//�A�C�R���̊�_
	const UINT IConSize[2] = { 40,40 };				//�A�C�R���̏c��
	/////////////////////////////////////////////// 
	
	//�X�v���C�g�̎��s�D��x
	enum SpruitePrio {
		FlamePrio,
		CurrentPrio,
		FontPrio,
		IConPrio,
		Num
	};

	///�t�H���g�̏������f�[�^//////////////////////
	const Vector2 FontPos = { -515.0f, -220.0f };
	const float FontScale = 0.4f;
	const Vector2 FontPivot = { 0.0f,0.5f };
	///////////////////////////////////////////////
}

bool PlayerHp::Start()
{
	//���݂�HP�X�v���C�g��������
	InitCurrentSprite();

	//Hp�t���[����������
	InitFrameSprite();

	//HpICon��������
	InitIConSprite();

	//HpFont��������
	InitHpFont();
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
	//�t�H���g���X�V
	UpdateHpFont();
}

void PlayerHp::OnDestroy()
{
	//�X�v���C�g���폜
	DeleteGO(m_CurrentSprite);
	DeleteGO(m_FlameSprite);
	DeleteGO(m_ICon);

	//�t�H���g���폜
	DeleteGO(m_HpFont);
}

void PlayerHp::InitCurrentSprite()
{
	//�X�v���C�g�Ŏg���f�[�^���쐬
	SpriteData SpData;
	//�X�v���C�g�̃t�@�C���p�X
	SpData.sid.m_ddsFilePath[0] = "HpGauge.dds";
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
	//�A�C�R���̃T�C�Y��ݒ�
	SpData.sid.m_width = IConSize[0];
	SpData.sid.m_height = IConSize[1];
	//�A�C�R���̈ʒu��ύX
	SpData.pos = IConPos;
	//�A�C�R���̊�_��ύX
	SpData.pivot = Vector2::Zero;
	//�D�揇�ʂ�ύX
	SpData.prio = IConPrio;
	//�A�C�R���̊�_��ݒ�
	SpData.pivot = IConPivot;
	//m_HpICon��������
	m_ICon = SpriteInit(SpData);
}

void PlayerHp::InitHpFont()
{
	//�t�H���g�̃C���X�^���X���쐬
	m_HpFont = NewGO<CFontRender>(FontPrio);
	//Hp��\����������쐬
	wchar_t HpText[256] = {};
	//Hp��int����wchar_t�^�֕ϊ�
	_itow_s(m_Hp, HpText, 10);
	//�e�L�X�g��/��ǉ�
	//����͌��݂�Hp�ƍő�HP�̊Ԃɂ���A��
	wcscat_s(HpText, L"/");
	//�ő�Hp�p�̕�������쐬
	wchar_t MaxHpText[256] = {};
	//�ő�Hp��int����wchar_t�^�֕ϊ�
	_itow_s(m_MaxHp, MaxHpText, 10);
	//HP�e�L�X�g�ɒǉ�
	wcscat_s(HpText, MaxHpText);
	//�t�H���g�ɕ������ݒ�
	m_HpFont->SetText(HpText);
	//�t�H���g�̈ʒu��ݒ�
	m_HpFont->SetPosition(FontPos);
	m_HpFont->SetScale(FontScale);
	m_HpFont->SetPivot(FontPivot);
}

void PlayerHp::UpdateHpFont()
{
	//Hp��\����������쐬
	wchar_t HpText[256] = {};
	//Hp��int����wchar_t�^�֕ϊ�
	_itow_s(m_Hp, HpText, 10);
	//�e�L�X�g��/��ǉ�
	//����͌��݂�Hp�ƍő�HP�̊Ԃɂ���A��
	wcscat_s(HpText, L"/");
	//�ő�Hp�p�̕�������쐬
	wchar_t MaxHpText[256] = {};
	//�ő�Hp��int����wchar_t�^�֕ϊ�
	_itow_s(m_MaxHp, MaxHpText, 10);
	//HP�e�L�X�g�ɒǉ�
	wcscat_s(HpText, MaxHpText);
	//�t�H���g�ɕ������ݒ�
	m_HpFont->SetText(HpText);
}
