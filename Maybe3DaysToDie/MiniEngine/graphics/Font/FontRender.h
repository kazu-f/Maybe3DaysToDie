/// <summary>
/// フォントレンダー。
/// </summary>
/// <remarks>
/// GameObjectManager下で管理する、フォントのラッパークラス。
/// ユーザー定義のタイミングで描画をする際は、Fontクラスで行うこと。
/// </remarks>

#pragma once

#include "Font.h"

namespace Engine {
	class CFontRender : public IGameObject
	{
	public:
		/// <summary>
		/// テキストを設定。
		/// 文字列コピーがあるため速度遅め。用途に合わせて使用すること。
		/// </summary>
		/// <param name="text">テキスト。</param>
		void SetText(const wchar_t* text)
		{
			if (wcscmp(m_text.c_str(), text) != 0) {
				//文字列に変更があった。
				//ここでコピーが発生する？
				m_text = text;
			}
		}
		/// <summary>
		/// アンセーフ版、SetText。
		/// <para>直接生ポインタを入れてテキストを設定するため、寿命の問題に注意。</para>
		/// <para>基本的には設定元の文字列を、メンバ変数において使用するなどの対処をとること。</para>
		/// </summary>
		/// <param name="text"></param>
		void SetTextUnsafe(const wchar_t* text)
		{
			//コピーが発生しない。
			m_textUnsafe = text;
		}
		/// <summary>
		/// フォントを表示する座標設定。
		/// <para>画面中央が0,0</para>
		/// </summary>
		/// <param name="pos">座標</param>
		void SetPosition(const Vector2& pos)
		{
			m_position = pos;
		}
		/// <summary>
		/// フォントの色を設定。
		/// </summary>
		/// <param name="color">カラー</param>
		void SetColor(const Vector3& color)
		{
			m_color = color;
		}
		/// <summary>
		/// フォントの色を設定。
		/// <para>α設定できる方。</para>
		/// </summary>
		/// <param name="color">カラー</param>
		void SetColor(const Vector4& color)
		{
			m_color = color;
		}
		/// <summary>
		/// 回転を設定。
		/// </summary>
		/// <param name="rot">回転。</param>
		void SetRotation(float rot)
		{
			m_rotation = rot;
		}
		/// <summary>
		/// 拡大率。
		/// </summary>
		/// <param name="scale">スケール。</param>
		void SetScale(float scale)
		{
			m_scale = scale;
		}
		/// <summary>
		/// ピボットの設定。
		/// </summary>
		/// <param name="pivot">ピボット。</param>
		void SetPivot(const Vector2& pivot)
		{
			m_pivot = pivot;
		}
		/// <summary>
		/// シャドウのパラメーターを設定。
		/// </summary>
		/// <param name="isDrawShadow">シャドウを描画するか</param>
		/// <param name="shadowOffset">シャドウオフセット。</param>
		/// <param name="shadowColor">シャドウカラー。</param>
		void SetShadowParam(const bool& isDrawShadow, const float& shadowOffset, const Vector4& shadowColor)
		{
			m_font.SetShadowParam(isDrawShadow, shadowOffset, shadowColor);
		}
	private:
		void PostRender(RenderContext& rc) override;
	private:
		CFont			m_font;								//フォント。
		std::wstring	m_text;								//テキスト。
		const wchar_t*	m_textUnsafe;						//アンセーフテキスト。
		Vector2			m_position = Vector2::Zero;			//座標。(0.0f,0.0f)で真ん中。
		Vector4			m_color = Vector4::White;			//カラー。
		float			m_rotation = 0.0f;					//回転。
		float			m_scale = 1.0f;						//スケール。
		Vector2			m_pivot = {0.5f, 0.5f};				//ピボット。
	};
}
