#include "MiniEngine.h"
#include "system.h"
#include "graphics/GraphicsEngine.h"
#include "Mause/MauseInfo.h"
namespace Engine {
	HWND			g_hWnd = NULL;				//ウィンドウハンドル。

	///////////////////////////////////////////////////////////////////
	//メッセージプロシージャ。
	//hWndがメッセージを送ってきたウィンドウのハンドル。
	//msgがメッセージの種類。
	//wParamとlParamは引数。今は気にしなくてよい。
	///////////////////////////////////////////////////////////////////
	LRESULT CALLBACK MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		if (wParam > 0) {
			MauseInfo::GetInstance()->SetMauseState(MauseInfo::State::MauseWheelUp);
		}
		if (wParam < 0) {
			MauseInfo::GetInstance()->SetMauseState(MauseInfo::State::MauseWheelDown);
		}
		//送られてきたメッセージで処理を分岐させる。
		switch (msg)
		{
		case WM_DESTROY:
			//エンジンの破棄。
			GameEngine().Release();
			PostQuitMessage(0);
			break;
		case WM_KEYDOWN:
			switch (wParam)
			{
			case VK_ESCAPE:
				DestroyWindow(g_hWnd);
				break;
			default:
				break;
			}
			//渡された message から、イベントの種類を解析する
		case WM_LBUTTONDOWN:
			MauseInfo::GetInstance()->SetMauseState(MauseInfo::State::MauseLClick);
			break;
		case WM_RBUTTONDOWN:
			MauseInfo::GetInstance()->SetMauseState(MauseInfo::State::MauseRClick);
			break;
		default:
			MauseInfo::GetInstance()->SetMauseState(MauseInfo::State::None);
			return DefWindowProc(hWnd, msg, wParam, lParam);
		}
		return 0;
	}


	///////////////////////////////////////////////////////////////////
	// ウィンドウの初期化。
	///////////////////////////////////////////////////////////////////
	void InitWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow, const TCHAR* appName)
	{
		//ウィンドウクラスのパラメータを設定(単なる構造体の変数の初期化です。)
		WNDCLASSEX wc =
		{
			sizeof(WNDCLASSEX),		//構造体のサイズ。
			CS_CLASSDC,				//ウィンドウのスタイル。
									//ここの指定でスクロールバーをつけたりできるが、ゲームでは不要なのでCS_CLASSDCでよい。
			MsgProc,				//メッセージプロシージャ(後述)
			0,						//0でいい。
			0,						//0でいい。
			GetModuleHandle(NULL),	//このクラスのためのウインドウプロシージャがあるインスタンスハンドル。
									//何も気にしなくてよい。
			NULL,					//アイコンのハンドル。アイコンを変えたい場合ここを変更する。とりあえずこれでいい。
			NULL,					//マウスカーソルのハンドル。NULLの場合はデフォルト。
			NULL,					//ウィンドウの背景色。NULLの場合はデフォルト。
			NULL,					//メニュー名。NULLでいい。
			appName,				//ウィンドウクラスに付ける名前。
			NULL					//NULLでいい。
		};
		//ウィンドウクラスの登録。
		RegisterClassEx(&wc);

		// ウィンドウの作成。
		g_hWnd = CreateWindow(
			appName,				//使用するウィンドウクラスの名前。
									//先ほど作成したウィンドウクラスと同じ名前にする。
			appName,				//ウィンドウの名前。ウィンドウクラスの名前と別名でもよい。
			WS_OVERLAPPEDWINDOW,	//ウィンドウスタイル。ゲームでは基本的にWS_OVERLAPPEDWINDOWでいい、
			0,						//ウィンドウの初期X座標。
			0,						//ウィンドウの初期Y座標。
			FRAME_BUFFER_W,			//ウィンドウの幅。
			FRAME_BUFFER_H,			//ウィンドウの高さ。
			NULL,					//親ウィンドウ。ゲームでは基本的にNULLでいい。
			NULL,					//メニュー。今はNULLでいい。
			hInstance,				//アプリケーションのインスタンス。
			NULL
		);

		ShowWindow(g_hWnd, nCmdShow);

	}


	//ゲームの初期化。
	void InitGame(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow, const TCHAR* appName, const SInitParam& initParam)
	{
		MauseInfo::Create();
		//ウィンドウを初期化。
		InitWindow(hInstance, hPrevInstance, lpCmdLine, nCmdShow, appName);
		//エンジンのインスタンスを作成。
		TkEngine::CreateInstance();
		//TKエンジンの初期化。
		GameEngine().Init(g_hWnd, initParam);
	}
	//ウィンドウメッセージをディスパッチ。falseが返ってきたら、ゲーム終了。
	bool DispatchWindowMessage()
	{
		MSG msg = { 0 };
		while (WM_QUIT != msg.message) {
			//ウィンドウからのメッセージを受け取る。
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else {
				//ウィンドウメッセージが空になった。
				break;
			}
		}
		return msg.message != WM_QUIT;
	}
}