#include "stdafx.h"
#include "TerrainWorld.h"
#include "TerrainRender\TerrainRender.h"

namespace nsTerrain {
	bool TerrainWorld::Start()
	{
		//�n�`�`��N���X�쐬�B
		m_terrainRender = NewGO<TerrainRender>(10);
		TerrainInitData initData;
		initData.vertexNum = width * width * height * 15;

		m_terrainRender->Init(initData);

		//�n�`�f�[�^�쐬�B
		PopurerTerrainMap();
		//���b�V���f�[�^���쐬�B
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
						//���̏ꏊ�̍����ɑ΂��ău���b�N���͂��Ă��Ȃ��B
						if (y <= thisHeight - 0.5f)
							point = 0.0f;
						//���̏ꏊ�̏�ɂ��u���b�N������B
						else if (y > thisHeight + 0.5f)
							point = 1.0f;
						//���̏ꏊ�̃u���b�N�̉e���l�v�Z�B(������B)
						else if (y > thisHeight)
							point = (float)y - thisHeight;
						//���̏ꏊ�̃u���b�N�̉e���l�v�Z�B(�������B)
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
			//�e���_�̉e���x�H����
			//�O�p�`�e�[�u���̃C���f�b�N�X���쐬����B
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

		//�g���C�A���O���e�[�u����̂��̔ԍ��ɎO�p�`�͂Ȃ��B
		if (configIndex == 0 || configIndex == 255)
		{
			return;
		}

		int edgeIndex = 0;

		//�L���[�u��ɑ��݂���O�p�`�͍ő�5�B
		for (int i = 0; i < 5; i++)
		{
			//�O�p�|���S���̒��_���W�B
			Vector3 vertPos[3];
			//�O�p�|���S���̒��S���W�B
			Vector3 center = Vector3::Zero;
			int p = 0;
			for (; p < 3; p++)
			{
				int indice = nsMarching::TriangleConnectionTable[configIndex][edgeIndex];

				//�O�p�`���Ȃ��B
				if (indice == -1)
					return;

				//�G�b�W���\������2���_���擾�B
				Vector3 vert1 = position + nsMarching::EdgeTable[indice][0];
				Vector3 vert2 = position + nsMarching::EdgeTable[indice][1];

				//���_�̍��W���v�Z�B
				vertPos[p] = (vert1 + vert2) / 2.0f * TERRAIN_UNIT;
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

			//�O�p�|���S����X�����v�Z�B
			Vector3 axisX;
			//�@����Y�����ł͂Ȃ��B
			if (fabsf(normal.Dot(Vector3::AxisY)) < 0.998f)
			{
				axisX.Cross(Vector3::AxisY, normal);
			}
			else {
				axisX.Cross(Vector3::AxisZ, normal);
			}
			axisX.Normalize();
			//�O�p�|���S����Y�����v�Z�B
			Vector3 axisY;
			axisY.Cross(normal, axisX);
			axisX.Normalize();

			for (int j = 0; j < p; j++)
			{
				Vertex vert;
				vert.m_pos = vertPos[j];
				vert.m_normal = normal;

				//UV���W���v�Z����B
				Vector2 uv;
				uv.x = vDir[j].Dot(axisX) / 2.0f + 0.5f;
				uv.y = vDir[j].Dot(axisY) / 2.0f + 0.5f;

				vert.m_uv = uv;

				m_terrainRender->AddVertex(vert);
			}


		}

	}
}