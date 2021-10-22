#pragma once

namespace nsTerrain {

	enum EnTerrainRelated
	{
		en_terrainOnUp,		//上に隣接。
		en_terrainOnDown,	//下に隣接。
		en_terrainOnLeft,	//左に隣接。
		en_terrainOnRight,	//右に隣接。
		en_terrainOnFront,	//前に隣接。
		en_terrainOnBack,	//後に隣接。
		en_terrainOnNum		//隣接する面の数。
	};

	static const int NEAR_VERT_COUNT = 4;

	struct TerrainVertex {
		Vector3 vertPos;	//頂点座標。
		int vertNo = 0;			//頂点番号。
		TerrainVertex* nearVert[NEAR_VERT_COUNT] = { nullptr };	//隣接頂点のアドレス。
	};


	//地形オブジェクト。
	class Terrain :public DestructibleObject
	{
	public:
		Terrain();
		~Terrain()  override final;

		/// <summary>
		/// 座標を設定。
		/// </summary>
		void SetPosition(const Vector3& pos);

		/// <summary>
		/// 頂点のデータを構築していく。
		/// </summary>
		void BuildVertex();
		/// <summary>
		/// 頂点接続。
		/// </summary>
		void ConnectVertex();
		/// <summary>
		/// 隣接地形を設定。
		/// </summary>
		/// <param name="terrain">隣接地形。</param>
		/// <param name="enRelated">どの位置か。</param>
		void SetRelatedTerrain(Terrain* terrain,EnTerrainRelated enRelated);

		//頂点を取得する。
		TerrainVertex& GetVertex(int index)
		{
			return m_vertex[index];
		}

	private:
		static int GetIndexFromVertexRelated(EnTerrainRelated fromSide, EnTerrainRelated relatedSide);
		static const Vector3 VERTEX_CONST[en_terrainOnNum];
		static const EnTerrainRelated CONECT_VERTEX_LIST[en_terrainOnNum][NEAR_VERT_COUNT];

	private:
		Terrain* m_relatedTerrain[en_terrainOnNum] = { nullptr };	//隣接地形。
		TerrainVertex m_vertex[en_terrainOnNum];	//地形の頂点。
		int m_terrainId = -1;		//地形id番号。
		float m_scale = 1.0f;		//スケール。
	};

}
