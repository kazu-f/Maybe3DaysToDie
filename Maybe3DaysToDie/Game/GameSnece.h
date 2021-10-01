#pragma once
class Player;
class Stage;
class GameCamera;
class GameSnece : public IGameObject
{
private:
	/// <summary>
	/// GameObject‚ÉÏ‚Ü‚ê‚é‚Æˆê“x‚¾‚¯ŒÄ‚Î‚ê‚é‰Šú‰»ŠÖ”
	/// </summary>
	/// <returns>true‚ª•Ô‚é‚Ü‚Åƒ‹[ƒv‚·‚é</returns>
	bool Start()override final;
	/// <summary>
	/// delete‚³‚ê‚é‚ÆŒÄ‚Î‚ê‚é
	/// </summary>
	void OnDestroy()override final;

private:
	Player* m_Player = nullptr;
	GameCamera* m_Camera = nullptr;
	Stage* m_Stage = nullptr;
};