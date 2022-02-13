#pragma once
#include "IRenderer.h"
namespace Engine {

	class CRendererManager : Noncopyable
	{
		using RendererArray = std::vector <prefab::IRenderer*>;
	public:
		/// <summary>
		/// �����_���[�}�l�[�W���[���������B
		/// </summary>
		/// <param name="prio">�ő�D��x�B</param>
		void InitRendererManager(unsigned char prio)
		{
			MAX_PRIO = prio;
			m_rendererArrayList.resize(MAX_PRIO);
		}
		/// <summary>
		/// �����_���[�̓o�^���s���B
		/// </summary>
		/// <param name="renderer"></param>
		void RegistRenderer(prefab::IRenderer* renderer)
		{
			int prio = renderer->GetPriority();
			m_rendererArrayList[prio].push_back(renderer);
		}
		/// <summary>
		/// �����_���[�̓o�^����������B
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
		/// �V���h�E�}�b�v�̕`����s���B
		/// </summary>
		/// <param name="rc">�����_�����O�R���e�L�X�g�B</param>
		/// <param name="LVP">���C�g�r���[�v���W�F�N�V�����s��B</param>
		/// <param name="i">�V���h�E�}�b�v�ԍ��B</param>
		void RenderToShadowMap(RenderContext& rc, const Matrix& LVP, int i);

		/// <summary>
		/// GBuffer�ɕ`�悷��B
		/// </summary>
		/// <param name="rc">�����_�����O�R���e�L�X�g�B</param>
		void RenderToGBuffer(RenderContext& rc);

		/// <summary>
		/// �t�H���[�h�����_�[�����s����B
		/// </summary>
		/// <param name="rc">�����_�����O�R���e�L�X�g�B</param>
		void ForwardRender(RenderContext& rc);

		/// <summary>
		/// 2D�`������s����B
		/// </summary>
		/// <param name="rc">�����_�����O�R���e�L�X�g�B</param>
		void Render2D(RenderContext& rc);

	private:
		unsigned char MAX_PRIO = 0;
		std::vector<RendererArray> m_rendererArrayList;		//�����_���[�N���X�̔z�񃊃X�g�B
	};

}
