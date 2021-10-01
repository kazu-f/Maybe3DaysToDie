#pragma once

namespace Engine {
	/// <summary>
	/// �t�H���g�G���W���B
	/// </summary>
	class FontEngine
	{
	public:
		~FontEngine();
		/// <summary>
		/// �������B
		/// </summary>
		void Init(RenderContext& rc);
		/// <summary>
		/// �`��J�n�B
		/// </summary>
		/// <param name="rc"></param>
		void BeginDraw();
		/// <summary>
		/// �`��B
		/// </summary>
		/// <param name="text">�\������e�L�X�g�B</param>
		/// <param name="pos">�ʒu�B</param>
		/// <param name="color">�F�B</param>
		/// <param name="rotation">��]�B</param>
		/// <param name="scale">�X�P�[���B</param>
		/// <param name="pivot">�s�{�b�g�B</param>
		void Draw(
			const wchar_t* text,
			const Vector2& pos,
			const Vector4& color,
			float rotation,
			float scale,
			Vector2 pivot
		);
		/// <summary>
		/// �`��I���B
		/// </summary>
		void EndDraw();
	private:
		std::unique_ptr<DirectX::SpriteBatch>	m_spriteBatch;		//�X�v���C�g�o�b�`�B
		std::unique_ptr<DirectX::SpriteFont>	m_spriteFont;		//�X�v���C�g�t�H���g�B
		ID3D12DescriptorHeap* m_srvDescriptorHeap = nullptr;		//SRV�̃f�B�X�N���v�^�q�[�v�B
		RenderContext* m_rc;										//��񂱂�B
	};
}


