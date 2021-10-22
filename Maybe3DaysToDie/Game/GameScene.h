#pragma once

class Player;
class Stage;
class GameCamera;
class PlacementObject;

/// <summary>
/// �V���O���g���B
/// </summary>
class CGameScene
{
public:
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
private:
	Player* m_Player = nullptr;
	GameCamera* m_Camera = nullptr;
	Stage* m_Stage = nullptr;
	PlacementObject* m_PlacementObject = nullptr;		//�ݒu�I�u�W�F�N�g
	//Samples//
	CFontRender* m_fontRender = nullptr;			//�t�H���g�����_�[�B

};