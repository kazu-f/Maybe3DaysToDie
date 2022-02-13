#include "MiniEngine.h"
#include "SpriteRender.h"

namespace Engine {
	namespace prefab {
		bool CSpriteRender::SubStart()
		{
			//�������ς݁H
			return m_isInited;
		}

		void CSpriteRender::Update()
		{
			//�X�v���C�g�̍X�V�B
			m_sprite.Update(m_position, m_rotation, m_scale, m_pivot);
		}

		void CSpriteRender::Init(const char* FilePath, float w, float h, bool isDraw3D)
		{
			//�������f�[�^���쐬����B
			SpriteInitData spriteData;
			spriteData.m_fxFilePath = Sprite::SPRITE_SHADER_PATH;
			spriteData.m_ddsFilePath[0] = FilePath;
			spriteData.m_width = static_cast<UINT>(w);
			spriteData.m_height = static_cast<UINT>(h);
			spriteData.m_colorBufferFormat[0] = DXGI_FORMAT_R32G32B32A32_FLOAT;
			m_sprite.Init(spriteData,isDraw3D);
			m_isDraw3D = isDraw3D;
			m_isInited = true;				//�������ς݁B
		}

		void CSpriteRender::OnForwardRender(RenderContext& rc)
		{
			//3D��Ԃŕ`�悷��B
			if (m_isDraw3D) {
				m_sprite.Draw(rc, MainCamera().GetViewMatrix(), MainCamera().GetProjectionMatrix());
			}
		}

		void CSpriteRender::OnRender2D(RenderContext& rc)
		{
			//2D�`�������B
			if (!m_isDraw3D)
			{
				m_sprite.Draw(rc, MainCamera2D().GetViewMatrix(), MainCamera2D().GetProjectionMatrix());
			}
		}

	}//namespace prefab

}//namespace Engine
