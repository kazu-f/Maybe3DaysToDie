#pragma once

#include "physics/ICollider.h"

namespace Engine {

	/// <summary>
	/// ���b�V���R���C�_�[�B
	/// </summary>
	class CMeshCollider:public ICollider
	{
	public:
		//�R���X�g���N�^�B
		CMeshCollider();
		//�f�X�g���N�^�B
		~CMeshCollider();
		/// <summary>
		/// ���f���N���X���烁�b�V���R���C�_�[�𐶐��B
		/// </summary>
		/// <param name="model">�X�L�����f��</param>
		/// <param name="offsetMatrix">�s��B</param>
		void CreateFromModel(const Model& model, const Matrix* offsetMatrix);
		/// <summary>
		/// tkm�t�@�C�����烁�b�V���R���C�_�[�𐶐��B
		/// </summary>
		/// <param name="tkmFile">tkm�t�@�C���B</param>
		/// <param name="offsetMatrix">�s��B</param>
		void CreateFromTkmFile(const TkmFile& tkmFile, const Matrix* offsetMatrix);
		/// <summary>
		/// ���_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@����R���C�_�[���쐬�B
		/// </summary>
		/// <param name="vertices">���_�o�b�t�@�B</param>
		/// <param name="indices">�C���f�b�N�X�o�b�t�@�B</param>
		/// <param name="offsetMatrix">�s��B</param>
		void CreateFromBuffer(const std::vector<Vector3>& vertices, const std::vector<int>& indices, const Matrix* offsetMatrix);

		/// <summary>
		/// ���_�o�b�t�@�@����R���C�_�[���쐬�B
		/// </summary>
		/// <param name="vertices">���_�o�b�t�@�B</param>
		/// <param name="offsetMatrix">�s��B</param>
		void CreateFromBuffer(const std::vector<Vector3>& vertices, const Matrix* offsetMatrix);

		/// <summary>
		/// �V�F�C�v���擾�B
		/// </summary>
		btCollisionShape* GetBody() const override
		{
			return m_meshShape.get();
		}
	private:
		typedef std::vector<Vector3>		VertexBuffer;		//���_�o�b�t�@�B
		typedef std::vector<unsigned int>	IndexBuffer;		//�C���f�b�N�X�o�b�t�@�B
		typedef std::unique_ptr<VertexBuffer>	VertexBufferPtr;	//���_�o�b�t�@�̃��j�[�N�|�C���^�B
		typedef std::unique_ptr<IndexBuffer>	IndexBufferPtr;		//�C���f�b�N�X�o�b�t�@�̃��j�[�N�|�C���^�B
		std::vector<VertexBufferPtr>		m_vertexBufferArray;	//���_�o�b�t�@�̔z��B
		std::vector<IndexBufferPtr>			m_indexBufferArray;		//�C���f�b�N�X�o�b�t�@�̔z��B
		std::unique_ptr<btBvhTriangleMeshShape>		m_meshShape;		//���b�V���`��B
		std::unique_ptr<btTriangleIndexVertexArray> m_stridingMeshInterface;

	};

}
