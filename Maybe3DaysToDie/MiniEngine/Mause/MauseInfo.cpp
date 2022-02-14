#include "MiniEngine.h"
#include "MauseInfo.h"

MauseInfo* MauseInfo::m_MauseInfo = nullptr;
Vector2 MauseInfo::m_InitialMausePos = { 500.0f,200.0f };

void MauseInfo::Create()
{
	if (m_MauseInfo == nullptr) {
		m_MauseInfo = new MauseInfo;
	}
}

void MauseInfo::Delete()
{
	delete m_MauseInfo;
	m_MauseInfo = nullptr;
}

void MauseInfo::MauseMoveUpdate()
{
	//�}�E�X�J�[�\���̈ʒu���擾
	POINT pt;
	GetCursorPos(&pt);
	//���̃t���[���ł̈ړ���
	float lstx = pt.x - m_DefaultPoint.x;
	float lsty = pt.y - m_DefaultPoint.y;
	Vector2 MausePos = { 
		pt.x + lstx ,
		pt.y + lsty
	};
	m_MauseMove = { lstx,lsty };
	SetMauseCursor(MausePos);
	m_MauseCorsoluPos = MausePos;
	m_DefaultPoint = MausePos;
}

void MauseInfo::SetMauseCursor(const Vector2& CorsorPos)
{
	//�}�E�X�J�[�\���̈ʒu���Œ�
	SetCursorPos((int)CorsorPos.x, (int)CorsorPos.y);
	m_DefaultPoint = CorsorPos;
}
