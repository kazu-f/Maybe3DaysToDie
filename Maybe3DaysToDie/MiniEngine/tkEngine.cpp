#include "MiniEngine.h"
#include "tkEngine.h"
#include "graphics/GraphicsEngine.h"
#include "physics/PhysicsWorld.h"

namespace Engine {

	TkEngine::TkEngine()
	{
	}

	TkEngine::~TkEngine()
	{
		Release();
	}
	void TkEngine::Release()
	{
		if (m_graphicsEngine) {
			delete m_graphicsEngine;
			m_graphicsEngine = nullptr;
		}
	}
	void TkEngine::Init(HWND hwnd, const SInitParam& initParam)
	{
		//�O���t�B�b�N�G���W���̏������B
		m_graphicsEngine = new CGraphicsEngine();
		m_graphicsEngine->Init(hwnd, initParam);
		//�����G���W���̏������B
		m_physicsWorld.Init();
		//�T�E���h�G���W���̏������B
		m_soundEngine.Init();
		//�Q�[���I�u�W�F�N�g�}�l�[�W���[�̏������B
		GameObjectManager().Init(initParam.gameObjectPrioMax);
	}
	void TkEngine::GameUpdate()
	{

		BeginFrame();

		//�T�E���h�G���W���̍X�V�B
		m_soundEngine.Update();
		//	�����G���W���̍X�V�B
		m_physicsWorld.Update(GameTime().GetFrameDeltaTime());
		//�O���t�B�b�N�G���W���̍X�V�B
		m_graphicsEngine->Update();

		GameObjectManager().ExecuteFromGameThread();

		EndFrame();
	}
	void TkEngine::BeginFrame()
	{
		m_sw.Start();

		for (auto& pad : m_pad) {
			pad.BeginFrame();
			pad.Update();
		}

	}
	void TkEngine::EndFrame()
	{
		m_sw.Stop();

		//GameSleep();

		m_gameTime.PushFrameDeltaTime(static_cast<float>(m_sw.GetElapsed()));
	}
	void TkEngine::GameSleep()
	{
		const double MIN_FRAME_TIME = 1.0 / 60.0;
		double currentTime = m_sw.GetElapsed();
		if (currentTime < MIN_FRAME_TIME)
		{
			//���点�鎞��(�~���b)
			DWORD sleepTime = static_cast<DWORD>((MIN_FRAME_TIME - currentTime) * 1000);

			Sleep(sleepTime);   //���点��B

			//fps�v���̂��߂ɂ�����x�o�ߎ��Ԃ�}��B
			m_sw.Stop();
		}
	}
}