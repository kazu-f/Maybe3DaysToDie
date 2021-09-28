#pragma once

#include "physics/ICollider.h"

namespace Engine {

	class CBoxCollider : public ICollider
	{
	public:
		/// <summary>
		/// �R���X�g���N�^�B
		/// </summary>
		CBoxCollider();
		/// <summary>
		/// �f�X�g���N�^�B
		/// </summary>
		~CBoxCollider();
		/// <summary>
		/// �{�b�N�X�R���C�_�[���쐬�B
		/// </summary>
		void Create(const Vector3& size);
		/// <summary>
		/// �V�F�C�v���擾�B
		/// </summary>
		btCollisionShape* GetBody()const override
		{
			return shape.get();
		}
	private:
		std::unique_ptr<btBoxShape> shape;		//�V�F�C�v�B

	};///class CBoxCollider;

}///namespace Engine;

