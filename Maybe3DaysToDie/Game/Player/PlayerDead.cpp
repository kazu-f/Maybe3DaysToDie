#include "stdafx.h"
#include "PlayerDead.h"
#include <windows.h>

namespace
{
	const Vector2 BottonPos = { 0.0f,0.0f };
}

bool PlayerDead::Start()
{
	while (true) {
		int returnNo = ShowCursor(true);
		if (returnNo >= 0) {
			break;
		}
	}
	m_Font = NewGO<CFontRender>(0);
	m_Font->SetText(L"死んだ");
	m_Font->SetColor(Vector4::Red);
	m_Font->SetShadowParam(true, 0.5f, Vector4::White);

	m_BackSprite = InitSprite("Assets/sprite/BackColor.dds");
	m_SelectSprite = InitSprite("Assets/sprite/SelectBotton.dds");
	m_BottonSprite = InitSprite("Assets/sprite/respownBotton.dds");

    return true;
}

void PlayerDead::Update()
{
	ReSpownTime -= GameTime().GetFrameDeltaTime();
    if (ReSpownTime < 0.0) {

    }
}

void PlayerDead::OnDestroy()
{
	DeleteGO(m_Font);
	DeleteGO(m_BottonSprite);
	DeleteGO(m_BackSprite);
	DeleteGO(m_SelectSprite);
}

prefab::CSpriteRender* PlayerDead::InitSprite(const char* fileName)
{
	static int layer = 0;
	prefab::CSpriteRender* render = NewGO<prefab::CSpriteRender>(layer++);
	render->Init(fileName, 500.0f, 200.0f);
	render->SetPosition(BottonPos);
	return render;
}

LRESULT  CALLBACK  PlayerDead::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    HDC         hdc;
    PAINTSTRUCT ps;
	float x = 0.0f;
	float y = 0.0f;
    //渡された message から、イベントの種類を解析する
    switch (msg) {
    case WM_CREATE:
        x = 50;
        y = 50;
        break;
    case WM_LBUTTONDOWN:
        x = LOWORD(lParam);
        y = HIWORD(lParam);
        InvalidateRect(hWnd, NULL, TRUE);  //領域無効化
        UpdateWindow(hWnd);                //再描画命令
        break;
    case WM_RBUTTONDOWN:
        x = LOWORD(lParam);
        y = HIWORD(lParam);
        InvalidateRect(hWnd, NULL, TRUE);  //領域無効化
        UpdateWindow(hWnd);                //再描画命令
        break;
        //----ペイント----
    case WM_PAINT:
        break;
        //----終了処理----
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0L;
    }
    //デフォルトの処理
    return  DefWindowProc(hWnd, msg, wParam, lParam);
}