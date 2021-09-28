#include "stdafx.h"
#include "MeshParts.h"
#include "Skeleton.h"
#include "Material.h"
#include "graphics\UserMaterial.h"

namespace Engine {
	MeshParts::~MeshParts()
	{
		for (auto& mesh : m_meshs) {
			//�C���f�b�N�X�o�b�t�@���폜�B
			for (auto& ib : mesh->m_indexBufferArray) {
				delete ib;
			}
			//�}�e���A�����폜�B
			for (auto& mat : mesh->m_materials) {
				delete mat;
			}
			//���b�V�����폜�B
			delete mesh;
		}
	}
	void MeshParts::InitFromTkmFile(
		const TkmFile& tkmFile,
		const SShaderInitData& shaderData,
		void* expandData,
		int expandDataSize,
		IShaderResource* expandShaderResourceView,
		StructuredBuffer* instancingDataSB,
		int maxInstance
	)
	{
		//�C���X�^���V���O�`��p�̃f�[�^�B
		m_instancingDataPtr = instancingDataSB;
		m_maxInstance = maxInstance;
		
		m_meshs.resize(tkmFile.GetNumMesh());
		int meshNo = 0;
		tkmFile.QueryMeshParts([&](const TkmFile::SMesh& mesh) {
			//tkm�t�@�C���̃��b�V����񂩂烁�b�V�����쐬����B
			CreateMeshFromTkmMesh(mesh, meshNo, shaderData);


			meshNo++;
			});
		//���ʒ萔�o�b�t�@�̍쐬�B
		m_commonConstantBuffer.Init(sizeof(SConstantBuffer), nullptr);
		//���[�U�[�g���p�̒萔�o�b�t�@���쐬�B
		if (expandData) {
			m_expandConstantBuffer.Init(expandDataSize, nullptr);
			m_expandData = expandData;
		}
		m_expandShaderResourceView = expandShaderResourceView;
		////�f�B�X�N���v�^�q�[�v���쐬�B
		//CreateDescriptorHeaps();
	}

	void MeshParts::CreateDescriptorHeaps()
	{
		//�f�B�X�N���v�^�q�[�v�̓}�e���A���̐��������쐬�����B
		int numDescriptorHeap = 0;
		for (auto& mesh : m_meshs) {
			for (int matNo = 0; matNo < mesh->m_materials.size(); matNo++) {
				numDescriptorHeap++;
			}
		}
		//�f�B�X�N���v�^�q�[�v���h�J�b�Ɗm�ہB
		m_descriptorHeap.resize(numDescriptorHeap);
		//�f�B�X�N���v�^�q�[�v���\�z���Ă����B
		int descriptorHeapNo = 0;
		for (auto& mesh : m_meshs) {
			for (int matNo = 0; matNo < mesh->m_materials.size(); matNo++) {
				auto& descriptorHeap = m_descriptorHeap[descriptorHeapNo];
				int descSRNo = 0;
				//�f�B�X�N���v�^�q�[�v�Ƀf�B�X�N���v�^��o�^���Ă����B
				descriptorHeap.RegistShaderResource(descSRNo++, mesh->m_materials[matNo]->GetAlbedoMap());		//�A���x�h�}�b�v(0��)�B
				descriptorHeap.RegistShaderResource(descSRNo++, mesh->m_materials[matNo]->GetNormalMap());		//�@���}�b�v(1��)�B
				descriptorHeap.RegistShaderResource(descSRNo++, mesh->m_materials[matNo]->GetSpecularMap());	//�X�y�L�����}�b�v(2��)�B
				descriptorHeap.RegistShaderResource(descSRNo++, mesh->m_materials[matNo]->GetReflectionMap());	//���˃}�b�v(3��)�B
				descriptorHeap.RegistShaderResource(descSRNo++, m_boneMatricesStructureBuffer);				//�{�[���̐ݒ�(4��)�B
				descriptorHeap.RegistShaderResource(descSRNo++, GraphicsEngine()->GetLightManager()->GetDirectionLightStructuredBuffer());	//���C�g�̐ݒ�(5��)�B
				for (int i = 0; i < NUM_SHADOW_MAP; i++) {
					//�V���h�E�}�b�v�B
					descriptorHeap.RegistShaderResource(descSRNo++, *GraphicsEngine()->GetShadowMap()->GetShadowMapTexture(i));
				}
				if (m_instancingDataPtr != nullptr) {
					descriptorHeap.RegistShaderResource(descSRNo, *m_instancingDataPtr);			//�C���X�^���V���O�`��p�̃f�[�^(9��)�B
				}
				descSRNo++;
				if (m_expandShaderResourceView) {
					//���[�U�[�g���̃V�F�[�_�[���\�[�X�B(10��)
					descriptorHeap.RegistShaderResource(EXPAND_SRV_REG__START_NO, *m_expandShaderResourceView);
				}
				int descCBNo = 0;
				descriptorHeap.RegistConstantBuffer(descCBNo++, m_commonConstantBuffer);											//���f���̒萔�o�b�t�@(0��)�B
				descriptorHeap.RegistConstantBuffer(descCBNo++, GraphicsEngine()->GetLightManager()->GetLightParamConstantBuffer());		//���C�g�̐ݒ�(1��)�B
				descriptorHeap.RegistConstantBuffer(descCBNo++, mesh->m_materials[matNo]->GetConstantBuffer());				//�}�e���A���̒萔�o�b�t�@(2��)�B
				descriptorHeap.RegistConstantBuffer(descCBNo++, GraphicsEngine()->GetShadowMap()->GetShadowMapConstantBuffer());		//�V���h�E�}�b�v�̒萔�o�b�t�@(3��)�B
				if (m_expandConstantBuffer.IsValid()) {
					//���[�U�[�g���̒萔�o�b�t�@(4��)�B
					descriptorHeap.RegistConstantBuffer(descCBNo++, m_expandConstantBuffer);
				}
				//�f�B�X�N���v�^�q�[�v�ւ̓o�^���m�肳����B
				descriptorHeap.Commit();
				descriptorHeapNo++;
			}
		}
		//�f�B�X�N���v�^�q�[�v���쐬���ꂽ�B
		m_isCreateDescriptHeap = true;
	}
	void MeshParts::CreateMeshFromTkmMesh(
		const TkmFile::SMesh& tkmMesh,
		int meshNo,
		const SShaderInitData& shaderData)
	{
		//���_�o�b�t�@���쐬�B
		int numVertex = (int)tkmMesh.vertexBuffer.size();
		int vertexStride = sizeof(TkmFile::SVertex);
		auto mesh = new SMesh;
		mesh->skinFlags.reserve(tkmMesh.materials.size());
		mesh->m_vertexBuffer.Init(vertexStride * numVertex, vertexStride);
		mesh->m_vertexBuffer.Copy((void*)&tkmMesh.vertexBuffer[0]);

		auto SetSkinFlag = [&](int index) {
			if (tkmMesh.vertexBuffer[index].skinWeights.x > 0.0f) {
				//�X�L��������B
				mesh->skinFlags.push_back(1);
			}
			else {
				//�X�L���Ȃ��B
				mesh->skinFlags.push_back(0);
			}
		};
		//�C���f�b�N�X�o�b�t�@���쐬�B
		if (!tkmMesh.indexBuffer16Array.empty()) {
			//�C���f�b�N�X�̃T�C�Y��2byte
			mesh->m_indexBufferArray.reserve(tkmMesh.indexBuffer16Array.size());
			for (auto& tkIb : tkmMesh.indexBuffer16Array) {
				auto ib = new IndexBuffer;
				ib->Init(static_cast<int>(tkIb.indices.size()) * 2, 2);
				ib->Copy((void*)&tkIb.indices.at(0));

				//�X�L�������邩�ǂ�����ݒ肷��B
				SetSkinFlag(tkIb.indices[0]);

				mesh->m_indexBufferArray.push_back(ib);
			}
		}
		else {
			//�C���f�b�N�X�̃T�C�Y��4byte
			mesh->m_indexBufferArray.reserve(tkmMesh.indexBuffer32Array.size());
			for (auto& tkIb : tkmMesh.indexBuffer32Array) {
				auto ib = new IndexBuffer;
				ib->Init(static_cast<int>(tkIb.indices.size()) * 4, 4);
				ib->Copy((void*)&tkIb.indices.at(0));

				//�X�L�������邩�ǂ�����ݒ肷��B
				SetSkinFlag(tkIb.indices[0]);

				mesh->m_indexBufferArray.push_back(ib);
			}
		}
		//�}�e���A�����쐬�B
		mesh->m_materials.reserve(tkmMesh.materials.size());
		int matNo = 0;
		for (auto& tkmMat : tkmMesh.materials) {
			IMaterial* mat = nullptr;
			//�t�@�C���p�X���w�肳��Ă��Ȃ��B
			if (shaderData.vsFxFilePath == nullptr
				&& shaderData.psFxFilePath == nullptr) {
				//���炩���ߗp�ӂ����V�F�[�_�[���g���B
				if (mesh->skinFlags[matNo]) {
					mat = new SkinMaterial;
				}
				else {
					mat = new NonSkinMaterial;
				}
			}
			else {
				//�V�����V�F�[�_�[�����B
				//TODO:�X�L���̗L����n����悤�ɂ��Ȃ��Ɖe���Ƃ��̂���肭�����Ȃ������H
				mat = new UserMaterial;
			}

			mat->InitFromTkmMaterila(tkmMat, shaderData);
			mesh->m_materials.push_back(mat);
			matNo++;
		}

		m_meshs[meshNo] = mesh;

	}

	void MeshParts::BindSkeleton(Skeleton& skeleton)
	{
		m_skeleton = &skeleton;
		//�\�����o�b�t�@���쐬����B
		m_boneMatricesStructureBuffer.Init(
			sizeof(Matrix),
			m_skeleton->GetNumBones(),
			m_skeleton->GetBoneMatricesTopAddress()
		);
	}
	void MeshParts::FindMesh(OnFindMesh findMesh) const
	{
		for (auto* mesh : m_meshs)
		{
			findMesh(mesh);
		}

	}
	void MeshParts::FindMaterial(OnFindMateral findMaterial) const
	{
		FindMesh([&](SMesh* mesh) 
			{
				for (auto* material : mesh->m_materials) {
					findMaterial(material);
				}
			}
		);

	}
	void MeshParts::Draw(
		RenderContext& rc,
		const Matrix& mWorld,
		const Matrix& mView,
		const Matrix& mProj, 
		const int instanceNum
	)
	{
		if (m_isCreateDescriptHeap == false) {
			CreateDescriptorHeaps();
		}
#if 1

		//���b�V�����ƂɃh���[
		//�v���~�e�B�u�̃g�|���W�[�̓g���C�A���O�����X�g�̂݁B
		rc.SetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		//�萔�o�b�t�@���X�V����B
		SConstantBuffer cb;
		cb.mWorld = mWorld;
		cb.mView = mView;
		cb.mProj = mProj;
		cb.emissionColor = m_emissionColor;
		cb.isShadowReceiver = m_isShadowReceiver ? 1 : 0;

		m_commonConstantBuffer.CopyToVRAM(&cb);

		if (m_expandData) {
			m_expandConstantBuffer.CopyToVRAM(m_expandData);
		}
		if (m_boneMatricesStructureBuffer.IsInited()) {
			//�{�[���s����X�V����B
			m_boneMatricesStructureBuffer.Update(m_skeleton->GetBoneMatricesTopAddress());
		}
		int descriptorHeapNo = 0;
		for (auto& mesh : m_meshs) {
			//���_�o�b�t�@��ݒ�B
			rc.SetVertexBuffer(mesh->m_vertexBuffer);
			//�}�e���A�����ƂɃh���[�B
			for (int matNo = 0; matNo < mesh->m_materials.size(); matNo++) {
				//���̃}�e���A�����\���Ă��郁�b�V���̕`��J�n�B
				mesh->m_materials[matNo]->BeginRender(rc, m_maxInstance);
				//�f�B�X�N���v�^�q�[�v��o�^�B
				rc.SetDescriptorHeap(m_descriptorHeap.at(descriptorHeapNo));
				//�C���f�b�N�X�o�b�t�@��ݒ�B
				auto& ib = mesh->m_indexBufferArray[matNo];
				rc.SetIndexBuffer(*ib);

				//�h���[�B
				rc.DrawIndexed(
					ib->GetCount(), 
					m_maxInstance > 1 ? instanceNum : 1
				);
				descriptorHeapNo++;
			}
		}
#endif
	}
}