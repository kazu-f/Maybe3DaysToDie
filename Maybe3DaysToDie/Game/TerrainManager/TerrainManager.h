#pragma once

#include "MarchingCubeTable.h"
#include "TerrainChunkData.h"
#include "TerrainWorld.h"

class NaviMeshManager;

namespace nsTerrain {

	class TerrainManager : public IGameObject
	{
	public:
		TerrainManager()
			:m_perlinNoise(2)
		{

		}

		bool Start()override final;
		void Update()override final;
		void OnDestroy() override final;
		void ForwardRender(RenderContext& rc) override final;

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
		/// �n�`�������s���B
		/// </summary>
		void PopurerTerrainMap();
		/// <summary>
		/// �`�����N���̒n�`�𐶐�����B
		/// </summary>
		/// <param name="chunkX">�`�����N��x�ʒu</param>
		/// <param name="chunkY">�`�����N��y�ʒu</param>
		void ChunkTerrainGenerate(int chunkX, int chunkY);
	private:
		static const int TERRAIN_WORLD_CHUNKSIZE = LoadingChunks;		//�n�`�̕\���͈́B
	private:
		CNoise m_perlinNoise;
		Terrain m_terrains[MAX_CHUNK_SIDE * ChunkWidth + 1][ChunkHeight][MAX_CHUNK_SIDE * ChunkWidth + 1];
		TerrainChunkData m_terrainChunkData[MAX_CHUNK_SIDE][MAX_CHUNK_SIDE];
		TerrainWorld* m_terrainWorlds[TERRAIN_WORLD_CHUNKSIZE][TERRAIN_WORLD_CHUNKSIZE] = { nullptr };
		NaviMeshManager* m_naviMeshManager = nullptr;
		bool m_isInitNVM = false;						//�i�r���b�V�������ς݂��H
	};

}
