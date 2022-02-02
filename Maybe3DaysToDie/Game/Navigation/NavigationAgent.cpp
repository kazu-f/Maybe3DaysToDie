#include "stdafx.h"
#include "NavigationAgent.h"
#include "AStar.h"
#include "NaviMeshManager.h"
#include "Stage.h"

void NavigationAgent::MoveForFootStep(prefab::ModelRender* model, Vector3& start, Vector3& goal, float serchTime)
{
	if (m_stage == nullptr) {
		return;
	}

	//float EnemyGrid[2] = { 0 };
	////�v���C���[�̈ʒu���O���b�h���B
	//EnemyGrid[0] = static_cast<int>(std::floor((m_AgentPos.x / OBJECT_UNIT) / ChunkWidth));// +MAX_CHUNK_SIDE / 2;
	//EnemyGrid[1] = static_cast<int>(std::floor((m_AgentPos.z / OBJECT_UNIT) / ChunkWidth));// +MAX_CHUNK_SIDE / 2;
	//EnemyGrid[0] = max(min(MAX_CHUNK_SIDE - 1, EnemyGrid[0]), 1);
	//EnemyGrid[1] = max(min(MAX_CHUNK_SIDE - 1, EnemyGrid[1]), 1);

	nsTerrain::TerrainWorld* currentChunk =  m_stage->GetTerrainWorld()->GetTerrainWorld(0, 0);

	//�o�H���v�Z����B
	if (m_isArrive || m_serchTime > serchTime) {
		m_nodeList = m_astar.Search(start, goal, currentChunk->GetCellList());
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
