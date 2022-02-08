#pragma once
#include "IRenderer.h"
namespace Engine {

	class CRendererManager : Noncopyable
	{
		using RendererArray = std::vector <prefab::IRenderer*>;
	public:
		/// <summary>
		/// レンダラーマネージャーを初期化。
		/// </summary>
		/// <param name="prio">最大優先度。</param>
		void InitRendererManager(unsigned char prio)
		{
			MAX_PRIO = prio;
			m_rendererArrayList.resize(MAX_PRIO);
		}
		/// <summary>
		/// レンダラーの登録を行う。
		/// </summary>
		/// <param name="renderer"></param>
		void RegistRenderer(prefab::IRenderer* renderer)
		{
			int prio = renderer->GetPriority();
			m_rendererArrayList[prio].push_back(renderer);
		}
		/// <summary>
		/// レンダラーの登録を解除する。
		/// </summary>
		/// <param name="renderer"></param>
		void RemoveRenderer(prefab::IRenderer* renderer)
		{
			int prio = renderer->GetPriority();
			auto it = std::find(m_rendererArrayList[prio].begin(), m_rendererArrayList[prio].end(), renderer);
			if (it != m_rendererArrayList[prio].end()) {
				m_rendererArrayList[prio].erase(it);
			}
		}

	public:

		/// <summary>
		/// シャドウマップの描画を行う。
		/// </summary>
		/// <param name="rc">レンダリングコンテキスト。</param>
		/// <param name="LVP">ライトビュープロジェクション行列。</param>
		/// <param name="i">シャドウマップ番号。</param>
		void RenderToShadowMap(RenderContext& rc, const Matrix& LVP, int i);

		/// <summary>
		/// GBufferに描画する。
		/// </summary>
		/// <param name="rc">レンダリングコンテキスト。</param>
		void RenderToGBuffer(RenderContext& rc);

		/// <summary>
		/// フォワードレンダーを実行する。
		/// </summary>
		/// <param name="rc">レンダリングコンテキスト。</param>
		void ForwardRender(RenderContext& rc);

		/// <summary>
		/// 2D描画を実行する。
		/// </summary>
		/// <param name="rc">レンダリングコンテキスト。</param>
		void Render2D(RenderContext& rc);

	private:
		unsigned char MAX_PRIO = 0;
		std::vector<RendererArray> m_rendererArrayList;		//レンダラークラスの配列リスト。
	};

}
