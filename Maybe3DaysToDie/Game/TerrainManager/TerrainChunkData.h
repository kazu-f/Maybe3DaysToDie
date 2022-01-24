#pragma once

#include "MarchingCubeTable.h"
#include "DestructibleObject/Terrain/Terrain.h"

namespace nsTerrain {
	class TerrainChunkData
	{
	public:
		void SetTerrainData(Terrain* terrain, const int x, const int y, const int z)
		{
			if (CheckChunkSize(x,y,z)) {
				m_terrainMap[x][y][z] = terrain;
				m_terrainMap[x][y][z]->SetTerrainChunk(this);
			}
		}
		/// <summary>
		/// 地形データを取得する。
		/// </summary>
		/// <param name="x">x要素</param>
		/// <param name="y">y要素</param>
		/// <param name="z">z要素</param>
		/// <returns></returns>
		Terrain* GetTerrainData(const int x, const int y, const int z)
		{
			if (CheckChunkSize(x, y, z)) {
				return m_terrainMap[x][y][z];
			}
			return nullptr;
		}
		/// <summary>
		/// 地形データを取得する。
		/// </summary>
		/// <param name="pos">整数型の3要素</param>
		/// <returns></returns>
		Terrain* GetTerrainData(const Vector3Int& pos)
		{
			if (CheckChunkSize(pos.x, pos.y, pos.z))
			{
				return m_terrainMap[pos.x][pos.y][pos.z];
			}
			return nullptr;
		}
	public:		//Updateフラグ。
		/// <summary>
		/// 地形が更新された。
		/// </summary>
		void EnableUpdated()
		{
			m_isUpdated = true;
		}
		/// <summary>
		/// 地形更新があったか？
		/// </summary>
		bool IsUpdated()
		{
			return m_isUpdated;
		}
		/// <summary>
		/// 更新フラグを解除。
		/// </summary>
		void ResetUpdated()
		{
			m_isUpdated = false;
		}
	private:	//チャンク内判定用関数。
		/// <summary>
		/// チャンク内に収まっているかどうか。
		/// </summary>
		/// <param name="x">x要素</param>
		/// <param name="y">y要素</param>
		/// <param name="z">z要素</param>
		/// <returns></returns>
		bool CheckChunkSize(int x,int y,int z)
		{
			return (
				CheckSize(ChunkWidth + 1, x)
				&& CheckSize(ChunkHeight, y)
				&& CheckSize(ChunkWidth + 1, z)
				);
		}

		bool CheckSize(int maxSize, int num)
		{
			return (num >= 0) && (num < maxSize);
		}
	private:
		Terrain* m_terrainMap[ChunkWidth + 1][ChunkHeight][ChunkWidth + 1] = { nullptr };
		bool m_isUpdated = false;						//地形の更新がある。
	};
}

