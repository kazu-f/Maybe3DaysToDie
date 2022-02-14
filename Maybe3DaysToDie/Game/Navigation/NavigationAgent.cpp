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

	//経路を計算する。
	if (m_isArrive || m_serchTime > serchTime) {
		
		//全部のセルを統合。
		std::vector<NVMGenerator::Cell*> cellList;

		for (int chunkX = 0; chunkX < LoadingChunkCols; chunkX++)
		{
			for (int chunkY = 0; chunkY < LoadingChunkCols; chunkY++)
			{
				nsTerrain::TerrainWorld* currentChunk = m_stage->GetTerrainWorld()->GetTerrainWorld(chunkX, chunkY);

				for (auto& cell : currentChunk->GetCellList())
				{
					cellList.push_back(&cell);
				}

				for (auto& cell : m_stage->GetTerrainWorld()->GetNaviMeshManager()->GetEdgeCellList(chunkX, chunkY))
				{
					cellList.push_back(&cell);
				}
			}
		}

		//検索。
		m_nodeList = m_astar.Search(start, goal, cellList);
		m_serchTime = 0.0f;

	}

	//タイマー更新。
	m_serchTime += GameTime().GetFrameDeltaTime();

	if (m_nodeList.size() == 0) {
		m_isArrive = true;
		//ノードがない。
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

	if (dist < 10.0f) {
		//waypointに到着。
		m_nodeList.erase(m_nodeList.begin());
	}
}
