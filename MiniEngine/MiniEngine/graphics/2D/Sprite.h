#pragma once

#include "graphics/GPUBuffer/Indexbuffer.h"
#include "graphics/GPUBuffer/VertexBuffer.h"
#include "graphics/GPUBuffer/ConstantBuffer.h"
#include "graphics/DescriptorHeap.h"

namespace Engine {
	class Texture;

	//�X�v���C�g�ɐݒ�ł���ő�e�N�X�`�����B
	const int MAX_TEXTURE = 16;
	//�g��SRV���ݒ肳��郌�W�X�^�̊J�n�ԍ��B
	const int EXPAND_SRV_REG__START_NO = 10;

	class IShaderResource;

	template< class TExpandData > struct SpriteExpandDataInfo {
		TExpandData* m_expandData = nullptr;
		int m_expandDataSize = 0;
	};
	/// <summary>
	/// �X�v���C�g�̏������f�[�^�B
	/// </summary>
	struct SpriteInitData {
		const char* m_ddsFilePath[MAX_TEXTURE] = { nullptr };		//DDS�t�@�C���̃t�@�C���p�X�B
		Texture* m_textures[MAX_TEXTURE] = { nullptr };			//�g�p����e�N�X�`���BDDS�t�@�C���̃p�X���w�肳��Ă���ꍇ�́A���̃p�����[�^�͖�������܂��B
		const char* m_vsEntryPointFunc = "VSMain";				//���_�V�F�[�_�[�̃G���g���[�|�C���g�B
		const char* m_psEntryPoinFunc = "PSMain";				//�s�N�Z���V�F�[�_�[�̃G���g���[�|�C���g�B
		const char* m_fxFilePath = nullptr;						//.fx�t�@�C���̃t�@�C���p�X�B
		UINT m_width = 0;										//�X�v���C�g�̕��B
		UINT m_height = 0;										//�X�v���C�g�̍����B
		bool m_isAlpha = true;									//���u�����f�B���O�L���H
		void* m_expandConstantBuffer = nullptr;					//���[�U�[�g���̒萔�o�b�t�@
		int m_expandConstantBufferSize = 0;						//���[�U�[�g���̒萔�o�b�t�@�̃T�C�Y�B
		IShaderResource* m_expandShaderResoruceView = nullptr;	//���[�U�[�g���̃V�F�[�_�[���\�[�X�B
	};
	/// <summary>
	/// �X�v���C�g�N���X�B
	/// </summary>
	class Sprite {
	public:
		static const Vector2	DEFAULT_PIVOT;					//!<�s�{�b�g�B
		static const char* SPRITE_SHADER_PATH;					//!<�X�v���C�g�̃V�F�[�_�[�̃t�@�C���p�X�B
		~Sprite();
		/// <summary>
		/// �������B
		/// </summary>
		/// <param name="initData">�������f�[�^</param>
		void Init(const SpriteInitData& initData, bool isDraw3D = false);
		/// <summary>
		/// �X�V�B
		/// </summary>
		/// <param name="pos">���W</param>
		/// <param name="rot">��]</param>
		/// <param name="scale">�g�嗦</param>
		/// <param name="pivot">
		/// �s�{�b�g
		/// 0.5, 0.5�ŉ摜�̒��S����_�B
		/// 0.0, 0.0�ŉ摜�̍����B
		/// 1.0, 1.0�ŉ摜�̉E��B
		/// Unity��uGUI�ɏ����B
		/// </param>
		void Update(const Vector3& pos, const Quaternion& rot, const Vector3& scale, const Vector2& pivot = DEFAULT_PIVOT);
		/// <summary>
		/// �`��B
		/// </summary>
		/// <param name="renderContext">�����_�����O�R���e�L�X�g</param>
		/// <param name="viewMat">�r���[�s��B</param>
		/// <param name="projMat">�v���W�F�N�V�����s��B</param>
		void Draw(RenderContext& renderContext, const Matrix& viewMat, const Matrix& projMat);
	public:		//Set�֐��B
		void SetMulColor(const Vector4& col)
		{
			m_mulColor = col;
		}
		/// <summary>
		/// �f�B�X�N���v�^�q�[�v���������B
		/// </summary>
		/// <param name="initData"></param>
		void InitDescriptorHeap(const SpriteInitData& initData);

	private:
		/// <summary>
		/// �e�N�X�`�����������B
		/// </summary>
		/// <param name="initData"></param>
		void InitTextures(const SpriteInitData& initData);
		/// <summary>
		/// �V�F�[�_�[���������B
		/// </summary>
		/// <param name="initData"></param>
		void InitShader(const SpriteInitData& initData);
		/// <summary>
		/// ���_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@���������B
		/// </summary>
		/// <param name="initData"></param>
		void InitVertexBufferAndIndexBuffer(const SpriteInitData& initData);
		/// <summary>
		/// �p�C�v���C���X�e�[�g������������B
		/// </summary>
		void InitPipelineState(bool isDraw3D, bool isAlpha);
		/// <summary>
		/// �萔�o�b�t�@���������B
		/// </summary>
		/// <param name="initData"></param>
		void InitConstantBuffer(const SpriteInitData& initData);
	private:
		IndexBuffer m_indexBuffer;			//�C���f�b�N�X�o�b�t�@�B
		VertexBuffer m_vertexBuffer;		//���_�o�b�t�@�B
		int m_numTexture = 0;				//�e�N�X�`���̖����B
		Texture m_textures[MAX_TEXTURE];	//�e�N�X�`���B
		Texture* m_textureExternal[MAX_TEXTURE] = { nullptr };	//�O������w�肳�ꂽ�e�N�X�`��
		Vector3 m_position;				//���W�B
		Vector2 m_size;						//�T�C�Y�B
		Vector4 m_mulColor = Vector4::White;	//��Z�J���[�B
		Quaternion m_rotation;			//��]�B
		Matrix m_world;					//���[���h�s��B

		struct LocalConstantBuffer {
			Matrix mvp;
			Vector4 mulColor;
			Vector4 screenParam;
		};
		LocalConstantBuffer m_constantBufferCPU;	//CPU���̒萔�o�b�t�@�B
		ConstantBuffer		m_constantBufferGPU;	//GPU���̒萔�o�b�t�@�B
		ConstantBuffer		m_userExpandConstantBufferGPU;	//���[�U�[�g���̒萔�o�b�t�@(GPU��)
		void* m_userExpandConstantBufferCPU = nullptr;		//���[�U�[�g���̒萔�o�b�t�@(CPU��)
		DescriptorHeap		m_descriptorHeap;		//�f�B�X�N���v�^�q�[�v�B
		RootSignature		m_rootSignature;		//���[�g�V�O�l�`���B
		PipelineState		m_pipelineState;		//�p�C�v���C���X�e�[�g�B
		Shader				m_vs;					//���_�V�F�[�_�[�B
		Shader				m_ps;					//�s�N�Z���V�F�[�_�[�B
	};
}