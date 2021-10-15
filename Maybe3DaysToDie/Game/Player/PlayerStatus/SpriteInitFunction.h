#pragma once
/// <summary>
/// SpriteInitDataにポジションやスケールを含めたもの
/// </summary>
struct SpriteData {
	SpriteInitData sid;
	Vector2 pos = Vector2::Zero;
	Vector2 pivot = Vector2::Zero;
	int prio = 0;
};

/// <summary>
/// スプライトを初期化するときに使用する
/// SpriteDataで初期化する
/// </summary>
/// <param name="sd">初期化したいデータ</param>
/// <returns>スプライトレンダーのポインタ</returns>
static prefab::CSpriteRender* SpriteInit(SpriteData& sd)
{
	//Hpスプライトを初期化
	prefab::CSpriteRender* sp = NewGO<prefab::CSpriteRender>(sd.prio);
	char filePath[256] = "Assets/sprite/";
	strcat_s(filePath, sd.sid.m_ddsFilePath[0]);
	//シェーダーのファイルパス
	sd.sid.m_fxFilePath = "Assets/shader/sprite.fx";
	sd.sid.m_ddsFilePath[0] = filePath;
	sp->Init(sd.sid);
	sp->SetPosition(sd.pos);
	sp->SetPivot(sd.pivot);
	return sp;
}