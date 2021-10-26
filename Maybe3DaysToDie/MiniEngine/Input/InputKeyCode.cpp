#include "MiniEngine.h"
#include "InputKeyCode.h"

void CInputKeyCode::Init()
{
	for (int i = 0; i < VK_OEM_CLEAR; i++) {
		//VK���ꉞ�������B
		m_isPress[i] = false;
		m_isTrigger[i] = false;
	}
}

void CInputKeyCode::Update()
{
	//���ׂẴL�[�R�[�h���X�e�[�g���`�F�b�N���Ă����B
	for (int keyCode = 0; keyCode < VK_OEM_CLEAR; keyCode++) {
		if (GetAsyncKeyState(keyCode)) {
			//������Ă���B
			//isTriiger�t���O�̔���B
			m_isTrigger[keyCode] = m_isPress[keyCode] ^ 1;
			//press�͋�����true�B
			m_isPress[keyCode] = 1;
		}
		else {
			//������Ă��Ȃ��B
			m_isTrigger[keyCode] = 0;
			m_isPress[keyCode] = 0;
		}
	}//loop:end
}
