#include "stdafx.h"
#include "Terrain.h"

namespace Terrain {

	void Terrain::SetPosition(const Vector3& pos)
	{
		m_position = pos;
		for (int i = 0; i < en_terrainOnNum; i++ )
		{
			//���_���W��ݒ�B
			m_vertex[i].vertPos = pos + VERTEX_CONST[i];
		}
	}
	void Terrain::BuildVertex()
	{
		//��̒��_�B
		{
			m_vertex[en_terrainOnUp].nearVert[0] = &m_vertex[en_terrainOnFront];
			m_vertex[en_terrainOnUp].nearVert[1] = &m_vertex[en_terrainOnLeft];
			m_vertex[en_terrainOnUp].nearVert[2] = &m_vertex[en_terrainOnBack];
			m_vertex[en_terrainOnUp].nearVert[3] = &m_vertex[en_terrainOnRight];
		}
		//���̒��_�B
		{
			m_vertex[en_terrainOnDown].nearVert[0] = &m_vertex[en_terrainOnFront];
			m_vertex[en_terrainOnDown].nearVert[1] = &m_vertex[en_terrainOnLeft];
			m_vertex[en_terrainOnDown].nearVert[2] = &m_vertex[en_terrainOnBack];
			m_vertex[en_terrainOnDown].nearVert[3] = &m_vertex[en_terrainOnRight];
		}
		//�E�̒��_�B
		{
			m_vertex[en_terrainOnRight].nearVert[0] = &m_vertex[en_terrainOnFront];
			m_vertex[en_terrainOnRight].nearVert[1] = &m_vertex[en_terrainOnUp];
			m_vertex[en_terrainOnRight].nearVert[2] = &m_vertex[en_terrainOnBack];
			m_vertex[en_terrainOnRight].nearVert[3] = &m_vertex[en_terrainOnDown];
		}
		//���̒��_�B
		{
			m_vertex[en_terrainOnLeft].nearVert[0] = &m_vertex[en_terrainOnFront];
			m_vertex[en_terrainOnLeft].nearVert[1] = &m_vertex[en_terrainOnUp];
			m_vertex[en_terrainOnLeft].nearVert[2] = &m_vertex[en_terrainOnBack];
			m_vertex[en_terrainOnLeft].nearVert[3] = &m_vertex[en_terrainOnDown];
		}
		//�O�̒��_�B
		{
			m_vertex[en_terrainOnFront].nearVert[0] = &m_vertex[en_terrainOnRight];
			m_vertex[en_terrainOnFront].nearVert[1] = &m_vertex[en_terrainOnUp];
			m_vertex[en_terrainOnFront].nearVert[2] = &m_vertex[en_terrainOnLeft];
			m_vertex[en_terrainOnFront].nearVert[3] = &m_vertex[en_terrainOnDown];
		}
		//��̒��_�B
		{
			m_vertex[en_terrainOnBack].nearVert[0] = &m_vertex[en_terrainOnRight];
			m_vertex[en_terrainOnBack].nearVert[1] = &m_vertex[en_terrainOnUp];
			m_vertex[en_terrainOnBack].nearVert[2] = &m_vertex[en_terrainOnLeft];
			m_vertex[en_terrainOnBack].nearVert[3] = &m_vertex[en_terrainOnDown];
		}

	}
}
