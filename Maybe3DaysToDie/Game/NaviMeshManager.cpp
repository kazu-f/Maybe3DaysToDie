#include "stdafx.h"
#include "NaviMeshManager.h"
#include "Player/Player.h"
#include "Load/TerrainLoad/LoadingByChunk.h"
#include "TerrainManager/TerrainManager.h"

NaviMeshManager::~NaviMeshManager()
{
}

bool NaviMeshManager::Start()
{
	m_terrainManager = FindGO<nsTerrain::TerrainManager>("Terrain");
	m_loadingByChunk = FindGO<LoadingByChunk>("LoadingByChunk");

	//�ŏ���NVM�����������y�сA�`�����N�̏������������Ăяo���B
	return true;
}

void NaviMeshManager::Update()
{

	for (int x = 0; x < LoadingChunkCols; x++)
	{
		for (int y = 0; y < LoadingChunkCols; y++)
		{
			bool LoadingChunkUpdateFlag = m_loadingByChunk->IsNvmDirty(x, y);

			if (!LoadingChunkUpdateFlag && !m_terrainManager->GetTerrainWorld(x, y)->IsUpdateNvm())
			{
				//�X�V�K�v�Ȃ��B
				continue;
			}

			//�n�`�ɍX�V������B
			m_terrainManager->GetTerrainWorld(x, y)->ResetNvm();
			m_edgeCellList[x][y].clear();

			//�ǉ��Z���B
			std::vector<NVMGenerator::Cell> AddCellList;

			//�ݒu���ꂽ�u���b�N�̍��W�������B
			for (int i = 0; i < m_loadingByChunk->GetChunkBlock(x, y)->GetInstancingDataSize(); i++)
			{
				for (const auto& placementObject : m_loadingByChunk->GetChunkBlock(x, y)->GetInstancingData(i))
				{
					//�u���b�N��ʂ̂S�_���v�Z�B
					Vector3 UpperSufaceVertexs[4];
					UpperSufaceVertexs[VERTEX_BackLeft] =
					{ placementObject.pos.x - 50.0f, placementObject.pos.y + 50.0f, placementObject.pos.z + 50.0f };
					UpperSufaceVertexs[VERTEX_BackRight] =
					{ placementObject.pos.x + 50.0f, placementObject.pos.y + 50.0f, placementObject.pos.z + 50.0f };
					UpperSufaceVertexs[VERTEX_FrontLeft] =
					{ placementObject.pos.x - 50.0f, placementObject.pos.y + 50.0f, placementObject.pos.z - 50.0f };
					UpperSufaceVertexs[VERTEX_FrontRight] =
					{ placementObject.pos.x + 50.0f, placementObject.pos.y + 50.0f, placementObject.pos.z - 50.0f };

					//�Z���𐶐����Ă����B
					NVMGenerator::Cell cell[2];
					//�����Z���B
					cell[0].pos[0] = UpperSufaceVertexs[VERTEX_BackLeft];
					cell[0].pos[1] = UpperSufaceVertexs[VERTEX_BackRight];
					cell[0].pos[2] = UpperSufaceVertexs[VERTEX_FrontLeft];
					cell[0].m_CenterPos =
					{ placementObject.pos.x - 25.0f, placementObject.pos.y + 50.0f, placementObject.pos.z + 25.0f };
					//�E���Z���B
					cell[1].pos[0] = UpperSufaceVertexs[VERTEX_FrontRight];
					cell[1].pos[1] = UpperSufaceVertexs[VERTEX_FrontLeft];
					cell[1].pos[2] = UpperSufaceVertexs[VERTEX_BackRight];
					cell[1].m_CenterPos = 
					{ placementObject.pos.x + 25.0f, placementObject.pos.y + 50.0f, placementObject.pos.z - 25.0f };

					AddCellList.push_back(cell[0]);
					AddCellList.push_back(cell[1]);
				}
			}

			for (auto& baseCell : AddCellList) {
				m_terrainManager->GetTerrainWorld(x, y)->AddCell(&baseCell);
			}

			m_terrainManager->GetTerrainWorld(x, y)->CreateNVM(x, y);
		}
	}

	for (int x = 0; x < LoadingChunkCols; x++)
	{
		for (int y = 0; y < LoadingChunkCols; y++)
		{

			bool LoadingChunkUpdateFlag = m_loadingByChunk->IsNvmDirty(x, y);

			if (!LoadingChunkUpdateFlag && !m_terrainManager->GetTerrainWorld(x, y)->IsUpdateNvm())
			{
				continue;
			}

			m_terrainManager->GetTerrainWorld(x, y)->SerchLinkCell(x,y);
			m_terrainManager->GetTerrainWorld(x, y)->PreRenderNVM(x,y);

			m_terrainManager->GetTerrainWorld(x, y)->ResetUpdateNvmFlag();
			m_loadingByChunk->NvmDirtyFlagDown(x, y);

		}
	}

}

void NaviMeshManager::SerchLinkCell(NVMGenerator::Cell* cell)
{
	
}
