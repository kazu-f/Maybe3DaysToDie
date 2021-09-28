#pragma once

namespace Engine {
	/// <summary>
	/// �悭�g���p�C�v���C���X�e�[�g���܂Ƃ߂�B
	/// </summary>
	class CPipelineStatesDefault
	{
	public://�V�F�[�_�[�̃t�@�C���p�X���B
		static const wchar_t* MODEL_SHADER_PATH;						//���f���V�F�[�_�[�̃t�@�C���p�X�B
		static const char* VS_MODEL_ENTRY_POINT;						//�ʏ탂�f���̒��_�V�F�[�_�[�B
		static const char* VS_MODELINSTANCING_ENTRY_POINT;				//�C���X�^���V���O���f���̒��_�V�F�[�_�[�B
		static const char* VS_SKINMODEL_ENTRY_POINT;					//�X�L�����f���̒��_�V�F�[�_�[�B
		static const char* VS_SKINMODELINTANCING_ENTRY_POINT;			//�X�L������C���X�^���V���O���f���̒��_�V�F�[�_�[�B
		static const char* VS_MODEL_SHADOW_ENTRY_POINT;					//�V���h�E�}�b�v�p���_�V�F�[�_�[�B
		static const char* VS_MODEL_SHADOWINSTANCING_ENTRY_POINT;		//�V���h�E�}�b�v�E�C���X�^���V���O���f���p���_�V�F�[�_�[�B
		static const char* VS_SKINMODEL_SHADOW_ENTRY_POINT;				//�V���h�E�}�b�v�E�X�L�����胂�f���p���_�V�F�[�_�[�B
		static const char* VS_SKINMODEL_SHADOWINSTANCING_ENTRY_POINT;	//�V���h�E�}�b�v�E�X�L������C���X�^���V���O���f���p���_�V�F�[�_�[�B
		static const char* PS_GBUFFER_ENTRY_POINT;						//G-Bffer�ɏ������ރs�N�Z���V�F�[�_�[�B
		static const char* PS_SHADOW_ENTRY_POINT;						//�V���h�E�}�b�v�ɏ������ރs�N�Z���V�F�[�_�[�B
		static const char* PS_TRANS_ENTRY_POINT;						//�t�H���[�h�p���_�V�F�[�_�[�B

		static const wchar_t* COPY_SHADER_PATH;							//�R�s�[�p�V�F�[�_�[�̃t�@�C���p�X�B
		static const char* VS_COPY_ENTRY_POINT;							//�R�s�[�p���_�V�F�[�_�[�B
		static const char* PS_COPY_ENTRY_POINT;							//�R�s�[�p�s�N�Z���V�F�[�_�[�B

	public://���f���p�̐ݒ�B
		static RootSignature m_modelDrawRootSignature;			//���f���`��p�̃��[�g�V�O�l�`���B
		static Shader m_vsModel;								//���f���p�̒��_�V�F�[�_�[�B
		static Shader m_vsModelInstancing;						//�C���X�^���V���O���f���p�̒��_�V�F�[�_�[�B
		static Shader m_vsSkinModel;							//���f���p�̒��_�V�F�[�_�[�B(�X�L������)
		static Shader m_vsSkinModelInstancing;					//�C���X�^���V���O���f���p�̒��_�V�F�[�_�[�B(�X�L������)
		static Shader m_psModel;								//���f���p�̃s�N�Z���V�F�[�_�[�B(G-Buffer�������݁B)
		static Shader m_vsModelShadowMap;						//�V���h�E�}�b�v�̃��f���p�̒��_�V�F�[�_�[�B
		static Shader m_vsModelShadowInstancing;				//�V���h�E�}�b�v�̃C���X�^���X���f���p�B
		static Shader m_vsSkinModelShadowMap;					//�V���h�E�}�b�v�̃��f���p�̒��_�V�F�[�_�[�B(�X�L������)
		static Shader m_vsSkinModelShadowInstancing;			//�V���h�E�}�b�v�̃C���X�^���X���f���p�B(�X�L������)
		static Shader m_psModelShadowMap;						//�V���h�E�}�b�v�̃��f���p�̃s�N�Z���V�F�[�_�[�B
		static Shader m_psTransModel;							//�������̃��f���p�̃s�N�Z���V�F�[�_�[�B

		static PipelineState m_ModelPipelineState;				//���f���p�̃p�C�v���C���X�e�[�g�B
		static PipelineState m_ModelInstancingPipelineState;	//�C���X�^���V���O���f���p�̃p�C�v���C���X�e�[�g�B
		static PipelineState m_SkinModelPipelineState;			//���f���p�̃p�C�v���C���X�e�[�g�B(�X�L������)
		static PipelineState m_SkinModelInstancingPipelineState;//�C���X�^���V���O���f���p�̃p�C�v���C���X�e�[�g�B(�X�L������)
		static PipelineState m_transModelPipelineState;			//���f���p�̃p�C�v���C���X�e�[�g(�������}�e���A��)�B
		static PipelineState m_transSkinModelPipelineState;			//���f���p�̃p�C�v���C���X�e�[�g(�������}�e���A��)�B(�X�L������)
		static PipelineState m_transModelInstancingPipelineState;			//�C���X�^���V���O���f���p�̃p�C�v���C���X�e�[�g(�������}�e���A��)�B
		static PipelineState m_transSkinModelInstancingPipelineState;			//�C���X�^���V���O���f���p�̃p�C�v���C���X�e�[�g(�������}�e���A��)�B(�X�L������)
		static PipelineState m_ModelShadowPipelineState;		//�V���h�E�}�b�v�̃��f���p�̃p�C�v���C���X�e�[�g�B
		static PipelineState m_ModelShadowInstancingPipelineState;		//�V���h�E�}�b�v�̃C���X�^���X���f���p�B
		static PipelineState m_SkinModelShadowPipelineState;		//�V���h�E�}�b�v�̃��f���p�̃p�C�v���C���X�e�[�g�B(�X�L������)
		static PipelineState m_SkinModelShadowInstancingPipelineState;		//�V���h�E�}�b�v�̃C���X�^���X���f���p�B(�X�L������)

	public:	//�R�s�[�p�B
		static Shader m_vsCopy;									//�R�s�[�p�̒��_�V�F�[�_�[�B
		static Shader m_psCopy;									//�R�s�[�p�̃s�N�Z���V�F�[�_�[�B

		static RootSignature m_copyRootSignature;				//�R�s�[�p�̃��[�g�V�O�l�`���B
		static PipelineState m_copyPipelineState;				//�R�s�[�p�p�C�v���C���X�e�[�g�B

	public:
		/// <summary>
		/// ���������s���B
		/// </summary>
		static void Init();
	private:
		//�V�F�[�_�[�̏������B
		static void InitShaders();
		//���[�g�V�O�l�`���̏������B
		static void InitRootSignature();
		//���f���p�p�C�v���C���X�e�[�g�������B
		static void InitModelPipelineState();
		//�R�s�[�p�p�C�v���C���X�e�[�g�������B
		static void InitCopyPipelineState();

	};///class CPipelineStatesDefault;

}///namespace Engine;
