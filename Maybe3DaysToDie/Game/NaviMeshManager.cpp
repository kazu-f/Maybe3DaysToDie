#include "stdafx.h"
#include "NaviMeshManager.h"
#include "Player/Player.h"

NaviMeshManager::~NaviMeshManager()
{
}

bool NaviMeshManager::Start()
{
	//よくないがFindあるんだし使うよなぁ！？
	m_playerPtr = FindGO<Player>("player");



	//最初のNVM初期化処理及び、チャンクの初期化処理を呼び出す。
	return true;
}

void NaviMeshManager::Update()
{
	if (!m_isUpdateNVM)
	{
		//地形の更新がない。
		return;
	}

	//NVMを更新していく。

}

void NaviMeshManager::CalcPlayerGrid()
{
	if (m_playerPtr == nullptr)
	{
		//移動しているオブジェクトがないため更新は必要ない。
		return;
	}

	//playerの位置。
	Vector3 playerPos = m_playerPtr->GetPosition();

	//プレイヤーの位置をグリッド化。
	m_playerGrid[0] = static_cast<int>(std::floor((playerPos.x / OBJECT_UNIT) / ChunkWidth));// +MAX_CHUNK_SIDE / 2;
	m_playerGrid[1] = static_cast<int>(std::floor((playerPos.z / OBJECT_UNIT) / ChunkWidth));// +MAX_CHUNK_SIDE / 2;
	m_playerGrid[0] = max(min(MAX_CHUNK_SIDE - 1, m_playerGrid[0]), 1);
	m_playerGrid[1] = max(min(MAX_CHUNK_SIDE - 1, m_playerGrid[1]), 1);
}