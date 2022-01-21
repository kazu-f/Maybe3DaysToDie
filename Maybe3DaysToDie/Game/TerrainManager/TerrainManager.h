#pragma once
#include "MarchingCubeTable.h"
#include "TerrainChunkData.h"
#include "TerrainWorld.h"
#include <Game\GameConfig\WorldConfig\WorldConfig.h>

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
		CNoise m_perlinNoise;
		TerrainChunkData m_terrainChunkData[MAX_CHUNK_SIDE][MAX_CHUNK_SIDE];
		TerrainWorld* m_terrainWorlds[LoadingChunkCols][LoadingChunkCols] = { nullptr };
	};

}
