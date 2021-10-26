#pragma once

/// <summary>
/// GetAsyncKeyのラッパークラス。
/// isTriggerとisPress分けたかったので作成。
/// todo:padクラスと処理が重複してる場所があるのでそこの修正する。
/// </summary>
class CInputKeyCode
{
public:
	/// <summary>
	/// 初期化。
	/// <para>呼び出さなくても大丈夫な気がするがReleaseとかで</para>
	/// <para>もしかしたらバグるかもしれない。</para>
	/// </summary>
	void Init();
	/// <summary>
	/// 更新処理。
	/// </summary>
	void Update();
	/// <summary>
	/// トリガー。
	/// </summary>
	/// <param name="code">コード。</param>
	bool IsTriggerKey(const int code)
	{
		return m_isTrigger[code] != 0;
	}
	/// <summary>
	/// プレス。普通のasyncと変化なし。
	/// </summary>
	/// <param name="code">コード。</param>
	bool IsPressKey(const char code)
	{
		return m_isPress[code] != 0;
	}
private:	
	bool m_isPress[VK_OEM_CLEAR];		//isPress
	bool m_isTrigger[VK_OEM_CLEAR];		//isTrigger
};

