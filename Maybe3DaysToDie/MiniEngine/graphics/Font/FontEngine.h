#pragma once

namespace Engine {
	/// <summary>
	/// フォントエンジン。
	/// </summary>
	class FontEngine
	{
	public:
		~FontEngine();
		/// <summary>
		/// 初期化。
		/// </summary>
		void Init(RenderContext& rc);
		/// <summary>
		/// 描画開始。
		/// </summary>
		/// <param name="rc"></param>
		void BeginDraw();
		/// <summary>
		/// 描画。
		/// </summary>
		/// <param name="text">表示するテキスト。</param>
		/// <param name="pos">位置。</param>
		/// <param name="color">色。</param>
		/// <param name="rotation">回転。</param>
		/// <param name="scale">スケール。</param>
		/// <param name="pivot">ピボット。</param>
		void Draw(
			const wchar_t* text,
			const Vector2& pos,
			const Vector4& color,
			float rotation,
			float scale,
			Vector2 pivot
		);
		/// <summary>
		/// 描画終了。
		/// </summary>
		void EndDraw();
	private:
		std::unique_ptr<DirectX::SpriteBatch>	m_spriteBatch;		//スプライトバッチ。
		std::unique_ptr<DirectX::SpriteFont>	m_spriteFont;		//スプライトフォント。
		ID3D12DescriptorHeap* m_srvDescriptorHeap = nullptr;		//SRVのディスクリプタヒープ。
		RenderContext* m_rc;										//れんこん。
	};
}


