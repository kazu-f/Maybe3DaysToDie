#pragma once

#include "IEnemyState.h"
#include "Navigation/NavigationAgent.h"
#include "IK/FootIK.h"

class EnemyGenerator;

/// <summary>
/// �G�L�����̊��N���X�B
/// </summary>
/// <remarks>
/// �G�L�������쐬����ۂ́A���̃N���X���p�����č쐬���Ă������ƁB
/// �T���v���R�[�h��StandardZombie�ɂ���B
/// ���A�p�����[�^�[�͔h����̃N���X�ŕێ��A���������s�����ƁB
/// </remarks>
class IEnemy : public IGameObject
{
public:
	/// <summary>
	/// �G�l�~�[�̏������p�����[�^�[�B
	/// </summary>
	/// <remarks>
	/// �h���N���X�ŕێ������āA�e�p�����[�^�����������Ďg�p���邱�ƁB
	/// </remarks>
	struct EnemyParams
	{
		//Status
		unsigned int Attack = 20;		//�U���́B		
		unsigned int Deffence = 5;		//�h��́B		
		unsigned int EXP = 500;			//�����o���l�B	
		float MoveSpeed = 3.0f;			//�ړ����x�B	

		//move(cm)
		float AttackRange = 150.0f;		//�U���͈́B	
		float SearchRange = 20000.0f;	//���G�͈́B	
	};
public:
	/// <summary>
	/// �R���X�g���N�^�B
	/// </summary>
	IEnemy();
	
	void OnDestroy() override final;
	/// <summary>
	/// �X�^�[�g�B
	/// </summary>
	/// <returns></returns>
	virtual bool Start() override = 0;
	/// <summary>
	/// �X�V�B
	/// </summary>
	virtual void Update() override = 0;
	/// <summary>
	/// �G�l�~�[�̃p�����[�^�[���擾�B
	/// <para>�h���N���X�Ńp�����[�^�[��Ԃ��������������邱�ƁB</para>
	/// </summary>
	/// <returns></returns>
	virtual EnemyParams& GetEnemyParameters() = 0;
public:
	/// <summary>
	/// �G�[�W�F���g�t�����f���������B
	/// </summary>
	/// <param name="initData">�������f�[�^�[�B</param>
	/// <param name="tag">�^�O�B</param>
	/// <param name="mesh">�i�r���b�V���B</param>
	/// <param name="animClipDatas">�A�j���[�V�����N���b�v�B</param>
	/// <param name="isRandMove">�����_���ړ����邩�B</param>
	//void InitNavActor(ModelInitData& initData, const char* tag, NaviMesh* mesh, AnimClipInitData animClipDatas[] = nullptr, int animSize = 0,  bool isRandMove = false);
public://�Ȃ�tripleTrash�I�J�s�[�B
	/// <summary>
	/// �A�N�^�[�������B
	/// <para>�G�[�W�F���g�͊܂܂Ȃ��B</para>
	/// </summary>
	/// <param name="initData">���f���̏������f�[�^�[�B</param>
	/// <param name="tag">�^�O�B</param>
	/// <param name="animClipDatas">�A�j���[�V�����f�[�^�[�B</param>
	void InitActor(ModelInitData& initData, const char* tag, AnimClipInitData animClipDatas[] = nullptr, int animSize = 0);
public://setter
	/// <summary>
	/// �X�e�[�g��ύX�B
	/// </summary>
	/// <param name="state"></param>
	void ChangeState(IEnemyState* state)
	{
		if (m_currentState == state) {
			//�ꏏ�̏ꍇ�͓��ɉ����s��Ȃ��B
			return;
		}

		//�X�e�[�g��ύX�̍ۂɊ֐����Ăяo���B
		if (m_currentState != nullptr) {
			m_currentState->Leave();
		}
		m_currentState = state;
		m_currentState->Enter();
	}
	/// <summary>
	/// �W�F�l���[�^�[��ݒ�B
	/// </summary>
	/// <param name="generator">�W�F�l���[�^�[�B</param>
	void SetEnemyGenerator(EnemyGenerator* generator)
	{
		m_generatorPtr = generator;
	}
	/// <summary>
	/// NVM�W�F�l���[�^�[��ݒ�B
	/// </summary>
	/// <param name="generator"></param>
	void SetNVMGenerator(Stage* stage)
	{
		m_agent.SetGenerator(stage);
	}
	/// <summary>
	/// �ʒu��ݒ�B
	/// </summary>
	/// <param name="pos"></param>
	void SetPos(Vector3& pos)
	{
		m_pos = pos;
	}
public://getter
	/// <summary>
	/// �G�[�W�F���g���擾�B
	/// </summary>
	/// <returns></returns>
	NavigationAgent& GetAgent()
	{
		return m_agent;
	}
	/// <summary>
	/// ���f�������_�[���擾�B
	/// </summary>
	/// <returns></returns>
	prefab::ModelRender* GetModelRender() const
	{
		return m_modelRender;
	}
	/// <summary>
	/// ���݂̃X�e�[�g���擾�B
	/// </summary>
	/// <returns></returns>
	IEnemyState* GetCurrentState() const 
	{
		return m_currentState;
	}
	/// <summary>
	/// �ʒu���擾�B
	/// </summary>
	/// <returns></returns>
	Vector3& GetPos()
	{
		return m_pos;
	}
	/// <summary>
	/// ��]���擾�B
	/// </summary>
	/// <returns></returns>
	Quaternion& GetRot()
	{
		return m_rot;
	}

	FootIK& GetIK()
	{
		return m_footIK;
	}
private:
	prefab::ModelRender*	m_modelRender = nullptr;	//�����_�[�B
	EnemyGenerator*			m_generatorPtr;				//�W�F�l���[�^�[�̃|�C���^�B
	IEnemyState*			m_currentState = nullptr;	//���݂̃X�e�[�g�B
	Vector3					m_pos = g_vec3Zero;			//���W�B
	Quaternion				m_rot = g_quatIdentity;		//��]�B
	NavigationAgent			m_agent;					//�G�[�W�F���g�B
	FootIK					m_footIK;
};

