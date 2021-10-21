#pragma once

namespace nsTerrain {

	/// <summary>
	/// �n�`�̒��_�f�[�^�B
	/// </summary>
	struct Vertex {
		Vector3 m_pos;
		Vector2 m_uv;
	};

	//�n�`�`��N���X�̏������f�[�^�B
	struct TerrainInitData {
		int vertexNum = 0;			//���_���B

	};

	class TerrainRender : public IGameObject
	{
	public:
		bool Start()override final;
		void Update()override final;
		void ForwardRender(RenderContext& rc)override final;
		/// <summary>
		/// �������B
		/// </summary>
		void Init(TerrainInitData& initData);

		/// <summary>
		/// ���_��ǉ�����B
		/// </summary>
		/// <param name="vert"></param>
		void AddVertex(const Vertex& vert)
		{
			m_vertices[m_vertexCount] = vert;
			m_indices[m_vertexCount] = m_vertexCount;
			m_vertexCount++;
		}

	private:
		void InitVertexBuffer(int maxVertexNum);
		void InitIndexBuffer(int maxIndexNum);
		void InitShader();			//�V�F�[�_�[�̏������B
		void InitPipelineState();	//�p�C�v���C���X�e�[�g�̏������B
		void InitConstantBuffer();	//�萔�o�b�t�@�̏������B
		void InitTexrure();			//�e�N�X�`���������B
		void InitDescriptorHeap();	//�f�B�X�N���v�^�q�[�v�̏������B

	private:
		struct SCBTerrin{
			Matrix mView;	//�r���[�s��B
			Matrix mProj;	//�v���W�F�N�V�����s��B
		};

	private:
		Texture* m_terrainTex = nullptr;				//�n�`�̃e�N�X�`���B
		Shader m_vsTerrain;					//�n�`�p�̒��_�V�F�[�_�[�B
		Shader m_psTerrain;					//�n�`�p�̃s�N�Z���V�F�[�_�[�B
		PipelineState m_terrainPS;			//�n�`�p�̃p�C�v���C���X�e�[�g�B
		ConstantBuffer m_cbTerrain;			//�n�`�p�̒萔�o�b�t�@�B
		DescriptorHeap m_descriptorHeap;	//�n�`�p�f�B�X�N���v�^�q�[�v�B
		VertexBuffer m_vertexBuffer;		//�n�`�̒��_�o�b�t�@�B
		IndexBuffer m_indexBuffer;			//�n�`�̃C���f�b�N�X�o�b�t�@�B
		std::vector<Vertex> m_vertices;	//���_�̔z��B
		std::vector<short> m_indices;			//�C���f�b�N�X�ԍ��̔z��B
		int m_vertexCount = 0;
	};

}
