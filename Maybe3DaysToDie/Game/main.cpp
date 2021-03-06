#include "stdafx.h"
#include "GameScene.h"
#include "Scene\TerrainDebugScene.h"
#include "Item/ItemDataFile.h"

//1フレームの経過時間を出力する。
#define CALC_TIME
void SetInitParam(SInitParam& initParam)
{
	initParam.frameBuffer_W = FRAME_BUFFER_W;	//フレームバッファのサイズ(幅)
	initParam.frameBuffer_H = FRAME_BUFFER_H;	//フレームバッファのサイズ(高さ)
	initParam.gameObjectPrioMax = 20;			//ゲームオブジェクトの優先度の最大数。

	initParam.graphicsConf.shadowConf.isEnable = true;		//シャドウマップの有効化フラグ。
	initParam.graphicsConf.shadowConf.shadowMapWidth = 4096;
	initParam.graphicsConf.shadowConf.shadowMapWidth = 4096;
	initParam.graphicsConf.shadowConf.shadowAreas[0] = 2000.0f;		//シャドウマップの有効範囲(近景)
	initParam.graphicsConf.shadowConf.shadowAreas[1] = 4000.0f;		//シャドウマップの有効範囲(中景)
	initParam.graphicsConf.shadowConf.shadowAreas[2] = 20000.0f;	//シャドウマップの有効範囲(遠景)
	//initParam.graphicsConf.shadowConf.depthOffset[0] = 0.01f;
	//initParam.graphicsConf.shadowConf.depthOffset[1] = 0.02f;
	//initParam.graphicsConf.shadowConf.depthOffset[2] = 0.02f;
	initParam.graphicsConf.shadowConf.lightHeight = 5000.0f;
	initParam.graphicsConf.postEffectConf.tonemap.isEnable = false;		//トーンマップ有効化フラグ。
	initParam.graphicsConf.postEffectConf.tonemap.luminance = 0.24f;	//明るさ。
	initParam.graphicsConf.postEffectConf.isBloom = true;	//ブルームの有効化フラグ。
	initParam.graphicsConf.postEffectConf.isFxaa = true;	//アンチエイリアス有効化フラグ。
}

///////////////////////////////////////////////////////////////////
// ウィンドウプログラムのメイン関数。
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	SInitParam initParam;
	SetInitParam(initParam);

	//ゲームの初期化。
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, TEXT("Game"), initParam);
	//デバッグモードオン
	//PhysicsWorld().SetDebugMode(1);
	//フェードイン
	CFade::GetInstance()->StartFadeIn();
	//マウスカーソルの表示を消す
	ShowCursor(false);

	//アイテムデータファイルのインスタンスを作成
	ItemDataFile::CreateInstance();
	NewGO<CGameScene>(0);
	//NewGO<TerrainDebugScene>(0);
#ifdef CALC_TIME
	Stopwatch sw;
#endif
	// ここからゲームループ。
	while (DispatchWindowMessage())
	{
#ifdef CALC_TIME
		//1フレームの経過時間を測る。
		sw.Start();
#endif
		GameEngine().GameUpdate();

#ifdef CALC_TIME
		sw.Stop();
#endif
		
#ifdef CALC_TIME
		char text[256];
		sprintf_s(text, "1フレームの経過時間::%dミリ秒\n", static_cast<int>(sw.GetElapsedMillisecond()));
		OutputDebugString(text);
#endif

	}
	return 0;
}


