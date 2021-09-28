#pragma once

namespace Engine {


	class CTonemap : Noncopyable
	{
	public:
		void Init(const SPostEffectConfig& config);


	public:
		/// <summary>
		/// ���ϋP�x�̌v�Z�B
		/// </summary>
		/// <param name="rc">�����_�����O�R���e�L�X�g�B</param>
		void CalcLuminanceAverage(RenderContext& rc, CPostEffect* postEffect);
		/// <summary>
		/// �g�[���}�b�v�̎��s�B
		/// <para>�g�[���}�b�v�̏����̑O��CalcLuminanceAverage�����s���ĕ��ϋP�x�̌v�Z���s���K�v������B</para>
		/// <para>���ϋP�x�̌v�Z�̓|�X�g�G�t�F�N�g�̐擪�ōs���B</para>
		/// </summary>
		/// <param name="rc">�����_�����O�R���e�L�X�g�B</param>
		/// <param name="postEffect">�|�X�g�G�t�F�N�g�B</param>
		void Render(RenderContext& rc,CPostEffect* postEffect);
		/// <summary>
		/// �g�[���}�b�v�̏��������Z�b�g�B
		/// <para>�P�x���傫���ς��V�[���؂�ւ��Ȃǂ���������ꍇ�ȂǂɁA</para>
		/// <para>���Ï�������������������ꍇ�����邽�߁A</para>
		/// <para>���̂悤�ȏꍇ�Ƀ��Z�b�g���s���B</para>
		/// </summary>
		void Reset()
		{
			m_isFirstWhenChangeScene = true;
		}
		/// <summary>
		/// ���邳��ݒ�B
		/// </summary>
		/// <param name="lum">���邳�B���̒l��傫������Ɩ��邭�Ȃ�B</param>
		void SetLuminance(float lum)
		{
			m_tonemapParam.middleGray = lum;
		}
		/// <summary>
		/// �g�[���}�b�v�̗L��������ݒ�B
		/// </summary>
		void SetEnable(bool flag)
		{
			m_isEnable = flag;
		}
	private:
		/// <summary>
		/// �����_�����O�^�[�Q�b�g�̍쐬�B
		/// </summary>
		void CreateRenderTargets();
		/// <summary>
		/// �V�F�[�_�[�̏������B
		/// </summary>
		void InitShader();
		/// <summary>
		/// �p�C�v���C���X�e�[�g�̍쐬�B
		/// </summary>
		void InitPipelineState();
		/// <summary>
		/// �萔�o�b�t�@�̍쐬�B
		/// </summary>
		void CreateConstantBuffer();
		/// <summary>
		/// �f�B�X�N���v�^�q�[�v�̍쐬�B
		/// </summary>
		void CreateDescriptorHeap();

	public:
		static const int MAX_SAMPLES = 16;
	private:
		struct STonemapParam {
			float deltaTime;
			float middleGray;
		};
		static const	int NUM_CALC_AVG_RT = 5;			//���ϋP�x�v�Z�Ɏg�������_�����O�^�[�Q�b�g�̖����B
		RenderTarget	m_calcAvgRT[NUM_CALC_AVG_RT];		//���ϋP�x�v�Z�p�̃����_�����O�^�[�Q�b�g�B
		RenderTarget	m_avgRT[2];							//���ϋP�x���i�[����郌���_�����O�^�[�Q�b�g�B
		int				m_currentAvgRT = 0;					//���ݎg���Ă��郌���_�����O�^�[�Q�b�g�̔ԍ��B
		RootSignature	m_rootSignature;					//���[�g�V�O�l�`���B
		Shader			m_vsShader;							//���_�V�F�[�_�[�B
		Shader			m_psCalcLuminanceLogAverage;		//�P�x�̑ΐ����ς����߂�s�N�Z���V�F�[�_�[�B
		Shader			m_psCalcLuminanceAverage;			//�P�x�̕��ς����߂�s�N�Z���V�F�[�_�[�B
		Shader			m_psCalcLuminanceExpAverage;		//�P�x�̎w�����ς����߂�s�N�Z���V�F�[�_�[�B
		Shader			m_psCalcAdaptedLuminance;			//���Ï����̃s�N�Z���V�F�[�_�[�B
		Shader			m_psCalcAdaptedLuminanceFirst;		//���Ï����̃s�N�Z���V�F�[�_�[�B(�V�[�����؂�ւ�������Ɏg�p�����B)
		Shader			m_psFinal;							//�ŏI�����V�F�[�_�[�B
		PipelineState	m_calcLumionanceLogAveragePipelineState;		//�P�x�̑ΐ����ς����߂�p�C�v���C���X�e�[�g�B
		PipelineState	m_calcLuminanceAveragePipelineState;			//�P�x�̕��ς����߂�p�C�v���C���X�e�[�g�B
		PipelineState	m_calcLuminanceExpAveragePipelineState;			//�P�x�̎w�����ς����߂�p�C�v���C���X�e�[�g�B
		PipelineState	m_calcAdaptedLuminancePipelineState;			//���Ï����̂��߂̃p�C�v���C���X�e�[�g�B
		PipelineState	m_calcAdaptedLuminanceFirstPipelineState;		//���Ï����̂��߂̃p�C�v���C���X�e�[�g�B(�V�[�����؂�ւ�������Ɏg�p�����B)
		PipelineState	m_finalPipelineState;							//�ŏI�`��̃p�C�v���C���X�e�[�g�B
		DescriptorHeap	m_calcAvgDescriptorHeap[NUM_CALC_AVG_RT];		//���ϋP�x�v�Z�p�̃f�B�X�N���v�^�q�[�v�B
		DescriptorHeap	m_calcAdaptedLuminanceDescriptorHeap[2];		//���Ï����p�̃f�B�X�N���v�^�q�[�v�B
		DescriptorHeap	m_finalDescriptorHeap[2];						//�ŏI�`��̃f�B�X�N���v�^�q�[�v�B
		bool			m_isFirstWhenChangeScene = true;	//�V�[�����؂�ւ���ď���̕`�悩�ǂ����̃t���O�B
		Vector4			m_avSampleOffsets[MAX_SAMPLES];
		ConstantBuffer	m_cbCalcLuminanceLog[NUM_CALC_AVG_RT];				//�P�x�̕��ϑΐ������߂邽�߂̒萔�o�b�t�@�B
		ConstantBuffer	m_cbTonemapCommon;					//�g�[���}�b�v���ʂ̒萔�o�b�t�@�B
		STonemapParam	m_tonemapParam;
		bool			m_isEnable = false;					//�g�[���}�b�v�L�����t���O�B
	};//class CTonemap;

}//namespace Engine;

