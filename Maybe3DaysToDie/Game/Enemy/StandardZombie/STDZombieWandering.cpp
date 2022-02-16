#include "stdafx.h"
#include "STDZombieWandering.h"
#include "StandardZombie.h"
#include "Enemy/IEnemy.h"
#include "Stage.h"
#include "Player/Player.h"

STDZombieWandering::STDZombieWandering(IEnemy* enemy) : IEnemyState::IEnemyState(enemy)
{
}

void STDZombieWandering::Enter()
{
	m_enemy->GetModelRender()->PlayAnimation(StandardZombie::EnAnimationState_Walk, 0.5f);
	m_enemy->GetAgent().ResetNodeList();
	m_target = m_enemy->GetPos();

}

void STDZombieWandering::Update()
{
	if (m_enemy->GetAgent().MoveForFootStep(m_enemy->GetModelRender(), m_enemy->GetPos(), m_target, m_serchTime))
	{
		//EnemyGrid.
		int enemyGrid[2];
		enemyGrid[0] = static_cast<int>(std::floor((m_enemy->GetPos().x / OBJECT_UNIT) / ChunkWidth));// +MAX_CHUNK_SIDE / 2;
		enemyGrid[1] = static_cast<int>(std::floor((m_enemy->GetPos().z / OBJECT_UNIT) / ChunkWidth));// +MAX_CHUNK_SIDE / 2;
		enemyGrid[0] = max(min(MAX_CHUNK_SIDE - 1, enemyGrid[0]), 1);
		enemyGrid[1] = max(min(MAX_CHUNK_SIDE - 1, enemyGrid[1]), 1);

		//PlayerGrid.
		int playerGrid[2];
		playerGrid[0] = static_cast<int>(std::floor((m_enemy->GetPlayer()->GetPosition().x / OBJECT_UNIT) / ChunkWidth));// +MAX_CHUNK_SIDE / 2;
		playerGrid[1] = static_cast<int>(std::floor((m_enemy->GetPlayer()->GetPosition().z / OBJECT_UNIT) / ChunkWidth));// +MAX_CHUNK_SIDE / 2;
		playerGrid[0] = max(min(MAX_CHUNK_SIDE - 1, playerGrid[0]), 1);
		playerGrid[1] = max(min(MAX_CHUNK_SIDE - 1, playerGrid[1]), 1);
		
		int E2PGrid[2];
		E2PGrid[0] = (enemyGrid[0] - playerGrid[0]) / 2;
		E2PGrid[1] = (enemyGrid[1] - playerGrid[1]) / 2;

		//自チャンクのセルをランダムで抽選して、それを次のパスに。
		auto& cellList = m_enemy->GetStage()->GetTerrainWorld()->GetTerrainWorld(E2PGrid[0], E2PGrid[1])->GetCellList();
		if (&cellList == nullptr)
		{
			return;
		}
		int index = rand() % cellList.size();
		
		m_target = cellList[index].m_CenterPos;

		m_serchTime = SUCCESS_TIME;
	}
	else
	{
		//探査失敗。
		m_serchTime = FAILED_TIME;
	}

	Quaternion qRot;
	qRot.SetRotation(Vector3::AxisY, atan2f(m_enemy->GetAgent().GetWayPoint().x, m_enemy->GetAgent().GetWayPoint().z));
	m_enemy->GetRot().Slerp(0.01f, m_enemy->GetRot(), qRot);
	m_enemy->SetPos(m_enemy->GetAgent().GetAgentPos());

}

void STDZombieWandering::Leave()
{
}
