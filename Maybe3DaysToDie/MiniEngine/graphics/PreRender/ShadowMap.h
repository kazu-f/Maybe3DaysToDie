#pragma once


namespace Engine {
	/// <summary>
	/// �w�����V���h�E�}�b�v�N���X�B
	/// </summary>
	/// <remarks>
	/// �J�X�P�[�h�V���h�E����Ă݂�B
	/// </remarks>

	class CShadowMap : Noncopyable
	{
	public:
		/// <summary>
		/// �����������B
		/// </summary>
		void Init(const SShadowMapConfig& cnfig);
		/// <summary>
		/// �V���h�E�}�b�v�ւ̃����_�����O���s���B
		/// </summary>
		void RenderToShadowMap(RenderContext& rc);
		/// <summary>
		/// �V���h�E�}�b�v�ւ̃����_�����O�����҂��B
		/// </summary>
		void WaitEndRenderToShadowMap(RenderContext& rc);
		/// <summary>
		/// �X�V�����B
		/// </summary>
		void Update();
		/// <summary>
		/// �V���h�E�}�b�v��L���ɂ���B
		/// </summary>
		void SetEnable()
		{
			m_isEnable = true;
		}
		/// <summary>
		/// �V���h�E�}�b�v�𖳌��ɂ���B
		/// </summary>
		void SetDisable()
		{
			m_isEnable = false;
		}
		/// <summary>
		/// ���C�g�̌�����ύX����B
		/// </summary>
		void SetLightDirection(const Vector3& dir)
		{
			m_lightDirection = dir;
			m_lightDirection.Normalize();
		}
	public:
		/// <summary>
		/// �萔�o�b�t�@���擾�B
		/// </summary>
		ConstantBuffer& GetShadowMapConstantBuffer()
		{
			return m_shadowCb;
		}
		/// <summary>
		/// �V���h�E�}�b�v�̃����_�����O�^�[�Q�b�g�̃e�N�X�`�����擾�B
		/// </summary>
		/// <remarks>0�`2�܂ł̒l�Ŏ擾�B</remarks>
		Texture* GetShadowMapTexture(int i)
		{
			if (i < NUM_SHADOW_MAP) {
				return &m_shadowMaps[i].GetRenderTargetTexture();
			}
			return nullptr;
		}

	private:	//�����I�ȏ����B
		/// <summary>
		/// ���C�g�̍��W���v�Z����B
		/// </summary>
		Vector3 CalcLightPosition(float lightHeight, Vector3 viewFrustomCenterPosition);

	private:		//�\���̂Ƃ�
		/// <summary>
		/// �V���h�E�}�b�v�p�̒萔�o�b�t�@�̏��B
		/// </summary>
		struct SShadowCb {
			Matrix mLVP[NUM_SHADOW_MAP];
			Vector4 texOffset[NUM_SHADOW_MAP];
			float depthOffset[NUM_SHADOW_MAP];
			float pading;
			float shadowAreaDepthInViewSpace[NUM_SHADOW_MAP];	//�J������Ԃł̉e�𗎂Ƃ��G���A�̐[�x�e�[�u���B
		};

		Matrix m_LVPMatrix[NUM_SHADOW_MAP];							//���C�g�r���[�v���W�F�N�V�����s��B
		SShadowCb m_shadowCbEntity;
	private:
		ConstantBuffer m_shadowCb;								//�萔�o�b�t�@�B
		RenderTarget m_shadowMaps[NUM_SHADOW_MAP];				//�V���h�E�}�b�v�̃����_�[�^�[�Q�b�g�B
		Vector3 m_lightDirection = { 0.0f,-1.0f,0.0f };			//���C�g�̕����B
		float m_shadowAreas[NUM_SHADOW_MAP] = { 0.0f };			//�e��������͈́B
		float m_depthOffset[NUM_SHADOW_MAP] = { 0.0f };			//�[�x�l�I�t�Z�b�g�B
		float m_lightHeight = 500.0f;							//���C�g�̍����B
		bool m_isEnable = true;									//�V���h�E�}�b�v���L�����ǂ����B
	};
}

