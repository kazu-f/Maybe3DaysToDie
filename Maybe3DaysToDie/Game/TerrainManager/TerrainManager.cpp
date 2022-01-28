#include "stdafx.h"
#include "TerrainManager.h"
#include "DestructibleObject/Terrain/Terrain.h"
#include "Enemy/StandardZombie/StandardZombie.h"
#include "Enemy/EnemyGenerator.h"

namespace nsTerrain {
	bool TerrainManager::Start()
	{
		PopurerTerrainMap();		//�n�`�f�[�^�𐶐��B

		for (int chunkX = 0; chunkX < TERRAIN_WORLD_CHUNKSIZE; chunkX++)
		{
			for (int chunkY = 0; chunkY < TERRAIN_WORLD_CHUNKSIZE; chunkY++)
			{
				//�n�`�𐶐�����B
				m_terrainWorlds[chunkX][chunkY] = NewGO<TerrainWorld>(0);
				m_terrainWorlds[chunkX][chunkY]->SetTerrainChunkData(&m_terrainChunkData[chunkX][chunkY]);
				m_terrainWorlds[chunkX][chunkY]->SetTerrainPosition(
					{
						static_cast<float>(chunkX * ChunkWidth * OBJECT_UNIT),
						0.0f,
						static_cast<float>(chunkY * ChunkWidth * OBJECT_UNIT)
					}
				);
			}
		}

		return true;
	}
	void TerrainManager::Update()
	{
		if (m_terrainWorlds[0][0]->IsInited()
			&& !m_isInitNVM)
		{
			//NVM�f�[�^���쐬�B
			//m_NVMGenerator.CreateNVM(m_terrainWorlds[0][0]->GetTerrainRender(), true);
			////�G�L�������쐬�B
			//m_enemyGenerator.Create<StandardZombie>(&m_NVMGenerator);

			m_isInitNVM = true;
		}

		//if (InputKeyCode().IsTriggerKey(VK_F4)) {
		//	m_NVMGenerator.ChangeDrawFlag();
		//}
	}
	void TerrainManager::OnDestroy()
	{
		for (int chunkX = 0; chunkX < TERRAIN_WORLD_CHUNKSIZE; chunkX++)
		{
			for (int chunkY = 0; chunkY < TERRAIN_WORLD_CHUNKSIZE; chunkY++)
			{
				DeleteGO(m_terrainWorlds[chunkX][chunkY]);
			}
		}
	}
	void TerrainManager::PopurerTerrainMap()
	{
		//�n�`�𐶐�����B
		for (int chunkX = 0; chunkX < MAX_CHUNK_SIDE; chunkX++)
		{
			for (int chunkY = 0; chunkY < MAX_CHUNK_SIDE; chunkY++)
			{
				//�`�����N���ɒn�`���v�Z���Ă����B
				ChunkTerrainGenerate(chunkX, chunkY);
			}
		}
	}
	void TerrainManager::ChunkTerrainGenerate(int chunkX, int chunkY)
	{
		for (int x = 0; x < ChunkWidth + 1; x++)
		{
			for (int y = 0; y < ChunkHeight; y++)
			{
				for (int z = 0; z < ChunkWidth + 1; z++)
				{
					auto& terrain = m_terrains[x + ChunkWidth * chunkX][y][z + ChunkWidth * chunkY];
					float noise = m_perlinNoise.CalculationNoise(
						(static_cast<double>(x + (ChunkWidth * chunkX)) / static_cast<double>(ChunkWidth) * 1.5 + 0.001),
						(static_cast<double>(z + (ChunkWidth * chunkY)) / static_cast<double>(ChunkWidth) * 1.5 + 0.001)
						//,(static_cast<double>(y) / static_cast<double>(height) * 1.5 + 0.001)
					);

					noise = max(0.0f, min(1.0f, noise));

					float thisHeight = (static_cast<float>(ChunkHeight) * noise);

					float point = 0;

					////���̏ꏊ�̍����ɑ΂��ău���b�N���͂��Ă��Ȃ��B
					//if (y <= thisHeight - nsMarching::TERRAIN_SURFACE)
					//	point = 0.0f;
					////���̏ꏊ�̏�ɂ��u���b�N������B
					//else if (y > thisHeight + nsMarching::TERRAIN_SURFACE)
					//	point = 1.0f;
					////���̏ꏊ�̃u���b�N�̉e���l�v�Z�B(������B)
					//else if (y > thisHeight)
					//	point = (float)y - thisHeight;
					////���̏ꏊ�̃u���b�N�̉e���l�v�Z�B(�������B)
					//else
					//	point = thisHeight - (float)y;

					//���̏ꏊ�̍����ɑ΂��ău���b�N���͂��Ă��Ȃ��B
					if (y >= thisHeight - nsMarching::TERRAIN_SURFACE)
						point = 0.0f;
					//���̏ꏊ�̏�ɂ��u���b�N������B
					else if (y < thisHeight + nsMarching::TERRAIN_SURFACE)
						point = 1.0f;
					//���̏ꏊ�̃u���b�N�̉e���l�B
					else
						point = 0.5f;

					if (y == 0)
					{
						point = 1.0f;
					}

					terrain.SetVoxel(point);

					Vector3 pos;
					pos.x = static_cast<float>((x + ChunkWidth * chunkX)) * OBJECT_UNIT;
					pos.y = static_cast<float>(y) * OBJECT_UNIT;
					pos.z = static_cast<float>((z + ChunkWidth * chunkY)) * OBJECT_UNIT;
					terrain.SetPosition(pos);

					m_terrainChunkData[chunkX][chunkY].SetTerrainData(&terrain, x, y, z);
				}
			}
		}
	}
	void TerrainManager::ForwardRender(RenderContext& rc)
	{
		//m_NVMGenerator.DebugDraw(m_terrainWorlds[0][0]->GetTerrainRender());
	}
}