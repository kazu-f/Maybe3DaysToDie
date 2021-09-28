#pragma once

#include "graphics/GPUBuffer/VertexBuffer.h"
#include "graphics/GPUBuffer/IndexBuffer.h"

namespace Engine {
	/// <summary>
	/// �v���~�e�B�u�g�|���W�[�B
	/// </summary>
	enum EnPrimitiveTopology {
		enPrimitiveTopology_TriangleList = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
		enPrimitiveTopology_TriangleStrip = D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP,
		enPrimitiveTopology_Undex = 0xFFFFFFFF
	};
	/// <summary>
	/// �v���~�e�B�u�f�[�^�B
	/// </summary>
	struct PrimitiveInitData {
		EnPrimitiveTopology topology;			//�g�|���W�[�B
		int vertexSize = 0;						//���_�f�[�^�̃T�C�Y�B
		int vertexStride = 0;					//���_�̃T�C�Y�B
		void* pSrcVertexBuffer = nullptr;		//���_�f�[�^�B
		int indexSize = 0;						//�C���f�b�N�X�o�b�t�@�f�[�^�̃T�C�Y�B
		int indexStride = 0;					//�C���f�b�N�X�o�b�t�@�̃T�C�Y�B
		void* pSrcIndexBuffer = nullptr;		//�C���f�b�N�X�f�[�^�B

	};

	/// <summary>
	/// �v���~�e�B�u�B
	/// </summary>
	class CPrimitive : Noncopyable
	{
	public:
		/// <summary>
		/// �R���X�g���N�^�B
		/// </summary>
		CPrimitive();
		/// <summary>
		/// �f�X�g���N�^�B
		/// </summary>
		~CPrimitive();
		/// <summary>
		/// �������B
		/// </summary>
		/// <param name="initData">�������f�[�^�B</param>
		/// <returns>true�ō쐬�����B</returns>
		void Create(PrimitiveInitData& initData);
		/// <summary>
		/// �`��B
		/// </summary>
		/// <param name="rc"></param>
		void Draw(RenderContext& rc);
		/// <summary>
		/// ���_�o�b�t�@���擾�B
		/// </summary>
		VertexBuffer& GetVertexBuffer()
		{
			return m_vertexBuffer;
		}
		/// <summary>
		/// �C���f�b�N�X�o�b�t�@���擾�B
		/// </summary>
		IndexBuffer& GetIndexBuffer()
		{
			return m_indexBuffer;
		}
		/// <summary>
		/// �v���~�e�B�u�g�|���W�[���擾�B
		/// </summary>
		D3D12_PRIMITIVE_TOPOLOGY GetPrimitiveTopology()
		{
			return static_cast<D3D12_PRIMITIVE_TOPOLOGY>(m_topology);
		}

	private:
		VertexBuffer m_vertexBuffer;			//���_�f�[�^�B
		IndexBuffer m_indexBuffer;				//�C���f�b�N�X�o�b�t�@�B
		EnPrimitiveTopology m_topology = enPrimitiveTopology_Undex;		 //�g�|���W�[�B
	};

}

