#pragma once

class Player;
class Stage;
class GameCamera;

class GameSnece : public IGameObject
{
private:
	/// <summary>
	/// GameObject�ɐς܂��ƈ�x�����Ă΂�鏉�����֐�
	/// </summary>
	/// <returns>true���Ԃ�܂Ń��[�v����</returns>
	bool Start()override final;
	/// <summary>
	/// delete�����ƌĂ΂��
	/// </summary>
	void OnDestroy()override final;

private:
	Player* m_Player = nullptr;
	GameCamera* m_Camera = nullptr;
	Stage* m_Stage = nullptr;

	//Samples//
	CFontRender* m_fontRender = nullptr;	//�t�H���g�����_�[�B
};