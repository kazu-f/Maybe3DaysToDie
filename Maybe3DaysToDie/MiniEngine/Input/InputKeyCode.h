#pragma once

/// <summary>
/// GetAsyncKey�̃��b�p�[�N���X�B
/// isTrigger��isPress�������������̂ō쐬�B
/// todo:pad�N���X�Ə������d�����Ă�ꏊ������̂ł����̏C������B
/// </summary>
class CInputKeyCode
{
public:
	/// <summary>
	/// �������B
	/// <para>�Ăяo���Ȃ��Ă����v�ȋC�����邪Release�Ƃ���</para>
	/// <para>������������o�O�邩������Ȃ��B</para>
	/// </summary>
	void Init();
	/// <summary>
	/// �X�V�����B
	/// </summary>
	void Update();
	/// <summary>
	/// �g���K�[�B
	/// </summary>
	/// <param name="code">�R�[�h�B</param>
	bool IsTriggerKey(const int code)
	{
		return m_isTrigger[code] != 0;
	}
	/// <summary>
	/// �v���X�B���ʂ�async�ƕω��Ȃ��B
	/// </summary>
	/// <param name="code">�R�[�h�B</param>
	bool IsPressKey(const char code)
	{
		return m_isPress[code] != 0;
	}
private:	
	bool m_isPress[VK_OEM_CLEAR];		//isPress
	bool m_isTrigger[VK_OEM_CLEAR];		//isTrigger
};

