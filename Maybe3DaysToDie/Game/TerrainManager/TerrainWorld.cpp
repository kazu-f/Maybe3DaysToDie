#include "stdafx.h"
#include "TerrainWorld.h"
#include "TerrainChunkData.h"
#include "TerrainRender\TerrainRender.h"


namespace nsTerrain {
	bool TerrainWorld::Start()
	{
		//地形描画クラス作成。
		m_terrainRender = NewGO<TerrainRender>(10);
		TerrainInitData initData;
		initData.vertexNum = ChunkWidth * ChunkWidth * ChunkHeight * 15;

		m_terrainRender->Init(initData);
		//m_terrainRender->SetPosition({ -TERRAIN_UNIT * width / 2,-TERRAIN_UNIT * height / 2 ,-TERRAIN_UNIT * width / 2 });

		//メッシュデータを作成。
		CreateMeshData();

		//物理オブジェクト作成。
		CreateCollider();

		PhysicsWorld().SetDebugMode(btIDebugDraw::DBG_DrawWireframe);

		m_isInited = true;

		return true;
	}
	void TerrainWorld::Update()
	{
		//地形の更新があった場合に頂点を再形成。
		if (m_terrainChunkData->IsUpdated()) {
			//頂点をクリア。
			m_terrainRender->ClearVertex();
			m_vertices.clear();
			//メッシュデータを作成。
			CreateMeshData();
			//コライダー作成。
			CreateCollider();

			m_terrainChunkData->ResetUpdated();
		}
		m_terrainRender->SetPosition(m_position);
	}
	void TerrainWorld::OnDestroy()
	{
		DeleteGO(m_terrainRender);
	}
	void TerrainWorld::ForwardRender(RenderContext& rc)
	{
		//m_NVMGenerator.DebugDraw(m_terrainRender);
	}

	bool TerrainWorld::SetTerrainChunkData(TerrainChunkData* terrainCD)
	{
		if (m_terrainChunkData != terrainCD)
		{
			//変更がある
			m_terrainChunkData = terrainCD;
			//マーチンキューブの更新フラグも立てる
			m_terrainChunkData->EnableUpdated();
			return true;
		}
		return false;
	}

	Terrain& TerrainWorld::GetTerrain(const Vector3& pos)
	{
		int resX = static_cast<int>(std::floor(pos.x / OBJECT_UNIT));
		int resY = static_cast<int>(std::floor(pos.y / OBJECT_UNIT));
		int resZ = static_cast<int>(std::floor(pos.z / OBJECT_UNIT));

		return *(m_terrainChunkData->GetTerrainData(resX, resY, resZ));
	}
	Terrain& TerrainWorld::GetTerrain(const int pos[3])
	{
		return *(m_terrainChunkData->GetTerrainData(pos[0], pos[1], pos[2]));
	}

	int TerrainWorld::GetCubeConfihuration(const Cube& cube)
	{
		int configrationIndex = 0;

		for (int i = 0; i < 8; i++)
		{
			//各頂点の影響度？から
			//三角形テーブルのインデックスを作成する。
			if (cube.cube[i] < nsMarching::TERRAIN_SURFACE)
				configrationIndex |= 1 << i;
		}

		return configrationIndex;
	}
	void TerrainWorld::CreateMeshData()
	{
		for (int x = 0; x < ChunkWidth; x++)
		{
			for (int y = 0; y < ChunkHeight - 1; y++)
			{
				for (int z = 0; z < ChunkWidth; z++)
				{
					Cube cube;
					for (int i = 0; i < 8; i++)
					{
						Vector3Int corner = { x, y, z };
						corner += nsMarching::CornerTable[i];
						auto* terrain = m_terrainChunkData->GetTerrainData(corner);
						if (terrain != nullptr) {
							cube.cube[i] = terrain->GetVoxel();
						}
						else {
							cube.cube[i] = 0.0f;
						}
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
		//エッジフラグを計算。
		int edgeFlags = nsMarching::CubeEdgeFlags[configIndex];

		//エッジが使われない。
		if (edgeFlags == 0) return;

		//エッジ上の頂点初期化。
		Vector3 EdgeVertex[12] = { {0.0f,0.0f,0.0f} };

		//Find the point of intersection of the surface with each edge
		for (int i = 0; i < 12; i++)
		{
			//そのエッジを使うかどうか。
			if ((edgeFlags & (1 << i)) != 0)
			{
				//オフセットを計算する。
				float offset = GetOffset(cube.cube[nsMarching::EdgeConnection[i][0]], cube.cube[nsMarching::EdgeConnection[i][1]]);

				//エッジ上の頂点の位置をキューブの頂点の影響値から計算する。
				EdgeVertex[i].x = (static_cast<float>(nsMarching::CornerTable[nsMarching::EdgeConnection[i][0]].x) * (1.0f - offset) 
					+ offset * static_cast<float>(nsMarching::CornerTable[nsMarching::EdgeConnection[i][1]].x));

				EdgeVertex[i].y = (static_cast<float>(nsMarching::CornerTable[nsMarching::EdgeConnection[i][0]].y) * (1.0f - offset) 
					+ offset * static_cast<float>(nsMarching::CornerTable[nsMarching::EdgeConnection[i][1]].y));

				EdgeVertex[i].z = (static_cast<float>(nsMarching::CornerTable[nsMarching::EdgeConnection[i][0]].z) * (1.0f - offset) 
					+ offset * static_cast<float>(nsMarching::CornerTable[nsMarching::EdgeConnection[i][1]].z));

				////エッジ上の頂点の位置をキューブの頂点の影響値から計算する。
				//EdgeVertex[i].x = (static_cast<float>(nsMarching::CornerTable[nsMarching::EdgeConnection[i][0]].x) * offset 
				//	+ (1.0f - offset) * static_cast<float>(nsMarching::CornerTable[nsMarching::EdgeConnection[i][1]].x));

				//EdgeVertex[i].y = (static_cast<float>(nsMarching::CornerTable[nsMarching::EdgeConnection[i][0]].y) * offset
				//	+ (1.0f - offset)  * static_cast<float>(nsMarching::CornerTable[nsMarching::EdgeConnection[i][1]].y));

				//EdgeVertex[i].z = (static_cast<float>(nsMarching::CornerTable[nsMarching::EdgeConnection[i][0]].z) * offset
				//	+ (1.0f - offset) * static_cast<float>(nsMarching::CornerTable[nsMarching::EdgeConnection[i][1]].z));

				////エッジ上の頂点の位置をキューブの頂点の影響値から計算する。
				//EdgeVertex[i].x = (static_cast<float>(nsMarching::CornerTable[nsMarching::EdgeConnection[i][0]].x)
				//	+ offset * static_cast<float>(nsMarching::EdgeDirectionTable[i].x));

				//EdgeVertex[i].y = (static_cast<float>(nsMarching::CornerTable[nsMarching::EdgeConnection[i][0]].y)
				//	+ offset * static_cast<float>(nsMarching::EdgeDirectionTable[i].y));

				//EdgeVertex[i].z = (static_cast<float>(nsMarching::CornerTable[nsMarching::EdgeConnection[i][0]].z)
				//	+ offset * static_cast<float>(nsMarching::EdgeDirectionTable[i].z));
			}
		}

		int edgeIndex = 0;

		//キューブ上に存在する三角形は最大5個。
		for (int i = 0; i < 5; i++)
		{
			//三角ポリゴンの頂点座標。
			Vector3 vertPos[3];
			//エッジ座標。
			Vector3 edgePos[3];
			//三角ポリゴンの中心座標。
			Vector3 center = Vector3::Zero;
			int p = 0;
			for (; p < 3; p++)
			{
				int indice = nsMarching::TriangleConnectionTable[configIndex][edgeIndex];

				//三角形がない。
				if (indice == -1)
					return;

				edgePos[p] = EdgeVertex[indice];
				edgePos[p].x -= 0.5f;
				edgePos[p].y -= 0.5f;
				edgePos[p].z -= 0.5f;

				//頂点の座標を計算。
				vertPos[p] = (position + EdgeVertex[indice]) * OBJECT_UNIT;
				m_vertices.push_back(vertPos[p]);	//頂点を積む。
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

			//三角ポリゴンのV軸を計算。
			Vector3 axisV;
			//法線がY方向ではない。
			if (fabsf(normal.Dot(Vector3::AxisY)) < 0.998f)
			{
				axisV.Cross(normal, Vector3::AxisY);
			}
			else {
				axisV.Cross(normal, Vector3::AxisX);
			}
			axisV.Normalize();
			//三角ポリゴンのU軸を計算。
			Vector3 axisU;
			axisU.Cross(normal, axisV);
			axisU.Normalize();

			for (int j = 0; j < p; j++)
			{
				TerrainVertex vert;
				vert.m_pos = vertPos[j];
				vert.m_normal = normal;

				//TODO:いつか直す。
				//UV座標を計算する。
				Vector2 uv;
				uv.x = edgePos[j].Dot(axisU) + 0.5f;
				uv.y = edgePos[j].Dot(axisV) + 0.5f;

				vert.m_uv = uv;

				m_terrainRender->AddVertex(vert);
			}

			m_terrainRender->AddCenter(center);

		}

	}
	void TerrainWorld::CreateCollider()
	{
		//物理オブジェクト作成。
		m_staticObj.CreateBuffer(
			m_position,
			Quaternion::Identity,
			Vector3::One,
			m_vertices
		);		
	}
}