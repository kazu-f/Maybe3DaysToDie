#pragma once
/// <summary>
/// スレッドの基底クラス
/// </summary>
class Thread
{
public:
	virtual ~Thread() 
	{ 
		delete m_thread;
	}

	/// <summary>
	/// スレッドを立てる
	/// </summary>
	void ThreadStart()
	{
		m_thread = new std::thread([&]() {
			//スレッドから関数を実行
			Run();
		});
	}

	/// <summary>
	/// スレッドの処理が終わるまで待つ
	/// </summary>
	void Join()
	{
		m_thread->join();
	}

	/// <summary>
	/// スレッドの処理
	/// </summary>
	virtual void Run() = 0;
private:
	std::thread* m_thread = nullptr;		//スレッド
};

