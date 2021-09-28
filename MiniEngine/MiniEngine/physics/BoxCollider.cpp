#include "stdafx.h"
#include "BoxCollider.h"

namespace Engine {
	CBoxCollider::CBoxCollider()
	{
	}
	CBoxCollider::~CBoxCollider()
	{
	}
	void CBoxCollider::Create(const Vector3& size)
	{
		//�{�b�N�X�R���C�_�[�̍쐬�B
		shape = std::make_unique<btBoxShape>(
			btVector3(
				size.x * 0.5f, 
				size.y * 0.5f, 
				size.z * 0.5f)
			);
	}
}
