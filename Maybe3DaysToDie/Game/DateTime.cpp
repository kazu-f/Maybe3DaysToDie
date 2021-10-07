#include "stdafx.h"
#include "DateTime.h"
#include <wchar.h>

namespace {
	const int OneMinute = 1;					//�P���o����
	const int OneHune = 5;						//�P���Ԍo����
	const int OneDay = 2;						//�P���o����
	const Vector2 FontPos = { -150.0f,330.0f };	//Font�̈ʒu
}

bool DateTime::Start()
{
	//�t�H���g��New
	m_TimeFont = NewGO<CFontRender>(0);

	//���ԗp�̕�����
	wchar_t Time[256] = {};
	//�t�H���g�ɓn���e�L�X�g
	wchar_t TimerData[256] = {};
	
	//���ɂ��̕������쐬
	_itow_s(m_Day, Time, 10);
	wcscpy_s(Time, L"��     ");
	wcscat_s(TimerData, Time);

	//���Ԃ̕�����A��
	_itow_s(m_Hours, Time, 10);
	wcscat_s(Time, L"��  ");
	wcscat_s(TimerData, Time);

	//���̕�����A��
	_itow_s(m_minit, Time, 10);
	wcscat_s(Time, L"��");
	wcscat_s(TimerData, Time);

	//�e�L�X�g��ݒ�
	m_TimeFont->SetText(TimerData);
	//�F��ݒ�
	m_TimeFont->SetColor(Vector4::White);
	//��_��ݒ�
	m_TimeFont->SetPivot({ 0.5f, 0.5f });
	//�ʒu��ݒ�
	m_TimeFont->SetPosition(FontPos);
	return true;
}

void DateTime::Update()
{
	//���Ԃ��J�E���g
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

	_itow_s(m_Day, Time, 10);
	wcscpy_s(TimerData, Time);
	wcscpy_s(Time, L"��       ");
	wcscat_s(TimerData, Time);

	_itow_s(m_Hours, Time, 10);
	wcscat_s(Time, L"��  ");
	wcscat_s(TimerData, Time);

	_itow_s(m_minit, Time, 10);
	wcscat_s(Time, L"��");
	wcscat_s(TimerData, Time);
	m_TimeFont->SetText(TimerData);
	m_TimeFont->SetScale(0.5f);
}

void DateTime::OnDestroy()
{
	//�t�H���g���폜
	DeleteGO(m_TimeFont);
}
