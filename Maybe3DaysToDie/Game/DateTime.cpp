#include "stdafx.h"
#include "DateTime.h"
#include <wchar.h>

namespace {
	const int OneMinute = 1;					//１分経つ時間
	const int OneHune = 5;						//１時間経つ時間
	const int OneDay = 2;						//１日経つ時間
	const Vector2 FontPos = { -300.0f,330.0f };	//Fontの位置
}

bool DateTime::Start()
{
	m_TimeFont = NewGO<CFontRender>(0);

	wchar_t Time[256] = {};
	wchar_t TimerData[256] = {};
	wchar_t TimeData[256] = {};
	
	_itow_s(m_Day, Time, 10);
	wcscpy_s(TimerData, Time);
	wcscpy_s(Time, L"日       ");
	wcscat_s(TimerData, Time);

	_itow_s(m_Hours, Time, 10);
	wcscpy_s(TimeData, Time);
	wcscat_s(Time, L"時  ");
	wcscat_s(TimerData, Time);

	_itow_s(m_minit, Time, 10);
	wcscpy_s(TimeData, Time);
	wcscat_s(Time, L"分");
	wcscat_s(TimerData, Time);

	//wchar_t baka[256] = L"9あ.\nReo is Baka\nReo is UNKO\nHima is Neet";
	m_TimeFont->SetText(TimerData);
	//m_TimeFont->SetText(baka);
	m_TimeFont->SetColor(Vector4::White);
	m_TimeFont->SetShadowParam(true, 0.5f, Vector4::Black);
	m_TimeFont->SetPivot({ 0.5f, 0.5f });
	m_TimeFont->SetPosition(FontPos);
	return true;
}

void DateTime::Update()
{
	m_Second += GameTime().GetFrameDeltaTime();
	if (m_Second >= OneMinute) {
		m_minit++;
		m_Second = 0;
	}
	if (m_minit >= OneHune) {
		m_Hours++;
		m_minit = 0;
	}
	if (m_Hours >= OneDay) {
		m_Day++;
		m_Hours = 0;
	}
	wchar_t Time[256] = {};
	wchar_t TimerData[256] = {};
	wchar_t TimeData[256] = {};

	_itow_s(m_Day, Time, 10);
	wcscpy_s(TimerData, Time);
	wcscpy_s(Time, L"日       ");
	wcscat_s(TimerData, Time);

	_itow_s(m_Hours, Time, 10);
	wcscpy_s(TimeData, Time);
	wcscat_s(Time, L"時  ");
	wcscat_s(TimerData, Time);

	_itow_s(m_minit, Time, 10);
	wcscpy_s(TimeData, Time);
	wcscat_s(Time, L"分");
	wcscat_s(TimerData, Time);
	m_TimeFont->SetText(TimerData);
}

void DateTime::OnDestroy()
{
	//フォントを削除
	DeleteGO(m_TimeFont);
}
