#include "MiniEngine.h"
#include "RendererManager.h"

namespace Engine {
	void CRendererManager::RenderToShadowMap(RenderContext& rc, const Matrix& LVP, int i)
	{
		//�����_���[���V���h�E�}�b�v�ɏ������ށB
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
		//�����_���[��GBuffer�ɏ������ށB
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
		//�t�H���[�h�����_�[�B
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
		//2D�`��
		for (auto& list : m_rendererArrayList)
		{
			for (auto* renderer : list)
			{
				renderer->OnRender2D(rc);
			}
		}
	}
}
