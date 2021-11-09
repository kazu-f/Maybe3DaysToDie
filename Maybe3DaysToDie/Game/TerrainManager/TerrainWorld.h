#pragma once

#include "MarchingCubeTable.h"
#include "DestructibleObject/Terrain/Terrain.h"
#include "Navigation/NVMGenerator.h"
#include "Enemy/EnemyGenerator.h"

namespace nsTerrain {


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
	private:
		bool Start()override final;
		void Update()override final;
		void OnDestroy()override final;
		void ForwardRender(RenderContext& rc) override final;
	public:	//特定の地形を取得する。
		Terrain& GetTerrain(const Vector3& pos);

		/// <summary>
		/// 地形が更新された。
		/// </summary>
		void EnableUpdated()
		{
			m_isUpdated = true;
		}

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

		/// <summary>
		/// コライダーの再生成。
		/// </summary>
		void CreateCollider();

		//オフセットを計算。
		float GetOffset(float v1, float v2)
		{
			float delta = v2 - v1;
			return (delta == 0.0f) ? m_terrainSurface : (m_terrainSurface - v1) / delta;

			//float ret = 0.0f;
			//float weight = v1 + v2;
			//if (v1 > v2)
			//{
			//	ret = m_terrainSurface * v1 / weight;
			//}
			//else if(v1 < v2){
			//	ret = 1.0f - m_terrainSurface * v2 / weight;
			//}
			//else if (v1 == v2)
			//{
			//	ret = m_terrainSurface;
			//}

			//return ret;
		}

	private:
		static const int width = 16;
		static const int height = 8;
		float m_terrainSurface = 0.5f;

		Terrain m_terrainMap[width][height][width];
		CNoise m_perlinNoise;
		TerrainRender* m_terrainRender = nullptr;		//地形描画クラス。
		NVMGenerator m_NVMGenerator;					//NVM生成。
		EnemyGenerator m_enemyGenerator;				//enemyGenerator.
		std::vector<Vector3> m_vertices;				//頂点データ。
		CPhysicsStaticObject m_staticObj;				//物理オブジェクト。
		bool m_isUpdated = false;						//地形の更新がある。
	};

}