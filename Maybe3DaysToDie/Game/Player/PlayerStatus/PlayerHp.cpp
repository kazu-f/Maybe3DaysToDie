#include "stdafx.h"
#include "PlayerHp.h"

namespace {
	/////HpCurrentの初期化データ///////////////////
	const Vector2 SpPivot = Vector2::Zero;		//スプライトの基点
	const Vector2 SpPos= { -600.0f, -250.0f };	//スプライトの位置
	const UINT SpSize[2] = { 180,40 };			//スプライトの縦横
	const int HpCurrentPrio = 1;				//実行優先度
	///////////////////////////////////////////////
	
	//Hpフレーム専用の初期化データ/////////////////
	const int HpFlarmPrio = 0;					//実行優先度
	///////////////////////////////////////////////

	///ICon専用の初期化データ////////////////
	const Vector2 IConPos = { -580.0f,-245.0f };	//アイコンの位置
	const Vector2 IConPivot = { 0.0f,0.0f };		//アイコンの基点
	const UINT IConSize[2] = { 30,30 };				//アイコンの縦横
	const int IConPrio = 2;							//実行優先度
	////////////////////////////////////////////
}

bool PlayerHp::Start()
{
	//スプライトで使うデータを設定
	SpriteData SpData;
	SpData.sid.m_ddsFilePath[0] = "HpGauge.dds";
	SpData.sid.m_fxFilePath = "Assets/shader/sprite.fx";
	//スプライトの縦横
	SpData.sid.m_height = SpSize[1];
	SpData.sid.m_width = SpSize[0];
	//SpDataにポジションを設定
	SpData.pos = SpPos;
	//優先順位を設定
	SpData.prio = HpCurrentPrio;
	//m_HpSpriteを初期化
	m_HpCurrentSprite = SpriteInit(SpData);

	//ファイルパスをHpフレームに変更
	SpData.sid.m_ddsFilePath[0] = "statusGauge.dds";
	//優先順位を変更
	SpData.prio = HpFlarmPrio;
	//Hpフレームを初期化
	m_HpFlameSprite = SpriteInit(SpData);
	
	//ファイルパスをHpアイコンに変更
	SpData.sid.m_ddsFilePath[0] = "HPIcon.dds";
	//アイコンのサイズを設定
	SpData.sid.m_width = IConSize[0];
	SpData.sid.m_height = IConSize[1];
	//アイコンの位置を変更
	SpData.pos = IConPos;
	//アイコンの基点を変更
	SpData.pivot = IConPivot;
	//優先順位を変更
	SpData.prio = IConPrio;
	//m_HpIConを初期化
	m_HpICon = SpriteInit(SpData);
	return true;
}

void PlayerHp::Update()
{
	//時間を計測
	m_nowHpRegeneTime += GameTime().GetFrameDeltaTime();
	//自然回復するまで時間が立っているか
	if (m_nowHpRegeneTime >= m_RegeneTime) {
		//自然回復をする
		m_Hp--;
		m_Hp = min(m_MaxHp, m_Hp);
		m_nowHpRegeneTime = 0;
	}
	//スプライトの大きさの変数
	Vector3 SpriteScale = Vector3::One;
	//Hpの割合を計算する
	SpriteScale.x = (float)m_Hp / (float)m_MaxHp;
	//大きさをスプライトに設定
	m_HpCurrentSprite->SetScale(SpriteScale);
}

void PlayerHp::OnDestroy()
{
	//スプライトを削除
	DeleteGO(m_HpCurrentSprite);
	DeleteGO(m_HpFlameSprite);
	DeleteGO(m_HpICon);
}