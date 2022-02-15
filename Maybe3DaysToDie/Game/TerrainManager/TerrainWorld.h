#pragma once

#include "MarchingCubeTable.h"
#include "DestructibleObject/Terrain/Terrain.h"
#include "Navigation/NVMGenerator.h"
#include "TerrainChunkData.h"

class NaviMeshManager;

namespace nsTerrain {


	class TerrainRender;
	class TerrainChunkData;

	struct Cube {
		float cube[8];
		int terrainID[8] = { 0 };
	};

	class TerrainWorld : public IGameObject
	{
	public:

	private:
		bool Start()override final;
		void Update()override final;
		void OnDestroy()override final;
	
	public:
		/// <summary>
		/// NVMをリセット。
		/// </summary>
		void ResetNvm()
		{
			m_indexCount = 0;
			m_indices.clear();
			m_cellList.clear();
			//m_edgeCellList.clear();
		}

		/// <summary>
		/// セルを追加。
		/// </summary>
		/// <param name="cell"></param>
		void AddCell(NVMGenerator::Cell* cell)
		{
			m_indices.push_back(m_indexCount);
			m_indices.push_back(++m_indexCount);
			m_indices.push_back(++m_indexCount);
			m_indexCount++;
			m_cellList.push_back(*cell);
		}

		/// <summary>
		/// ナビメッシュを生成する。
		/// </summary>
		void CreateNVM(int x, int y);

		/// <summary>
		/// リンクセルをサーチ。
		/// </summary>
		void SerchLinkCell(int x, int y);

		/// <summary>
		/// NVM描画の準備。
		/// </summary>
		void PreRenderNVM(int x, int y);

		/// <summary>
		/// 地形情報データを登録。
		/// </summary>
		bool SetTerrainChunkData(TerrainChunkData* terrainCD);

		/// <summary>
		/// 地形の座標を設定する。
		/// </summary>
		void SetTerrainPosition(const Vector3& pos)
		{
			m_position = pos;
		}

		/// <summary>
		/// セルリストを取得。
		/// </summary>
		/// <returns></returns>
		std::vector<NVMGenerator::Cell>& GetCellList()
		{
			return m_cellList;
		}

		/// <summary>
		/// ナビメッシュマネージャーを設定。
		/// </summary>
		/// <param name="navimeshManager"></param>
		void SetNavimeshMnager(NaviMeshManager* navimeshManager)
		{
			m_naviMeshManager = navimeshManager;
		}

		/// <summary>
		/// 最小、最大の重心座標を返す。
		/// <para>端チャンクを判定する用の関数。</para>
		/// </summary>
		/// <param name="min">最小格納用。</param>
		/// <param name="max">最大格納用。</param>
		void GetMinMaxCenterPos(Vector3& Min, Vector3& Max);

		/// <summary>
		/// 初期化済みかどうか。
		/// </summary>
		bool IsInited()
		{
			return m_isInited;
		}

		/// <summary>
		/// nvmを更新するか。
		/// </summary>
		/// <returns></returns>
		bool IsUpdateNvm()
		{
			return m_isUpdateNvm;
		}

		/// <summary>
		/// nvmフラグをリセット。
		/// </summary>
		void ResetUpdateNvmFlag()
		{
			m_isUpdateNvm = false;
		}

	public:	//特定の地形を取得する。
		Terrain& GetTerrain(const Vector3& pos);
		Terrain& GetTerrain(const int pos[3]);

	private:
		//三角形テーブルのインデックスを取得。
		int GetCubeConfihuration(const Cube& cube);

		//メッシュデータ構築。
		void CreateMeshData();		

		/// <summary>
		/// マーチングキューブの三角形を構成。
		/// </summary>
		/// <param name="position">生成する座標。</param>
		/// <param name="configIndex">三角形の生成パターン番号。</param>
		void MarchCube(Vector3Int& positionInt);

		/// <summary>
		/// コライダーの再生成。
		/// </summary>
		void CreateCollider();

		//オフセットを計算。
		float GetOffset(float v1, float v2)
		{
			float delta = v2 - v1;
			return (delta == 0.0f) ? nsMarching::TERRAIN_SURFACE : (nsMarching::TERRAIN_SURFACE - v1) / delta;

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
		//static const int width = 16;
		//static const int height = 8;

		TerrainChunkData* m_terrainChunkData = nullptr;
		TerrainRender* m_terrainRender = nullptr;		//地形描画クラス。
		std::vector<Vector3> m_vertices;				//頂点データ。
		CPhysicsStaticObject m_staticObj;				//物理オブジェクト。
		Vector3 m_position = Vector3::Zero;				//座標。

		NaviMeshManager* m_naviMeshManager = nullptr;	//nvmマネージャー。
		std::vector<NVMGenerator::Cell> m_cellList;		//セルリスト。
		bool m_isNVMDebug = false;						//デバッグ描画する？
		bool m_isUpdateNvm = false;						//nvmを初期化する？
		NVMDebugDraw* m_nvmDebugDraw = nullptr;			//デバッグ描画。
		std::vector<int> m_indices;						//デバッグ用インデックスリスト。
		int m_indexCount = 0;							//デバッグ用

		bool m_isInited = false;						//初期化済みフラグ。
	};

}