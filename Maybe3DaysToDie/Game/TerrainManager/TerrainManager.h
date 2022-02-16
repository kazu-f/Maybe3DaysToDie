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
		/// セーブデータファイルをセット。
		/// </summary>
		/// <param name="saveData"></param>
		void SetSaveDataFile(SaveDataFile* saveData)
		{
			m_saveDataFile = saveData;
		}
		/// <summary>
		/// パーリンノイズを使った地形生成を行う。
		/// </summary>
		/// <remarks>
		/// <para>Start関数が走る前に地形を生成しておく必要があります。</para>
		/// <para>この関数かLoadTerrainData関数を使ってTerrainデータを構築してください。</para>
		/// </remarks>
		void PopurerTerrainMap();
		/// <summary>
		/// セーブデータから読み込んで地形を生成する。
		/// </summary>
		/// <param name="saveDataFile"></param>
		void LoadTerrainData(SaveDataFile* saveDataFile);
		/// <summary>
		/// 地形をセーブする。
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
		NaviMeshManager* GetNaviMeshManager()
		{
			return m_naviMeshManager;
		}


	private:
		/// <summary>
		/// チャンク毎の地形を生成する。
		/// </summary>
		/// <param name="chunkX">チャンクのx位置</param>
		/// <param name="chunkY">チャンクのy位置</param>
		void ChunkTerrainGenerate(int chunkX, int chunkY);
		/// <summary>
		/// チャンク毎で地形データを読み込む。
		/// </summary>
		void LoadTerrainInChunk(int chunkX, int chunkY, SaveDataFile* saveDataFile);
		/// <summary>
		/// チャンク毎で地形データをセーブ。
		/// </summary>
		void SaveTerrainInChunk(int chunkX, int chunkY, SaveDataFile* saveDataFile);

	private:
		static const int TERRAIN_WORLD_CHUNKSIZE = LoadingChunks;		//地形の表示範囲。
		static const int SIDE_END = ChunkWidth * MAX_CHUNK_SIDE;
	private:
		CNoise m_perlinNoise;
		std::unique_ptr<Terrain> m_terrains[MAX_CHUNK_SIDE * ChunkWidth + 1][ChunkHeight][MAX_CHUNK_SIDE * ChunkWidth + 1];
		TerrainChunkData m_terrainChunkData[MAX_CHUNK_SIDE][MAX_CHUNK_SIDE];
		TerrainWorld* m_terrainWorlds[TERRAIN_WORLD_CHUNKSIZE][TERRAIN_WORLD_CHUNKSIZE] = { nullptr };
		SaveDataFile* m_saveDataFile = nullptr;
		NaviMeshManager* m_naviMeshManager = nullptr;
		bool m_isInitNVM = false;						//ナビメッシュ生成済みか？
	};

}
