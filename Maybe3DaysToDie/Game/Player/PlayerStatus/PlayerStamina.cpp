#include "stdafx.h"
#include "PlayerStamina.h"
#include "SpriteInitFunction.h"

namespace {
	///ゲージスプライトの初期値////////////////////////////////////
	const Vector2 GaugePos = { -570.0f, -300.0f };	//スプライトの位置
	const UINT GaugeSize[2] = { 180,40 };		//スプライトのサイズ
	///////////////////////////////////////////////////////////////
	
	/////Frame専用の初期化定数/////////////////////////////////////
	const Vector2 IconPos = { -570.0f,-280.0f };	//アイコンの位置
	const Vector2 IconPivot = { 0.5f,0.5f };		//アイコンの基点
	const UINT IConSize[2] = { 50,50 };				//アイコンのサイズ
	///////////////////////////////////////////////////////////////
	
	//スプライトの実行優先度
	enum SpritePrio {
		Flame,
		Current,
		ICon,
		Num
	};
}

bool PlayerStamina::Start()
{
	//CurrentSpriteを初期化
	CurrentSpriteInit();

	//FlameSpriteを初期化
	FlameSpriteInit();

	//IConSpriteを初期化
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
	//CurrentSpriteの大きさを設定
	m_CurrentSprite->SetScale(StaminaScale);
}

void PlayerStamina::OnDestroy()
{
	//CurrentSpriteを削除
	DeleteGO(m_CurrentSprite);
	//FlameSpriteを削除
	DeleteGO(m_FlameSprite);
	//IConSpriteを削除
	DeleteGO(m_IConSprite);
}

void PlayerStamina::CurrentSpriteInit()
{
	//スプライトで使うデータを作成
	SpriteData sd;
	//CurrentSpriteのファイルパス
	sd.sid.m_ddsFilePath[0] = "staminaGauge.dds";
	//CurrentSpriteの位置を設定
	sd.pos = GaugePos;
	//CurrentSpriteのサイズを設定
	sd.sid.m_width = GaugeSize[0];
	sd.sid.m_height = GaugeSize[1];
	//CurrentSpriteの実行優先度を設定
	sd.prio = Current;
	//CurrentSpriteを初期化
	m_CurrentSprite = SpriteInit(sd);
}

void PlayerStamina::FlameSpriteInit()
{
	//スプライトで使うデータを作成
	SpriteData sd;
	//FlameSpriteのファイルパス
	sd.sid.m_ddsFilePath[0] = "statusGauge.dds";
	//FlameSpriteの位置を設定
	sd.pos = GaugePos;
	//FlameSpriteのサイズを設定
	sd.sid.m_width = GaugeSize[0];
	sd.sid.m_height = GaugeSize[1];
	//FlameSpriteの実行優先度を設定
	sd.prio = Flame;
	//FlameSpriteを初期化
	m_FlameSprite = SpriteInit(sd);
}

void PlayerStamina::IConSpriteInit()
{
	//スプライトで使うデータを作成
	SpriteData sd;
	//CurrentSpriteのファイルパス
	sd.sid.m_ddsFilePath[0] = "shoesIcon.dds";
	//IConSpriteの位置を設定
	sd.pos = IconPos;
	//IConSpriteのサイズを設定
	sd.sid.m_width = IConSize[0];
	sd.sid.m_height = IConSize[1];
	//IConSpriteの実行優先度を設定
	sd.prio = ICon;
	//IConSpriteの基点を設定
	sd.pivot = IconPivot;
	//IConSpriteを初期化
	m_IConSprite = SpriteInit(sd);
}