#include "MiniEngine.h"
#include "FontRender.h"

namespace Engine {
	void CFontRender::OnRender2D(RenderContext& rc)
	{
		//フォントの描画設定。
		m_font.Begin();
		const wchar_t* text = nullptr;
		if (m_textUnsafe != nullptr) {
			//アンセーフ版を使用している。
			text = m_textUnsafe;
		}
		else if (m_text.c_str() != nullptr) {
			//テキストがある。
			text = m_text.c_str();
		}

		//描画。
		m_font.Draw(
			text,
			m_position,
			m_color,
			m_rotation,
			m_scale,
			m_pivot
		);

		//描画設定をもとにもどす。
		m_font.End();
	}
}