#pragma once

#include "Save/TerrainSave/TerrainSave.h"
#include "Save/TerrainSave/TerrainLoad.h"
#include "Save/ChestSave/ChestSave.h"
#include "Save/ChestSave/ChestLoad.h"
#include "AccessObject/AccessObject.h"

class Player;
class Stage;
class GameCamera;

class PlacementObject;
class DestroyObject;
class Tool;

class LoadingByChunk;
class NaviMeshManager;

class CGameScene : public IGameObject
{
public:
	CGameScene() {};
	~CGameScene();
public:
	/// <summary>
	/// �X�^�[�g�B
	/// </summary>
	bool Start()override final;
	/// <summary>
	/// �X�V�B
	/// </summary>
	void Update()override final;
private:
	Player* m_Player = nullptr;
	GameCamera* m_Camera = nullptr;
	Stage* m_Stage = nullptr;

	//���u��//
	//Samples//
	CFontRender* m_fontRender = nullptr;			//�t�H���g�����_�[�B
	TerrainSave m_TerrainSave;		//�n�`�Z�[�u�p�̃N���X
	TerrainLoad m_TerrainLoad;
	ChestSave m_ChestSave;		//�`�F�X�g�Z�[�u�p�̃N���X
	ChestLoad m_ChestLoad;		//�`�F�X�g���[�h�p�̃N���X
	SaveDataFile m_SaveDataFile;
	ChestDataFile m_ChestDataFile;
	LoadingByChunk* m_LoadingByChunk = nullptr;
	AccessObject m_AccessObject;		//�ݒu���ɃA�N�Z�X���邽�߂̃N���X
};