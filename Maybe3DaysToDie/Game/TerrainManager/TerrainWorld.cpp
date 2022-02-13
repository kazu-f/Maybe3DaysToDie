#include "stdafx.h"
#include "TerrainWorld.h"
#include "TerrainChunkData.h"
#include "TerrainRender\TerrainRender.h"
#include "Navigation/NVMDebugDraw.h"
#include "RayTest.h"
#include "NaviMeshManager.h"

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

		//PhysicsWorld().SetDebugMode(btIDebugDraw::DBG_DrawWireframe);

		m_nvmDebugDraw = NewGO<NVMDebugDraw>(1);
		m_nvmDebugDraw->Init();

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
			//nvm更新。
			m_isUpdateNvm = true;
			m_terrainChunkData->ResetUpdated();
		}

		m_terrainRender->SetPosition(m_position);
	}
	void TerrainWorld::OnDestroy()
	{
		DeleteGO(m_terrainRender);
	}

	void TerrainWorld::CreateNVM(int x, int y)
	{
		//重点の数はメッシュの数。
		int meshCount = m_terrainRender->GetCenterArray().size();

		//頂点カウント。
		int vertCount = 0;

		//NVMの基本パラメーターを流し込んでいく。
		for (int mesh = 0; mesh < meshCount; mesh++) {
			if (m_terrainRender->GetVertexList().at(vertCount).m_normal.y > 0.000001f) {
				//法線が下向きの場合は歩くことができない傾斜のため除外。

				//セルを作成する。
				NVMGenerator::Cell cell;

				//重点。
				cell.m_CenterPos = m_terrainRender->GetCenterArray().at(mesh) + m_position;

				//メッシュ全ての３頂点を計算する。
				cell.pos[0] = m_terrainRender->GetVertexList().at(vertCount).m_pos + m_position;
				m_indices.push_back(m_indexCount);
				cell.pos[1] = m_terrainRender->GetVertexList().at(vertCount + 1).m_pos + m_position;
				m_indices.push_back(++m_indexCount);
				cell.pos[2] = m_terrainRender->GetVertexList().at(vertCount + 2).m_pos + m_position;
				m_indices.push_back(++m_indexCount);
				m_indexCount++;

				//作成したセルの上にコリジョンがないか調べる。あった場合はこのセルは除外。
				RayResult callback;
				btVector3 start = { cell.m_CenterPos.x, cell.m_CenterPos.y - 1.0f, cell.m_CenterPos.z };
				btVector3 end = { cell.m_CenterPos.x, cell.m_CenterPos.y + 200.0f, cell.m_CenterPos.z };

				PhysicsWorld().RayTest(start, end, callback);

				if (callback.isHit)
				{
					vertCount += 3;
					continue;
				}

				//端セルを取る。
				Vector3 centerPos = cell.m_CenterPos - m_position;
				if (centerPos.x < 34.0f || centerPos.z < 34.0f
					|| centerPos.x >(ChunkWidth * OBJECT_UNIT) - 34.0f
					|| centerPos.z >(ChunkWidth * OBJECT_UNIT) - 34.0f
					)
				{
					//端セルだった。
					m_naviMeshManager->AddEdgeCellList(cell, x, y);
				}
				else
				{
					//管理をリストに移す。
					m_cellList.push_back(cell);
				}



			}
			//次メッシュの頂点へ。
			vertCount += 3;
		}
	}

	void TerrainWorld::SerchLinkCell(int x, int y)
	{
		//色々頭悪いがこれで行こうｗ

		//地形インデックス計算。
		Vector2 linkChunkIndexList[4] = { Vector2::Zero };
		linkChunkIndexList[0] = { -1 , 0 };
		linkChunkIndexList[1] = { 1 , 0 };
		linkChunkIndexList[2] = { 0 ,-1 };
		linkChunkIndexList[3] = { 0 , 1 };

		std::vector<NVMGenerator::Cell*> serchCellList;

		//端セルと端セルの隣接を取る。
		for (auto linkChunkIndex : linkChunkIndexList)
		{
			//調べるチャンクのインデックスを算出.
			Vector2 reserchChunk = { x + linkChunkIndex.x , y + linkChunkIndex.y };

			if (reserchChunk.x < 0 || reserchChunk.y < 0 || abs(reserchChunk.x) > 2 || abs(reserchChunk.y) > 2)
			{
				//不正な隣接インデックス。
				continue;
			}

			for (auto& cell : m_naviMeshManager->GetEdgeCellList(reserchChunk.x, reserchChunk.y))
			{
				//周囲4チャンク分
				serchCellList.push_back(&cell);
			}
		}

		for (auto& cell : m_naviMeshManager->GetEdgeCellList(x, y))
		{
			//自チャンク分。
			serchCellList.push_back(&cell);
		}

		for (auto& cell : m_cellList)
		{
			serchCellList.push_back(&cell);
		}

		//端セルと端セルとをつなぐ。
		for (auto& baseCell : m_naviMeshManager->GetEdgeCellList(x, y))
		{
			int linkCellIndex = 0;
			for (auto& serchCell : serchCellList)
			{
				//リンクセルを検索していく。
				if (&baseCell == serchCell) {
					//ベースセルとリンクセルのアドレスが同一なのでスキップ。
					continue;
				}

				int linkVertex = 0;	//隣接頂点の数。

				//頂点比較。
				for (auto& baseVertex : baseCell.pos) {
					for (auto& serchVertex : serchCell->pos) {
						if (/*baseVertex.x == serchVertex.x && baseVertex.z == serchVertex.z*/baseVertex == serchVertex) {
							//頂点が一緒
							linkVertex++;
						}
					}
				}//VertexSerch.

				if (linkVertex >= 2) {
					//隣接ラインが2つあるためこいつは隣接頂点である。
					baseCell.m_linkCell[linkCellIndex] = serchCell;
					linkCellIndex++;
					if (linkCellIndex == 3) {
						//リンクセル３つ目到達検索を終了。
						break;
					}
				}
			}
		}

		serchCellList.clear();

		for (auto& cell : m_naviMeshManager->GetEdgeCellList(x, y))
		{
			serchCellList.push_back(&cell);
		}

		for (auto& cell : m_cellList)
		{
			serchCellList.push_back(&cell);
		}

		for (auto& baseCell : m_cellList)
		{
			int linkCellIndex = 0;
			for (auto& serchCell : serchCellList)
			{
				//リンクセルを検索していく。
				if (&baseCell == serchCell) {
					//ベースセルとリンクセルのアドレスが同一なのでスキップ。
					continue;
				}

				int linkVertex = 0;	//隣接頂点の数。

				//頂点比較。
				for (auto& baseVertex : baseCell.pos) {
					for (auto& serchVertex : serchCell->pos) {
						if (/*baseVertex.x == serchVertex.x && baseVertex.z == serchVertex.z*/baseVertex == serchVertex) {
							//頂点が一緒
							linkVertex++;
						}
					}
				}//VertexSerch.

				if (linkVertex >= 2) {
					//隣接ラインが2つあるためこいつは隣接頂点である。
					baseCell.m_linkCell[linkCellIndex] = serchCell;
					linkCellIndex++;
					if (linkCellIndex == 3) {
						//リンクセル３つ目到達検索を終了。
						break;
					}
				}
			}
		}
	}

	void TerrainWorld::PreRenderNVM(int x, int y)
	{
		if (m_isNVMDebug) {
			m_nvmDebugDraw->ClearCellData();

			for (auto& cell : m_cellList) {
				m_nvmDebugDraw->PushVertex(cell.pos[0]);
				m_nvmDebugDraw->PushVertex(cell.pos[1]);
				m_nvmDebugDraw->PushVertex(cell.pos[2]);
				for (auto* linkCell : cell.m_linkCell) {
					if (linkCell == nullptr) {
						break;
					}
					//隣接デバッグ用にラインを形成して、格納。
					NVMDebugDraw::Line line;
					line.start = cell.m_CenterPos;
					line.end = linkCell->m_CenterPos;
					m_nvmDebugDraw->PushToLinkCellLine(line);
				}
			}

			for (auto& cell : m_naviMeshManager->GetEdgeCellList(x, y))
			{
				m_nvmDebugDraw->PushVertex(cell.pos[0]);
				m_nvmDebugDraw->PushVertex(cell.pos[1]);
				m_nvmDebugDraw->PushVertex(cell.pos[2]);
				for (auto* linkCell : cell.m_linkCell) {
					if (linkCell == nullptr) {
						break;
					}
					//隣接デバッグ用にラインを形成して、格納。
					NVMDebugDraw::Line line;
					line.start = cell.m_CenterPos;
					line.end = linkCell->m_CenterPos;
					m_nvmDebugDraw->PushToLinkCellLine(line);
				}
			}

			m_nvmDebugDraw->CreateBuffers(m_indices, m_indexCount);
		}
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

	void TerrainWorld::GetMinMaxCenterPos(Vector3& Min, Vector3& Max)
	{
		//初期化。
		Min = { FLT_MAX, FLT_MAX, FLT_MAX };
		Max = { -FLT_MAX, -FLT_MAX, -FLT_MAX };

		for (int i = 0; i < m_terrainRender->GetCenterArray().size(); i++)
		{
			Vector3 centerPos = m_terrainRender->GetCenterArray().at(i) + m_position;

			//ローカル座標系でのedge位置を求める。
			Min.x = min(Min.x, centerPos.x);
			//Min.y = min(Min.y, centerPos.y);
			Min.z = min(Min.z, centerPos.z);

			Max.x = max(Max.x, centerPos.x);
			//Max.y = max(Max.y, centerPos.y);
			Max.z = max(Max.z, centerPos.z);
		}
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
							cube.terrainID[i] = terrain->GetTerrainID();
						}
						else {
							cube.cube[i] = 0.0f;
							cube.terrainID[i] = 0;
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
		Vector4 EdgeTexture[12] = { {0.0f,0.0f,0.0f,0.0f} };

		//Find the point of intersection of the surface with each edge
		for (int i = 0; i < 12; i++)
		{
			//そのエッジを使うかどうか。
			if ((edgeFlags & (1 << i)) != 0)
			{
				//オフセットを計算する。
				float offset = GetOffset(cube.cube[nsMarching::EdgeConnection[i][0]], cube.cube[nsMarching::EdgeConnection[i][1]]);

				Vector4 tex1 = { 0.0f,0.0f,0.0f,0.0f };
				tex1.v[cube.terrainID[nsMarching::EdgeConnection[i][0]]] = 1.0f;
				Vector4 tex2 = { 0.0f,0.0f,0.0f,0.0f };
				tex2.v[cube.terrainID[nsMarching::EdgeConnection[i][1]]] = 1.0f;

				EdgeTexture[i] = tex1 * (1.0f - offset) + tex2 * offset;

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

			Vector4 vertTexType[3];
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

				vertTexType[p] = EdgeTexture[indice];

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
				vert.m_texType = vertTexType[j];
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