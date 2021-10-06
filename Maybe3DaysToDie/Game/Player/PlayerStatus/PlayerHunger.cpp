#include "stdafx.h"
#include "PlayerHunger.h"
#include "SpriteInitFunction.h"

namespace {
	const UINT GaugeSize[2] = { 300,50 };
	const Vector2 GaugePos = { 0.0,-500.0f };
	const Vector2 GaugePivot = { 0.0f,0.5f };

	enum SpritePrio {
		Flame,
		Current,
		ICon,
		Num
	};
}
bool PlayerHunger::Start()
{
	CurrentSpriteInit();
	FrameSpriteInit();
	IConSpriteInit();
	return true;
}

void PlayerHunger::Update()
{
}

void PlayerHunger::OnDestroy()
{
}

void PlayerHunger::CurrentSpriteInit()
{
	SpriteData sd;
	sd.sid.m_ddsFilePath[0] = "HPGauge.dds";
	sd.sid.m_width = GaugeSize[0];
	sd.sid.m_height = GaugeSize[1];
	sd.pos = GaugePos;
	sd.pivot = GaugePivot;
	sd.prio = Current;
	m_CrrentSprite = SpriteInit(sd);
}

void PlayerHunger::FrameSpriteInit()
{
	SpriteData sd;
	sd.sid.m_ddsFilePath[0]="statusGauge.dds";
	sd.sid.m_width = GaugeSize[0];
	sd.sid.m_height = GaugeSize[1];
	sd.pos = GaugePos;
}

void PlayerHunger::IConSpriteInit()
{
}
