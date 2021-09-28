#include "stdafx.h"
#include "PhysicsObjectBase.h"
#include "physics/BoxCollider.h"
#include "physics/CapsuleCollider.h"
#include "physics/SphereCollider.h"
#include "physics/MeshCollider.h"
#include "graphics/Model.h"
#include "prefab/ModelRender.h"

namespace Engine {
	void CPhysicsObjectBase::CreateBox(const Vector3& pos, const Quaternion& rot, const Vector3& size)
	{
		Release();
		//�{�b�N�X�R���C�_�[���쐬�B
		auto boxCollider = std::make_unique<CBoxCollider>();
		boxCollider->Create(size);
		m_sphere = std::move(boxCollider);
		//�����I�u�W�F�N�g�̍쐬�A�o�^�B
		CreateCommon(pos, rot);
	}
	void CPhysicsObjectBase::CreateCapsule(const Vector3& pos, const Quaternion& rot, const float radius, const float height)
	{
		Release();
		//�J�v�Z���R���C�_�[���쐬�B
		auto capsuleCollider = std::make_unique<CCapsuleCollider>();
		capsuleCollider->Create(radius, height);
		m_sphere = std::move(capsuleCollider);
		//�����I�u�W�F�N�g�̍쐬�A�o�^�B
		CreateCommon(pos, rot);
	}
	void CPhysicsObjectBase::CreateSphere(const Vector3& pos, const Quaternion& rot, const float radius)
	{
		Release();
		//���̃R���C�_�[�̍쐬�B
		auto sphereCollider = std::make_unique<CSphereCollider>();
		sphereCollider->Create(radius);
		m_sphere = std::move(sphereCollider);
		//�����I�u�W�F�N�g�̍쐬�A�o�^�B
		CreateCommon(pos, rot);
	}
	void CPhysicsObjectBase::CreateMesh(const Vector3& pos, const Quaternion& rot, const TkmFile& tkmFile)
	{
		Release();
		//���b�V���R���C�_�[�̍쐬�B
		auto meshCollider = std::make_unique<CMeshCollider>();
		meshCollider->CreateFromTkmFile(tkmFile, nullptr);
		m_sphere = std::move(meshCollider);
		//�����I�u�W�F�N�g�쐬�A�o�^�B
		CreateCommon(pos, rot);
	}
	void CPhysicsObjectBase::CreateMesh(const Vector3& pos, const Quaternion& rot, const Vector3 & scale, const Model& model)
	{
		Release();
		//�X�P�[���𒲐����邽�߂̍s��쐬�B
		Matrix mScale;
		mScale.MakeScaling(scale);
		//���b�V���R���C�_�[�̍쐬�B
		auto meshCollider = std::make_unique<CMeshCollider>();
		meshCollider->CreateFromModel(model, &mScale);
		m_sphere = std::move(meshCollider);
		//�����I�u�W�F�N�g�̍쐬�A�o�^�B
		CreateCommon(pos, rot);
	}
	void CPhysicsObjectBase::CreateMesh(const Vector3& pos, const Quaternion& rot, const Vector3& scale, prefab::ModelRender* modelRender)
	{
		//���f������쐬�B
		CreateMesh(pos, rot, scale, modelRender->GetModel());
	}
}