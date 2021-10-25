#pragma once

class Player;
class Stage;
class GameCamera;
class PlacementObject;

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
	PlacementObject* m_PlacementObject = nullptr;		//�ݒu�I�u�W�F�N�g
	//Samples//
	CFontRender* m_fontRender = nullptr;			//�t�H���g�����_�[�B

};