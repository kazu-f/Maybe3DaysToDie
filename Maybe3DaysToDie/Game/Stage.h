#pragma once
#include "Stage/SuperFlat/SuperFlat.h"
#include "Stage/Hill/Hill.h"
#include "Enemy/EnemyGenerator.h"
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
	/// <summary>
	/// �n�ʂ�\������
	/// </summary>
	void NewGround();
public:
	/// <summary>
	/// �G�l�~�[�W�F�l���[�^�[���擾�B
	/// </summary>
	/// <returns></returns>
	EnemyGenerator& GetEnemyGenerator()
	{
		return m_enemyGenerator;
	}
private:
	SuperFlat m_stage;
	EnemyGenerator m_enemyGenerator;				//�G�l�~�[�W�F�l���[�^�[�B
	//prefab::ModelRender* m_Model = nullptr;		//�n��
	//CPhysicsStaticObject m_StaticCol;		//�ÓI�����I�u�W�F�N�g
	//Vector3 m_pos = Vector3::Zero;		//�|�W�V����
	//Quaternion m_qrot = Quaternion::Identity;		//��]
	//Vector3 m_scale = Vector3::One;		//�X�P�[��
};

