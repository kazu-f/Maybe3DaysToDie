#pragma once

#include "TerrainManager/TerrainManager.h"
#include "Navigation/NVMGenerator.h"

class LoadingByChunk;

/// <summary>
/// �n�`�`�����N�ƃu���b�N�`�����N���܂Ƃ߂��`�����N�N���X�B
/// </summary>
class WorldChunk : public IGameObject
{
//private:
//	//chunkData.
//	LoadingByChunk* m_LoadingByChunk = nullptr;	//PlaceMentObject���̃`�����N�B
//	nsTerrain::TerrainManager* m_Terrain;		//�n�`�f�[�^�[���̃`�����N�B
//	
//	//NVM.
//	using Cell = NVMGenerator::Cell;			//�Z���B
//	bool m_isNVMUpdate = true;					//NVM�̍X�V���K�v���B
//	Cell CellByChunk[][][]
//
//	Vector3 m_playerGrid = Vector3::Zero;		//Player�̃O���b�h�ʒu�B
};

