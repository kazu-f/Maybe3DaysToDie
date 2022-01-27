#pragma once
/// <summary>
/// �X���b�h�̊��N���X
/// </summary>
class Thread
{
public:
	virtual ~Thread() 
	{ 
		delete m_thread;
	}

	/// <summary>
	/// �X���b�h�𗧂Ă�
	/// </summary>
	void ThreadStart()
	{
		m_thread = new std::thread([&]() {
			//�X���b�h����֐������s
			Run();
		});
	}

	/// <summary>
	/// �X���b�h�̏������I���܂ő҂�
	/// </summary>
	void Join()
	{
		m_thread->join();
	}

	/// <summary>
	/// �X���b�h�̏���
	/// </summary>
	virtual void Run() = 0;
private:
	std::thread* m_thread = nullptr;		//�X���b�h
};

