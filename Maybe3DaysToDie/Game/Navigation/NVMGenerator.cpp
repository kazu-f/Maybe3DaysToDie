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

//void NVMGenerator::CreateNVM(nsTerrain::TerrainRender* terrain, bool isDebugDraw)
//{
//	//�d�_�̐��̓��b�V���̐��B
//	int meshCount = terrain->GetCenterArray().size();
//
//	//���_�J�E���g�B
//	int vertCount = 0;
//	//NVM�̊�{�p�����[�^�[�𗬂�����ł����B
//	for (int mesh = 0; mesh < meshCount; mesh++) {
//		if (terrain->GetVertexList().at(vertCount).m_normal.y > 0.000001f) {
//			//�@�����������̏ꍇ�͕������Ƃ��ł��Ȃ��X�΂̂��ߏ��O�B
//			//�Z�����쐬����B
//			Cell cell;
//			//���b�V���S�Ă̂R���_���v�Z����B
//			cell.pos[0] = terrain->GetVertexList().at(vertCount).m_pos;
//			cell.pos[1] = terrain->GetVertexList().at(vertCount + 1).m_pos;
//			cell.pos[2] = terrain->GetVertexList().at(vertCount + 2).m_pos;
//			//�d�_�B
//			cell.m_CenterPos = terrain->GetCenterArray().at(mesh);
//			//�Ǘ������X�g�Ɉڂ��B
//			m_cellList.push_back(cell);
//		}
//		//�����b�V���̒��_�ցB
//		vertCount += 3;
//	}
//
//	////���b�V���̏�Ƀ��b�V�������݂��Ă��Ȃ����m�F���Ă����B
//	//for (int cellIndex = 0; cellIndex < m_cellList.size(); cellIndex++) {
//	//	//���S�_����^������Ƀ��C���΂��B
//	//	btVector3 start;
//	//	start.setValue(m_cellList[cellIndex].m_CenterPos.x, m_cellList[cellIndex].m_CenterPos.y, m_cellList[cellIndex].m_CenterPos.z);
//	//	btVector3 end;
//	//	end.setValue(m_cellList[cellIndex].m_CenterPos.x, m_cellList[cellIndex].m_CenterPos.y + 200, m_cellList[cellIndex].m_CenterPos.z);
//	//	//�R�[���o�b�N�B�ʂɓ��ʂȏ�������Ȃ�������ł����邩�I�H
//	//	btCollisionWorld::ClosestRayResultCallback cb(start, end);
//	//	//���C�e�X�g�B
//	//	PhysicsWorld().RayTest(start, end, cb);
//	//	if (cb.hasHit()) {
//	//		//�Ȃ񂩂ɏՓ˂�������A���̃��b�V���͏����Bitr::cast
//	//		m_cellList.erase(m_cellList.begin() + cellIndex);
//	//	}
//	//}
//
//	//�אڃZ���`���B
//	for (auto& baseCell : m_cellList) {
//		//���b�V���S�̂Ɍ������|���āA�אڃZ���������B
//		int linkCellIndex = 0;	//�אڃZ���p�C���f�b�N�X�B
//		for (auto& serchCell : m_cellList) {
//			
//			//�����N�Z�����������Ă����B
//			if (&baseCell == &serchCell) {
//				//�x�[�X�Z���ƃ����N�Z���̃A�h���X������Ȃ̂ŃX�L�b�v�B
//				continue;
//			}
//			
//			int linkVertex = 0;	//�אڒ��_�̐��B
//
//			//���_��r�B
//			for (auto& baseVertex : baseCell.pos) {
//				for (auto& serchVertex : serchCell.pos) {
//					if (baseVertex == serchVertex) {
//						//���_���ꏏ
//						linkVertex++;
//					}
//				}
//			}//VertexSerch.
//
//			if (linkVertex >= 2) {
//				//�אڃ��C����2���邽�߂����͗אڒ��_�ł���B
//				baseCell.m_linkCell[linkCellIndex] = &serchCell;
//				linkCellIndex++;
//				if (linkCellIndex == 3) {
//					//�����N�Z���R�ړ��B�������I���B
//					break;
//				}
//			}
//		}//linkCellSerch.
//	}
//
//
//
//	if (isDebugDraw) {
//		//�f�o�b�O�B
//		m_nvmDebugDraw = new NVMDebugDraw;
//		m_isDebugDraw = isDebugDraw;
//
//		for (auto& cell : m_cellList) {
//			m_nvmDebugDraw->PushVertex(cell.pos[0]);
//			m_nvmDebugDraw->PushVertex(cell.pos[1]);
//			m_nvmDebugDraw->PushVertex(cell.pos[2]);
//			for (auto* linkCell : cell.m_linkCell) {
//				if(linkCell == nullptr){
//					break;
//				}
//				//�אڃf�o�b�O�p�Ƀ��C�����`�����āA�i�[�B
//				NVMDebugDraw::Line line;
//				line.start = cell.m_CenterPos;
//				line.end = linkCell->m_CenterPos;
//				m_nvmDebugDraw->PushToLinkCellLine(line);
//			}
//		}
//
//		m_nvmDebugDraw->Init(terrain->GetIndexList());
//	}
//
//	//���_���W���Z���̗אڃZ�����v�Z����B
//
//	//
//}

void NVMGenerator::UpdateNVM(nsTerrain::TerrainRender* terrain)
{
}

void NVMGenerator::DebugDraw(nsTerrain::TerrainRender* terrain)
{
	if (!m_isDebugDraw) {
		return;
	}

	//m_nvmDebugDraw->Render(terrain->GetVertexCount());
}
