#pragma once

#include "Enemy/EnemyGenerator.h"

class Player;
class Stage;
class GameCamera;
class PlacementObject;

/// <summary>
/// �V���O���g���B
/// </summary>
class CGameScene
{
private:
	CGameScene() {};
	~CGameScene();
public:
	/// <summary>
	/// �X�^�[�g�B
	/// </summary>
	void Start();
	/// <summary>
	/// �X�V�B
	/// </summary>
	void Update();
public:
	/// <summary>
	/// �C���X�^���X���B
	/// </summary>
	void Instantiate()
	{
		if (m_instance == nullptr) {
			//�C���X�^���X����ĂȂ��̂ō쐬�B
			m_instance = new CGameScene;
		}
	}
	/// <summary>
	/// �C���X�^���X���폜�B
	/// </summary>
	void DeleteInstance()
	{
		if (m_instance != nullptr) {
			//�폜�B
			delete m_instance;
		}
	}
public://Getter.
	/// <summary>
	/// �C���X�^���X���擾�B
	/// </summary>
	/// <returns></returns>
	static CGameScene* GetInstance()
	{
		return m_instance;
	}
	/// <summary>
	/// �v���C���[���擾�BFindGO�̃I�[�o�[�w�b�h�Ȃ����H��
	/// </summary>
	/// <returns></returns>
	Player* GetPlayer() const 
	{
		return m_Player;
	}
	/// <summary>
	/// �G�l�~�[�W�F�l���[�^�[���擾�B
	/// </summary>
	/// <returns></returns>
	EnemyGenerator& GetEnemyGenerator()
	{
		return m_enemyGenerator;
	}
private:
	static CGameScene* m_instance;					//�V���O���g���C���X�^���X�B
	Player* m_Player = nullptr;
	GameCamera* m_Camera = nullptr;
	Stage* m_Stage = nullptr;
	PlacementObject* m_PlacementObject = nullptr;		//�ݒu�I�u�W�F�N�g
	EnemyGenerator m_enemyGenerator;				//�G�l�~�[�W�F�l���[�^�[�B
	//Samples//
	CFontRender* m_fontRender = nullptr;			//�t�H���g�����_�[�B

};

/// <summary>
/// �Q�[���V�[�����擾�B
/// </summary>
/// <returns></returns>
static inline CGameScene* GameScene()
{
	return CGameScene::GetInstance();
}