#pragma once
class MauseInfo
{
public:
	enum State {
		MauseLClick,
		MauseRClick,
		MauseWheelUp,
		MauseWheelDown,
		MauseCenterClick,
		None,
	};
	static void Create();
	static void Delete();
	static MauseInfo* GetInstance(){
		return m_MauseInfo;
	}
	void SetMauseState(const State& st) {
		m_MauseState = st;
	}
	void SetMauseMove(const Vector2& moveSpeed) {
		m_MauseMove = moveSpeed;
	}
	State GetMauseState() {
		return m_MauseState;
	}
	Vector2 GetMauseMove() const {
		return m_MauseMove;
	}
	void MauseMoveUpdate();

	void SetMauseCursor(const Vector2& CorsorPos);

	static Vector2 IntialMausePos() {
		return m_InitialMausePos;
	}

	Vector2 GetMausePos()const {
		return m_MauseCorsoluPos;
	}
private:
	static MauseInfo* m_MauseInfo;
	MauseInfo() {};
	Vector2 m_MauseMove = Vector2::Zero;
	State m_MauseState = State::None;
	bool m_ShowCursor = false;			//マウスカーソルを見せる
	Vector2 m_DefaultPoint = { 500.0f,300.0f };
	Vector2 m_MauseCorsoluPos = { 500.0f,300.0f };
	static Vector2 m_InitialMausePos;
};

