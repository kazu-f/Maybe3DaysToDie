#pragma once

#include "tkFile/TkmFile.h"


namespace Engine {
	/// <summary>
	/// �}�e���A���B
	/// </summary>
	class IMaterial {
	public:
		virtual ~IMaterial() {};
		/// <summary>
		/// tkm�t�@�C���̃}�e���A����񂩂珉��������B
		/// </summary>
		/// <param name="tkmMat">tkm�}�e���A��</param>
		virtual void InitFromTkmMaterila(
			const TkmFile::SMaterial& tkmMat,
			const SShaderInitData& shaderData);
		/// <summary>
		/// �����_�����O���J�n����Ƃ��ɌĂяo���֐��B
		/// </summary>
		/// <param name="rc">�����_�����O�R���e�L�X�g</param>
		/// <param name="maxInstance">�C���X�^���X�̐�</param>
		virtual void BeginRender(RenderContext& rc, int maxInstance = 1) = 0;
	public:
		void SetAlbedoMap(Texture& tex)
		{
			m_albedoMap.InitFromD3DResource(tex.Get());
		}


	public:		//Get�֐��B
		/// <summary>
		/// �A���x�h�}�b�v���擾�B
		/// </summary>
		/// <returns></returns>
		Texture& GetAlbedoMap()
		{
			return m_albedoMap;
		}
		/// <summary>
		/// �@���}�b�v���擾�B
		/// </summary>
		/// <returns></returns>
		Texture& GetNormalMap()
		{
			return m_normalMap;
		}
		/// <summary>
		/// �X�y�L�����}�b�v���擾�B
		/// </summary>
		/// <returns></returns>
		Texture& GetSpecularMap()
		{
			return m_specularMap;
		}
		Texture& GetReflectionMap()
		{
			return m_reflectionMap;
		}
		/// <summary>
		/// �萔�o�b�t�@���擾�B
		/// </summary>
		/// <returns></returns>
		ConstantBuffer& GetConstantBuffer()
		{
			return m_constantBuffer;
		}
	protected:
		/// <summary>
		/// �e�N�X�`�����������B
		/// </summary>
		/// <param name="tkmMat"></param>
		void InitTexture(const TkmFile::SMaterial& tkmMat);

	protected:
		/// <summary>
		/// �}�e���A���p�����[�^�B
		/// </summary>
		struct SMaterialParam {
			int hasNormalMap;	//�@���}�b�v��ێ����Ă��邩�ǂ����̃t���O�B
			int hasSpecMap;		//�X�y�L�����}�b�v��ێ����Ă��邩�ǂ����̃t���O�B
			int hasReflectionMap;		//�X�y�L�����}�b�v��ێ����Ă��邩�ǂ����̃t���O�B
		};
		Texture	m_albedoMap;	//�A���x�h�}�b�v�B
		Texture	m_normalMap;							//�@���}�b�v�B
		Texture	m_specularMap;							//�X�y�L�����}�b�v�B
		Texture	m_reflectionMap;						//���˃}�b�v�B
		ConstantBuffer m_constantBuffer;				//�萔�o�b�t�@�B
	};
	/// <summary>
	/// �X�L�������}�e���A���B
	/// </summary>
	class NonSkinMaterial : public IMaterial {
	public:
		/// <summary>
		/// �����_�����O���J�n����Ƃ��ɌĂяo���֐��B
		/// </summary>
		/// <param name="rc">�����_�����O�R���e�L�X�g</param>
		/// <param name="maxInstance">�C���X�^���X�̐�</param>
		void BeginRender(RenderContext& rc, int maxInstance = 1) override final;

	};
	/// <summary>
	/// �X�L������}�e���A���B
	/// </summary>
	class SkinMaterial :public IMaterial{
	public:
		/// <summary>
		/// �����_�����O���J�n����Ƃ��ɌĂяo���֐��B
		/// </summary>
		/// <param name="rc">�����_�����O�R���e�L�X�g</param>
		/// <param name="maxInstance">�C���X�^���X�̐�</param>
		void BeginRender(RenderContext& rc, int maxInstance = 1) override final;
	};
}