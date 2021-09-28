#pragma once

namespace Engine {
	/// <summary>
	/// �u���[���B
	/// </summary>
	class CBloom : Noncopyable
	{
	public:
		/// <summary>
		/// �������B
		/// </summary>
		/// <param name="config">�O���t�B�b�N�ݒ�B</param>
		void Init(const SPostEffectConfig& config);
		/// <summary>
		/// �`��B
		/// </summary>
		/// <param name="rc">�����_�����O�R���e�L�X�g�B</param>
		/// <param name="postEffect">�|�X�g�G�t�F�N�g�B</param>
		void Render(RenderContext& rc, CPostEffect* postEffect);
		/// <summary>
		/// �d�݂��X�V�B
		/// </summary>
		void UpdateWeight(float dispersion);

	private:	//���������B
		/// <summary>
		/// �����_�����O�^�[�Q�b�g���������B
		/// </summary>
		void InitRenderTargets();
		/// <summary>
		/// �V�F�[�_�[�������B
		/// </summary>
		void InitShaders();
		/// <summary>
		/// �p�C�v���C���X�e�[�g�������B
		/// </summary>
		void InitPipelineState();
		/// <summary>
		/// �f�B�X�N���v�^�q�[�v�̍쐬�B
		/// </summary>
		void CreateDescriptorHeap();

	private:	//�u���[���Ɏg�������B
		/// <summary>
		/// �P�x���o�B
		/// </summary>
		void SamplingLuminance(RenderContext& rc, CPostEffect* postEffect);
		/// <summary>
		/// �P�x�e�N�X�`���Ƀu���[���|����B
		/// </summary>
		void BlurLuminanceTexture(RenderContext& rc, CPostEffect* postEffect);
		/// <summary>
		/// �{�P�摜�������B
		/// </summary>
		/// <param name="rc"></param>
		void CombineBlurImage(RenderContext& rc, CPostEffect* postEffect);
		/// <summary>
		/// ���C�������_�����O�^�[�Q�b�g�ւ̍����B
		/// </summary>
		void CombineMainRenderTarget(RenderContext& rc, CPostEffect* postEffect);

	private:
		static const int NUM_WEIGHTS = 8;			//�d�ݕt�����鐔�B
		static const int NUM_DOWN_SAMPRING_RT = 10;		//�_�E���T���v�����O���鐔�B(�c�Ɖ������邽�߃_�E���T���v�����O�������� * 2)
		/// <summary>
		/// �u���[�p�̃p�����[�^�B
		/// </summary>
		struct SBlurParam {
			Vector4 offset;
			float weights[NUM_WEIGHTS];
		};
		RootSignature m_rootSignature;		//�u���[���`��p�̃��[�g�V�O�l�`���B
		//�p�C�v���C���X�e�[�g
		PipelineState m_samplingLuminancePipelineState;			//�P�x���o�p
		PipelineState m_xblurLuminancePipelineState;			//x�����ɋP�x���ڂ����X�e�b�v�̃p�C�v���C���X�e�[�g�B
		PipelineState m_yblurLuminancePipelineState;			//y�����ɋP�x���ڂ����X�e�b�v�̃p�C�v���C���X�e�[�g�B
		PipelineState m_combineBlurImagePipelineState;			//�{�P�摜����������X�e�b�v�̃p�C�v���C���X�e�[�g�B
		PipelineState m_combineMainRenderTargetPipelineState;	//���C�������_�����O�^�[�Q�b�g�ւ̍����X�e�b�v�̃p�C�v���C���X�e�[�g�B
		//�����_�����O�^�[�Q�b�g�B
		RenderTarget m_luminanceRT;								//�P�x�𒊏o���邽�߂̃����_�����O�^�[�Q�b�g�B
		RenderTarget m_combineRT;								//�ڂ��������p�̃����_�����O�^�[�Q�b�g�B
		RenderTarget m_downSamplingRT[NUM_DOWN_SAMPRING_RT];	//�_�E���T���v�����O�p�̃����_�����O�^�[�Q�b�g�B
		//�u���[�p�̃p�����[�^�B
		SBlurParam m_blurParam;									//�u���[�p�̃p�����[�^�B
		//�V�F�[�_�[�B
		Shader m_vs;											//�����̒��_�V�F�[�_�[�B
		Shader m_psLuminance;									//�P�x���o�p�X�̃s�N�Z���V�F�[�_�[�B
		Shader m_vsXBlur;										//X�����u���[�p�X�̒��_�V�F�[�_�[�B
		Shader m_vsYBlur;										//Y�����u���[�p�X�̒��_�V�F�[�_�[�B
		Shader m_psBlur;										//X�����u���[/Y�����u���[�p�X�̃s�N�Z���V�F�[�_�[�B
		Shader m_psCombine;										//�{�P�����p�X�̃s�N�Z���V�F�[�_�[�B
		//�u���[�p�̒萔�o�b�t�@�B
		ConstantBuffer m_blurParamCB[NUM_DOWN_SAMPRING_RT];		//�u���[�p�̒萔�o�b�t�@�B
		//�f�B�X�N���v�^�q�[�v�B
		DescriptorHeap m_sampleLuminanceDescriptorHeap;			//�P�x���o���Ɏg�p����f�B�X�N���v�^�q�[�v�B
		DescriptorHeap m_combineBlurDescriptorHeap;				//�{�P�����Ɏg�p����f�B�X�N���v�^�q�[�v�B
		DescriptorHeap m_downSampleDescriptorHeap[NUM_DOWN_SAMPRING_RT];	//�_�E���T���v�����O�p�̃f�B�X�N���v�^�q�[�v�B
		DescriptorHeap m_combineMainRenderTargetDescriptorHeap;	//���C�������_�����O�^�[�Q�b�g�ւ̍����Ɏg�p����f�B�X�N���v�^�q�[�v�B
		bool m_isEnable = false;
	};

}
