#pragma once
/// <summary>
/// ���C�g�}�l�[�W���[�B
/// </summary>

#include "LightData.h"

namespace Engine {
	namespace prefab {
		class CLightBase;
		class CDirectionLight;
		class CPointLight;
	}

	/// <summary>
	/// ���C�g�̊Ǘ��ҁB
	/// </summary>
	/// <remarks>
	/// �C���X�^���X�����ꂽLightBase�̃C���X�^���X�͂��ׂēo�^�����B
	/// ���̃N���X��GraphicsEngine�N���X�݂̂��ێ�����B
	/// </remarks>
	class CLightManager : Noncopyable
	{
	public:
		/// <summary>
		/// �����������B
		/// </summary>
		void Init();
		/// <summary>
		/// ���C�g��ǉ�����B
		/// </summary>
		void AddLight(prefab::CLightBase* light);
		/// <summary>
		/// ���C�g���폜����B
		/// </summary>
		void RemoveLight(prefab::CLightBase* light);
		/// <summary>
		/// �X�V�����B
		/// </summary>
		void LightUpdate();

	public:		//�`��֌W�̏����B
		void Render(RenderContext& rc);

		void SendLightDataToGPU(RenderContext& rc);

	public:	//Get�֐�,Set�֐��B
		/// <summary>
		/// �|�C���g���C�g�̐����擾�B
		/// </summary>
		int GetNumPointLight()const
		{
			return static_cast<int>(0);			//��Ń��X�g�̃T�C�Y��n���Ă����B
		}
		/// <summary>
		/// �A���r�G���g���C�g���擾�B
		/// </summary>
		const Vector3& GetAmbientLight() const
		{
			return m_lightParam.ambientLight;
		}
		/// <summary>
		/// �A���r�G���g���C�g��ݒ�B
		/// </summary>
		void SetAmbientLight(const Vector3& ambient)
		{
			m_lightParam.ambientLight = ambient;
		}
		/// <summary>
		/// ���ʃ��C�g�p�����[�^�̒萔�o�b�t�@���擾�B
		/// </summary>
		ConstantBuffer& GetLightParamConstantBuffer()
		{
			return m_lightParamCB;
		}
		/// <summary>
		/// �f�B���N�V�������C�g�̃X�g���N�`���[�o�b�t�@���擾�B
		/// </summary>
		StructuredBuffer& GetDirectionLightStructuredBuffer()
		{
			return m_directionLightSB;
		}
	private:
		static const int MAX_DIRECTION_LIGHT = 8;				//�f�B���N�V�������C�g�̍ő吔�B
		static const int MAX_POINT_LIGHT = 1024;				//�|�C���g���C�g�̍ő吔�B
		/// <summary>
		/// ���f���V�F�[�_�[�Ŏg�p���郉�C�g�p�̃p�����[�^�B
		/// </summary>
		/// <remarks>
		/// �����o�ϐ���ǉ�������A���т�ς����肵����
		/// �V�F�[�_�[�����ύX����K�v������B
		/// </remarks>
		struct SLightParam {
			Vector3 eyePos;			//�����̈ʒu�B
			int numDirectionLight;	//�f�B���N�V�������C�g�̐��B
			Vector3 ambientLight;	//�A���r�G���g���C�g�B(����)
			int numPointLight;		//�|�C���g���C�g�̐��B
			Vector4 screenParam;	//�X�N���[���p�����[�^�B
		};
		/// <summary>
		/// ���C�g�J�����O�p�̃J�����f�[�^�B
		/// </summary>
		struct SLightCullingCameraData {
			Matrix mProj;		//�v���W�F�N�V�����s��B
			Matrix mProjInv;	//�v���W�F�N�V�����s��̋t�s��B
			Matrix mCameraRot;	//�J�����̉�]�s��B
		};

		SLightParam	m_lightParam;			//���C�g�̃p�����[�^�B
		SLightCullingCameraData m_lightCullingCameraData;	//���C�g�J�����O�p�̃J�����f�[�^�B
		SDirectionLight m_rawDirectionLights[MAX_DIRECTION_LIGHT];		//�f�B���N�V�������C�g�̃f�[�^�̔z��B
		SPointLight		m_rawPointLights[MAX_POINT_LIGHT];				//�|�C���g���C�g�̃f�[�^�̔z��B
		std::list<prefab::CDirectionLight*> m_directionLights;			//�f�B���N�V�������C�g�̔z��B
		std::list<prefab::CPointLight*> m_pointLights;			//�|�C���g���C�g�̔z��B
		Shader m_csLightCulling;				//���C�g�J�����O�p�̃R���s���[�g�V�F�[�_�[�B
		ConstantBuffer m_lightParamCB;			//���C�g���̒萔�o�b�t�@�B
		ConstantBuffer m_lightCullingCameraCB;	//���C�g�J�����O�p�̃J�����f�[�^�̒萔�o�b�t�@�B
		StructuredBuffer m_directionLightSB;	//�f�B���N�V�������C�g�̃X�g���N�`���o�b�t�@�B
		StructuredBuffer m_pointLightSB;		//�|�C���g���C�g�̃X�g���N�`���o�b�t�@�B
		RWStructuredBuffer m_pointLightNoListInTileUAV;		//�^�C�����Ƃ̃|�C���g���C�g�̔ԍ��̃��X�g���o�͂���UAV�B
	};

}
