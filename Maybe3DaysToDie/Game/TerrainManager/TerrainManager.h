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
		/// 地形生成を行う。
		/// </summary>
		void PopurerTerrainMap();
		/// <summary>
		/// チャンク毎の地形を生成する。
		/// </summary>
		/// <param name="chunkX">チャンクのx位置</param>
		/// <param name="chunkY">チャンクのy位置</param>
		void ChunkTerrainGenerate(int chunkX, int chunkY);
	private:
		CNoise m_perlinNoise;
		TerrainChunkData m_terrainChunkData[MAX_CHUNK_SIDE][MAX_CHUNK_SIDE];
		TerrainWorld* m_terrainWorlds[LoadingChunkCols][LoadingChunkCols] = { nullptr };
	};

}
