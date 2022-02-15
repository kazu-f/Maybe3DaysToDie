#include "stdafx.h"
#include "PlayerWater.h"
#include "SpriteInitFunction.h"

#include "Player/Player.h"

namespace {
	const Vector2 GaugePos = { -0.0f,-330.0f };		//�X�v���C�g�̈ʒu
	const UINT GaugeSize[2] = { 262,15 };		//�X�v���C�g�̃T�C�Y
	const Vector2 GaugePivot = { 0.0f,0.5f };	//�X�v���C�g�̊�_
}

bool PlayerWater::Start()
{
	//���݂̐����X�v���C�g��������
	CurretSpriteInit();
	//�����X�v���C�g�̘g��������
	FlameSpriteInit();
	return true;
}

void PlayerWater::Update()
{
	//���Ԃ��J�E���g
	m_WaterCountTime += GameTime().GetFrameDeltaTime();
	//��莞�Ԃ����ƍA������
	if (m_WaterCountTime > m_DecWaterTime) {
		m_Water--;
		m_WaterCountTime = 0.0f;
		if (m_Water < 0) {
			m_Player->HitDamage(1.0f);
		}
	}
	//�X�v���C�g�T�C�Y�̕ϐ�
	Vector3 WaterSize = Vector3::One;
	//�������v�Z
	WaterSize.x = (float)m_Water / (float)m_MaxWater;
	//�X�v���C�g�X�P�[����ݒ�
	m_CurrentWaterSprite->SetScale(WaterSize);
}

void PlayerWater::OnDestroy()
{
	//���݂̐����X�v���C�g���폜
	DeleteGO(m_CurrentWaterSprite);
	//�����X�v���C�g�̘g���폜
	DeleteGO(m_FlameWaterSprite);
}

void PlayerWater::CurretSpriteInit()
{
	//�X�v���C�g�̏������\����
	SpriteData sd;
	//�t�@�C���p�X
	sd.sid.m_ddsFilePath[0] = "staminaGauge.dds";
	//�摜�T�C�Y
	sd.sid.m_width = GaugeSize[0];
	sd.sid.m_height = GaugeSize[1];
	//�ʒu
	sd.pos = GaugePos;
	//��_
	sd.pivot = GaugePivot;
	//�X�v���C�g������������
	m_CurrentWaterSprite = SpriteInit(sd);
}

void PlayerWater::FlameSpriteInit()
{
	//�X�v���C�g�̏������\����
	SpriteData sd;
	//�t�@�C���p�X
	sd.sid.m_ddsFilePath[0] = "statusGauge.dds";
	//�摜�T�C�Y
	sd.sid.m_width = GaugeSize[0];
	sd.sid.m_height = GaugeSize[1];
	//�ʒu
	sd.pos = GaugePos;
	//��_
	sd.pivot = GaugePivot;
	//�X�v���C�g��������
	m_FlameWaterSprite = SpriteInit(sd);
}
