#include "stdafx.h"
#include "PlayerStamina.h"
#include "SpriteInitFunction.h"

namespace {
	///ゲージスプライトの初期値////////////////////////////////////
	const Vector2 GaugePos = { -600.0f, -300.0f };	//スプライトの位置
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
		Font,
		ICon,
		Num
	};
	///フォントの初期化データ//////////////////////
	const Vector2 FontPos = { -515.0f, -270.0f };
	const float FontScale = 0.4f;
	const Vector2 FontPivot = { 0.0f,0.5f };
	///////////////////////////////////////////////
}

bool PlayerStamina::Start()
{
	//CurrentSpriteを初期化
	CurrentSpriteInit();

	//FlameSpriteを初期化
	FlameSpriteInit();

	//IConSpriteを初期化
	IConSpriteInit();

	//スタミナのフォントを初期化
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
	//CurrentSpriteの大きさを設定
	m_CurrentSprite->SetScale(StaminaScale);
	//スタミナのフォントを更新
	UpdateStaminaFont();
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

void PlayerStamina::InitStaminaFont()
{
	m_StaminaFont = NewGO<CFontRender>(Font);
	//Hpを表す文字列を作成
	wchar_t StaminaText[256] = {};
	//Hpをintからwchar_t型へ変換
	_itow_s(m_Stamina, StaminaText, 10);
	//テキストに/を追加
	//これは現在のHpと最大HPの間にあるアレ
	wcscat_s(StaminaText, L"/");
	//最大Hp用の文字列を作成
	wchar_t MaxHpText[256] = {};
	//最大Hpをintからwchar_t型へ変換
	_itow_s(m_MaxStamina, MaxHpText, 10);
	//HPテキストに追加
	wcscat_s(StaminaText, MaxHpText);
	//フォントに文字列を設定
	m_StaminaFont->SetText(StaminaText);
	//フォントの位置
	m_StaminaFont->SetPosition(FontPos);
	//フォントの基点
	m_StaminaFont->SetPivot(FontPivot);
	//フォントの大きさ
	m_StaminaFont->SetScale(FontScale);
}

void PlayerStamina::UpdateStaminaFont()
{
	//Hpを表す文字列を作成
	wchar_t StaminaText[256] = {};
	//Hpをintからwchar_t型へ変換
	_itow_s(m_Stamina, StaminaText, 10);
	//テキストに/を追加
	//これは現在のHpと最大HPの間にあるアレ
	wcscat_s(StaminaText, L"/");
	//最大Hp用の文字列を作成
	wchar_t MaxHpText[256] = {};
	//最大Hpをintからwchar_t型へ変換
	_itow_s(m_MaxStamina, MaxHpText, 10);
	//HPテキストに追加
	wcscat_s(StaminaText, MaxHpText);
	//フォントに文字列を設定
	m_StaminaFont->SetText(StaminaText);
}
