#pragma once

#include "physics/ICollider.h"

namespace Engine {

	class CCapsuleCollider : public ICollider
	{
	public:
		/// <summary>
		/// �J�v�Z���R���C�_�[�̍쐬�B
		/// </summary>
		/// <param name="radius">���a�B</param>
		/// <param name="height">�����B</param>
		void Create(float radius,float height) 
		{
			m_shape = std::make_unique<btCapsuleShape>(radius, height);
			m_radius = radius;
			m_height = height;
		}
		//�V�F�C�v�̎擾�B
		btCollisionShape* GetBody()const override
		{
			return m_shape.get();
		}
		//���a�̎擾�B
		float GetRadius() const
		{
			return m_radius;
		}
		//�����̎擾�B
		float GetHeight()const
		{
			return m_height;
		}

	private:
		std::unique_ptr<btCapsuleShape> m_shape;	//�J�v�Z���V�F�C�v�B
		float m_radius = 0.0f;		//���a�B
		float m_height = 0.0f;		//�����B
	};///CCapsuleCollider
}///namespace Engine
