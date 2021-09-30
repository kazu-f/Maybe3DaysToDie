#pragma once
class Player;
class Stage;
class GameCamera;
class GameSnece : public IGameObject
{
	/// <summary>
	/// ‰Šú‰»
	/// </summary>
	/// <returns>true‚É‚È‚é‚Ü‚Åƒ‹[ƒv‚·‚é</returns>
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