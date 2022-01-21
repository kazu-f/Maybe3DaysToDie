#pragma once
#include "MarchingCubeTable.h"
#include "TerrainChunkData.h"
#include "TerrainWorld.h"
#include <Game\GameConfig\WorldConfig\WorldConfig.h>
#include "Navigation/NVMGenerator.h"
#include "Enemy/EnemyGenerator.h"

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
		static const int TERRAIN_WORLD_CHUNKSIZE = LoadingChunks;		//地形の表示範囲。
	private:
		CNoise m_perlinNoise;
		Terrain m_terrains[MAX_CHUNK_SIDE * ChunkWidth + 1][ChunkHeight][MAX_CHUNK_SIDE * ChunkWidth + 1];
		TerrainChunkData m_terrainChunkData[MAX_CHUNK_SIDE][MAX_CHUNK_SIDE];
		TerrainWorld* m_terrainWorlds[TERRAIN_WORLD_CHUNKSIZE][TERRAIN_WORLD_CHUNKSIZE] = { nullptr };
		NVMGenerator m_NVMGenerator;					//NVM生成。
		EnemyGenerator m_enemyGenerator;				//enemyGenerator.
		bool m_isInitNVM = false;						//ナビメッシュ生成済みか？
	};

}
