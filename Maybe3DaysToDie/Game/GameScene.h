#pragma once
#include "GameConfig/WorldConfig/WorldConfig.h"

#include "Save/TerrainSave/TerrainSave.h"
#include "Load/TerrainLoad/TerrainLoad.h"

class Player;
class Stage;
class GameCamera;
class ItemBar;

class PlacementObject;
class DestroyObject;
class Tool;
class BlockManager;

class LoadingByChunk;

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
	ItemBar* m_ItemBar = nullptr;
	//���u��//
	//todo ��قǃv���C���[���ɂ����Ă�������
	PlacementObject* m_PlacementObject = nullptr;		//�ݒu�I�u�W�F�N�g
	DestroyObject* m_DestroyObject = nullptr;		//�I�u�W�F�N�g�j��
	Tool* tool = nullptr;
	//Samples//
	CFontRender* m_fontRender = nullptr;			//�t�H���g�����_�[�B
	BlockManager* m_BlockManager = nullptr;
	TerrainSave m_TerrainSave;		//�n�`�Z�[�u�p�̃N���X
	TerrainLoad m_TerrainLoad;
	SaveDataFile m_SaveDataFile;
	LoadingByChunk* m_LoadingByChunk = nullptr;
	WorldConfig m_WorldConfig;		//���[���h�ݒ�
};