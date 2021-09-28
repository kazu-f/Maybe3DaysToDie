#pragma once
#include "graphics/Material.h"

namespace Engine {
	/// <summary>
	/// ���[�U�[�w��̃V�F�[�_�[�̃}�e���A���B
	/// </summary>
	class UserMaterial : public IMaterial {
	public:
		/// <summary>
		/// tkm�t�@�C���̃}�e���A����񂩂珉��������B
		/// </summary>
		/// <param name="tkmMat">tkm�}�e���A��</param>
		void InitFromTkmMaterila(
			const TkmFile::SMaterial& tkmMat,
			const SShaderInitData& shaderData) override final;
		/// <summary>
		/// �����_�����O���J�n����Ƃ��ɌĂяo���֐��B
		/// </summary>
		/// <param name="rc">�����_�����O�R���e�L�X�g</param>
		/// <param name="maxInstance">�C���X�^���X�̐�</param>
		void BeginRender(RenderContext& rc, int maxInstance = 1) override final;
	private:
		/// <summary>
		/// �V�F�[�_�[�̏������B
		/// </summary>
		/// <param name="fxFilePath">fx�t�@�C���̃t�@�C���p�X</param>
		/// <param name="vsEntryPointFunc">���_�V�F�[�_�[�̃G���g���[�|�C���g�̊֐���</param>
		/// <param name="psEntryPointFunc">�s�N�Z���V�F�[�_�[�̃G���g���[�|�C���g�̊֐���</param>
		void InitShaders(const SShaderInitData& shaderData);
		/// <summary>
		/// �p�C�v���C���X�e�[�g�̏������B
		/// </summary>
		void InitPipelineState();

	private:
		RootSignature m_rootSignature;					//���[�g�V�O�l�`���B
		PipelineState m_ModelPipelineState;				//���f���p�̃p�C�v���C���X�e�[�g�B
		PipelineState m_transModelPipelineState;		//���f���p�̃p�C�v���C���X�e�[�g(�������}�e���A��)�B

		Shader m_vsModel;								//���f���p�̒��_�V�F�[�_�[�B
		Shader m_psModel;								//���f���p�̃s�N�Z���V�F�[�_�[�B
		Shader m_psTransModel;							//�������̃��f���p�̃s�N�Z���V�F�[�_�[�B
	};///class UserMaterial;

}///namespace Engine;

