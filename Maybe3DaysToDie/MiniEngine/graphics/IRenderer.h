#pragma once

namespace Engine {
	namespace prefab {
		class IRenderer : public IGameObject
		{
		protected:
			virtual ~IRenderer() {};
			bool Start()override final;			//�������֐��B
			void OnDestroy()override final;		//�폜�������B

			/// <summary>
			/// �h����ł̏��������s���֐��B
			/// </summary>
			/// <returns>�������������ǂ����B</returns>
			virtual bool SubStart()
			{
				return true;
			}

			/// <summary>
			/// �h����ł̍폜�����B
			/// </summary>
			virtual void SubOnDestroy()
			{

			}
		public:
			/// <summary>
			/// �V���h�E�}�b�v�ւ̕`��p�X����Ă΂�鏈���B
			/// </summary>
			/// <param name="rc">�����_�����O�R���e�L�X�g</param>
			/// <param name="lvpMatrix">���C�g�r���[�v���W�F�N�V�����s��</param>
			virtual void OnRenderShadowMap(
				RenderContext& rc,
				int shadowMapNo,
				const Matrix& lvpMatrix
			)
			{

			}

			/// <summary>
			/// G-Buffer�`��p�X����Ă΂�鏈���B
			/// </summary>
			virtual void OnRenderToGBuffer(RenderContext& rc)
			{

			}

			/// <summary>
			/// �t�H���[�h�����_�[�p�X����Ă΂�鏈���B
			/// </summary>
			virtual void OnForwardRender(RenderContext& rc)
			{

			}

			/// <summary>
			/// 2D�`��p�X����Ă΂�鏈���B
			/// </summary>
			/// <param name="rc"></param>
			virtual void OnRender2D(RenderContext& rc)
			{

			}

		private:
			bool m_isRegistRenderer = false;		//�����_���[���o�^����Ă��邩�B
		};
	}
}
