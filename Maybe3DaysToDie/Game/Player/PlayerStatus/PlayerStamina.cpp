#include "stdafx.h"
#include "PlayerStamina.h"
#include "SpriteInitFunction.h"

namespace {
	///��̂̃X�v���C�g�̏����l////////////////////////////////////
	const Vector2 spPos = { -600.0f, -300.0f };	//�X�v���C�g�̈ʒu
	const UINT StaminaSize[2] = { 180,40 };		//�X�v���C�g�̃T�C�Y
	///////////////////////////////////////////////////////////////
	
	/////Frame��p�̏������萔/////////////////////////////////////
	const Vector2 IconPos = { -580.0f,-295.0f };	//�A�C�R���̈ʒu
	const UINT IConSize[2] = { 30,30 };			//�A�C�R���̃T�C�Y
	///////////////////////////////////////////////////////////////
	
	//�X�v���C�g�̎��s�D��x
	enum SpritePrio {
		Flame,
		Current,
		ICon,
		Num
	};
}

bool PlayerStamina::Start()
{
	//CurrentSprite��������
	CurrentSpriteInit();

	//FlameSprite��������
	FlameSpriteInit();

	//IConSprite��������
	IConSpriteInit();
	return true;
}

void PlayerStamina::Update()
{
	m_nowRegeneTimer += GameTime().GetFrameDeltaTime();
	if (m_nowRegeneTimer >= m_RegeneTime) {
		m_Stamina--;
		m_nowRegeneTimer = 0.0f;
	}
	Vector3 StaminaScale = Vector3::One;
	StaminaScale.x = (float)m_Stamina / (float)m_MaxStamina;
	//CurrentSprite�̑傫����ݒ�
	m_StaminaCurrentSprite->SetScale(StaminaScale);
}

void PlayerStamina::OnDestroy()
{
	//CurrentSprite���폜
	DeleteGO(m_StaminaCurrentSprite);
	//FlameSprite���폜
	DeleteGO(m_StaminaFlameSprite);
	//IConSprite���폜
	DeleteGO(m_StaminaIConSprite);
}

void PlayerStamina::CurrentSpriteInit()
{
	//�X�v���C�g�Ŏg���f�[�^���쐬
	SpriteData sd;
	//CurrentSprite�̃t�@�C���p�X
	sd.sid.m_ddsFilePath[0] = "staminaGauge.dds";
	//�V�F�[�_�[�̃t�@�C���p�X
	sd.sid.m_fxFilePath = "Assets/shader/sprite.fx";
	//CurrentSprite�̈ʒu��ݒ�
	sd.pos = spPos;
	//CurrentSprite�̃T�C�Y��ݒ�
	sd.sid.m_width = StaminaSize[0];
	sd.sid.m_height = StaminaSize[1];
	//CurrentSprite�̎��s�D��x��ݒ�
	sd.prio = Current;
	//CurrentSprite��������
	m_StaminaCurrentSprite = SpriteInit(sd);
}

void PlayerStamina::FlameSpriteInit()
{
	//�X�v���C�g�Ŏg���f�[�^���쐬
	SpriteData sd;
	//FlameSprite�̃t�@�C���p�X
	sd.sid.m_ddsFilePath[0] = "statusGauge.dds";
	//�V�F�[�_�[�̃t�@�C���p�X
	sd.sid.m_fxFilePath = "Assets/shader/sprite.fx";
	//FlameSprite�̈ʒu��ݒ�
	sd.pos = spPos;
	//FlameSprite�̃T�C�Y��ݒ�
	sd.sid.m_width = StaminaSize[0];
	sd.sid.m_height = StaminaSize[1];
	//FlameSprite�̎��s�D��x��ݒ�
	sd.prio = Flame;
	//FlameSprite��������
	m_StaminaFlameSprite = SpriteInit(sd);
}

void PlayerStamina::IConSpriteInit()
{
	//�X�v���C�g�Ŏg���f�[�^���쐬
	SpriteData sd;
	//CurrentSprite�̃t�@�C���p�X
	sd.sid.m_ddsFilePath[0] = "shoesIcon.dds";
	//�V�F�[�_�[�̃t�@�C���p�X
	sd.sid.m_fxFilePath = "Assets/shader/sprite.fx";
	//IConSprite�̈ʒu��ݒ�
	sd.pos = IconPos;
	//IConSprite�̃T�C�Y��ݒ�
	sd.sid.m_width = IConSize[0];
	sd.sid.m_height = IConSize[1];
	//IConSprite�̎��s�D��x��ݒ�
	sd.prio = ICon;
	//IConSprite��������
	m_StaminaIConSprite = SpriteInit(sd);
}