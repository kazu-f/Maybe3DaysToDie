#pragma once

#include "TerrainManager/TerrainManager.h"
#include "Navigation/NVMGenerator.h"

class LoadingByChunk;
class Player;

/// <summary>
/// �n�`�`�����N�ƃu���b�N�`�����N���܂Ƃ߂��`�����N�N���X�B
/// </summary>
class NaviMeshManager : public IGameObject
{
private:
	//pl���B
	Player* m_playerPtr = nullptr;							//�v���C���[�B
	LoadingByChunk* m_loadingByChunk = nullptr;				//�`�����N���[�f�B���O�B
	nsTerrain::TerrainManager* m_terrainManager = nullptr;	//�n�`�B

	int m_playerGrid[2] = { 0 };						//�O�t���[����Player�̃O���b�h�ʒu�B
	
	//NVM.
	bool m_isUpdateNVM = false;							//nvm���X�V����H

public:
	virtual ~NaviMeshManager();
	bool Start() override;
	void Update() override;

	void SetLoadingByChunk(LoadingByChunk* loadingByChunk)
	{
		m_loadingByChunk = loadingByChunk;
	}

private:
	void CalcPlayerGrid();
};

