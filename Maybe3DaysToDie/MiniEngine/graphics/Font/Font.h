/// <summary>
/// �t�H���g
/// </summary>
/// <remarks>
/// �t�H���g�̕`�揈���B
/// ��{�̓t�H���g�����_�[���g���ĕ`�悷�邱�ƁB
/// ������Draw����ꍇ�́ABegin��Draw��End�̏��ԂŌĂяo���Ă��������B
/// </remarks>

#pragma once


namespace Engine {
	class FontEngine;

	class CFont
	{
	public:
		CFont();
		~CFont();
		/// <summary>
		/// �`��J�n�����B
		/// <para>HUD�`��Ńt�H���g��`�悷��ۂ̓��[�U�[�͂��̊֐����Ăяo���K�v�͂���܂���B</para>
		/// <para>HUD�`��ȊO�ŌĂяo���ۂ̓��[�U�[�͂��̊֐����g�p���Ă��������B</para>
		/// </summary>
		void Begin();
		/// <summary>
		/// �`��I�������B
		/// <para>HUD�`��Ńt�H���g��`�悷��ۂ̓��[�U�[�͂��̊֐����Ăяo���K�v�͂���܂���B</para>
		/// <para>HUD�`��ȊO�ŌĂяo���ۂ̓��[�U�[�͂��̊֐����g�p���Ă��������B</para>
		/// </summary>
		void End();
		/// <summary>
		/// �`��B
		/// </summary>
		/// <param name="text">�\������e�L�X�g</param>
		/// <param name="pos">�ʒu</param>
		/// <param name="color">�F</param>
		/// <param name="rotation">��]</param>
		/// <param name="scale">�傫��</param>
		/// <param name="pivot">��_</param>
		void Draw(
			wchar_t const* text,
			const Vector2& pos,
			const Vector4& color = Vector4::White,
			float rotation = 0.0f,
			float scale = 1.0f,
			Vector2 pivot = {0.5f, 0.5f}
		);
		/// <summary>
		/// �e��`�悷��ݒ�B
		/// </summary>
		/// <param name="isDrawShadow">�e��`�悷�邩�B</param>
		/// <param name="shadowOffset">�V���h�E�I�t�Z�b�g�B</param>
		/// <param name="shadowColor">�V���h�E�J���[�B</param>
		void SetShadowParam(const bool& isDrawShadow, const float& shadowOffset, const Vector4& shadowColor)
		{
			m_isDrawShadow = isDrawShadow;
			m_shadowOffset = shadowOffset;
			m_shadowColor = shadowColor;
		}
	private:
		FontEngine*		m_fe;								//�t�H���g�G���W���B
		bool			m_isDrawShadow = false;				//�e��`�悷�邩�B
		float			m_shadowOffset = 0.0f;				//�e��`���Ƃ��̃s�N�Z���̃I�t�Z�b�g�ʁB
		Vector4			m_shadowColor = Vector4::Black;		//�e�̐F�B
	};
}

