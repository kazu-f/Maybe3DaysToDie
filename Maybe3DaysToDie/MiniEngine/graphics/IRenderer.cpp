#include "MiniEngine.h"
#include "IRenderer.h"

namespace Engine {
	namespace prefab
	{
		bool IRenderer::Start()
		{
			//ƒŒƒ“ƒ_ƒ‰[“o˜^‚ðÏ‚Ü‚¹‚éB
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

