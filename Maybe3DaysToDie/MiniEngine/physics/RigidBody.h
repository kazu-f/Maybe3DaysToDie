#pragma once

#include "ICollider.h"

namespace Engine {

	class ICollider;

	/// <summary>
	/// ���̏��B
	/// </summary>
	struct RigidBodyInfo {
		RigidBodyInfo() :
			collider(NULL),
			mass(0.0f)
		{
			pos = Vector3::Zero;
			rot = Quaternion::Identity;
			localInteria = Vector3::Zero;
		}
		Vector3 pos;			//���W
		Quaternion rot;			//��]
		Vector3 localInteria;	//�����e���\���B��]�̂��₷��(0.0f �` 1.0f)�B
		ICollider* collider;	//�R���C�_�[�B
		float mass;				//���ʁB
	};///struct RigidBodyInfo

	/// <summary>
	/// ���̃N���X�B
	/// </summary>
	class CRigidBody : Noncopyable
	{					//�������[���h�ɒǉ�����Ă��邩�H
	public:
		~CRigidBody();
		void Release();		//����B
		/// <summary>
		/// ���̂��쐬����B
		/// </summary>
		/// <param name="rbInfo">���̏��B</param>
		/// <param name="isRegistPhysicsWorld">�������[���h�ɓo�^���邩�H</param>
		void Create(RigidBodyInfo& rbInfo,bool isRegistPhysicsWorld = true);
		//���̂��擾�B
		btRigidBody* GetBody()
		{
			return m_rigidBody.get();
		}
		//�������[���h�ɓo�^�����������B
		void SetMarkAddPhysicsWorld()
		{
			m_isAddPhysicsWorld = true;
		}
		//�������[���h�ɓo�^���̈���O���B
		void SetUnMarkAddPhysicsWorld()
		{
			m_isAddPhysicsWorld = false;
		}
		//�������[���h�ɒǉ�����Ă��邩�H
		bool IsAddPhysicsWorld() const
		{
			return m_isAddPhysicsWorld;
		}
	public:		//Get�֐��B
		/// <summary>
		/// �����I�u�W�F�N�g�̍��W�Ɖ�]���擾�B
		/// </summary>
		/// <param name="pos"></param>
		/// <param name="rot"></param>
		void GetPositionAndRotation(Vector3& pos, Quaternion& rot)
		{
			btTransform trans;
			m_myMotionState->getWorldTransform(trans);
			pos.Set(trans.getOrigin());
			rot.Set(trans.getRotation());
		}


	public:		//Set�֐��B
		/// <summary>
		/// �����I�u�W�F�N�g�̍��W�Ɖ�]��ݒ�B
		/// </summary>
		void SetPositionAndRotation(const Vector3& pos, const Quaternion& rot)
		{
			btTransform trans;
			btVector3 btPos;
			pos.CopyTo(btPos);
			trans.setOrigin(btPos);
			btQuaternion btRot;
			rot.CopyTo(btRot);
			trans.setRotation(btRot);
			m_rigidBody->setWorldTransform(trans);
		}
		/// <summary>
		/// ���x��ݒ�B
		/// </summary>
		/// <param name="vel">���x�x�N�g���B</param>
		void SetLinerVelocity(const Vector3& vel)
		{
			btVector3 btVel;
			btVel.setValue(vel.x, vel.y, vel.z);
			m_rigidBody->setLinearVelocity(btVel);
			m_rigidBody->activate();
		}
		/// <summary>
		/// ���C��ݒ�B
		/// </summary>
		/// <param name="frict">���C�W���H</param>
		void SetFriction(const float frict)
		{
			m_rigidBody->setFriction(frict);			//�ړ��p�̖��C�H
			m_rigidBody->setRollingFriction(frict);		//��]�ɂ����C���g���炵���H
		}
		/// <summary>
		/// �ړ��\���̐ݒ�B
		/// </summary>
		/// <param name="x">X���B</param>
		/// <param name="y">Y���B</param>
		/// <param name="z">Z���B</param>
		void SetLinearFactor(const float x, const float y, const float z)
		{
			Vector3 v = { x,y,z };
			SetLinearFactor(v);
		}
		/// <summary>
		/// �ړ��\���̐ݒ�B
		/// </summary>
		/// <param name="linearFactor">���̒l�B</param>
		void SetLinearFactor(const Vector3& linearFactor)
		{
			btVector3 v;
			v.setValue(linearFactor.x, linearFactor.y, linearFactor.z);
			m_rigidBody->setLinearFactor(v);
		}
		/// <summary>
		/// �p���x�̐ݒ�B
		/// </summary>
		/// <param name="angVel">�p���x�B</param>
		void SetAngularVelocity(const Vector3& angVel)
		{
			btVector3 v;
			v.setValue(angVel.x, angVel.y, angVel.z);
			m_rigidBody->setAngularVelocity(v);
			m_rigidBody->activate();
		}
		/// <summary>
		/// ��]�\����ݒ�B
		/// </summary>
		/// <param name="x">X���B</param>
		/// <param name="y">Y���B</param>
		/// <param name="z">Z���B</param>
		void SetAngularFactor(const float x, const float y, const float z)
		{
			SetAngularFactor({ x,y,z });
		}
		/// <summary>
		/// ��]�\����ݒ�B
		/// </summary>
		/// <param name="angFactor">��]�\���B</param>
		void SetAngularFactor(const Vector3& angFactor)
		{
			btVector3 v;
			v.setValue(angFactor.x, angFactor.y, angFactor.z);
			m_rigidBody->setAngularFactor(v);
		}

		void SetGravity(const float g)
		{
			btVector3 v;
			v.setValue(0.0f, -g, 0.0f);
			m_rigidBody->setGravity(v);
		}
		/// <summary>
		/// �͂�������B
		/// </summary>
		/// <param name="force">�́B</param>
		/// <param name="relPos">��������W�B</param>
		void AddForce(const Vector3& force, const Vector3& relPos)
		{
			btVector3 btForce;
			btVector3 btRelPos;
			force.CopyTo(btForce);
			relPos.CopyTo(btRelPos);
			m_rigidBody->applyForce(btForce, btRelPos);
			m_rigidBody->activate();
		}

	private:
		std::unique_ptr<btRigidBody>		m_rigidBody;		//���́B
		std::unique_ptr<btDefaultMotionState>	m_myMotionState;//���[�V�����X�e�[�g�B�H
		bool m_isAddPhysicsWorld = false;

	};///class CRigidBody;

}///namespace Engine;
