#include "stdafx.h"
#include "NavigationAgent.h"
#include "AStar.h"

void NavigationAgent::MoveForFootStep(prefab::ModelRender* model, Vector3& start, Vector3& goal, float serchTime)
{
	if (m_generator == nullptr) {
		return;
	}

	//�o�H���v�Z����B
	if (m_isArrive && m_serchTime > serchTime) {
		m_nodeList = m_astar.Search(start, goal, m_generator->GetCellList());
		m_serchTime = 0.0f;
	}

	//�^�C�}�[�X�V�B
	m_serchTime += GameTime().GetFrameDeltaTime();

	if (m_nodeList.size() <= 1) {
		m_isArrive = true;
		//�m�[�h���q�����ĂȂ����ߓ����Ȃ��B
		return;
	}

	//�������Ă��Ȃ��B
	m_isArrive = false;
	
	//��]�v�Z�B
	m_toWayPoint = m_nodeList.front()->m_CenterPos - model->GetPosition();
	//�ړ��ʎZ�o�p��dist����Ă����B
	float dist = m_toWayPoint.Length();
	m_toWayPoint.Normalize();
	m_AgentQrot.SetRotation(Vector3::AxisY, atan2f(m_toWayPoint.x, m_toWayPoint.z));

	//footstep���A�ʒu�v�Z�B
	Vector3 footStep = model->GetFootstepMove();
	m_AgentPos = start + m_toWayPoint * footStep.Length();;

	if (dist < 5) {
		//waypoint�ɓ����B
		m_nodeList.erase(m_nodeList.begin());
	}
}
