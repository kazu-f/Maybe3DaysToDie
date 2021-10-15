#pragma once
#include "graphics/Primitive.h"

/*
	�f�B�t�@�[�h�����_�����O���s���N���X�B
*/

namespace Engine {

	class CGBufferRender;

	class CDefferdShading : Noncopyable
	{
	public:
		CDefferdShading() {};
		~CDefferdShading() {};

		void Init();
		/// <summary>
		/// �f�B�t�@�[�h�����_�����O���s���B
		/// </summary>
		void Render(RenderContext& rc);
		/// <summary>
		/// �L���[�u�}�b�v��ݒ肷��B
		/// </summary>
		/// <param name="tex"></param>
		void SetCubeMapTexture(Texture& tex)
		{
			m_cubeMapTexture.InitFromD3DResource(tex.Get());
			//�f�B�X�N���v�^�q�[�v����蒼���B
			CreateDescriptorHeap();
		}

	private:
		/// <summary>
		/// �l�p�`�v���~�e�B�u�̍쐬�B
		/// </summary>
		void InitPrimitive();
		/// <summary>
		/// �V�F�[�_�[�̏������B
		/// </summary>
		void InitShader();
		/// <summary>
		/// �p�C�v���C���X�e�[�g�̏������B
		/// </summary>
		void InitPipelineState();
		/// <summary>
		/// �萔�o�b�t�@�̏������B
		/// </summary>
		void InitConstantBuffer();
		/// <summary>
		/// �f�B�X�N���v�^�q�[�v�̍쐬�B
		/// </summary>
		void CreateDescriptorHeap();

	private:
		//�f�B�t�@�[�h�̒萔�o�b�t�@�\���́B
		struct SDefferdCB
		{
			Matrix mViewProjInv;					//�r���[�v���W�F�N�V�����s��̋t�s��B
		};

		CPrimitive m_primitive;						//�l�p�`�v���~�e�B�u�B
		Shader m_vsDefferd;							//�f�B�t�@�[�h�̒��_�V�F�[�_�[�B
		Shader m_psDefferd;							//�f�B�t�@�[�h�̃s�N�Z���V�F�[�_�[�B
		PipelineState m_defferdPipelineState;		//�p�C�v���C���X�e�[�g�B
		DescriptorHeap m_defferdDescriptorHeap;		//�f�B�X�N���v�^�q�[�v�B
		ConstantBuffer m_constantBuffer;			//�萔�o�b�t�@�B
		Texture m_cubeMapTexture;		//�e�N�X�`���B
	};

}

