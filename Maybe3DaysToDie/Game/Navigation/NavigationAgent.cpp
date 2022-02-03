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
	////プレイヤーの位置をグリッド化。
	//EnemyGrid[0] = static_cast<int>(std::floor((m_AgentPos.x / OBJECT_UNIT) / ChunkWidth));// +MAX_CHUNK_SIDE / 2;
	//EnemyGrid[1] = static_cast<int>(std::floor((m_AgentPos.z / OBJECT_UNIT) / ChunkWidth));// +MAX_CHUNK_SIDE / 2;
	//EnemyGrid[0] = max(min(MAX_CHUNK_SIDE - 1, EnemyGrid[0]), 1);
	//EnemyGrid[1] = max(min(MAX_CHUNK_SIDE - 1, EnemyGrid[1]), 1);

	nsTerrain::TerrainWorld* currentChunk =  m_stage->GetTerrainWorld()->GetTerrainWorld(0, 0);

	//経路を計算する。
	if (m_isArrive || m_serchTime > serchTime) {
		m_nodeList = m_astar.Search(start, goal, currentChunk->GetCellList());
		m_serchTime = 0.0f;

	}

	//タイマー更新。
	m_serchTime += GameTime().GetFrameDeltaTime();

	if (m_nodeList.size() <= 1) {
		m_isArrive = true;
		//ノードが繋がってないため動かない。
		return;
	}

	//到着していない。
	m_isArrive = false;
	
	//回転計算。
	m_toWayPoint = m_nodeList.front()->m_CenterPos - model->GetPosition();
	//移動量算出用にdist取っておく。
	float dist = m_toWayPoint.Length();
	m_toWayPoint.Normalize();
	m_AgentQrot.SetRotation(Vector3::AxisY, atan2f(m_toWayPoint.x, m_toWayPoint.z));

	//footstepより、位置計算。
	Vector3 footStep = model->GetFootstepMove();
	m_AgentPos = start + m_toWayPoint * footStep.Length();;

	if (dist < 5) {
		//waypointに到着。
		m_nodeList.erase(m_nodeList.begin());
	}
}
