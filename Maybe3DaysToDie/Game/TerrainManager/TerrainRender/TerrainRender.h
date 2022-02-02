#pragma once

namespace nsTerrain {

	/// <summary>
	/// �n�`�̒��_�f�[�^�B
	/// </summary>
	struct TerrainVertex {
		Vector3 m_pos;		//���W�B
		Vector3 m_normal;	//�@���B
		Vector2 m_uv;		//UV�B
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

		//���W�ݒ�B
		void SetPosition(const Vector3& pos)
		{
			m_position = pos;
		}
		//��]�ݒ�B
		void SetRotation(const Quaternion& rot)
		{
			m_rotation = rot;
		}
		//�X�P�[���ݒ�B
		void SetScale(const Vector3& scale)
		{
			m_scale = scale;
		}

		/// <summary>
		/// ���_��ǉ�����B
		/// </summary>
		/// <param name="vert"></param>
		void AddVertex(const TerrainVertex& vert)
		{
			m_vertices[m_vertexCount] = vert;
			m_indices[m_vertexCount] = m_vertexCount;
			m_vertexCount++;
			m_isUpdateTerrain = true;
		}
		/// <summary>
		/// �O�p�|���S���̒��S���W���L�^�B
		/// </summary>
		/// <param name="center"></param>
		void AddCenter(const Vector3& center)
		{
			m_centers.push_back(center);
		}
		/// <summary>
		/// �O�p�|���S���̒��S���W���擾�B
		/// </summary>
		/// <returns></returns>
		const std::vector<Vector3>& GetCenterArray()const
		{
			return m_centers;
		}
		/// <summary>
		/// ���_���N���A�B
		/// </summary>
		void ClearVertex()
		{
			m_vertices.clear();
			m_indices.clear();
			m_centers.clear();
			m_vertexCount = 0;
			m_vertices.resize(m_initData.vertexNum);
			m_indices.resize(m_initData.vertexNum);
			m_isUpdateTerrain = true;
		}

	public://getter
		/// <summary>
		/// �n�`�̃o�[�e�b�N�X�f�[�^���擾�B
		/// </summary>
		/// <returns></returns>
		std::vector<TerrainVertex>& GetVertexList()
		{
			return m_vertices;
		}
		/// <summary>
		/// �C���f�b�N�X���X�g���擾�B
		/// </summary>
		/// <returns></returns>
		std::vector<int>& GetIndexList()
		{
			return m_indices;
		}
		/// <summary>
		/// �o�[�e�b�N�X�̐��擾�B
		/// </summary>
		/// <returns></returns>
		int& GetVertexCount()
		{
			return m_vertexCount;
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
			Matrix mWorld;  //���[���h�s��B
			Matrix mView;	//�r���[�s��B
			Matrix mProj;	//�v���W�F�N�V�����s��B
		};

	private:
		TerrainInitData m_initData;
		Texture* m_terrainTex = nullptr;				//�n�`�̃e�N�X�`���B
		Shader m_vsTerrain;					//�n�`�p�̒��_�V�F�[�_�[�B
		Shader m_psTerrain;					//�n�`�p�̃s�N�Z���V�F�[�_�[�B
		PipelineState m_terrainPS;			//�n�`�p�̃p�C�v���C���X�e�[�g�B
		ConstantBuffer m_cbTerrain;			//�n�`�p�̒萔�o�b�t�@�B
		DescriptorHeap m_descriptorHeap;	//�n�`�p�f�B�X�N���v�^�q�[�v�B
		VertexBuffer m_vertexBuffer;		//�n�`�̒��_�o�b�t�@�B
		IndexBuffer m_indexBuffer;			//�n�`�̃C���f�b�N�X�o�b�t�@�B
		Vector3 m_position = Vector3::Zero;				//�n�`�̍��W�B
		Quaternion m_rotation = Quaternion::Identity;	//�n�`�̉�]�B
		Vector3 m_scale = Vector3::One;				//�n�`�̃X�P�[���B
		Matrix m_world = Matrix::Identity;				//�n�`�̃��[���h�s��B
		std::vector<TerrainVertex> m_vertices;	//���_�̔z��B
		std::vector<int> m_indices;			//�C���f�b�N�X�ԍ��̔z��B
		std::vector<Vector3> m_centers;			//�O�p�|���S���̒��S���W�̔z��B
		int m_vertexCount = 0;
		bool m_isRenderTerrain = false;		//�n�`�`�悷��H
		bool m_isUpdateTerrain = false;		//�n�`�ύX�����������H
	};

}
