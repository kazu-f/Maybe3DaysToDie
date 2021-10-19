#pragma once

namespace Terrain {

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

	struct TerrainVertex {
		Vector3 vertPos;	//頂点座標。
		int vertNo = 0;			//頂点番号。
		TerrainVertex* nearVert[4] = { nullptr };	//隣接頂点のアドレス。
	};

	//地形オブジェクト。
	class Terrain :public DestructibleObject
	{
	public:
		Terrain() {}
		~Terrain()  override final {}

		/// <summary>
		/// 座標を設定。
		/// </summary>
		void SetPosition(const Vector3& pos);

		/// <summary>
		/// 頂点のデータを構築していく。
		/// </summary>
		void BuildVertex();

	private:
		const Vector3 VERTEX_CONST[en_terrainOnNum] = {
			{0.0f,100.0f,0.0f},		//上。
			{0.0f,0.0f,0.0f},		//下。
			{-100.0f,50.0f,0.0f},		//左。
			{100.0f,50.0f,0.0f},		//右。
			{0.0f,50.0f,100.0f},		//前。
			{0.0f,50.0f,-100.0f}		//後。
		};

	private:
		TerrainVertex m_vertex[en_terrainOnNum];	//地形の頂点。
		int m_terrainId = -1;		//地形id番号。
		float m_scale = 1.0f;		//スケール。
	};

}
