#pragma once

#include "PhysicsObjectBase.h"

namespace Engine
{
	/// <summary>
	/// �S�[�X�g�I�u�W�F�N�g
	/// </summary>
	/// <remarks>
	/// �g�p���@
	/// Collision���쐬������A
	/// PhysicsWorld().ContactTest()�ŐڐG�������肽������������ɓn���A
	/// �֐��I�u�W�F�N�g��p���Ď��g�ƐڐG���Ă��邩�𔻒肷��B
	/// </remarks>
	class CPhysicsGhostObject:public CPhysicsObjectBase
	{
	public:
		~CPhysicsGhostObject()
		{
			Release();
		}
		/// <summary>
		/// ����B
		/// </summary>
		void Release()override final;
		
		/// <summary>
		/// �����œn���ꂽ�S�[�X�g�I�u�W�F�N�g���������g������B
		/// </summary>
		bool IsSelf(const btCollisionObject& ghost) const
		{
			return &ghost == &m_ghostObject;
		}
		/// <summary>
		/// ���W��ݒ�B
		/// </summary>
		void SetPosition(const Vector3& pos)
		{
			auto& btTrans = m_ghostObject.getWorldTransform();
			btVector3 btPos;
			pos.CopyTo(btPos);
			btTrans.setOrigin(btPos);
		}
		/// <summary>
		/// ��]��ݒ肷��B
		/// </summary>
		void SetRotation(const Quaternion& rot)
		{
			auto& btTrans = m_ghostObject.getWorldTransform();
			btQuaternion btRot;
			rot.CopyTo(btRot);
			btTrans.setRotation(btRot);
		}
	private:
		/// <summary>
		/// �S�[�X�g�쐬�����̋��ʏ����B
		/// </summary>
		/// <param name="pos">���W�B</param>
		/// <param name="rot">��]�B</param>
		void CreateCommon(const Vector3& pos, const Quaternion& rot)override;
	private:
		bool			m_isRegistPhysicsWorld = false;		//�������[���h�ɓo�^�ς݂��H
		btGhostObject	m_ghostObject;						//�S�[�X�g�I�u�W�F�N�g�B
	};///class CGhostObject;
}///namespace Engine;

