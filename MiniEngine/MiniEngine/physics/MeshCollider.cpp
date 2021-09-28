#include "stdafx.h"
#include "MeshCollider.h"
#include "graphics/Model.h"

namespace Engine {
	CMeshCollider::CMeshCollider()
	{
	}
	CMeshCollider::~CMeshCollider()
	{
	}
	void CMeshCollider::CreateFromModel(const Model& model, const Matrix* offsetMatrix)
	{
		CreateFromTkmFile(model.GetTkmFile(), offsetMatrix);
	}
	void CMeshCollider::CreateFromTkmFile(const TkmFile& tkmFile, const Matrix* offsetMatrix)
	{
		Matrix mBias;
		mBias.MakeRotationX(Math::PI * -0.5f);
		if (offsetMatrix != nullptr) {
			mBias = mBias * (*offsetMatrix);
		}

		m_stridingMeshInterface = std::make_unique<btTriangleIndexVertexArray>();
		int numMesh = 0;
		//�����_�̃��j�[�N�|�C���^�̃L���v�`�����悭�킩��Ȃ������Ȃ�
		tkmFile.QueryMeshParts([&](const TkmFile::SMesh& mesh) {
			//���f���̒��_�o�b�t�@����A�����G���W���p�̒��_�o�b�t�@���쐬����B
			{
				VertexBufferPtr vertexBuffer = std::make_unique<VertexBuffer>();
				for (auto& vb : mesh.vertexBuffer) {
					auto pos = vb.pos;
					//�o�C�A�X��������B
					mBias.Apply(pos);
					vertexBuffer->push_back(pos);
				}

				m_vertexBufferArray.push_back(std::move(vertexBuffer));
			}

			//���f���̃C���f�b�N�X�o�b�t�@����A�����G���W���p�̃C���f�b�N�X�o�b�t�@���쐬�B
			{
				IndexBufferPtr indexBuffer = std::make_unique <IndexBuffer>();
				if (!mesh.indexBuffer16Array.empty()) {
					//16bit�C���f�b�N�X�o�b�t�@����쐬�B
					for (auto& ib : mesh.indexBuffer16Array) {
						for (auto index : ib.indices) {
							indexBuffer->push_back(index);
						}
					}

				}
				else {
					//32bit�C���f�b�N�X�o�b�t�@����쐬�B
					for (auto& ib : mesh.indexBuffer32Array) {
						for (auto index : ib.indices) {
							indexBuffer->push_back(index);
						}
					}
				}

				m_indexBufferArray.push_back(std::move(indexBuffer));
			}

			//BulletPhysics�̃C���f�b�N�X���b�V�����쐬�B
			btIndexedMesh indexedMesh;
			IndexBuffer* ib = m_indexBufferArray.back().get();
			VertexBuffer* vb = m_vertexBufferArray.back().get();
			indexedMesh.m_numTriangles = static_cast<int>(ib->size() / 3);
			indexedMesh.m_triangleIndexBase = reinterpret_cast<unsigned char*>(&ib->front());
			indexedMesh.m_triangleIndexStride = 12;		//12�Œ�ł����H
			indexedMesh.m_numVertices = static_cast<int>(vb->size());
			indexedMesh.m_vertexBase = reinterpret_cast<unsigned char*>(&vb->front());
			indexedMesh.m_vertexStride = sizeof(Vector3);
			//�C���f�b�N�X���b�V����ǉ��B
			m_stridingMeshInterface->addIndexedMesh(indexedMesh);

			numMesh++;
		});
		//�C���f�b�N�X���b�V�����g���ă��b�V�������o���B
		m_meshShape = std::make_unique<btBvhTriangleMeshShape>(m_stridingMeshInterface.get(), true);
	}
}
