#pragma once

#include "RigidBody.h"
#include "PhysicsDebugDraw.h"

namespace Engine {
	class CCharacterController;

	class CPhysicsWorld : Noncopyable
	{
		std::unique_ptr<btDefaultCollisionConfiguration>	 m_collisionConfig;		//�R���W�����̐ݒ�H
		std::unique_ptr<btCollisionDispatcher>				 m_collisionDispatcher;	//�Փˉ��������B
		std::unique_ptr<btBroadphaseInterface>				 m_overlappingPairCache;	//�u���[�h�t�F�[�Y�B�Փ˔���̎}�؂�B�H
		std::unique_ptr<btSequentialImpulseConstraintSolver> m_constraintSolver;	//�R���X�g���C���g�\���o�[�B�S�������̉��������B�H
		std::unique_ptr<btDiscreteDynamicsWorld>			 m_dynamicWorld;		//�������[���h�B

#ifdef _DEBUG
		CPhysicsDebugDraw m_debugDraw;												//���C���[�t���[���\���B
#endif
	public:
		~CPhysicsWorld();
		void Init();		//�������B
		void Update(const float time);		//�������[���h�̍X�V�B
		void DebugDrawWorld(RenderContext& rc);		//�f�o�b�O�`��B
		void Release();		//��������B
		/// <summary>
		/// �d�͂̐ݒ�B
		/// </summary>
		void SetGravity(Vector3 g)
		{
			m_dynamicWorld->setGravity(btVector3(g.x, g.y, g.z));
		}
		/// <summary>
		/// �_�C�i�~�b�N���[���h�̎擾�B
		/// </summary>
		btDiscreteDynamicsWorld* GetDynamicWorld()
		{
			return m_dynamicWorld.get();
		}
		/// <summary>
		/// �f�o�b�O���[�h��ݒ肷��B
		/// </summary>
		/// <remarks>�w�肷��l��btIDebugDraw���Q�ƁB</remarks>
		/// <param name="debugMode"></param>
		void SetDebugMode(int debugMode)
		{
#ifdef _DEBUG
			m_debugDraw.setDebugMode(debugMode);
#endif
		}

		/// <summary>
		/// ���̂�o�^�B
		/// </summary>
		void AddRigidBody(CRigidBody& rb)
		{
			//�o�^����Ă��Ȃ��Ȃ�o�^�B
			if (rb.IsAddPhysicsWorld() == false) {
				m_dynamicWorld->addRigidBody(rb.GetBody());
				rb.SetMarkAddPhysicsWorld();
			}
		}
		/// <summary>
		/// ���̂�o�^�B(�}�X�N�t���B)
		/// </summary>
		/// <remarks>
		/// �}�X�N���g�����Ƃœ����蔻����s������𐧌��ł���炵���B
		/// </remarks>
		/// <param name="rb">���́B</param>
		/// <param name="grop">�O���[�v�H</param>
		/// <param name="mask">�}�X�N�B</param>
		void AddRigidBody(CRigidBody& rb, short group, short mask)
		{
			//�o�^����Ă��Ȃ��Ȃ�o�^�B
			if (rb.IsAddPhysicsWorld() == false) {
				m_dynamicWorld->addRigidBody(rb.GetBody(),group,mask);
				rb.SetMarkAddPhysicsWorld();
			}
		}
		/// <summary>
		/// ���̂�j���B
		/// </summary>
		void RemoveRigidBody(CRigidBody& rb)
		{
			//�o�^����Ă���Ȃ�j���B
			if (rb.IsAddPhysicsWorld() == true) {
				m_dynamicWorld->removeRigidBody(rb.GetBody());
				rb.SetUnMarkAddPhysicsWorld();
			}
		}
		/// <summary>
		/// �R���W�����I�u�W�F�N�g�����[���h�ɓo�^�B
		/// </summary>
		/// <param name="colliObj">�R���W�����I�u�W�F�N�g�B</param>
		void AddCollisionObject(btCollisionObject& colliObj)
		{
			m_dynamicWorld->addCollisionObject(&colliObj);
		}
		/// <summary>
		/// �R���W�����I�u�W�F�N�g�����[���h�ɓo�^�B(�}�X�N�t���B)
		/// </summary>
		/// <remarks>�����蔻����s������𐧌�ł���H</remarks>
		/// <param name="colliObj">�R���W�����I�u�W�F�N�g�B</param>
		/// <param name="grounp">�O���[�v�H</param>
		/// <param name="mask">�}�X�N�H</param>
		void AddCollisionObject(btCollisionObject& colliObj,short grounp,short mask)
		{
			m_dynamicWorld->addCollisionObject(&colliObj, grounp, mask);
		}
		/// <summary>
		/// �R���W�����I�u�W�F�N�g�����[���h����폜�B
		/// </summary>
		/// <param name="colliObj">�R���W�����I�u�W�F�N�g�B</param>
		void RemoveCollisionObject(btCollisionObject& colliObj)
		{
			m_dynamicWorld->removeCollisionObject(&colliObj);
		}
		/// <summary>
		/// �Փˌ��o���s���B
		/// </summary>
		/// <param name="castShape">���o���s������</param>
		/// <param name="convexFromWorld">�ړ��̎n�_�B</param>
		/// <param name="convextoWorld">�ړ��̏I�_</param>
		/// <param name="resultCallback">�R�[���o�b�N�p�֐��I�u�W�F�N�g</param>
		/// <param name="allowedCcdPenetration">�Ȃ񂾂�?</param>
		void ConvexSweepTest(
			const btConvexShape* castShape,
			const btTransform& convexFromWorld,
			const btTransform& convextoWorld,
			btCollisionWorld::ConvexResultCallback& resultCallback,
			btScalar allowedCcdPenetration = 0.0f
		) {
			m_dynamicWorld->convexSweepTest(
				castShape,
				convexFromWorld,
				convextoWorld,
				resultCallback,
				allowedCcdPenetration
			);
		}
		/// <summary>
		/// �ڐG���Ă��邩����B
		/// </summary>
		/// <param name="colObj">�R���W�����B</param>
		/// <param name="cb">�����̊֐��B</param>
		void ContactTest(
			btCollisionObject* colObj,
			std::function<void(const btCollisionObject& contactCollisionObject)> cb
		);
		/// <summary>
		/// �ڐG���Ă��邩����B
		/// </summary>
		/// <param name="rb">���W�b�h�{�f�B�B</param>
		/// <param name="cb">�����̊֐��B</param>
		void ContactTest(
			CRigidBody& rb,
			std::function<void(const btCollisionObject& contactCollisionObject)> cb
		);
		/// <summary>
		/// �ڐG���Ă��邩����B
		/// </summary>
		/// <param name="charaCon">�L�����R���B</param>
		/// <param name="cb">�����̊֐��B</param>
		void ContactTest(
			CCharacterController& charaCon,
			std::function<void(const btCollisionObject& contactCollisionObject)> cb	
		);

	};///class CPhysicsWorld

}///namespace Engine;