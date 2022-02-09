#pragma once

namespace Engine {
	namespace prefab {
		class IRenderer : public IGameObject
		{
		protected:
			virtual ~IRenderer() {};
			bool Start()override final;			//初期化関数。
			void OnDestroy()override final;		//削除時処理。

			/// <summary>
			/// 派生先での初期化を行う関数。
			/// </summary>
			/// <returns>初期化完了かどうか。</returns>
			virtual bool SubStart()
			{
				return true;
			}

			/// <summary>
			/// 派生先での削除処理。
			/// </summary>
			virtual void SubOnDestroy()
			{

			}
		public:
			/// <summary>
			/// シャドウマップへの描画パスから呼ばれる処理。
			/// </summary>
			/// <param name="rc">レンダリングコンテキスト</param>
			/// <param name="lvpMatrix">ライトビュープロジェクション行列</param>
			virtual void OnRenderShadowMap(
				RenderContext& rc,
				int shadowMapNo,
				const Matrix& lvpMatrix
			)
			{

			}

			/// <summary>
			/// G-Buffer描画パスから呼ばれる処理。
			/// </summary>
			virtual void OnRenderToGBuffer(RenderContext& rc)
			{

			}

			/// <summary>
			/// フォワードレンダーパスから呼ばれる処理。
			/// </summary>
			virtual void OnForwardRender(RenderContext& rc)
			{

			}

			/// <summary>
			/// 2D描画パスから呼ばれる処理。
			/// </summary>
			/// <param name="rc"></param>
			virtual void OnRender2D(RenderContext& rc)
			{

			}

		public:		//ラッパー関数。
			void RenderShadowMapWrapper(
				RenderContext& rc,
				int shadowMapNo,
				const Matrix& lvpMatrix)
			{
				if (m_isActive && m_isStart && !m_isDead && !m_isRegistDeadList && m_isRegistRenderer) {
					OnRenderShadowMap(rc, shadowMapNo, lvpMatrix);
				}
			}
			void RenderToGBufferWrapper(RenderContext& rc)
			{
				if (m_isActive && m_isStart && !m_isDead && !m_isRegistDeadList && m_isRegistRenderer) {
					OnRenderToGBuffer(rc);
				}
			}
			void ForwardRenderWrapper(RenderContext& rc)
			{
				if (m_isActive && m_isStart && !m_isDead && !m_isRegistDeadList && m_isRegistRenderer) {
					OnForwardRender(rc);
				}
			}
			void Render2DWrapper(RenderContext& rc)
			{
				if (m_isActive && m_isRegistRenderer && !m_isDead && !m_isRegistDeadList && m_isRegistRenderer) {
					OnRender2D(rc);
				}
			}
		private:
			bool m_isRegistRenderer = false;		//レンダラーが登録されているか。
		};
	}
}
