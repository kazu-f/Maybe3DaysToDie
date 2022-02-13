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
		//�n�`�`��N���X�쐬�B
		m_terrainRender = NewGO<TerrainRender>(10);
		TerrainInitData initData;
		initData.vertexNum = ChunkWidth * ChunkWidth * ChunkHeight * 15;

		m_terrainRender->Init(initData);
		//m_terrainRender->SetPosition({ -TERRAIN_UNIT * width / 2,-TERRAIN_UNIT * height / 2 ,-TERRAIN_UNIT * width / 2 });

		//���b�V���f�[�^���쐬�B
		CreateMeshData();

		//�����I�u�W�F�N�g�쐬�B
		CreateCollider();

		//PhysicsWorld().SetDebugMode(btIDebugDraw::DBG_DrawWireframe);

		m_nvmDebugDraw = NewGO<NVMDebugDraw>(1);
		m_nvmDebugDraw->Init();

		m_isInited = true;

		return true;
	}
	void TerrainWorld::Update()
	{
		//�n�`�̍X�V���������ꍇ�ɒ��_���Č`���B
		if (m_terrainChunkData->IsUpdated()) {
			//���_���N���A�B
			m_terrainRender->ClearVertex();
			m_vertices.clear();
			//���b�V���f�[�^���쐬�B
			CreateMeshData();
			//�R���C�_�[�쐬�B
			CreateCollider();
			//nvm�X�V�B
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
		//�d�_�̐��̓��b�V���̐��B
		int meshCount = m_terrainRender->GetCenterArray().size();

		//���_�J�E���g�B
		int vertCount = 0;

		//NVM�̊�{�p�����[�^�[�𗬂�����ł����B
		for (int mesh = 0; mesh < meshCount; mesh++) {
			if (m_terrainRender->GetVertexList().at(vertCount).m_normal.y > 0.000001f) {
				//�@�����������̏ꍇ�͕������Ƃ��ł��Ȃ��X�΂̂��ߏ��O�B

				//�Z�����쐬����B
				NVMGenerator::Cell cell;

				//�d�_�B
				cell.m_CenterPos = m_terrainRender->GetCenterArray().at(mesh) + m_position;

				//���b�V���S�Ă̂R���_���v�Z����B
				cell.pos[0] = m_terrainRender->GetVertexList().at(vertCount).m_pos + m_position;
				m_indices.push_back(m_indexCount);
				cell.pos[1] = m_terrainRender->GetVertexList().at(vertCount + 1).m_pos + m_position;
				m_indices.push_back(++m_indexCount);
				cell.pos[2] = m_terrainRender->GetVertexList().at(vertCount + 2).m_pos + m_position;
				m_indices.push_back(++m_indexCount);
				m_indexCount++;

				//�쐬�����Z���̏�ɃR���W�������Ȃ������ׂ�B�������ꍇ�͂��̃Z���͏��O�B
				RayResult callback;
				btVector3 start = { cell.m_CenterPos.x, cell.m_CenterPos.y - 1.0f, cell.m_CenterPos.z };
				btVector3 end = { cell.m_CenterPos.x, cell.m_CenterPos.y + 200.0f, cell.m_CenterPos.z };

				PhysicsWorld().RayTest(start, end, callback);

				if (callback.isHit)
				{
					vertCount += 3;
					continue;
				}

				//�[�Z�������B
				Vector3 centerPos = cell.m_CenterPos - m_position;
				if (centerPos.x < 34.0f || centerPos.z < 34.0f
					|| centerPos.x >(ChunkWidth * OBJECT_UNIT) - 34.0f
					|| centerPos.z >(ChunkWidth * OBJECT_UNIT) - 34.0f
					)
				{
					//�[�Z���������B
					m_naviMeshManager->AddEdgeCellList(cell, x, y);
				}
				else
				{
					//�Ǘ������X�g�Ɉڂ��B
					m_cellList.push_back(cell);
				}



			}
			//�����b�V���̒��_�ցB
			vertCount += 3;
		}
	}

	void TerrainWorld::SerchLinkCell(int x, int y)
	{
		//�F�X������������ōs������

		//�n�`�C���f�b�N�X�v�Z�B
		Vector2 linkChunkIndexList[4] = { Vector2::Zero };
		linkChunkIndexList[0] = { -1 , 0 };
		linkChunkIndexList[1] = { 1 , 0 };
		linkChunkIndexList[2] = { 0 ,-1 };
		linkChunkIndexList[3] = { 0 , 1 };

		std::vector<NVMGenerator::Cell*> serchCellList;

		//�[�Z���ƒ[�Z���̗אڂ����B
		for (auto linkChunkIndex : linkChunkIndexList)
		{
			//���ׂ�`�����N�̃C���f�b�N�X���Z�o.
			Vector2 reserchChunk = { x + linkChunkIndex.x , y + linkChunkIndex.y };

			if (reserchChunk.x < 0 || reserchChunk.y < 0 || abs(reserchChunk.x) > 2 || abs(reserchChunk.y) > 2)
			{
				//�s���ȗאڃC���f�b�N�X�B
				continue;
			}

			for (auto& cell : m_naviMeshManager->GetEdgeCellList(reserchChunk.x, reserchChunk.y))
			{
				//����4�`�����N��
				serchCellList.push_back(&cell);
			}
		}

		for (auto& cell : m_naviMeshManager->GetEdgeCellList(x, y))
		{
			//���`�����N���B
			serchCellList.push_back(&cell);
		}

		for (auto& cell : m_cellList)
		{
			serchCellList.push_back(&cell);
		}

		//�[�Z���ƒ[�Z���Ƃ��Ȃ��B
		for (auto& baseCell : m_naviMeshManager->GetEdgeCellList(x, y))
		{
			int linkCellIndex = 0;
			for (auto& serchCell : serchCellList)
			{
				//�����N�Z�����������Ă����B
				if (&baseCell == serchCell) {
					//�x�[�X�Z���ƃ����N�Z���̃A�h���X������Ȃ̂ŃX�L�b�v�B
					continue;
				}

				int linkVertex = 0;	//�אڒ��_�̐��B

				//���_��r�B
				for (auto& baseVertex : baseCell.pos) {
					for (auto& serchVertex : serchCell->pos) {
						if (/*baseVertex.x == serchVertex.x && baseVertex.z == serchVertex.z*/baseVertex == serchVertex) {
							//���_���ꏏ
							linkVertex++;
						}
					}
				}//VertexSerch.

				if (linkVertex >= 2) {
					//�אڃ��C����2���邽�߂����͗אڒ��_�ł���B
					baseCell.m_linkCell[linkCellIndex] = serchCell;
					linkCellIndex++;
					if (linkCellIndex == 3) {
						//�����N�Z���R�ړ��B�������I���B
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
				//�����N�Z�����������Ă����B
				if (&baseCell == serchCell) {
					//�x�[�X�Z���ƃ����N�Z���̃A�h���X������Ȃ̂ŃX�L�b�v�B
					continue;
				}

				int linkVertex = 0;	//�אڒ��_�̐��B

				//���_��r�B
				for (auto& baseVertex : baseCell.pos) {
					for (auto& serchVertex : serchCell->pos) {
						if (/*baseVertex.x == serchVertex.x && baseVertex.z == serchVertex.z*/baseVertex == serchVertex) {
							//���_���ꏏ
							linkVertex++;
						}
					}
				}//VertexSerch.

				if (linkVertex >= 2) {
					//�אڃ��C����2���邽�߂����͗אڒ��_�ł���B
					baseCell.m_linkCell[linkCellIndex] = serchCell;
					linkCellIndex++;
					if (linkCellIndex == 3) {
						//�����N�Z���R�ړ��B�������I���B
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
					//�אڃf�o�b�O�p�Ƀ��C�����`�����āA�i�[�B
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
					//�אڃf�o�b�O�p�Ƀ��C�����`�����āA�i�[�B
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
			//�ύX������
			m_terrainChunkData = terrainCD;
			//�}�[�`���L���[�u�̍X�V�t���O�����Ă�
			m_terrainChunkData->EnableUpdated();
			return true;
		}
		return false;
	}

	void TerrainWorld::GetMinMaxCenterPos(Vector3& Min, Vector3& Max)
	{
		//�������B
		Min = { FLT_MAX, FLT_MAX, FLT_MAX };
		Max = { -FLT_MAX, -FLT_MAX, -FLT_MAX };

		for (int i = 0; i < m_terrainRender->GetCenterArray().size(); i++)
		{
			Vector3 centerPos = m_terrainRender->GetCenterArray().at(i) + m_position;

			//���[�J�����W�n�ł�edge�ʒu�����߂�B
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
			//�e���_�̉e���x�H����
			//�O�p�`�e�[�u���̃C���f�b�N�X���쐬����B
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

		//�g���C�A���O���e�[�u����̂��̔ԍ��ɎO�p�`�͂Ȃ��B
		if (configIndex == 0 || configIndex == 255)
		{
			return;
		}
		//�G�b�W�t���O���v�Z�B
		int edgeFlags = nsMarching::CubeEdgeFlags[configIndex];

		//�G�b�W���g���Ȃ��B
		if (edgeFlags == 0) return;

		//�G�b�W��̒��_�������B
		Vector3 EdgeVertex[12] = { {0.0f,0.0f,0.0f} };
		Vector4 EdgeTexture[12] = { {0.0f,0.0f,0.0f,0.0f} };

		//Find the point of intersection of the surface with each edge
		for (int i = 0; i < 12; i++)
		{
			//���̃G�b�W���g�����ǂ����B
			if ((edgeFlags & (1 << i)) != 0)
			{
				//�I�t�Z�b�g���v�Z����B
				float offset = GetOffset(cube.cube[nsMarching::EdgeConnection[i][0]], cube.cube[nsMarching::EdgeConnection[i][1]]);

				Vector4 tex1 = { 0.0f,0.0f,0.0f,0.0f };
				tex1.v[cube.terrainID[nsMarching::EdgeConnection[i][0]]] = 1.0f;
				Vector4 tex2 = { 0.0f,0.0f,0.0f,0.0f };
				tex2.v[cube.terrainID[nsMarching::EdgeConnection[i][1]]] = 1.0f;

				EdgeTexture[i] = tex1 * (1.0f - offset) + tex2 * offset;

				//�G�b�W��̒��_�̈ʒu���L���[�u�̒��_�̉e���l����v�Z����B
				EdgeVertex[i].x = (static_cast<float>(nsMarching::CornerTable[nsMarching::EdgeConnection[i][0]].x) * (1.0f - offset) 
					+ offset * static_cast<float>(nsMarching::CornerTable[nsMarching::EdgeConnection[i][1]].x));

				EdgeVertex[i].y = (static_cast<float>(nsMarching::CornerTable[nsMarching::EdgeConnection[i][0]].y) * (1.0f - offset) 
					+ offset * static_cast<float>(nsMarching::CornerTable[nsMarching::EdgeConnection[i][1]].y));

				EdgeVertex[i].z = (static_cast<float>(nsMarching::CornerTable[nsMarching::EdgeConnection[i][0]].z) * (1.0f - offset) 
					+ offset * static_cast<float>(nsMarching::CornerTable[nsMarching::EdgeConnection[i][1]].z));

				////�G�b�W��̒��_�̈ʒu���L���[�u�̒��_�̉e���l����v�Z����B
				//EdgeVertex[i].x = (static_cast<float>(nsMarching::CornerTable[nsMarching::EdgeConnection[i][0]].x) * offset 
				//	+ (1.0f - offset) * static_cast<float>(nsMarching::CornerTable[nsMarching::EdgeConnection[i][1]].x));

				//EdgeVertex[i].y = (static_cast<float>(nsMarching::CornerTable[nsMarching::EdgeConnection[i][0]].y) * offset
				//	+ (1.0f - offset)  * static_cast<float>(nsMarching::CornerTable[nsMarching::EdgeConnection[i][1]].y));

				//EdgeVertex[i].z = (static_cast<float>(nsMarching::CornerTable[nsMarching::EdgeConnection[i][0]].z) * offset
				//	+ (1.0f - offset) * static_cast<float>(nsMarching::CornerTable[nsMarching::EdgeConnection[i][1]].z));

				////�G�b�W��̒��_�̈ʒu���L���[�u�̒��_�̉e���l����v�Z����B
				//EdgeVertex[i].x = (static_cast<float>(nsMarching::CornerTable[nsMarching::EdgeConnection[i][0]].x)
				//	+ offset * static_cast<float>(nsMarching::EdgeDirectionTable[i].x));

				//EdgeVertex[i].y = (static_cast<float>(nsMarching::CornerTable[nsMarching::EdgeConnection[i][0]].y)
				//	+ offset * static_cast<float>(nsMarching::EdgeDirectionTable[i].y));

				//EdgeVertex[i].z = (static_cast<float>(nsMarching::CornerTable[nsMarching::EdgeConnection[i][0]].z)
				//	+ offset * static_cast<float>(nsMarching::EdgeDirectionTable[i].z));
			}
		}

		int edgeIndex = 0;

		//�L���[�u��ɑ��݂���O�p�`�͍ő�5�B
		for (int i = 0; i < 5; i++)
		{
			//�O�p�|���S���̒��_���W�B
			Vector3 vertPos[3];

			Vector4 vertTexType[3];
			//�G�b�W���W�B
			Vector3 edgePos[3];
			//�O�p�|���S���̒��S���W�B
			Vector3 center = Vector3::Zero;
			int p = 0;
			for (; p < 3; p++)
			{
				int indice = nsMarching::TriangleConnectionTable[configIndex][edgeIndex];

				//�O�p�`���Ȃ��B
				if (indice == -1)
					return;

				edgePos[p] = EdgeVertex[indice];
				edgePos[p].x -= 0.5f;
				edgePos[p].y -= 0.5f;
				edgePos[p].z -= 0.5f;

				//���_�̍��W���v�Z�B
				vertPos[p] = (position + EdgeVertex[indice]) * OBJECT_UNIT;
				m_vertices.push_back(vertPos[p]);	//���_��ςށB
				//���S���W���v�Z����B
				center += vertPos[p];

				vertTexType[p] = EdgeTexture[indice];

				edgeIndex++;
			}

			//���S���W���Z�o�B
			center /= p;

			//���S���W����̃x�N�g���B
			Vector3 vDir[3];

			for (int vNum = 0; vNum < p; vNum++)
			{
				vDir[vNum] = vertPos[vNum] - center;
				vDir[vNum].Normalize();
			}

			//�@�����v�Z�B
			Vector3 normal;
			normal.Cross(vDir[0], vDir[1]);
			normal.Normalize();

			//�O�p�|���S����V�����v�Z�B
			Vector3 axisV;
			//�@����Y�����ł͂Ȃ��B
			if (fabsf(normal.Dot(Vector3::AxisY)) < 0.998f)
			{
				axisV.Cross(normal, Vector3::AxisY);
			}
			else {
				axisV.Cross(normal, Vector3::AxisX);
			}
			axisV.Normalize();
			//�O�p�|���S����U�����v�Z�B
			Vector3 axisU;
			axisU.Cross(normal, axisV);
			axisU.Normalize();

			for (int j = 0; j < p; j++)
			{
				TerrainVertex vert;
				vert.m_pos = vertPos[j];
				vert.m_texType = vertTexType[j];
				vert.m_normal = normal;

				//TODO:���������B
				//UV���W���v�Z����B
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
		//�����I�u�W�F�N�g�쐬�B
		m_staticObj.CreateBuffer(
			m_position,
			Quaternion::Identity,
			Vector3::One,
			m_vertices
		);		
	}
}