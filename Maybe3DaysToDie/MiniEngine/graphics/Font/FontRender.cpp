#include "MiniEngine.h"
#include "FontRender.h"

namespace Engine {
	void CFontRender::OnRender2D(RenderContext& rc)
	{
		//�t�H���g�̕`��ݒ�B
		m_font.Begin();
		const wchar_t* text = nullptr;
		if (m_textUnsafe != nullptr) {
			//�A���Z�[�t�ł��g�p���Ă���B
			text = m_textUnsafe;
		}
		else if (m_text.c_str() != nullptr) {
			//�e�L�X�g������B
			text = m_text.c_str();
		}

		//�`��B
		m_font.Draw(
			text,
			m_position,
			m_color,
			m_rotation,
			m_scale,
			m_pivot
		);

		//�`��ݒ�����Ƃɂ��ǂ��B
		m_font.End();
	}
}