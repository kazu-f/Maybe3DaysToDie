#pragma once

#include "physics/ICollider.h"

namespace Engine {
	/// <summary>
	/// ���̃R���C�_�[�B
	/// </summary>
	class CSphereCollider : public ICollider
	{
	public:
		//�R���X�g���N�^�B
		CSphereCollider();
		//�f�X�g���N�^�B
		~CSphereCollider();
		/// <summary>
		/// ���̃R���C�_�[���쐬�B
		/// </summary>
		/// <param name="radius">���̔��a�B</param>
		void Create(const float radius);
		/// <summary>
		/// �V�F�C�v���擾�B
		/// </summary>
		btCollisionShape* GetBody() const override
		{
			return shape.get();
		}
	private:
		std::unique_ptr<btSphereShape> shape;
	};///class CSphereCollider;
}///namespace Engine;

