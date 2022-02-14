#include "MiniEngine.h"
#include "MauseInfo.h"

MauseInfo* MauseInfo::m_MauseInfo = nullptr;

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
