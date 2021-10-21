#pragma once
#include "Stage/SuperFlat/SuperFlat.h"
#include "Stage/Hill/Hill.h"

class Stage : public IGameObject
{
private:
	/// <summary>
	/// ������
	/// </summary>
	/// <returns>true��Ԃ��܂Ń��[�v����</returns>
	bool Start();
	/// <summary>
	/// �X�V
	/// </summary>
	void Update();
	/// <summary>
	/// delete������ƌĂ΂��֐�
	/// </summary>
	void OnDestroy();

	/// <summary>
	/// �R���W�����쐬
	/// </summary>
	void CreatePhysics();

private:
	/// <summary>
	/// �n�ʂ�\������
	/// </summary>
	void NewGround();
private:
	SuperFlat m_stage;
	//prefab::ModelRender* m_Model = nullptr;		//�n��
	//CPhysicsStaticObject m_StaticCol;		//�ÓI�����I�u�W�F�N�g
	//Vector3 m_pos = Vector3::Zero;		//�|�W�V����
	//Quaternion m_qrot = Quaternion::Identity;		//��]
	//Vector3 m_scale = Vector3::One;		//�X�P�[��
};

