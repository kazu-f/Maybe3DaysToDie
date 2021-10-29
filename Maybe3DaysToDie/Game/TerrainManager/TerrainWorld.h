#pragma once

#include "MarchingCubeTable.h"
#include "Navigation/NVMGenerator.h"
#include "Enemy/EnemyGenerator.h"

namespace nsTerrain {

	static const float TERRAIN_UNIT = 100.0f;
	static const float TERRAIN_HALF_UNIT = 50.0f;

	class TerrainRender;

	union Cube {
		float cube[8];
	};

	class TerrainWorld : public IGameObject
	{
	public:
		TerrainWorld()
			:m_perlinNoise(2)
		{

		}

		bool Start()override final;
		void Update()override final;
		void OnDestroy()override final;
		void ForwardRender(RenderContext& rc) override final;

	private:
		/// <summary>
		/// 有名な地形生成関数？。
		/// </summary>
		void PopurerTerrainMap();		

		//三角形テーブルのインデックスを取得。
		int GetCubeConfihuration(const Cube& cube);

		//メッシュデータ構築。
		void CreateMeshData();		

		/// <summary>
		/// マーチングキューブの三角形を構成。
		/// </summary>
		/// <param name="position">生成する座標。</param>
		/// <param name="configIndex">三角形の生成パターン番号。</param>
		void MarchCube(Vector3 position, const Cube& cube);

		//オフセットを計算。
		float GetOffset(float v1, float v2)
		{
			float delta = v2 - v1;
			return (delta == 0.0f) ? m_terrainSurface : (m_terrainSurface - v1) / delta;
			//float delta = v2 - v1;
			//delta = max(-1.0f, min(1.0f, delta));
			//return(0.5f + 0.5f * delta);
		}

	private:
		static const int width = 64;
		static const int height = 16;
		float m_terrainSurface = 1.0f;

		float terrainMap[width + 1][height + 1][width + 1] = { 0.0f };
		CNoise m_perlinNoise;
		TerrainRender* m_terrainRender = nullptr;		//地形描画クラス。
		NVMGenerator m_NVMGenerator;					//NVM生成。
		EnemyGenerator m_enemyGenerator;				//enemyGenerator.
	};

}