#include "stdafx.h"
#include "PlayerHunger.h"
#include "SpriteInitFunction.h"

namespace {
	////////�Q�[�W�p�萔//////////////////////////////// 
	const UINT GaugeSize[2] = { 300,15 };
	const Vector2 GaugePos = { -300.0,-330.0f };
	const Vector2 GaugePivot = { 0.0f,0.5f };
	///////////////////////////////////////////////////
	
	////////�A�C�R���p�萔////////////////////////////////
	const UINT IConSize[2] = { 10,10 };
	const Vector2 IConsPos = { -250.0,-330.0f };
	const Vector2 IConPivot = { 0.5f,0.5f };
	/////////////////////////////////////////////////////

	////////���s�D��x////////////////////////////////
	enum SpritePrio {
		Flame,
		Current,
		ICon,
		Num
	};
	////////////////////////////////////////////////////////
}

bool PlayerHunger::Start()
{
	//CurrentSprite��������
	CurrentSpriteInit();
	//FlameSprite��������
	FlameSpriteInit();
	//IConSprite��������
	IConSpriteInit();
	return true;
}

void PlayerHunger::Update()
{
	m_HungeryCountTime += GameTime().GetFrameDeltaTime();
	//���Ԍo�߂ł�������
	if (m_HungeryCountTime > m_HungeryTime) {
		m_Hunder--;
		m_HungeryCountTime = 0.0f;
	}
	//�X�P�[��
	Vector3 SpriteScale = Vector3::One;
	//�������v�Z
	SpriteScale.x = (float)m_Hunder / (float)m_MaxHunger;
	//�X�P�[����ݒ�
	m_CurrentSprite->SetScale(SpriteScale);
}

void PlayerHunger::OnDestroy()
{
	//CurrentSprite���폜
	DeleteGO(m_CurrentSprite);
	//FlameSprite���폜
	DeleteGO(m_FlameSprite);
	//IConSprite���폜
	DeleteGO(m_IConSprite);
}

void PlayerHunger::CurrentSpriteInit()
{
	//CurrentSprite�p�̃f�[�^�\��
	SpriteData sd;
	//�t�@�C���p�X
	sd.sid.m_ddsFilePath[0] = "HPGauge.dds";
	//�T�C�Y
	sd.sid.m_width = GaugeSize[0];
	sd.sid.m_height = GaugeSize[1];
	//�ʒu
	sd.pos = GaugePos;
	//��_
	sd.pivot = GaugePivot;
	//���s�D��x
	sd.prio = Current;
	//CurrentSprite���쐬
	m_CurrentSprite = SpriteInit(sd);
}

void PlayerHunger::FlameSpriteInit()
{
	//FlameSprite�p�̃f�[�^�\��
	SpriteData sd;
	//�t�@�C���p�X
	sd.sid.m_ddsFilePath[0]="statusGauge.dds";
	//�T�C�Y
	sd.sid.m_width = GaugeSize[0];
	sd.sid.m_height = GaugeSize[1];
	//�ʒu
	sd.pos = GaugePos;
	//��_
	sd.pivot = GaugePivot;
	//���s�D��x
	sd.prio = Flame;
	//FlameSprite���쐬
	m_FlameSprite = SpriteInit(sd);
}

void PlayerHunger::IConSpriteInit()
{
	//IConSprite�̏������\����
	SpriteData sd;
	//�t�@�C���p�X
	sd.sid.m_ddsFilePath[0] = "HungerICon.dds";
	//�T�C�Y
	sd.sid.m_width = IConSize[0];
	sd.sid.m_height = IConSize[1];
	//�ʒu
	sd.pos = IConsPos;
	//��_
	sd.pivot = IConPivot;
	//���s�D��x
	sd.prio = ICon;
	//IconSprite���쐬
	m_IConSprite = SpriteInit(sd);
}
