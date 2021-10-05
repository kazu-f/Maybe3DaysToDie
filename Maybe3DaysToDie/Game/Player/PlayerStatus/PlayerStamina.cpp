#include "stdafx.h"
#include "PlayerStamina.h"
#include "SpriteInitFunction.h"

namespace {
	///大体のスプライトの初期値////////////////////////////////////
	const Vector2 spPos = { -600.0f, -300.0f };	//スプライトの位置
	const UINT StaminaSize[2] = { 180,40 };		//スプライトのサイズ
	///////////////////////////////////////////////////////////////
	
	/////Frame専用の初期化定数/////////////////////////////////////
	const Vector2 IconPos = { -580.0f,-295.0f };	//アイコンの位置
	const UINT IConSize[2] = { 30,30 };			//アイコンのサイズ
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
	m_StaminaCurrentSprite->SetScale(StaminaScale);
}

void PlayerStamina::OnDestroy()
{
	//CurrentSpriteを削除
	DeleteGO(m_StaminaCurrentSprite);
	//FlameSpriteを削除
	DeleteGO(m_StaminaFlameSprite);
	//IConSpriteを削除
	DeleteGO(m_StaminaIConSprite);
}

void PlayerStamina::CurrentSpriteInit()
{
	//スプライトで使うデータを作成
	SpriteData sd;
	//CurrentSpriteのファイルパス
	sd.sid.m_ddsFilePath[0] = "staminaGauge.dds";
	//シェーダーのファイルパス
	sd.sid.m_fxFilePath = "Assets/shader/sprite.fx";
	//CurrentSpriteの位置を設定
	sd.pos = spPos;
	//CurrentSpriteのサイズを設定
	sd.sid.m_width = StaminaSize[0];
	sd.sid.m_height = StaminaSize[1];
	//CurrentSpriteの実行優先度を設定
	sd.prio = Current;
	//CurrentSpriteを初期化
	m_StaminaCurrentSprite = SpriteInit(sd);
}

void PlayerStamina::FlameSpriteInit()
{
	//スプライトで使うデータを作成
	SpriteData sd;
	//FlameSpriteのファイルパス
	sd.sid.m_ddsFilePath[0] = "statusGauge.dds";
	//シェーダーのファイルパス
	sd.sid.m_fxFilePath = "Assets/shader/sprite.fx";
	//FlameSpriteの位置を設定
	sd.pos = spPos;
	//FlameSpriteのサイズを設定
	sd.sid.m_width = StaminaSize[0];
	sd.sid.m_height = StaminaSize[1];
	//FlameSpriteの実行優先度を設定
	sd.prio = Flame;
	//FlameSpriteを初期化
	m_StaminaFlameSprite = SpriteInit(sd);
}

void PlayerStamina::IConSpriteInit()
{
	//スプライトで使うデータを作成
	SpriteData sd;
	//CurrentSpriteのファイルパス
	sd.sid.m_ddsFilePath[0] = "shoesIcon.dds";
	//シェーダーのファイルパス
	sd.sid.m_fxFilePath = "Assets/shader/sprite.fx";
	//IConSpriteの位置を設定
	sd.pos = IconPos;
	//IConSpriteのサイズを設定
	sd.sid.m_width = IConSize[0];
	sd.sid.m_height = IConSize[1];
	//IConSpriteの実行優先度を設定
	sd.prio = ICon;
	//IConSpriteを初期化
	m_StaminaIConSprite = SpriteInit(sd);
}