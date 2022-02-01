#include "stdafx.h"
#include "NaviMeshManager.h"
#include "Player/Player.h"
#include "Load/TerrainLoad/LoadingByChunk.h"

NaviMeshManager::~NaviMeshManager()
{
}

bool NaviMeshManager::Start()
{
	//�悭�Ȃ���Find����񂾂��g����Ȃ��I�H
	m_playerPtr = FindGO<Player>("player");
	m_terrainManager = FindGO<nsTerrain::TerrainManager>("Terrain");
	m_loadingByChunk = FindGO<LoadingByChunk>("LoadingByChunk");

	//�ŏ���NVM�����������y�сA�`�����N�̏������������Ăяo���B
	return true;
}

void NaviMeshManager::Update()
{
	//NVM���X�V����̂̓R���W����������͈͂̂݁B


	for (int x = 0; x < LoadingChunkCols; x++)
	{
		for (int y = 0; y < LoadingChunkCols; y++)
		{
			if ( m_loadingByChunk->IsNvmDirty(x, y) || m_terrainManager->GetTerrainWorld(x, y)->IsUpdateNvm() )
			{
				//�X�V���K�v�ȃ`�����N�͍X�V����B
				m_terrainManager->GetTerrainWorld(x, y)->CreateNVM();
				m_terrainManager->GetTerrainWorld(x, y)->ResetUpdateNvmFlag();
				m_loadingByChunk->NvmDirtyFlagDown(x, y);
			}
		}
	}

	//if (IsNvmDirty)
	//{
	//	//�n�`�̍X�V���Ȃ��B
	//	return;
	//}


}

void NaviMeshManager::CalcPlayerGrid()
{
	if (m_playerPtr == nullptr)
	{
		//�ړ����Ă���I�u�W�F�N�g���Ȃ����ߍX�V�͕K�v�Ȃ��B
		return;
	}

	//player�̈ʒu�B
	Vector3 playerPos = m_playerPtr->GetPosition();

	//�v���C���[�̈ʒu���O���b�h���B
	m_playerGrid[0] = static_cast<int>(std::floor((playerPos.x / OBJECT_UNIT) / ChunkWidth));// +MAX_CHUNK_SIDE / 2;
	m_playerGrid[1] = static_cast<int>(std::floor((playerPos.z / OBJECT_UNIT) / ChunkWidth));// +MAX_CHUNK_SIDE / 2;
	m_playerGrid[0] = max(min(MAX_CHUNK_SIDE - 1, m_playerGrid[0]), 1);
	m_playerGrid[1] = max(min(MAX_CHUNK_SIDE - 1, m_playerGrid[1]), 1);
}