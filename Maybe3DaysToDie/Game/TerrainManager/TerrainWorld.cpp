#include "stdafx.h"
#include "TerrainWorld.h"
#include "TerrainChunkData.h"
#include "TerrainRender\TerrainRender.h"


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

		PhysicsWorld().SetDebugMode(btIDebugDraw::DBG_DrawWireframe);

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
			//�ύX������
			m_terrainChunkData = terrainCD;
			//�}�[�`���L���[�u�̍X�V�t���O�����Ă�
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

		//Find the point of intersection of the surface with each edge
		for (int i = 0; i < 12; i++)
		{
			//���̃G�b�W���g�����ǂ����B
			if ((edgeFlags & (1 << i)) != 0)
			{
				//�I�t�Z�b�g���v�Z����B
				float offset = GetOffset(cube.cube[nsMarching::EdgeConnection[i][0]], cube.cube[nsMarching::EdgeConnection[i][1]]);

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