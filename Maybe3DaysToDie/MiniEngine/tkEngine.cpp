#include "MiniEngine.h"
#include "tkEngine.h"
#include "graphics/GraphicsEngine.h"
#include "physics/PhysicsWorld.h"

namespace Engine {
	TkEngine* TkEngine::m_instance = nullptr;

	TkEngine::TkEngine()
	{
	}

	TkEngine::~TkEngine()
	{

	}
	void TkEngine::Release()
	{
		if (m_graphicsEngine) {
			delete m_graphicsEngine;
			m_graphicsEngine = nullptr;
		}
		CGameObjectManager::DeleteInstance();
		if (m_instance)
		{
			delete m_instance;
			m_instance = nullptr;
		}
	}
	void TkEngine::Init(HWND hwnd, const SInitParam& initParam)
	{
		//グラフィックエンジンの初期化。
		m_graphicsEngine = new CGraphicsEngine();
		m_graphicsEngine->Init(hwnd, initParam);
		//物理エンジンの初期化。
		m_physicsWorld.Init();
		//サウンドエンジンの初期化。
		m_soundEngine.Init();
		//キーボード入力初期化。
		m_inputKeyCode.Init();
		//ゲームオブジェクトマネージャーの初期化。
		CGameObjectManager::CreateInstance(initParam.gameObjectPrioMax);

	}
	void TkEngine::GameUpdate()
	{

		BeginFrame();

		//サウンドエンジンの更新。
		m_soundEngine.Update();
		//	物理エンジンの更新。
		m_physicsWorld.Update(GameTime().GetFrameDeltaTime());
		//グラフィックエンジンの更新。
		m_graphicsEngine->Update();
		//キーボード入力更新。
		m_inputKeyCode.Update();

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
		MauseInfo::GetInstance()->MauseMoveUpdate();
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
			//眠らせる時間(ミリ秒)
			DWORD sleepTime = static_cast<DWORD>((MIN_FRAME_TIME - currentTime) * 1000);

			Sleep(sleepTime);   //眠らせる。

			//fps計測のためにもう一度経過時間を図る。
			m_sw.Stop();
		}
	}
}