#include "stdafx.h"
#include "TerrainWorld.h"
#include "TerrainRender\TerrainRender.h"

namespace nsTerrain {
	bool TerrainWorld::Start()
	{
		//地形描画クラス作成。
		m_terrainRender = NewGO<TerrainRender>(10);
		TerrainInitData initData;
		initData.vertexNum = width * width * height * 15;

		m_terrainRender->Init(initData);

		//地形データ作成。
		PopurerTerrainMap();
		//メッシュデータを作成。
		CreateMeshData();

		return true;
	}
	void TerrainWorld::OnDestroy()
	{
		DeleteGO(m_terrainRender);
	}
	void TerrainWorld::PopurerTerrainMap()
	{
		for (int x = 0; x < width + 1; x++)
		{
			for (int y = 0; y < height + 1; y++)
			{
				for (int z = 0; z < width + 1; z++)
				{
					float thisHeight = static_cast<float>(height * m_perlinNoise.CalculationNoise(
						(static_cast<double>(x) / 16.0 * 1.5 + 0.001),
						(static_cast<double>(z) / 16.0 * 1.5 + 0.001))
						);

					//float thisHeight = 4.0f;

					float point = 0;

					if (y == 0)
					{
						point = 0.5f;
					}
					else {
						//この場所の高さに対してブロックが届いていない。
						if (y <= thisHeight - 0.5f)
							point = 0.0f;
						//この場所の上にもブロックがある。
						else if (y > thisHeight + 0.5f)
							point = 1.0f;
						//この場所のブロックの影響値計算。(上方向。)
						else if (y > thisHeight)
							point = (float)y - thisHeight;
						//この場所のブロックの影響値計算。(下方向。)
						else
							point = thisHeight - (float)y;
					}

					terrainMap[x][y][z] = point;

				}
			}
		}
	}
	int TerrainWorld::GetCubeConfihuration(const Cube& cube)
	{
		int configrationIndex = 0;

		for (int i = 0; i < 8; i++)
		{
			//各頂点の影響度？から
			//三角形テーブルのインデックスを作成する。
			if (cube.cube[i] > terrainSurface)
				configrationIndex |= 1 << i;

		}

		return configrationIndex;
	}
	void TerrainWorld::CreateMeshData()
	{
		for (int x = 0; x < width; x++)
		{
			for (int y = 0; y < height; y++)
			{
				for (int z = 0; z < width; z++)
				{
					Cube cube;
					for (int i = 0; i < 8; i++)
					{
						Vector3Int corner = { x, y, z };
						corner += nsMarching::CornerTable[i];
						cube.cube[i] = terrainMap[corner.x][corner.y][corner.z];

					}

					Vector3 pos;
					pos.x = static_cast<float>(x);
					pos.y = static_cast<float>(y);
					pos.z = static_cast<float>(z);

					MarchCube(pos, cube);

				}
			}
		}
	}
	void TerrainWorld::MarchCube(Vector3 position, const Cube& cube)
	{
		int configIndex = GetCubeConfihuration(cube);

		//トライアングルテーブル上のこの番号に三角形はない。
		if (configIndex == 0 || configIndex == 255)
		{
			return;
		}

		int edgeIndex = 0;

		//キューブ上に存在する三角形は最大5個。
		for (int i = 0; i < 5; i++)
		{
			//三角ポリゴンの頂点座標。
			Vector3 vertPos[3];
			//三角ポリゴンの中心座標。
			Vector3 center = Vector3::Zero;
			int p = 0;
			for (; p < 3; p++)
			{
				int indice = nsMarching::TriangleConnectionTable[configIndex][edgeIndex];

				//三角形がない。
				if (indice == -1)
					return;

				//エッジを構成する2頂点を取得。
				Vector3 vert1 = position + nsMarching::EdgeTable[indice][0];
				Vector3 vert2 = position + nsMarching::EdgeTable[indice][1];

				//頂点の座標を計算。
				vertPos[p] = (vert1 + vert2) / 2.0f * TERRAIN_UNIT;
				//中心座標を計算する。
				center += vertPos[p];

				edgeIndex++;
			}

			//中心座標を算出。
			center /= p;

			//中心座標からのベクトル。
			Vector3 vDir[3];

			for (int vNum = 0; vNum < p; vNum++)
			{
				vDir[vNum] = vertPos[vNum] - center;
				vDir[vNum].Normalize();
			}

			//法線を計算。
			Vector3 normal;
			normal.Cross(vDir[0], vDir[1]);
			normal.Normalize();

			//三角ポリゴンのX軸を計算。
			Vector3 axisX;
			//法線がY方向ではない。
			if (fabsf(normal.Dot(Vector3::AxisY)) < 0.998f)
			{
				axisX.Cross(Vector3::AxisY, normal);
			}
			else {
				axisX.Cross(Vector3::AxisZ, normal);
			}
			axisX.Normalize();
			//三角ポリゴンのY軸を計算。
			Vector3 axisY;
			axisY.Cross(normal, axisX);
			axisX.Normalize();

			for (int j = 0; j < p; j++)
			{
				Vertex vert;
				vert.m_pos = vertPos[j];
				vert.m_normal = normal;

				//UV座標を計算する。
				Vector2 uv;
				uv.x = vDir[j].Dot(axisX) / 2.0f + 0.5f;
				uv.y = vDir[j].Dot(axisY) / 2.0f + 0.5f;

				vert.m_uv = uv;

				m_terrainRender->AddVertex(vert);
			}


		}

	}
}