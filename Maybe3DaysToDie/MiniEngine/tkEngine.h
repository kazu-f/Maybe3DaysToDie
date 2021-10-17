#pragma once

#include "util/Stopwatch.h"
#include "EngineStruct.h"

namespace Engine {

	class CGraphicsEngine;
	class CPhysicsWorld;
	class CSoundEngine;

	class TkEngine : Noncopyable {
	private:
		/// <summary>
		/// �R���X�g���N�^�B
		/// </summary>
		TkEngine();
		/// <summary>
		/// �f�X�g���N�^�B
		/// </summary>
		~TkEngine();
	public:
		/// <summary>
		/// �C���X�^���X���쐬����B
		/// </summary>
		static void CreateInstance()
		{
			ENGINE_ASSERT(m_instance == nullptr,
				"�Q�[���G���W���������쐬����悤�Ƃ��Ă��܂��B");
			if (m_instance == nullptr)
			{
				m_instance = new TkEngine();
			}
		}
		/// <summary>
		/// ��������B
		/// </summary>
		void Release();
		/// <summary>
		/// �Q�[���̏����B
		/// </summary>
		void GameUpdate();
		/// <summary>
		/// �t���[���̊J�n���ɌĂ΂�鏈���B
		/// </summary>
		void BeginFrame();
		/// <summary>
		/// �t���[���̏I�����ɌĂ΂�鏈���B
		/// </summary>
		void EndFrame();
		/// <summary>
		/// �Q�[���G���W���̏������B
		/// </summary>
		void Init(HWND hwnd, const SInitParam& initParam);
		//�C���X�^���X���擾����B
		static TkEngine& Instance()
		{
			return *m_instance;
		}
	public:		//Get�֐��n��
		//�Q�[���^�C���B
		const CGameTime& GetGameTime()
		{
			return m_gameTime;
		}
		//�O���t�B�b�N�G���W���B
		CGraphicsEngine* GetGraphicsEngine()
		{
			return m_graphicsEngine;
		}
		/// <summary>
		/// ���\�[�X�G���W�����擾�B
		/// </summary>
		CResourceEngine& GetResourceEngine()
		{
			return m_resourceEngine;
		}
		//�������[���h�B
		CPhysicsWorld& GetPhyshicsWorld()
		{
			return m_physicsWorld;
		}
		//�T�E���h�G���W���B
		CSoundEngine& GetSoundEngine()
		{
			return m_soundEngine;
		}
		//�p�b�h�̎擾�B
		GamePad& GetPad(int padNo)
		{
			ENGINE_ASSERT(
				padNo < GamePad::CONNECT_PAD_MAX
				|| padNo >= 0
				, "�p�b�h�ԍ����͈͊O�ɂȂ��Ă��܂��B"
			);
			return m_pad[padNo];
		}
	private:
		void GameSleep();

	private:
		CGraphicsEngine* m_graphicsEngine = nullptr;		//�O���t�B�b�N�G���W���B
		CResourceEngine m_resourceEngine;				//���\�[�X�G���W���B
		CPhysicsWorld m_physicsWorld;					//�������[���h�B
		CSoundEngine m_soundEngine;						//�T�E���h�G���W���B
		GamePad m_pad[GamePad::CONNECT_PAD_MAX];		//�Q�[���p�b�h�B
		CGameTime			m_gameTime;					//�Q�[���^�C���B
	private:
		static TkEngine* m_instance;			//�C���X�^���X�B
	public:
		Stopwatch			m_sw;						//�^�C�}�[�N���X�B
	};

	/// <summary>
	/// �G���W�����擾�B
	/// </summary>
	static inline TkEngine& GameEngine()
	{
		return TkEngine::Instance();
	}
	/// <summary>
	/// �Q�[���^�C�����擾�B
	/// </summary>
	static inline const CGameTime& GameTime()
	{
		return GameEngine().GetGameTime();
	}
	/// <summary>
	/// �p�b�h���擾�B
	/// </summary>
	static inline const GamePad& Pad(int padNo)
	{
		return GameEngine().GetPad(padNo);
	}
	/// <summary>
	/// �O���t�B�b�N�G���W�����擾�B
	/// </summary>
	static inline CGraphicsEngine* GraphicsEngine()
	{
		return GameEngine().GetGraphicsEngine();
	}
	/// <summary>
	/// ���C���J�������擾�B
	/// </summary>
	static inline Camera& MainCamera()
	{
		return GraphicsEngine()->GetMainCamera();
	}
	/// <summary>
	/// 2D�J�������擾�B
	/// </summary>
	static inline Camera& MainCamera2D()
	{
		return GraphicsEngine()->Get2DCamera();
	}

	/// <summary>
	/// ���\�[�X�G���W�����擾�B
	/// </summary>
	static inline CResourceEngine& ResourceEngine()
	{
		return GameEngine().GetResourceEngine();
	}
	/// <summary>
	/// �������[���h���擾�B
	/// </summary>
	static inline CPhysicsWorld& PhysicsWorld()
	{
		return GameEngine().GetPhyshicsWorld();
	}
	/// <summary>
	/// �T�E���h�G���W�����擾�B
	/// </summary>
	static inline CSoundEngine& SoundEngine()
	{
		return GameEngine().GetSoundEngine();
	}
}