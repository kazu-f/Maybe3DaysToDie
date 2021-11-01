#include "stdafx.h"
#include "PlayerStamina.h"
#include "SpriteInitFunction.h"

namespace {
	///�Q�[�W�X�v���C�g�̏����l////////////////////////////////////
	const Vector2 GaugePos = { -600.0f, -300.0f };	//�X�v���C�g�̈ʒu
	const UINT GaugeSize[2] = { 180,40 };		//�X�v���C�g�̃T�C�Y
	///////////////////////////////////////////////////////////////
	
	/////Frame��p�̏������萔/////////////////////////////////////
	const Vector2 IconPos = { -570.0f,-280.0f };	//�A�C�R���̈ʒu
	const Vector2 IconPivot = { 0.5f,0.5f };		//�A�C�R���̊�_
	const UINT IConSize[2] = { 50,50 };				//�A�C�R���̃T�C�Y
	///////////////////////////////////////////////////////////////
	
	//�X�v���C�g�̎��s�D��x
	enum SpritePrio {
		Flame,
		Current,
		Font,
		ICon,
		Num
	};
	///�t�H���g�̏������f�[�^//////////////////////
	const Vector2 FontPos = { -515.0f, -270.0f };
	const float FontScale = 0.4f;
	const Vector2 FontPivot = { 0.0f,0.5f };
	///////////////////////////////////////////////
}

bool PlayerStamina::Start()
{
	//CurrentSprite��������
	CurrentSpriteInit();

	//FlameSprite��������
	FlameSpriteInit();

	//IConSprite��������
	IConSpriteInit();

	//�X�^�~�i�̃t�H���g��������
	InitStaminaFont();
	return true;
}

void PlayerStamina::Update()
{
	m_nowRegeneTimer += GameTime().GetFrameDeltaTime();
	if (m_nowRegeneTimer>1.0f) {
		m_nowRegeneTimer = 0.0f;
		m_Stamina++;
		m_Stamina = min(m_Stamina, m_MaxStamina);
	}
	Vector3 StaminaScale = Vector3::One;
	StaminaScale.x = (float)m_Stamina / (float)m_MaxStamina;
	//CurrentSprite�̑傫����ݒ�
	m_CurrentSprite->SetScale(StaminaScale);
	//�X�^�~�i�̃t�H���g���X�V
	UpdateStaminaFont();
}

void PlayerStamina::OnDestroy()
{
	//CurrentSprite���폜
	DeleteGO(m_CurrentSprite);
	//FlameSprite���폜
	DeleteGO(m_FlameSprite);
	//IConSprite���폜
	DeleteGO(m_IConSprite);
}

void PlayerStamina::CurrentSpriteInit()
{
	//�X�v���C�g�Ŏg���f�[�^���쐬
	SpriteData sd;
	//CurrentSprite�̃t�@�C���p�X
	sd.sid.m_ddsFilePath[0] = "staminaGauge.dds";
	//CurrentSprite�̈ʒu��ݒ�
	sd.pos = GaugePos;
	//CurrentSprite�̃T�C�Y��ݒ�
	sd.sid.m_width = GaugeSize[0];
	sd.sid.m_height = GaugeSize[1];
	//CurrentSprite�̎��s�D��x��ݒ�
	sd.prio = Current;
	//CurrentSprite��������
	m_CurrentSprite = SpriteInit(sd);
}

void PlayerStamina::FlameSpriteInit()
{
	//�X�v���C�g�Ŏg���f�[�^���쐬
	SpriteData sd;
	//FlameSprite�̃t�@�C���p�X
	sd.sid.m_ddsFilePath[0] = "statusGauge.dds";
	//FlameSprite�̈ʒu��ݒ�
	sd.pos = GaugePos;
	//FlameSprite�̃T�C�Y��ݒ�
	sd.sid.m_width = GaugeSize[0];
	sd.sid.m_height = GaugeSize[1];
	//FlameSprite�̎��s�D��x��ݒ�
	sd.prio = Flame;
	//FlameSprite��������
	m_FlameSprite = SpriteInit(sd);
}

void PlayerStamina::IConSpriteInit()
{
	//�X�v���C�g�Ŏg���f�[�^���쐬
	SpriteData sd;
	//CurrentSprite�̃t�@�C���p�X
	sd.sid.m_ddsFilePath[0] = "shoesIcon.dds";
	//IConSprite�̈ʒu��ݒ�
	sd.pos = IconPos;
	//IConSprite�̃T�C�Y��ݒ�
	sd.sid.m_width = IConSize[0];
	sd.sid.m_height = IConSize[1];
	//IConSprite�̎��s�D��x��ݒ�
	sd.prio = ICon;
	//IConSprite�̊�_��ݒ�
	sd.pivot = IconPivot;
	//IConSprite��������
	m_IConSprite = SpriteInit(sd);
}

void PlayerStamina::InitStaminaFont()
{
	m_StaminaFont = NewGO<CFontRender>(Font);
	//Hp��\����������쐬
	wchar_t StaminaText[256] = {};
	//Hp��int����wchar_t�^�֕ϊ�
	_itow_s(m_Stamina, StaminaText, 10);
	//�e�L�X�g��/��ǉ�
	//����͌��݂�Hp�ƍő�HP�̊Ԃɂ���A��
	wcscat_s(StaminaText, L"/");
	//�ő�Hp�p�̕�������쐬
	wchar_t MaxHpText[256] = {};
	//�ő�Hp��int����wchar_t�^�֕ϊ�
	_itow_s(m_MaxStamina, MaxHpText, 10);
	//HP�e�L�X�g�ɒǉ�
	wcscat_s(StaminaText, MaxHpText);
	//�t�H���g�ɕ������ݒ�
	m_StaminaFont->SetText(StaminaText);
	//�t�H���g�̈ʒu
	m_StaminaFont->SetPosition(FontPos);
	//�t�H���g�̊�_
	m_StaminaFont->SetPivot(FontPivot);
	//�t�H���g�̑傫��
	m_StaminaFont->SetScale(FontScale);
}

void PlayerStamina::UpdateStaminaFont()
{
	//Hp��\����������쐬
	wchar_t StaminaText[256] = {};
	//Hp��int����wchar_t�^�֕ϊ�
	_itow_s(m_Stamina, StaminaText, 10);
	//�e�L�X�g��/��ǉ�
	//����͌��݂�Hp�ƍő�HP�̊Ԃɂ���A��
	wcscat_s(StaminaText, L"/");
	//�ő�Hp�p�̕�������쐬
	wchar_t MaxHpText[256] = {};
	//�ő�Hp��int����wchar_t�^�֕ϊ�
	_itow_s(m_MaxStamina, MaxHpText, 10);
	//HP�e�L�X�g�ɒǉ�
	wcscat_s(StaminaText, MaxHpText);
	//�t�H���g�ɕ������ݒ�
	m_StaminaFont->SetText(StaminaText);
}
