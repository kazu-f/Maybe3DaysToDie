#pragma once

#include "AStar.h"
class NaviMeshManager;
class Stage;

/// <summary>
/// A*���b�p�[�N���X�B
/// </summary>
class NavigationAgent
{
public:
	/// <summary>
	/// �W�F�l���[�^��ݒ�B
	/// </summary>
	/// <param name="ganerator"></param>
	void SetGenerator(Stage* stage)
	{
		m_stage = stage;
	}
	/// <summary>
	/// �t�b�g�X�e�b�v�t���AA*�ړ��B
	/// </summary>
	/// <param name="model">���f�������_�[�B</param>
	/// <param name="start">�X�^�[�g�ʒu�B</param>
	/// <param name="goal">�����ʒu�B</param>
	/// <param name="serchTime">AStar�𑖂点��p�x�B</param>
	/// <returns>�o�H�T�����I���������B</returns>
	bool MoveForFootStep(prefab::ModelRender* model, Vector3& start, Vector3& goal, float serchTime = 3.0f);

	/// <summary>
	/// �G�[�W�F���g�̈ʒu�A��]���擾�B
	/// </summary>
	/// <param name="pos">�ʒu�B</param>
	/// <param name="qRot">��]�B</param>
	void GetAgentPositionAndRotation(Vector3& pos, Quaternion& qRot)
	{
		pos += m_AgentPos - pos;
		qRot = m_AgentQrot;
	}
private:
	AStar									m_astar;						//�o�H�T���B
	std::vector<NVMGenerator::Cell*>		m_nodeList;						//�m�[�h�Z���B
	bool									m_isArrive = true;				//�������Ă�H
	Stage*									m_stage;						//�W�F�l���[�^�[ptr�B
	Vector3									m_toWayPoint;					//���̌o�H�Ɍ������x�N�g���B
	Vector3									m_AgentPos;						//�G�[�W�F���g�̈ʒu�B
	Quaternion								m_AgentQrot;					//�G�[�W�F���g�̉�]�B
	float									m_serchTime = 0.0f;				//�G�[�W�F���g���o�H���ĒT������܂ł̎��ԁB
};

