#pragma once

#include "graphics/Primitive.h"
#include "Tonemap.h"
#include "Bloom.h"
#include "Fxaa.h"

namespace Engine {
	/// <summary>
	/// �|�X�g�G�t�F�N�g�B
	/// </summary>
	class CPostEffect : Noncopyable
	{
	public:
		/// <summary>
		/// �R���X�g���N�^�B
		/// </summary>
		CPostEffect();
		/// <summary>
		/// �f�X�g���N�^�B
		/// </summary>
		~CPostEffect();
		/// <summary>
		/// �J���B
		/// </summary>
		void Release();
		/// <summary>
		/// �쐬�B
		/// </summary>
		/// <param name="config">�R���t�B�O�B</param>
		void Create(const SPostEffectConfig& config);
		/// <summary>
		/// �`��B
		/// </summary>
		/// <param name="rc">�����_�����O�R���e�L�X�g�B</param>
		void Render(RenderContext& rc);
	public:
		/// <summary>
		/// �t���X�N���[���`��B
		/// </summary>
		/// <param name="rc">�����_�����O�R���e�L�X�g�B</param>
		void DrawFullScreenQuad(RenderContext& rc);

	public:
		/// <summary>
		/// �g�[���}�b�v�̎擾�B
		/// </summary>
		CTonemap& GetTonemap()
		{
			return m_tonemap;
		}

	private:
		/// <summary>
		/// �v���~�e�B�u���������B
		/// </summary>
		void InitPrimitive();

	private:
		CTonemap m_tonemap;
		CBloom m_bloom;				//�u���[���B
		CFxaa m_fxaa;				//�A���`�G�C���A�X�B
		CPrimitive m_quadPrimitive;	//�l�p�`�v���~�e�B�u�B
	};

}
