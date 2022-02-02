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
	//�悭�Ȃ���Find����񂾂��g����Ȃ��I�H
	m_playerPtr = FindGO<Player>("player");
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

			if ( !LoadingChunkUpdateFlag && !m_terrainManager->GetTerrainWorld(x, y)->IsUpdateNvm() )
			{
				//�X�V�K�v�Ȃ��B
				continue;
			}

			//�X�V���K�v�ȃ`�����N�͍X�V����B
			m_terrainManager->GetTerrainWorld(x, y)->ResetNvm();

			if (LoadingChunkUpdateFlag)
			{
				//�u���b�N���ݒuor�j�󂳂ꂽ�̂ŁA�Z���̒ǉ��A�폜�������s���B
				std::vector<NVMGenerator::Cell> AddCellList;
				
				//�ݒu���ꂽ�u���b�N�̍��W�������B
				for (int i = 0; i < BlockKinds; i++)
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
						//�E���Z���B
						cell[1].pos[0] = UpperSufaceVertexs[VERTEX_FrontRight];
						cell[1].pos[1] = UpperSufaceVertexs[VERTEX_FrontLeft];
						cell[1].pos[2] = UpperSufaceVertexs[VERTEX_BackRight];

						AddCellList.push_back(cell[0]);
						AddCellList.push_back(cell[1]);
					}
				}

				for (auto& AddCell : AddCellList)
				{
					m_terrainManager->GetTerrainWorld(x, y)->AddCell(&AddCell);
				}

			}
			m_terrainManager->GetTerrainWorld(x, y)->CreateNVM();
			m_terrainManager->GetTerrainWorld(x, y)->ResetUpdateNvmFlag();
			m_loadingByChunk->NvmDirtyFlagDown(x, y);
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