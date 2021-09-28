#pragma once
/// <summary>
/// �Q�[���I�u�W�F�N�g�}�l�[�W���[�N���X�B
/// </summary>

#include "IGameObject.h"
#include "util/Util.h"

namespace Engine {
	class CGameObjectManager : Noncopyable
	{
	private:
		CGameObjectManager() :
			m_gameObjectPriorityMax(0)
		{
		}
		~CGameObjectManager()
		{
		}
		/// <summary>
		/// �Q�[���I�u�W�F�N�g�̖��O�L�[���쐬�B
		/// </summary>
		static unsigned int MakeGameObjectNameKey(const char* objectName)
		{
			static const unsigned int defaultNameKey = Util::MakeHash("Undefined");		//�f�t�H���g�̖��O�L�[�B
			unsigned int hash;
			if (objectName == nullptr) {
				hash = defaultNameKey;
			}
			else {
				hash = Util::MakeHash(objectName);
			}
			return hash;
		}
	public:		//�}�l�[�W���[�̊O������Ăяo�������B
		/// <summary>
		/// �C���X�^���X�̎擾�B
		/// </summary>
		static CGameObjectManager&Instance()
		{
			static CGameObjectManager instance;
			return instance;
		}
		//�}�l�[�W���[�̍X�V�����B
		void ExecuteFromGameThread();

		/// <summary>
		/// �������B
		/// </summary>
		/// <param name="gameObjectPrioMax">�Q�[���I�u�W�F�N�g�̗D��x�̍ő�l�B(255�܂�)</param>
		void Init(int gameObjectPrioMax);

	public:		//�Q�[���I�u�W�F�N�g�̒ǉ��A�폜�����B

		void AddGameObject(GameObjectPrio prio, IGameObject* go, const char* objectName = nullptr)
		{
			(void)objectName;
			if (!go->m_isRegist) {
				//go->Awake();		//����ĂȂ������B
				unsigned int hash = MakeGameObjectNameKey(objectName);
				m_gameObjectListArray.at(prio).push_back(go);
				go->m_isRegist = true;		//�o�^�ς݁B
				go->m_priority = prio;		//�D��x�B
				go->m_isStart = false;		//�X�^�[�g�֐��͑����Ă��Ȃ��B
				go->m_nameKey = hash;		//���O�L�[�B
				if (go->m_isDead) {
					//���S�t���O�������Ă���B
					//�폜���X�g�ɓ����Ă����炻�����珜���H
					go->m_isDead = false;
				}
			}
		}
		/// <summary>
		/// �Q�[���I�u�W�F�N�g�̍쐬�B
		/// </summary>
		/// <param name="prio">���s�D�揇�ʁB</param>
		/// <param name="objectName">�I�u�W�F�N�g���B</param>
		/// <returns>�쐬�����Q�[���I�u�W�F�N�g�̃|�C���^�B</returns>
		template<class T>
		T* NewGameObject(GameObjectPrio prio, const char* objectName)
		{
			(void*)objectName;
			if (prio >= m_gameObjectPriorityMax){	//�D��x�̍ő吔���傫���B
#ifdef _DEBUG
				MessageBoxA(NULL, "�Q�[���I�u�W�F�N�g�̗D��x���傫������B", "Warning!!", MB_OK);
				std::abort();
#endif // DEBUG
			}
			T* newObject = new T();				//�C���X�^���X�̍쐬�B
			//newObject->Awake();				//����ĂȂ��z�B
			newObject->SetMarkNewFromGameObjectManager();			//NewGameObject�ō��ꂽ�B
			m_gameObjectListArray.at(prio).push_back(newObject);	//���X�g�ɒǉ��B
			unsigned int hash = MakeGameObjectNameKey(objectName);	//���O�L�[�̍쐬�B
			newObject->m_isRegist = true;		//���X�g�ɓo�^����Ă���B
			newObject->m_priority = prio;		//�D��x�̐ݒ�B
			newObject->m_nameKey = hash;		//���O�L�[�̐ݒ�B

			return newObject;
		}

		/// <summary>
		///	�Q�[���I�u�W�F�N�g�̍폜
		/// </summary>
		void DeleteGameObject(IGameObject* gameObject)
		{
			if (gameObject != nullptr
				&& gameObject->m_isRegist
			) {
				gameObject->SetDeadMark();		//���S�t���O�B
				gameObject->OnDestroyWrapper();	//�폜�����Ƃ��̏����B
				gameObject->m_isRegist = false;	//���X�g�̓o�^�t���O���O���B
				gameObject->m_isRegistDeadList = true;	//�폜���X�g�ɓo�^����Ă���B
				//�폜���X�g�ɓo�^����B
				m_deleteObjectArray[m_currentDeleteObjectBufferNo].at(gameObject->GetPriority()).push_back(gameObject);
				gameObject = nullptr;	//���ꂢ��H
			}
		}
		/// <summary>
		/// �Q�[���I�u�W�F�N�g�̌����B
		/// </summary>
		/// <remarks>�d�����炵���B</remarks>
		/// <param name="objectName">�I�u�W�F�N�g���B</param>
		/// <returns>���������I�u�W�F�N�g�̃|�C���^�B</returns>
		template<class T>
		T* FindGameObject(const char* objectName , bool enableError)
		{
			unsigned int nameKey = Util::MakeHash(objectName);
			for (auto goList : m_gameObjectListArray) {	//�D��x�B
				for (auto go : goList) {				//���X�g�B
					if (go->m_nameKey == nameKey) {
						//���������B
						T* p = dynamic_cast<T*>(go);
						if (p == nullptr){	//�^�ϊ��~�X�B
#ifdef _DEBUG
							MessageBoxA(NULL, "FindGameObject : �^�ϊ��Ɏ��s���܂����B", "Warning!!", MB_OK);
							throw;
#endif // DEBUG
						}
						return p;
					}
				}
			}
			//������Ȃ������B
			if (enableError == true) {
#ifdef _DEBUG
				MessageBoxA(NULL, "FindGO�֐��Ɏw�肳�ꂽ���O�̃C���X�^���X��������Ȃ������B", "Warrning!!", MB_OK);
#endif // DEBUG		
			}
			return nullptr;
		}
		/// <summary>
		/// �Q�[���I�u�W�F�N�g�̌����B
		/// </summary>
		/// <remarks>�d�����B</remarks>
		/// <param name="objectName">�I�u�W�F�N�g�̖��O�B</param>
		/// <param name="func">bool�̒l��Ԃ��֐��Bfalse��Ԃ��ƃN�G���𒆒f�B</param>
		template<class T>
		void FindGameObjects(const char* objectName, std::function<bool(T* go)>func)
		{
			unsigned int nameKey = Util::MakeHash(objectName);		//���O�L�[�̍쐬�B
			for (auto goList : m_gameObjectListArray) {
				for (auto go : goList) {
					if (go->m_nameKey == nameKey) {
						//�������O�̃Q�[���I�u�W�F�N�g���������B
						T* p = dynamic_cast<T*>(go);		//�h����ɃL���X�g�B
						if (func(p) == false) {
							//false�Ȃ�N�G�����f�B
							return;
						}
					}
				}
			}
		}
		/// <summary>
		/// �w�肵���^�O�̂����ꂩ���܂܂��Q�[���I�u�W�F�N�g���������āA���������ꍇ�w�肳�ꂽ�R�[���o�b�N�֐����Ăяo���B
		/// </summary>
		/// <param name="tags"></param>
		/// <param name="func"></param>
		void FindGameObjectsWithTag(unsigned int tags, std::function<void(IGameObject* go)> func)
		{
			for (auto& goList : m_gameObjectListArray) {
				for (auto& go : goList) {
					unsigned int goTags = go->GetTags();
					if ((goTags & tags) != 0) {
						func(go);
					}
				}
			}
		}

	private:	//�Q�[���I�u�W�F�N�g�}�l�[�W���[�̍X�V�����B
		/// <summary>
		/// �Q�[���I�u�W�F�N�g�̍폜�����s�B
		/// </summary>
		void ExecuteDeleteGameObjects();

		void Start();		//�X�^�[�g���Ăяo���B
		void PreUpdate();	//���O�X�V�B
		void Update();		//�X�V�������Ăяo���B
		void PostUpdate();	//�x���X�V�B

	public:
		/// <summary>
		/// �`��֌W�̍X�V�����̓O���t�B�b�N�G���W������Ăяo���B
		/// </summary>
		void ForwardRender(RenderContext& rc);
		void PreRender(RenderContext& rc);
		void PostRender(RenderContext& rc);

	private:
		typedef std::list<IGameObject*> GameObjectList;			//!<�Q�[���I�u�W�F�N�g*�̃��X�g�B
		std::vector<GameObjectList> m_gameObjectListArray;		//!<�D��x�t���̃Q�[���I�u�W�F�N�g���X�g�B
		std::vector<GameObjectList> m_deleteObjectArray[2];		//!<�폜����I�u�W�F�N�g�̃��X�g�B
																//!<�폜�������s���Ă���Œ���DeleteGameObject���Ă΂��\���������̂ŁA�_�u���o�b�t�@���B
		GameObjectPrio				m_gameObjectPriorityMax;	//!<�Q�[���I�u�W�F�N�g�̗D��x�̍ő吔�B
		int m_currentDeleteObjectBufferNo = 0;					//!<���݂̍폜�I�u�W�F�N�g�̃o�b�t�@�ԍ��B
		static const unsigned char	GAME_OBJECT_PRIO_MAX = 255;	//!<�Q�[���I�u�W�F�N�g�̗D��x�̍ő�l�B

	};	//!<CGameObjectManajer

	//�Q�[���I�u�W�F�N�g�}�l�[�W���[�̃C���X�^���X�擾�B
	static inline CGameObjectManager& GameObjectManager()
	{
		return CGameObjectManager::Instance();
	}
	/// <summary>
	/// �Q�[���I�u�W�F�N�g�̌����̃w���p�[�֐��B
	/// </summary>
	/// <remarks>���O�̌��������邽�ߒx���B</remarks>
	/// <param name="objectName">�Q�[���I�u�W�F�N�g�̖��O�B</param>
	/// <param name="enableErrorMassage">�G���[���b�Z�[�W��L���ɂ��邩�H</param>
	/// <returns>���������C���X�^���X�̃A�h���X�B������Ȃ��ꍇnullptr�B</returns>
	template<class T> 
	static inline T* FindGO(const char* objectName , bool enableErrorMassage = true)
	{
		return GameObjectManager().FindGameObject<T>(objectName,enableErrorMassage);
	}
	/// <summary>
	/// �Q�[���I�u�W�F�N�g�̌����̃w���p�[�֐��B
	/// </summary>
	/// <remarks>�����̃Q�[���I�u�W�F�N�g�S�Ăɑ΂��āA�N�G�����s���ꍇ�Ɏg�p����B</remarks>
	/// <param name="objectName">�Q�[���I�u�W�F�N�g�̖��O�B</param>
	/// <param name="func">
	/// <para>�Q�[���I�u�W�F�N�g�������������ɌĂ΂��R�[���o�b�N�֐��B</para>
	/// <para>false��Ԃ��ƃN�G���𒆒f����B</para>
	/// </param>
	template<class T>
	static inline void QueryGOs(const char* objectName, std::function<bool(T* go)> func) 
	{
		return GameObjectManager().FindGameObjects<T>(objectName, func);
	}
	/// <summary>
	/// �Q�[���I�u�W�F�N�g�����̃w���p�[�֐��B
	/// </summary>
	/// <param name="priority">�ݒ肵�����D��x�B</param>
	/// <param name="objctName">�Q�[���I�u�W�F�N�g�ɂ��閼�O�B</param>
	/// <param name="">��B���̈���������K�v�͂Ȃ��͂�...�H</param>
	/// <returns>���������C���X�^���X�̃A�h���X�B</returns>
	template<class T>
	static inline T* NewGO(int priority, const char* objctName = nullptr, typename T::IGameObjectIsBase* = nullptr)
	{
		return GameObjectManager().NewGameObject<T>((GameObjectPrio)priority, objctName);
	}
	/// <summary>
	/// �Q�[���I�u�W�F�N�g�폜�̃w���p�[�֐��B
	/// </summary>
	/// <param name="go">�폜����C���X�^���X�̃|�C���^�B</param>
	static inline void DeleteGO(IGameObject* go)
	{
		GameObjectManager().DeleteGameObject(go);
	}
	/// <summary>
	/// �Q�[���I�u�W�F�N�g�폜�̃w���p�[�֐��B
	/// </summary>
	/// <remarks>���O�̌��������邽�ߒx���B</remarks>
	/// <param name="objectName">�폜����Q�[���I�u�W�F�N�g�̖��O�B</param>
	static inline void DeleteGO(const char* objectName)
	{
		IGameObject* go = FindGO<IGameObject>(objectName);		//�������s���B
		GameObjectManager().DeleteGameObject(go);
	}
	/// <summary>
	/// �Q�[���I�u�W�F�N�g�𖼑O�w��ō폜�B
	/// </summary>
	/// <remarks>���O�������s���邽�ߒx���B</remarks>
	/// <param name="objectName">�폜����Q�[���I�u�W�F�N�g�̖��O�B</param>
	static inline void DeleteGOs(const char* objectName)
	{
		//�N�G�����g���đS�폜�B
		QueryGOs<IGameObject>(objectName, [](auto go) {
			DeleteGO(go);
			return true;
			}
		);
	}
	/// <summary>
	/// �Q�[���I�u�W�F�N�g�̒ǉ��̃w���p�[�֐�
	/// </summary>
	/// <param name="priority">�ǉ�����Q�[���I�u�W�F�N�g�B</param>
	/// <param name="go">�D��x�B</param>
	/// <param name="objectName">�Q�[���I�u�W�F�N�g�̖��O�B</param>
	static inline void AddGO(int priority, IGameObject* go, const char* objectName = nullptr)
	{
		GameObjectManager().AddGameObject(static_cast<GameObjectPrio>(priority), go, objectName);
	}
	/// <summary>
	/// �w�肵���^�O�̂����ꂩ���܂܂��Q�[���I�u�W�F�N�g���������āA���������ꍇ�w�肳�ꂽ�R�[���o�b�N�֐����Ăяo���B
	/// </summary>
	/// <param name="tags">�^�O</param>
	/// <param name="func">�R�[���o�b�N�֐��B</param>
	static inline void FindGameObjectsWithTag(unsigned int tags, std::function<void(IGameObject* go)> func)
	{
		GameObjectManager().FindGameObjectsWithTag(tags, func);
	}

}	//!<namespace Engine

