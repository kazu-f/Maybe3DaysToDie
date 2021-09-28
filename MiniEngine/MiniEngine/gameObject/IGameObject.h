#pragma once
/// <summary>
/// �Q�[���I�u�W�F�N�g�C���^�[�t�F�[�X�B
/// </summary>

namespace Engine {
	class CGameObjectManager;					//�Q�[���I�u�W�F�N�g�}�l�[�W���[�B
	typedef unsigned char  GameObjectPrio;		//���s�D��x�B

	/// <summary>
	/// �Q�[���I�u�W�F�N�g�B
	/// </summary>
	class IGameObject : Noncopyable
	{
	public:
		using IGameObjectIsBase = IGameObject;
		IGameObject() :
			m_priority(0),
			m_isStart(false),
			m_isDead(false),
			m_isNewFromGameObjectManager(false)
		{
		}
		virtual ~IGameObject()		//���z�����Ȃ��Ɣh���N���X�̃f�X�g���N�^���Ă΂�Ȃ�
		{
		}
	public:		//�C�x���g���X�i�[�̃p�����[�^
		/// <summary>
		/// �C�x���g
		/// </summary>
		enum EnEvent {
			enEvent_Undef,			//����`�C�x���g�B
			enEvent_Destroy,		//�C���X�^���X���j�������B
			enBaseClassEventNum,	//���N���X�Œ�`����Ă���C�x���g�̐��B
			enEvent_User,			//����ȍ~�Ƀ��[�U�[��`�C�x���g���쐬�B

		};

		/// <summary>
		/// �C�x���g�������̃f�[�^�B
		/// </summary>
		struct SEventParam {
			EnEvent eEvent = enEvent_Undef;		//�������Ă���C�x���g�B
			IGameObject* gameObject = nullptr;	//�C�x���g��ʒm���Ă���Q�[���I�u�W�F�N�g�̃C���X�^���X�B
		};

		/// <summary>
		/// �C�x���g���X�i�[�B
		/// </summary>
		typedef std::function<void(SEventParam& eventParam)> EventListener;

	public:	//�������A�X�V�����ȂǁB
		/// <summary>
		/// �C���X�^���X���������ꂽ����ɌĂяo�����֐��B
		/// </summary>
		/// <remarks> �R���X�g���N�^���Ăяo���ꂽ����ɌĂяo�����B </remarks>
		virtual void Awake() {}
		/// <summary>
		/// Update�̒��O�ŌĂ΂��J�n�����B
		/// </summary>
		/// <remarks>
		/// ���̊֐���ture��Ԃ��Ə��������Ɣ��f����A
		/// Update�֐����Ă΂ꂾ���Btrue��Ԃ��Ƃ���ȍ~Start�֐��͌Ă΂�Ȃ��B
		/// �������Ɏ��Ԃ�������ꍇ�Ȃǂ�false��Ԃ��āA�������X�e�b�v(?)���g���ēK�؂ȏ�����������B
		/// ��������������B
		/// </returns>
		virtual bool Start() { return true; }
		/// <summary>
		/// Update�֐������s�����O�ɌĂ΂��X�V�֐��B
		/// </summary>
		virtual void PreUpdate() {}
		/// <summary>
		/// �X�V�����B
		/// </summary>
		virtual void Update() {}
		/// <summary>
		/// Update�֐������s���ꂽ��ŌĂ΂��X�V�֐��B
		/// </summary>
		virtual void PostUpdate() {}
	public:		//�`��֌W�̏����B
		/// <summary>
		/// �V���h�E�}�b�v�ւ̃����_�����O�p�X����Ă΂��`�揈���B
		/// </summary>
		virtual void PreRender(RenderContext& rc)
		{
			(void)rc;
		}
		/// <summary>
		/// �t�H���[�h�����_�����O�B
		/// </summary>
		/// <remarks>
		/// ����ȃV�F�[�f�B���O���s�����̂������_�����O����B
		/// �ʏ�̃����_�����O�ɂ͕����x�[�X�V�F�[�_�[���g�p����Ă���H
		/// </remarks>
		virtual void ForwardRender(RenderContext& rc)
		{
			(void)rc;
		}
		/// <summary>
		/// �|�X�g�����_�����O�B
		/// </summary>
		/// <remarks>
		/// �|�X�g�G�t�F�N�g�̌�Ŏ��s�����B�|�X�g�G�t�F�N�g�̉e�����󂯂����Ȃ��`�敨�������_�����O����B
		/// </remarks>
		virtual void PostRender(RenderContext& rc)
		{
			(void)rc;
		}

		/// <summary>
		/// �폜�����Ƃ��ɌĂ΂��B
		/// </summary>
		/// <remarks>�f�X�g���N�^���O�Ɏ��s�����B</remarks>
		virtual void OnDestroy() {}
		/// <summary>
		/// ���s�D��x���擾�B
		/// </summary>
		/// <returns>���s�D��x�B</returns>
		GameObjectPrio GetPriority()const
		{
			return m_priority;
		}

	public:		//Set��Get�֌W�B
		/// <summary>
		/// ���S�t���O�𗧂Ă�B
		/// </summary>
		/// <remarks>���̊֐��̓G���W���̊O����͎��s���Ȃ��B</remarks>
		void SetDeadMark()
		{
			m_isDead = true;
		}
		/// <summary>
		/// ���S����B
		/// </summary>
		bool IsDead()const
		{
			return m_isDead;
		}
		/// <summary>
		/// Start�֐��������������H
		/// </summary>
		virtual bool IsStart()const
		{
			return m_isStart;
		}
		/// <summary>
		/// �A�N�e�B�u���ǂ����B
		/// </summary>
		bool IsActive()const
		{
			return m_isActive;
		}
		/// <summary>
		/// �A�N�e�B�u�t���O��ݒ�B
		/// </summary>
		void SetActiveFlag(bool flag)
		{
			m_isActive = flag;
		}
		/// <summary>
		/// �^�O��ݒ�B
		/// </summary>
		void SetTags(unsigned int tags)
		{
			m_tags = tags;
		}
		/// <summary>
		/// �^�O���擾�B
		/// </summary>
		unsigned int GetTags()const
		{
			return m_tags;
		}
		/// <summary>
		/// GameObjectManajer�œo�^��������ݒ�B
		/// </summary>
		void SetMarkNewFromGameObjectManager()
		{
			m_isNewFromGameObjectManager = true;
		}
		/// <summary>
		/// GameObjectManajer�œo�^�������H
		/// </summary>
		bool IsNewFromGameObjectManager() const
		{
			return m_isNewFromGameObjectManager;
		}

	public:		//�C�x���g���X�i�[�̏����B
		/// <summary>
		/// ���X�i�[�C�x���g��o�^�B
		/// </summary>
		/// <param name="listener">�C�x���g���X�i�[�B</param>
		void AddEventListener(EventListener listener)
		{
			m_eventListeners.push_back(listener);
		}
#if 0	//���ʂɎg���Ȃ���ł��������
		/// <summary>
		/// �C�x���g���X�i�[��j���B
		/// </summary>
		/// <param name="listener">�j������C�x���g���X�i�[�B</param>
		void RemoveEventListener(EventListener listener)
		{
			auto it = std::remove_if(
				m_eventListeners.begin(),
				m_eventListeners.end(),
				[&](EventListener& l) {return l == listener; }
			);

			m_eventListeners.erase(it, m_eventListeners.end());
		}
#endif // 0

	public: //�����̃��b�v�B
		void StartWrapper()
		{
			if (m_isActive && !m_isStart && !m_isDead && !m_isRegistDeadList) {
				if (Start()) {
					//�����������B
					m_isStart = true;
				}
			}
		}
		void PreUpdateWrapper()
		{
			if (m_isActive && m_isStart && !m_isDead && !m_isRegistDeadList) {
				PreUpdate();
			}
		}
		void UpdateWrapper()
		{
			if (m_isActive && m_isStart && !m_isDead && !m_isRegistDeadList) {
				Update();
			}
		}
		void PostUpdateWrapper()
		{
			if (m_isActive && m_isStart && !m_isDead && !m_isRegistDeadList) {
				PostUpdate();
			}
		}
		void OnDestroyWrapper()
		{
			SEventParam param;
			param.eEvent = enEvent_Destroy;
			param.gameObject = this;
			//�f�X�g���C�C�x���g�����X�i�[�ɒʒm����B
			for (auto& listener : m_eventListeners) {
				listener(param);
			}

			OnDestroy();
		}
		void PreRenderWrapper(RenderContext& rc)
		{
			if (m_isActive && m_isStart && !m_isDead && !m_isRegistDeadList) {
				PreRender(rc);
			}
		}
		void ForwardRenderWrapper(RenderContext& rc)
		{
			if (m_isActive && m_isStart && !m_isDead && !m_isRegistDeadList) {
				ForwardRender(rc);
			}
		}
		void PostRenderWrapper(RenderContext& rc)
		{
			if (m_isActive && m_isStart && !m_isDead && !m_isRegistDeadList) {
				PostRender(rc);
			}
		}

		friend class CGameObjectManager;
	protected:
		GameObjectPrio m_priority;			//!<���s�D��x�B
		bool m_isStart;						//!<Start�̊J�n�t���O�B
		bool m_isDead;						//!<���S�t���O�B
		bool m_isRegistDeadList = false;	//!<���S���X�g�ɐς܂�Ă���B
		bool m_isNewFromGameObjectManager;	//|<GameObjectManager��new���ꂽ�B
		bool m_isRegist = false;			//!<GameObjectManajer�ɓo�^����Ă���H
		bool m_isActive = true;			//!<�A�N�e�B�u�t���O�B
		unsigned int m_tags = 0;			//!<�^�O�B
		unsigned int m_nameKey = 0;			//!<���O�L�[�B
		std::list<EventListener> m_eventListeners;		//!<�C�x���g���X�i�[�B
	};	//!<class IGameObject

}	//!<namespace Engine

