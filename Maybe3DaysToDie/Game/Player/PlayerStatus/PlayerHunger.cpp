#include "stdafx.h"
#include "PlayerHunger.h"
#include "SpriteInitFunction.h"

namespace {
	////////ゲージ用定数//////////////////////////////// 
	const UINT GaugeSize[2] = { 300,15 };
	const Vector2 GaugePos = { -300.0,-330.0f };
	const Vector2 GaugePivot = { 0.0f,0.5f };
	///////////////////////////////////////////////////

	////////実行優先度////////////////////////////////
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
	//CurrentSpriteを初期化
	CurrentSpriteInit();
	//FlameSpriteを初期化
	FlameSpriteInit();
	return true;
}

void PlayerHunger::Update()
{
	m_HungeryCountTime += GameTime().GetFrameDeltaTime();
	//時間経過でお腹が空く
	if (m_HungeryCountTime > m_HungeryTime) {
		m_Hunder--;
		m_HungeryCountTime = 0.0f;
	}
	//スケール
	Vector3 SpriteScale = Vector3::One;
	//割合を計算
	SpriteScale.x = (float)m_Hunder / (float)m_MaxHunger;
	//スケールを設定
	m_CurrentSprite->SetScale(SpriteScale);
}

void PlayerHunger::OnDestroy()
{
	//CurrentSpriteを削除
	DeleteGO(m_CurrentSprite);
	//FlameSpriteを削除
	DeleteGO(m_FlameSprite);
}

void PlayerHunger::CurrentSpriteInit()
{
	//CurrentSprite用のデータ構造
	SpriteData sd;
	//ファイルパス
	sd.sid.m_ddsFilePath[0] = "HPGauge.dds";
	//サイズ
	sd.sid.m_width = GaugeSize[0];
	sd.sid.m_height = GaugeSize[1];
	//位置
	sd.pos = GaugePos;
	//基点
	sd.pivot = GaugePivot;
	//実行優先度
	sd.prio = Current;
	//CurrentSpriteを作成
	m_CurrentSprite = SpriteInit(sd);
}

void PlayerHunger::FlameSpriteInit()
{
	//FlameSprite用のデータ構造
	SpriteData sd;
	//ファイルパス
	sd.sid.m_ddsFilePath[0]="statusGauge.dds";
	//サイズ
	sd.sid.m_width = GaugeSize[0];
	sd.sid.m_height = GaugeSize[1];
	//位置
	sd.pos = GaugePos;
	//基点
	sd.pivot = GaugePivot;
	//実行優先度
	sd.prio = Flame;
	//FlameSpriteを作成
	m_FlameSprite = SpriteInit(sd);
}