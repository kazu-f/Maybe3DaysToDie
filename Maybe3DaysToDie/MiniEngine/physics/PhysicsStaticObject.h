#pragma once

#include "physics/RigidBody.h"
#include "physics/PhysicsObjectBase.h"

namespace Engine {

	class CPhysicsStaticObject : public CPhysicsObjectBase
	{
	public:
		~CPhysicsStaticObject()
		{
			Release();
		}
		/// <summary>
		/// ��������B
		/// </summary>
		void Release()override final;

		/// <summary>
		/// ���W�Ɖ�]��ݒ�B
		/// </summary>
		void SetPosAndRot(const Vector3& pos, const Quaternion& rot)
		{
			m_rigidBody.SetPositionAndRotation(pos, rot);
		}
		/// <summary>
		/// ���̂��擾�B
		/// </summary>
		CRigidBody& GetRigidBody()
		{
			return m_rigidBody;
		}

	private:
		/// <summary>
		/// �ÓI�����I�u�W�F�N�g�쐬�̋��ʏ����B
		/// </summary>
		void CreateCommon(const Vector3& pos, const Quaternion& rot)override final;
	private:
		CRigidBody m_rigidBody;			//���́B
	};///class CPhysicsStaticObject

}///namespace Engine

