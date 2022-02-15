#include "stdafx.h"
#include "DateTime.h"
#include <wchar.h>

namespace {
	const int OneMinute = 1;					//１分経つ時間
	const int OneHune = 9;						//１時間経つ時間
	const int OneHode = 1;						//１日経つ時間
	const Vector2 FontPos = { -150.0f,330.0f };	//フォントの位置
	const Vector2 FontPivot = { 0.5f,0.5f };	//フォントの基点
	const float FontScale = 0.5f;				//フォントの大きさ
}

bool DateTime::Start()
{
	//フォントのインスタンスを作成
	m_TimeFont = NewGO<CFontRender>(0);

	//時間用の文字列
	wchar_t Time[256] = {};
	//フォントに渡すテキスト
	wchar_t TimerData[256] = {};
	m_minit = 0;
	m_Hours = OneHode;
	wcscat_s(Time, L"あと     ");
	wcscat_s(TimerData, Time);

	//時間の文字を連結
	_itow_s(m_Hours, Time, 10);
	wcscat_s(Time, L"時  ");
	wcscat_s(TimerData, Time);

	//分の文字を連結
	_itow_s(m_minit, Time, 10);
	wcscat_s(Time, L"分");
	wcscat_s(TimerData, Time);

	//テキストを設定
	m_TimeFont->SetText(TimerData);
	//色を設定
	m_TimeFont->SetColor(Vector4::White);
	//基点を設定
	m_TimeFont->SetPivot(FontPivot);
	//位置を設定
	m_TimeFont->SetPosition(FontPos);
	return true;
}

void DateTime::Update()
{
	if (m_IsHode) {
		m_TimeFont->SetColor(Vector4::Red);
		m_Second = 0;
	}
	else {
		m_TimeFont->SetColor(Vector4::White);
	}
	//１秒をカウント
	m_Second += GameTime().GetFrameDeltaTime();
	//１分をカウント
	if (m_Second >= OneMinute) {
		m_minit--;
		if (m_minit < 0) {
			m_Hours--;
			m_minit = OneHune;
		}
		m_Second = 0;
	}
	if (m_Hours < 0) {
		m_Hours = 0;
		m_minit = 0;
		m_IsHode = true;
	}
	//時間の文字
	wchar_t Time[256] = {};
	//最終的にフォントに送られる文字
	wchar_t TimerData[256] = {};

	//まず日にちを決める
	//日をつける
	wcscat_s(Time, L"あと　");
	//フォント用文字にコピー
	wcscpy_s(TimerData, Time);

	//続いて時間
	//時間を文字列に変換
	_itow_s(m_Hours, Time, 10);
	//時をつける
	wcscat_s(Time, L"時　");
	//フォント用文字列に足す
	wcscat_s(TimerData, Time);

	//最後に分
	//分を文字列に変換
	_itow_s(m_minit, Time, 10);
	//分をつける
	wcscat_s(Time, L"分");
	//フォント用文字列に足す
	wcscat_s(TimerData, Time);
	//テキストを設定
	m_TimeFont->SetText(TimerData);
	//文字の大きさを設定
	m_TimeFont->SetScale(FontScale);
}

void DateTime::OnDestroy()
{
	//フォントを削除
	DeleteGO(m_TimeFont);
}

void DateTime::FinishHode()
{
	m_IsHode = false;
	m_minit = 0;
	m_Hours = OneHode;
}
