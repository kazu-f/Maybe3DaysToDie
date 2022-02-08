#pragma once
class MauseInfo
{
	enum State {
		MauseLClick,
		MauseRClick,
		MauseWheelUp,
		MauseWheelDown,
		MauseCenterClick,
		None,
	};
public:

	static void Create();
	static MauseInfo* GetInstance() {
		return m_MauseInfo;
	}
	void SetMauseState(State st) {
		m_MauseState = st;
	}
	void SetMauseMove(float moveSpeed) {
		m_MauseMove = moveSpeed;
	}
	State GetMauseState() {
		return m_MauseState;
	}
	float GetMauseMove() {
		return m_MauseMove;
	}
private:
	static MauseInfo* m_MauseInfo;
	MauseInfo() {};
	float m_MauseMove = 0.0f;
	State m_MauseState = State::None;
	bool m_ShowCursor = false;			//マウスカーソルを見せる
};

