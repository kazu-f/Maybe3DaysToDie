#pragma once

#include "MarchingCubeTable.h"
#include "TerrainChunkData.h"
#include "TerrainWorld.h"

class NaviMeshManager;
class SaveDataFile;

namespace nsTerrain {

	class TerrainManager : public IGameObject
	{
	public:
		TerrainManager()
			:m_perlinNoise(2)
		{
			for (auto& terrainX : m_terrains)
			{
				for (auto& terrainY : terrainX)
				{
					for (auto& terrain : terrainY)
					{
						terrain = std::make_unique<Terrain>();
					}
				}
			}
		}

		bool Start()override final;
		void Update()override final;
		void OnDestroy() override final;

	public:
		/// <summary>
		/// �n�`�������s���B
		/// </summary>
		void PopurerTerrainMap();
		/// <summary>
		/// �Z�[�u�f�[�^����ǂݍ���Œn�`�𐶐�����B
		/// </summary>
		/// <param name="saveDataFile"></param>
		void LoadTerrainData(SaveDataFile* saveDataFile);
		/// <summary>
		/// �n�`���Z�[�u����B
		/// </summary>
		/// <param name="saveDataFile"></param>
		void SaveTerrainData(SaveDataFile* saveDataFile);

	public:
		TerrainChunkData& GetTerrainChunkData(int chunkX, int chunkY)
		{
			return m_terrainChunkData[chunkX][chunkY];
		}
		TerrainWorld* GetTerrainWorld(int chunkX, int chunkY)
		{
			return m_terrainWorlds[chunkX][chunkY];
		}

	private:
		/// <summary>
		/// �`�����N���̒n�`�𐶐�����B
		/// </summary>
		/// <param name="chunkX">�`�����N��x�ʒu</param>
		/// <param name="chunkY">�`�����N��y�ʒu</param>
		void ChunkTerrainGenerate(int chunkX, int chunkY);
		/// <summary>
		/// �`�����N���Œn�`�f�[�^��ǂݍ��ށB
		/// </summary>
		void LoadTerrainInChunk(int chunkX, int chunkY, SaveDataFile* saveDataFile);
		/// <summary>
		/// �`�����N���Œn�`�f�[�^���Z�[�u�B
		/// </summary>
		void SaveTerrainInChunk(int chunkX, int chunkY, SaveDataFile* saveDataFile);

	private:
		static const int TERRAIN_WORLD_CHUNKSIZE = LoadingChunks;		//�n�`�̕\���͈́B
	private:
		CNoise m_perlinNoise;
		std::unique_ptr<Terrain> m_terrains[MAX_CHUNK_SIDE * ChunkWidth + 1][ChunkHeight][MAX_CHUNK_SIDE * ChunkWidth + 1];
		TerrainChunkData m_terrainChunkData[MAX_CHUNK_SIDE][MAX_CHUNK_SIDE];
		TerrainWorld* m_terrainWorlds[TERRAIN_WORLD_CHUNKSIZE][TERRAIN_WORLD_CHUNKSIZE] = { nullptr };
		NaviMeshManager* m_naviMeshManager = nullptr;
		bool m_isInitNVM = false;						//�i�r���b�V�������ς݂��H
	};

}
