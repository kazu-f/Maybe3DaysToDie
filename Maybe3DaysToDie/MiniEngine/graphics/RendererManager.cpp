#include "MiniEngine.h"
#include "RendererManager.h"

namespace Engine {
	void CRendererManager::RenderToShadowMap(RenderContext& rc, const Matrix& LVP, int i)
	{
		//レンダラーをシャドウマップに書き込む。
		for (auto& list : m_rendererArrayList)
		{
			for (auto* renderer : list)
			{
				renderer->OnRenderShadowMap(rc, i, LVP);
			}
		}
	}

	void CRendererManager::RenderToGBuffer(RenderContext& rc)
	{
		//レンダラーをGBufferに書き込む。
		for (auto& list : m_rendererArrayList)
		{
			for (auto* renderer : list)
			{
				renderer->OnRenderToGBuffer(rc);
			}
		}
	}

	void CRendererManager::ForwardRender(RenderContext& rc)
	{
		//フォワードレンダー。
		for (auto& list : m_rendererArrayList)
		{
			for (auto* renderer : list)
			{
				renderer->OnForwardRender(rc);
			}
		}
	}
	
	void CRendererManager::Render2D(RenderContext& rc)
	{
		//2D描画
		for (auto& list : m_rendererArrayList)
		{
			for (auto* renderer : list)
			{
				renderer->OnRender2D(rc);
			}
		}
	}
}
