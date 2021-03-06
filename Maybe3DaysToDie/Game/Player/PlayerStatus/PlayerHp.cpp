#include "stdafx.h"
#include "PlayerHp.h"
#include "SpriteInitFunction.h"

namespace {
	/////ゲージスプライトの初期化データ///////////////////
	const Vector2 GaugePivot = Vector2::Zero;		//スプライトの基点
	const Vector2 GaugePos= { -600.0f, -250.0f };	//スプライトの位置
	const UINT GaugeSize[2] = { 180,40 };			//スプライトの縦横
	///////////////////////////////////////////////
	
	///ICon専用の初期化データ////////////////////// 
	const Vector2 IConPos = { -570.0f,-230.0f };	//アイコンの位置
	const Vector2 IConPivot = { 0.5f,0.5f };		//アイコンの基点
	const UINT IConSize[2] = { 40,40 };				//アイコンの縦横
	/////////////////////////////////////////////// 
	
	//スプライトの実行優先度
	enum SpruitePrio {
		FlamePrio,
		CurrentPrio,
		FontPrio,
		IConPrio,
		Num
	};

	///フォントの初期化データ//////////////////////
	const Vector2 FontPos = { -515.0f, -220.0f };
	const float FontScale = 0.4f;
	const Vector2 FontPivot = { 0.0f,0.5f };
	///////////////////////////////////////////////
}

bool PlayerHp::Start()
{
	//現在のHPスプライトを初期化
	InitCurrentSprite();

	//Hpフレームを初期化
	InitFrameSprite();

	//HpIConを初期化
	InitIConSprite();

	//HpFontを初期化
	InitHpFont();
	return true;
}

void PlayerHp::Update()
{
	if (m_IsRegene) {
		//時間を計測
		m_nowHpRegeneTime += GameTime().GetFrameDeltaTime();
		//自然回復するまで時間が立っているか
		if (m_nowHpRegeneTime >= m_RegeneTime) {
			//自然回復をする
			m_Hp++;
			m_Hp = min(m_MaxHp, m_Hp);
			m_nowHpRegeneTime = 0;
			max(m_Hp, 0.0f);
		}
	}
	//スプライトの大きさの変数
	Vector3 SpriteScale = Vector3::One;
	//Hpの割合を計算する
	SpriteScale.x = (float)m_Hp / (float)m_MaxHp;
	//大きさをスプライトに設定
	m_CurrentSprite->SetScale(SpriteScale);
	//フォントを更新
	UpdateHpFont();
}

void PlayerHp::OnDestroy()
{
	//スプライトを削除
	DeleteGO(m_CurrentSprite);
	DeleteGO(m_FlameSprite);
	DeleteGO(m_ICon);

	//フォントを削除
	DeleteGO(m_HpFont);
}

void PlayerHp::InitCurrentSprite()
{
	//スプライトで使うデータを作成
	SpriteData SpData;
	//スプライトのファイルパス
	SpData.sid.m_ddsFilePath[0] = "HpGauge.dds";
	//スプライトの縦横
	SpData.sid.m_height = GaugeSize[1];
	SpData.sid.m_width = GaugeSize[0];
	//SpDataにポジションを設定
	SpData.pos = GaugePos;
	//優先順位を設定
	SpData.prio = CurrentPrio;
	//m_HpSpriteを初期化
	m_CurrentSprite = SpriteInit(SpData);
}

void PlayerHp::InitFrameSprite()
{
	//スプライトで使うデータを作成
	SpriteData SpData;
	//ファイルパスをHpフレームに変更
	SpData.sid.m_ddsFilePath[0] = "statusGauge.dds";
	//スプライトの縦横
	SpData.sid.m_height = GaugeSize[1];
	SpData.sid.m_width = GaugeSize[0];
	//SpDataにポジションを設定
	SpData.pos = GaugePos;
	//優先順位を変更
	SpData.prio = FlamePrio;
	//Hpフレームを初期化
	m_FlameSprite = SpriteInit(SpData);
}

void PlayerHp::InitIConSprite()
{
	//スプライトで使うデータを作成
	SpriteData SpData;
	//ファイルパスをHpアイコンに変更
	SpData.sid.m_ddsFilePath[0] = "HPIcon.dds";
	//アイコンのサイズを設定
	SpData.sid.m_width = IConSize[0];
	SpData.sid.m_height = IConSize[1];
	//アイコンの位置を変更
	SpData.pos = IConPos;
	//アイコンの基点を変更
	SpData.pivot = Vector2::Zero;
	//優先順位を変更
	SpData.prio = IConPrio;
	//アイコンの基点を設定
	SpData.pivot = IConPivot;
	//m_HpIConを初期化
	m_ICon = SpriteInit(SpData);
}

void PlayerHp::InitHpFont()
{
	//フォントのインスタンスを作成
	m_HpFont = NewGO<CFontRender>(FontPrio);
	//Hpを表す文字列を作成
	wchar_t HpText[256] = {};
	//Hpをintからwchar_t型へ変換
	_itow_s(m_Hp, HpText, 10);
	//テキストに/を追加
	//これは現在のHpと最大HPの間にあるアレ
	wcscat_s(HpText, L"/");
	//最大Hp用の文字列を作成
	wchar_t MaxHpText[256] = {};
	//最大Hpをintからwchar_t型へ変換
	_itow_s(m_MaxHp, MaxHpText, 10);
	//HPテキストに追加
	wcscat_s(HpText, MaxHpText);
	//フォントに文字列を設定
	m_HpFont->SetText(HpText);
	//フォントの位置を設定
	m_HpFont->SetPosition(FontPos);
	m_HpFont->SetScale(FontScale);
	m_HpFont->SetPivot(FontPivot);
}

void PlayerHp::UpdateHpFont()
{
	//Hpを表す文字列を作成
	wchar_t HpText[256] = {};
	//Hpをintからwchar_t型へ変換
	_itow_s(m_Hp, HpText, 10);
	//テキストに/を追加
	//これは現在のHpと最大HPの間にあるアレ
	wcscat_s(HpText, L"/");
	//最大Hp用の文字列を作成
	wchar_t MaxHpText[256] = {};
	//最大Hpをintからwchar_t型へ変換
	_itow_s(m_MaxHp, MaxHpText, 10);
	//HPテキストに追加
	wcscat_s(HpText, MaxHpText);
	//フォントに文字列を設定
	m_HpFont->SetText(HpText);
}
