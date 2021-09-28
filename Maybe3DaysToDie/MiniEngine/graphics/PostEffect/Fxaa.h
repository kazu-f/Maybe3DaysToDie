#pragma once
/*
*	FXAA
*/

namespace Engine {
	class CPostEffect;
	/// <summary>
	/// FXAA
	/// �|�X�g�G�t�F�N�g�ɂ��A���`�G�C���A�X���s���B
	/// </summary>
	class CFxaa : Noncopyable
	{
	public:
		/// <summary>
		/// �������B
		/// </summary>
		/// <param name="config">�R���t�B�O</param>
		void Init(const SPostEffectConfig& config);
		/// <summary>
		/// �A���`���s�B
		/// </summary>
		/// <param name="rc">�����_�����O�R���e�L�X�g�B</param>
		/// <param name="postEffect">�|�X�g�G�t�F�N�g�B</param>
		void Render(RenderContext& rc, CPostEffect* postEffect);
	private:
		/// <summary>
		/// �V�F�[�_�[�̏������B
		/// </summary>
		void InitShader();
		/// <summary>
		/// �p�C�v���C���X�e�[�g�̍쐬�B
		/// </summary>
		void InitPipelineState();
		/// <summary>
		/// �����_�����O�^�[�Q�b�g�̍쐬�B
		/// </summary>
		void InitRenderTarget();
		/// <summary>
		/// �f�B�X�N���v�^�q�[�v�̍쐬�B
		/// </summary>
		void CreateDescriptorHeap();
	private:
		/// <summary>
		/// �A���`�G�C���A�X���|����B
		/// </summary>
		/// <param name="rc">�����_�����O�R���e�L�X�g�B</param>
		/// <param name="postEffect">�|�X�g�G�t�F�N�g�B</param>
		void Fxaa(RenderContext& rc, CPostEffect* postEffect);
		/// <summary>
		/// ���C�������_�����O�^�[�Q�b�g�ɑ΂��čŏI�`��B
		/// </summary>
		/// <param name="rc">�����_�����O�R���e�L�X�g�B</param>
		/// <param name="postEffect">�|�X�g�G�t�F�N�g�B</param>
		void FinalDraw(RenderContext& rc, CPostEffect* postEffect);
	private:
		RenderTarget m_fxaaRenderTarget;		//�A���`���|�������̂��������ރ����_�����O�^�[�Q�b�g�B
		Shader m_vsShader;						//�����̒��_�V�F�[�_�[�B
		Shader m_psShader;						//�A���`�p�s�N�Z���V�F�[�_�[�B
		RootSignature m_rootSignature;			//���[�g�V�O�l�`���B
		PipelineState m_fxaaPipelineState;		//�A���`�G�C���A�X�p�p�C�v���C���X�e�[�g�B
		DescriptorHeap m_fxaaDescriptorHeap;	//�A���`�G�C���A�X�p�f�B�X�N���v�^�q�[�v�B
		DescriptorHeap m_copyDescriptorHeap;	//���C�������_�����O�^�[�Q�b�g�ɃR�s�[���邽�߂̃f�B�X�N���v�^�q�[�v�B
		bool m_isEnable = false;
	};//class Fxaa;

}///namespace Engine;

