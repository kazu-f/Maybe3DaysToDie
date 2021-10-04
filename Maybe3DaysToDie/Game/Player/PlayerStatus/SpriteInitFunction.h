#pragma once
/// <summary>
/// スプライトの初期化を分かりやすくしたヘッダーファイル
/// </summary>

/// <summary>
/// SpriteInitDataにポジションやスケールを含めたもの
/// </summary>
struct SpriteData {
	SpriteInitData sid;
	Vector2 pos = Vector2::Zero;
	Vector2 pivot = Vector2::Zero;
	int prio = 0;
};

static prefab::CSpriteRender* SpriteInit(SpriteData& sd)
{
	//Hpスプライトを初期化
	auto sp = NewGO<prefab::CSpriteRender>(sd.prio);
	char filePath[256] = "Assets/sprite/";
	strcat_s(filePath, sd.sid.m_ddsFilePath[0]);
	sd.sid.m_ddsFilePath[0] = filePath;
	sp->Init(sd.sid);
	sp->SetPosition(sd.pos);
	sp->SetPivot(sd.pivot);
	return sp;
}