#include "MiniEngine.h"
#include "InputKeyCode.h"

void CInputKeyCode::Init()
{
	for (int i = 0; i < VK_OEM_CLEAR; i++) {
		//VK分一応初期化。
		m_isPress[i] = false;
		m_isTrigger[i] = false;
	}
}

void CInputKeyCode::Update()
{
	//すべてのキーコード分ステートをチェックしていく。
	for (int keyCode = 0; keyCode < VK_OEM_CLEAR; keyCode++) {
		if (GetAsyncKeyState(keyCode)) {
			//押されている。
			//isTriigerフラグの判定。
			m_isTrigger[keyCode] = m_isPress[keyCode] ^ 1;
			//pressは強制でtrue。
			m_isPress[keyCode] = 1;
		}
		else {
			//押されていない。
			m_isTrigger[keyCode] = 0;
			m_isPress[keyCode] = 0;
		}
	}//loop:end
}
