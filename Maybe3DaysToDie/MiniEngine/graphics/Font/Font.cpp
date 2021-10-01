#include "MiniEngine.h"
#include "Font.h"

namespace Engine {
	CFont::CFont()
	{
		m_fe = &GraphicsEngine()->GetFontEngine();
	}

	CFont::~CFont()
	{
	}

	void CFont::Begin()
	{
		//���݂̃����_�[�X�e�[�g��ۑ�
		//*****
		//�`��ݒ�B
		m_fe->BeginDraw();
	}

	void CFont::End()
	{
		//�`��I���B
		m_fe->EndDraw();
	}

	void CFont::Draw(
		wchar_t const* text,
		const Vector2& pos,
		const Vector4& color,
		float rotation,
		float scale,
		Vector2 pivot
	)
	{
		if (text == nullptr) {
			//�Ȃɂ��Ȃ�����A�Ȃɂ�����I
			return;
		}

		pivot.y = 1.0f - pivot.y;
		DirectX::XMFLOAT2 tkFloat2Zero(0, 0);
		//���W�n���X�v���C�g�ƍ��킹��B
		Vector2 position = pos;
		float frameBufferHalfWidth = FRAME_BUFFER_W * 0.5f;
		float frameBufferHalfHeight = FRAME_BUFFER_H * 0.5f;
		position.x += frameBufferHalfWidth;
		position.y = -pos.y + frameBufferHalfHeight;

		//�e�`��B
		if (m_isDrawShadow) {

			Vector2 offsetTbl[] = {
				{ m_shadowOffset , 0.0f},
				{ -m_shadowOffset , 0.0f },
				{ 0.0f , m_shadowOffset },
				{ 0.0f , -m_shadowOffset },

				{ m_shadowOffset ,  m_shadowOffset },
				{ m_shadowOffset ,  -m_shadowOffset },
				{ -m_shadowOffset , m_shadowOffset },
				{ -m_shadowOffset , -m_shadowOffset },
			};

			for (auto offset : offsetTbl) {
				Vector2 sPos = position;
				sPos.x += offset.x;
				sPos.y += offset.y;
				m_fe->Draw(
					text,
					sPos,
					m_shadowColor,
					rotation,
					scale,
					pivot
				);
			}
		}

		m_fe->Draw(
			text,
			position,
			color,
			rotation,
			scale,
			pivot
		);
	}
}