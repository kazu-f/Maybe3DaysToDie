#pragma once

/// <summary>
/// �R���W�����̃f�o�b�O�\��
/// </summary>

namespace Engine {

	class CPhysicsDebugDraw : public btIDebugDraw
	{
	public:
		CPhysicsDebugDraw();
		~CPhysicsDebugDraw();
		/// <summary>
		/// �������B
		/// </summary>
		void Init();
		/// <summary>
		/// �`��̎��O�����B
		/// </summary>
		/// <param name="rc">�����_�����O�R���e�L�X�g�B</param>
		void BeginDraw(RenderContext& rc)
		{
			m_renderContext = &rc;
			m_numLine = 0;
		}
		/// <summary>
		/// �`��̏I�������B
		/// </summary>
		void EndDraw();
		/// <summary>
		/// ����`�悷��B
		/// </summary>
		void drawLine(const btVector3& from, const btVector3& to, const btVector3& color)override;

		void drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color) override
		{
		}
		void reportErrorWarning(const char* warningString) override
		{
		}
		void draw3dText(const btVector3& location, const char* textString) override
		{
		}

		void setDebugMode(int debugMode)override
		{
			m_debugMode = debugMode;
		}

		int getDebugMode()const override
		{
			return m_debugMode;
		}
	private:
		//�o�b�t�@�̏������B
		void InitBuffer();
		//�V�F�[�_�[�̏������B
		void InitShader();
		//�p�C�v���C���X�e�[�g�̏������B
		void InitPipelineState();
		//�f�B�X�N���v�^�q�[�v�̏������B
		void InitDescriptorHeap();

	private:
		//�萔�o�b�t�@�B
		struct SConstantBuffer
		{
			Matrix mView;		//�r���[�s��B
			Matrix mProj;		//�v���W�F�N�V�����s��B
		};
		int m_debugMode = btIDebugDraw::DBG_NoDebug;
		RenderContext* m_renderContext = nullptr;			//�����_�[�R���e�L�X�g�B
		Shader m_vs;										//���_�V�F�[�_�[�B
		Shader m_ps;										//�s�N�Z���V�F�[�_�[�B
		VertexBuffer m_vertexBuffer;						//���_�o�b�t�@�B
		IndexBuffer m_indexBuffer;							//�C���f�b�N�X�o�b�t�@�B
		ConstantBuffer m_cb;								//�萔�o�b�t�@�B
		RootSignature m_rootSignature;						//���[�g�V�O�l�`���B
		DescriptorHeap		m_descriptorHeap;				//�f�B�X�N���v�^�q�[�v�B
		PipelineState m_pipeLineState;						//�p�C�v���C���X�e�[�g�B
		static const int VERTEX_MAX = 1000000;
		std::array<Vector4, VERTEX_MAX> m_vertexData;		//���_�f�[�^�B
		int m_numLine = 0;									//���C�����B

	};///class CPhysicsDebugDraw;

}///namespace Engine;
