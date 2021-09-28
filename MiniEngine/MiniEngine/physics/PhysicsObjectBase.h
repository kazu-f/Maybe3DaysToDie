#pragma once

namespace Engine {
	class Model;
	class TkmFile;
	namespace prefab {
		class ModelRender;
	}

	/// <summary>
	/// �����I�u�W�F�N�g�̃x�[�X�N���X�B
	/// </summary>
	class CPhysicsObjectBase
	{
		//���z�֐��B
	public:
		/// <summary>
		/// �S�[�X�g�I�u�W�F�N�g������B
		/// </summary>
		virtual void Release() = 0;
	private:
		/// <summary>
		/// �ÓI�����I�u�W�F�N�g�쐬�����̋��ʏ����B
		/// </summary>
		virtual void CreateCommon(const Vector3& pos, const Quaternion& rot) = 0;

	public:
		/// <summary>
		/// �R���X�g���N�^�B
		/// </summary>
		CPhysicsObjectBase()
		{
		}
		/// <summary>
		/// �f�X�g���N�^�B
		/// </summary>
		virtual ~CPhysicsObjectBase()
		{
		}
		/// <summary>
		/// �{�b�N�X�`��̃S�[�X�g�I�u�W�F�N�g���쐬�B
		/// </summary>
		/// <param name="pos">���W�B</param>
		/// <param name="rot">��]�B</param>
		/// <param name="size">�T�C�Y�B</param>
		void CreateBox(const Vector3& pos, const Quaternion& rot, const Vector3& size);
		/// <summary>
		/// �J�v�Z���`��̃S�[�X�g�I�u�W�F�N�g���쐬�B
		/// </summary>
		/// <param name="pos">���W�B</param>
		/// <param name="rot">��]�B</param>
		/// <param name="radius">�J�v�Z���̔��a�B</param>
		/// <param name="height">�J�v�Z���̍����B</param>
		void CreateCapsule(const Vector3& pos, const Quaternion& rot, const float radius, const float height);
		/// <summary>
		/// ���̌`��̃S�[�X�g�I�u�W�F�N�g���쐬�B
		/// </summary>
		/// <param name="pos">���W�B</param>
		/// <param name="rot">��]�B</param>
		/// <param name="radius">���̂̔��a�B</param>
		void CreateSphere(const Vector3& pos, const Quaternion& rot, const float radius);
		/// <summary>
		/// ���b�V���`��̃S�[�X�g�I�u�W�F�N�g���쐬�B
		/// </summary>
		/// <param name="pos">���W�B</param>
		/// <param name="rot">��]�B</param>
		/// <param name="tkmFile">tkm�t�@�C���B</param>
		void CreateMesh(const Vector3& pos, const Quaternion& rot,const TkmFile& tkmFile);
		/// <summary>
		/// ���b�V���`��̃S�[�X�g�I�u�W�F�N�g���쐬�B(Model�N���X�B)
		/// </summary>
		/// <param name="pos">���W�B</param>
		/// <param name="rot">��]�B</param>
		/// <param name="scale">�X�P�[���B</param>
		/// <param name="model">�X�L�����f���B</param>
		void CreateMesh(const Vector3& pos, const Quaternion& rot, const Vector3 & scale, const Model& model);
		/// <summary>
		/// ���b�V���`��̃S�[�X�g�I�u�W�F�N�g���쐬�B(ModelRender�N���X�B)
		/// </summary>
		/// <param name="pos">���W�B</param>
		/// <param name="rot">��]�B</param>
		/// <param name="scale">�X�P�[���B</param>
		/// <param name="model">���f�������_�[�B</param>
		void CreateMesh(const Vector3& pos, const Quaternion& rot, const Vector3& scale, prefab::ModelRender* model);

	protected:
		std::unique_ptr<ICollider> m_sphere;		//�R���C�_�[�B
	};///class CPhysicsObjectBase

}///namespace Engine
