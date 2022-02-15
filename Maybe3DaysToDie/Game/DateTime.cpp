#include "stdafx.h"
#include "DateTime.h"
#include <wchar.h>

namespace {
	const int OneMinute = 1;					//�P���o����
	const int OneHune = 9;						//�P���Ԍo����
	const int OneHode = 1;						//�P���o����
	const Vector2 FontPos = { -150.0f,330.0f };	//�t�H���g�̈ʒu
	const Vector2 FontPivot = { 0.5f,0.5f };	//�t�H���g�̊�_
	const float FontScale = 0.5f;				//�t�H���g�̑傫��
}

bool DateTime::Start()
{
	//�t�H���g�̃C���X�^���X���쐬
	m_TimeFont = NewGO<CFontRender>(0);

	//���ԗp�̕�����
	wchar_t Time[256] = {};
	//�t�H���g�ɓn���e�L�X�g
	wchar_t TimerData[256] = {};
	m_minit = 0;
	m_Hours = OneHode;
	wcscat_s(Time, L"����     ");
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
	m_TimeFont->SetPivot(FontPivot);
	//�ʒu��ݒ�
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
	//�P�b���J�E���g
	m_Second += GameTime().GetFrameDeltaTime();
	//�P�����J�E���g
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
	//���Ԃ̕���
	wchar_t Time[256] = {};
	//�ŏI�I�Ƀt�H���g�ɑ����镶��
	wchar_t TimerData[256] = {};

	//�܂����ɂ������߂�
	//��������
	wcscat_s(Time, L"���Ɓ@");
	//�t�H���g�p�����ɃR�s�[
	wcscpy_s(TimerData, Time);

	//�����Ď���
	//���Ԃ𕶎���ɕϊ�
	_itow_s(m_Hours, Time, 10);
	//��������
	wcscat_s(Time, L"���@");
	//�t�H���g�p������ɑ���
	wcscat_s(TimerData, Time);

	//�Ō�ɕ�
	//���𕶎���ɕϊ�
	_itow_s(m_minit, Time, 10);
	//��������
	wcscat_s(Time, L"��");
	//�t�H���g�p������ɑ���
	wcscat_s(TimerData, Time);
	//�e�L�X�g��ݒ�
	m_TimeFont->SetText(TimerData);
	//�����̑傫����ݒ�
	m_TimeFont->SetScale(FontScale);
}

void DateTime::OnDestroy()
{
	//�t�H���g���폜
	DeleteGO(m_TimeFont);
}

void DateTime::FinishHode()
{
	m_IsHode = false;
	m_minit = 0;
	m_Hours = OneHode;
}
