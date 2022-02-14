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
	static MauseInfo* GetInstance() {
		return m_MauseInfo;
	}
	void SetMauseState(const State& st) {
		m_MauseState = st;
	}
	void SetMauseMove(float moveSpeed) {
		m_MauseMove = moveSpeed;
	}
	State GetMauseState() const {
		return m_MauseState;
	}
	float GetMauseMove() const {
		return m_MauseMove;
	}
private:
	static MauseInfo* m_MauseInfo;
	MauseInfo() {};
	float m_MauseMove = 0.0f;
	State m_MauseState = State::None;
	bool m_ShowCursor = false;			//マウスカーソルを見せる
};

