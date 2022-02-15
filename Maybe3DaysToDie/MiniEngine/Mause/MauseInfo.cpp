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
	//マウスカーソルの位置を取得
	POINT pt;
	GetCursorPos(&pt);
	//このフレームでの移動量
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
	//マウスカーソルの位置を固定
	SetCursorPos((int)CorsorPos.x, (int)CorsorPos.y);
	m_DefaultPoint = CorsorPos;
}
