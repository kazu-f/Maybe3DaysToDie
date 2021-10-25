#include "stdafx.h"
#include "NVMGenerator.h"
#include "DestructibleObject/Terrain/Terrain.h"
#include "NVMDebugDraw.h"

bool NVMGenerator::isInstantiate = false;

NVMGenerator::NVMGenerator()
{
	//�V���O���g���B
	assert(!isInstantiate);
	isInstantiate = true;
}

NVMGenerator::~NVMGenerator()
{
}

void NVMGenerator::CreateNVM(nsTerrain::TerrainRender* terrain, bool isDebugDraw)
{
	//�d�_�̐��̓��b�V���̐��B
	int meshCount = terrain->GetCenterArray().size();

	//���_�J�E���g�B
	int vertCount = 0;
	//NVM�̊�{�p�����[�^�[�𗬂�����ł����B
	for (int mesh = 0; mesh < meshCount; mesh++) {
		//�Z�����쐬����B
		Cell cell;
		//���b�V���S�Ă̂R���_���v�Z����B
		cell.pos[0] = terrain->GetVertexList().at(vertCount).m_pos;
		cell.pos[1] = terrain->GetVertexList().at(vertCount + 1).m_pos;
		cell.pos[2] = terrain->GetVertexList().at(vertCount + 2).m_pos;
		//�d�_�B
		cell.m_CenterPos = terrain->GetCenterArray().at(mesh);
		//�����b�V���̒��_�ցB
		vertCount += 3;
		//�Ǘ������X�g�Ɉڂ��B
		m_cellList.push_back(cell);
	}

	if (isDebugDraw) {
		//�f�o�b�O�B
		m_nvmDebugDraw = new NVMDebugDraw;
		m_isDebugDraw = isDebugDraw;

		for (auto& cell : m_cellList) {
			m_nvmDebugDraw->PushVertex(cell.pos[0]);
			m_nvmDebugDraw->PushVertex(cell.pos[1]);
			m_nvmDebugDraw->PushVertex(cell.pos[2]);
		}

		m_nvmDebugDraw->Init(terrain->GetIndexList());
	}

	//���_���W���Z���̗אڃZ�����v�Z����B

	//
}

void NVMGenerator::UpdateNVM(nsTerrain::TerrainRender* terrain)
{
}

void NVMGenerator::DebugDraw(nsTerrain::TerrainRender* terrain)
{
	if (!m_isDebugDraw) {
		return;
	}

	m_nvmDebugDraw->Render(terrain->GetVertexCount());
}
