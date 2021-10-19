#include "stdafx.h"
#include "Terrain.h"

namespace nsTerrain {

	const Vector3 Terrain::VERTEX_CONST[en_terrainOnNum] = {
			{0.0f,TERRAIN_UNIT,0.0f},		//上。
			{0.0f,0.0f,0.0f},		//下。
			{-TERRAIN_HALF_UNIT,TERRAIN_HALF_UNIT,0.0f},		//左。
			{TERRAIN_HALF_UNIT,TERRAIN_HALF_UNIT,0.0f},		//右。
			{0.0f,TERRAIN_HALF_UNIT,TERRAIN_HALF_UNIT},		//前。
			{0.0f,TERRAIN_HALF_UNIT,-TERRAIN_HALF_UNIT}		//後。
	};
	const EnTerrainRelated Terrain::CONECT_VERTEX_LIST[en_terrainOnNum][NEAR_VERT_COUNT] =
	{
		{en_terrainOnFront	,en_terrainOnRight	,en_terrainOnBack	,en_terrainOnLeft},		//上
		{en_terrainOnBack	,en_terrainOnLeft	,en_terrainOnFront	,en_terrainOnRight},	//下
		{en_terrainOnUp		,en_terrainOnFront	,en_terrainOnDown	,en_terrainOnBack},		//左
		{en_terrainOnDown	,en_terrainOnBack	,en_terrainOnUp		,en_terrainOnFront},	//右
		{en_terrainOnRight	,en_terrainOnUp		,en_terrainOnLeft	,en_terrainOnDown},		//前
		{en_terrainOnLeft	,en_terrainOnDown	,en_terrainOnRight	,en_terrainOnUp}		//後ろ
	};

	Terrain::Terrain()
	{
	}

	Terrain::~Terrain()
	{
	}

	void Terrain::SetPosition(const Vector3& pos)
	{
		m_position = pos;
		for (int i = 0; i < en_terrainOnNum; i++ )
		{
			//頂点座標を設定。
			m_vertex[i].vertPos = pos + VERTEX_CONST[i];
		}
	}
	void Terrain::BuildVertex()
	{
		////上の頂点。
		//{
		//	m_vertex[en_terrainOnUp].nearVert[0] = &m_vertex[CONECT_VERTEX_LIST[en_terrainOnUp][0]];
		//	m_vertex[en_terrainOnUp].nearVert[1] = &m_vertex[CONECT_VERTEX_LIST[en_terrainOnUp][1]];
		//	m_vertex[en_terrainOnUp].nearVert[2] = &m_vertex[CONECT_VERTEX_LIST[en_terrainOnUp][2]];
		//	m_vertex[en_terrainOnUp].nearVert[3] = &m_vertex[CONECT_VERTEX_LIST[en_terrainOnUp][3]];
		//}
		////下の頂点。
		//{
		//	m_vertex[en_terrainOnDown].nearVert[0] = &m_vertex[CONECT_VERTEX_LIST[en_terrainOnDown][0]];
		//	m_vertex[en_terrainOnDown].nearVert[1] = &m_vertex[CONECT_VERTEX_LIST[en_terrainOnDown][1]];
		//	m_vertex[en_terrainOnDown].nearVert[2] = &m_vertex[CONECT_VERTEX_LIST[en_terrainOnDown][2]];
		//	m_vertex[en_terrainOnDown].nearVert[3] = &m_vertex[CONECT_VERTEX_LIST[en_terrainOnDown][3]];
		//}
		////右の頂点。
		//{
		//	m_vertex[en_terrainOnRight].nearVert[0] = &m_vertex[CONECT_VERTEX_LIST[en_terrainOnRight][0]];
		//	m_vertex[en_terrainOnRight].nearVert[1] = &m_vertex[CONECT_VERTEX_LIST[en_terrainOnRight][1]];
		//	m_vertex[en_terrainOnRight].nearVert[2] = &m_vertex[CONECT_VERTEX_LIST[en_terrainOnRight][2]];
		//	m_vertex[en_terrainOnRight].nearVert[3] = &m_vertex[CONECT_VERTEX_LIST[en_terrainOnRight][3]];
		//}
		////左の頂点。
		//{
		//	m_vertex[en_terrainOnLeft].nearVert[0] = &m_vertex[CONECT_VERTEX_LIST[en_terrainOnLeft][0]];
		//	m_vertex[en_terrainOnLeft].nearVert[1] = &m_vertex[CONECT_VERTEX_LIST[en_terrainOnLeft][1]];
		//	m_vertex[en_terrainOnLeft].nearVert[2] = &m_vertex[CONECT_VERTEX_LIST[en_terrainOnLeft][2]];
		//	m_vertex[en_terrainOnLeft].nearVert[3] = &m_vertex[CONECT_VERTEX_LIST[en_terrainOnLeft][3]];
		//}
		////前の頂点。
		//{
		//	m_vertex[en_terrainOnFront].nearVert[0] = &m_vertex[CONECT_VERTEX_LIST[en_terrainOnFront][0]];
		//	m_vertex[en_terrainOnFront].nearVert[1] = &m_vertex[CONECT_VERTEX_LIST[en_terrainOnFront][1]];
		//	m_vertex[en_terrainOnFront].nearVert[2] = &m_vertex[CONECT_VERTEX_LIST[en_terrainOnFront][2]];
		//	m_vertex[en_terrainOnFront].nearVert[3] = &m_vertex[CONECT_VERTEX_LIST[en_terrainOnFront][3]];
		//}
		////後の頂点。
		//{
		//	m_vertex[en_terrainOnBack].nearVert[0] = &m_vertex[CONECT_VERTEX_LIST[en_terrainOnBack][0]];
		//	m_vertex[en_terrainOnBack].nearVert[1] = &m_vertex[CONECT_VERTEX_LIST[en_terrainOnBack][1]];
		//	m_vertex[en_terrainOnBack].nearVert[2] = &m_vertex[CONECT_VERTEX_LIST[en_terrainOnBack][2]];
		//	m_vertex[en_terrainOnBack].nearVert[3] = &m_vertex[CONECT_VERTEX_LIST[en_terrainOnBack][3]];
		//}

		for (int i = 0; i < en_terrainOnNum; i++)
		{
			for (int j = 0; j < NEAR_VERT_COUNT; j++)
			{
				//隣接頂点を構築。
				m_vertex[i].nearVert[j] = &m_vertex[CONECT_VERTEX_LIST[i][j]];
			}
		}

	}

	void Terrain::ConnectVertex()
	{
		for (int i = 0; i < en_terrainOnNum; i++)
		{
			if (m_relatedTerrain[i] != nullptr)
			{
				//どっち側接続するか。
				int mod = i % 2;
				
				int index = i;
				if (mod == 0)
				{
					index++;
				}
				else {
					index--;
				}

				for (int j = 0; j < NEAR_VERT_COUNT; j++)
				{
					//m_vertex[i].nearVert[j] = m_relatedTerrain[i]->GetVertex(index).nearVert[j];

					auto fromSide = CONECT_VERTEX_LIST[i][j];

					//接続を試みる。
					m_vertex[fromSide].nearVert[GetIndexFromVertexRelated(fromSide,static_cast<EnTerrainRelated>(i))] = 
						m_relatedTerrain[i]->GetVertex(index).nearVert[(j + 2) % NEAR_VERT_COUNT];
				}

			}
		}

	}

	void Terrain::SetRelatedTerrain(Terrain* terrain, EnTerrainRelated enRelated)
	{
		m_relatedTerrain[enRelated] = terrain;
	}


	int Terrain::GetIndexFromVertexRelated(EnTerrainRelated fromSide, EnTerrainRelated relatedSide)
	{
		for (int i = 0; i < NEAR_VERT_COUNT; i++)
		{
			if (CONECT_VERTEX_LIST[fromSide][i] == relatedSide)
			{
				return i;
			}
		}
		//失敗。
		return -1;
	}
}
