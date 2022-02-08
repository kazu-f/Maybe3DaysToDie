#include "MiniEngine.h"
#include "IRenderer.h"

namespace Engine {
	namespace prefab
	{
		bool IRenderer::Start()
		{
			//�����_���[�o�^���ς܂���B
			if (!m_isRegistRenderer) {
				GraphicsEngine()->GetRendererManager()->RegistRenderer(this);
				m_isRegistRenderer = true;
			}
			return SubStart();
		}

		void IRenderer::OnDestroy()
		{
			if (m_isRegistRenderer)
			{
				GraphicsEngine()->GetRendererManager()->RemoveRenderer(this);
				m_isRegistRenderer = false;
			}

			SubOnDestroy();
		}


	}
}

