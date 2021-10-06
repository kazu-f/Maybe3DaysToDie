#include "stdafx.h"
#include "PlayerWater.h"
#include "SpriteInitFunction.h"

namespace {
	const Vector2 GaugePos = { 0,-330.0f };
	const UINT GaugeSize[2] = { 300,15 };
	const Vector2 GaugePivot = { 0.0f,0.5f };

}

bool PlayerWater::Start()
{
	CurretSpriteInit();
	FlameSpriteInit();
	return true;
}

void PlayerWater::Update()
{
	m_WaterCountTime += GameTime().GetFrameDeltaTime();
	if (m_WaterCountTime > m_DecWaterTime) {
		m_Water--;
		m_WaterCountTime = 0.0f;
	}
	Vector3 WaterSize = Vector3::One;
	WaterSize.x = (float)m_Water / (float)m_MaxWater;
	m_CurrentWaterSprite->SetScale(WaterSize);
}

void PlayerWater::OnDestroy()
{
}

void PlayerWater::CurretSpriteInit()
{
	SpriteData sd;
	sd.sid.m_ddsFilePath[0] = "staminaGauge.dds";
	sd.sid.m_width = GaugeSize[0];
	sd.sid.m_height = GaugeSize[1];
	sd.pos = GaugePos;
	sd.pivot = GaugePivot;
	SpriteInit(sd);
}

void PlayerWater::FlameSpriteInit()
{
	SpriteData sd;
	sd.sid.m_ddsFilePath[0] = "statusGauge.dds";
	sd.sid.m_width = GaugeSize[0];
	sd.sid.m_height = GaugeSize[1];
	sd.pos = GaugePos;
	sd.pivot = GaugePivot;
	SpriteInit(sd);
}
