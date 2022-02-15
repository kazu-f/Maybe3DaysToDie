#include "stdafx.h"
#include "PlayerWater.h"
#include "SpriteInitFunction.h"

#include "Player/Player.h"

namespace {
	const Vector2 GaugePos = { -0.0f,-330.0f };		//スプライトの位置
	const UINT GaugeSize[2] = { 262,15 };		//スプライトのサイズ
	const Vector2 GaugePivot = { 0.0f,0.5f };	//スプライトの基点
}

bool PlayerWater::Start()
{
	//現在の水分スプライトを初期化
	CurretSpriteInit();
	//水分スプライトの枠を初期化
	FlameSpriteInit();
	return true;
}

void PlayerWater::Update()
{
	//時間をカウント
	m_WaterCountTime += GameTime().GetFrameDeltaTime();
	//一定時間が立つと喉が乾く
	if (m_WaterCountTime > m_DecWaterTime) {
		m_Water--;
		m_WaterCountTime = 0.0f;
		if (m_Water < 0) {
			m_Player->HitDamage(1.0f);
		}
	}
	//スプライトサイズの変数
	Vector3 WaterSize = Vector3::One;
	//割合を計算
	WaterSize.x = (float)m_Water / (float)m_MaxWater;
	//スプライトスケールを設定
	m_CurrentWaterSprite->SetScale(WaterSize);
}

void PlayerWater::OnDestroy()
{
	//現在の水分スプライトを削除
	DeleteGO(m_CurrentWaterSprite);
	//水分スプライトの枠を削除
	DeleteGO(m_FlameWaterSprite);
}

void PlayerWater::CurretSpriteInit()
{
	//スプライトの初期化構造体
	SpriteData sd;
	//ファイルパス
	sd.sid.m_ddsFilePath[0] = "staminaGauge.dds";
	//画像サイズ
	sd.sid.m_width = GaugeSize[0];
	sd.sid.m_height = GaugeSize[1];
	//位置
	sd.pos = GaugePos;
	//基点
	sd.pivot = GaugePivot;
	//スプライトを初期化する
	m_CurrentWaterSprite = SpriteInit(sd);
}

void PlayerWater::FlameSpriteInit()
{
	//スプライトの初期化構造体
	SpriteData sd;
	//ファイルパス
	sd.sid.m_ddsFilePath[0] = "statusGauge.dds";
	//画像サイズ
	sd.sid.m_width = GaugeSize[0];
	sd.sid.m_height = GaugeSize[1];
	//位置
	sd.pos = GaugePos;
	//基点
	sd.pivot = GaugePivot;
	//スプライトを初期化
	m_FlameWaterSprite = SpriteInit(sd);
}
