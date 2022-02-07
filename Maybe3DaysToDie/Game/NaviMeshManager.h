#pragma once

#include "TerrainManager/TerrainManager.h"

class LoadingByChunk;
class Player;

/// <summary>
/// �n�`�`�����N�ƃu���b�N�`�����N���܂Ƃ߂��`�����N�N���X�B
/// </summary>
class NaviMeshManager : public IGameObject
{
private:
	enum VERTEX
	{
		VERTEX_BackLeft,
		VERTEX_BackRight,
		VERTEX_FrontLeft,
		VERTEX_FrontRight,
	};

private:
	LoadingByChunk* m_loadingByChunk = nullptr;				//�`�����N���[�f�B���O�B
	nsTerrain::TerrainManager* m_terrainManager = nullptr;	//�n�`�B

	int m_playerGrid[2] = { 0 };						//�O�t���[����Player�̃O���b�h�ʒu�B
	
	//NVM.
	bool m_isUpdateNVM = false;							//nvm���X�V����H  

public:
	virtual ~NaviMeshManager();
	bool Start() override;
	void Update() override;

private:
	/// <summary>
	/// �אڃZ���������o���B
	/// <para>�ݒu�u���b�N�ƒn�`�u���b�N�̗אڃZ�������ɂȂ邽��</para>
	/// <para>���ʂ̗אڃZ���v�Z�����Ƃ͈قȂ郍�W�b�N�ɂȂ��Ă���B</para>
	/// </summary>
	/// <param name="cell">�Z���B</param>
	void SerchLinkCell(NVMGenerator::Cell* cell);
};

