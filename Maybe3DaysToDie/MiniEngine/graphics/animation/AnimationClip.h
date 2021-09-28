#pragma once

#include "tkFile/TkaFile.h"

/// <summary>
/// �A�j���[�V�����N���b�v�B
/// </summary>

namespace Engine {

	/// <summary>
	/// �L�[�t���[���B
	/// </summary>
	struct KeyFrame {
		std::uint32_t boneIndex;	//�{�[���C���f�b�N�X�B
		float time;					//���ԁB
		Matrix transform;			//�g�����X�t�H�[���B
	};
	///// <summary>
	///// �ǂݍ��݂Ɏg���L�[�t���[���\���́B
	///// </summary>
	//struct KeyframeRow
	//{
	//	std::uint32_t boneIndex;	//�{�[���C���f�b�N�X�B
	//	float time;					//���ԁB
	//	Vector3 transform[4];	//�g�����X�t�H�[���B
	//};

	//�A�j���[�V�����N���b�v�̏������f�[�^�B
	struct AnimClipInitData
	{
		std::string tkaFilePath;		//tka�t�@�C���̃p�X�B
		bool isLoop = false;			//���[�v�t���O�B
	};

	/// <summary>
	/// �A�j���[�V�����C�x���g�B
	/// </summary>
	class CAnimationEvent : Noncopyable{
	public:
		/// <summary>
		/// �C�x���g�������Ԃ��擾�B
		/// </summary>
		float GetInvokeTime()const
		{
			return m_invokeTime;
		}
		/// <summary>
		/// �C�x���g���擾�B
		/// </summary>
		const wchar_t* GetEventName()const
		{
			return m_eventName.c_str();
		}
		/// <summary>
		/// �C�x���g�������Ԃ�ݒ�B
		/// </summary>
		void SetInvokeTime(float time)
		{
			m_invokeTime = time;
		}
		/// <summary>
		/// �C�x���g����ݒ�B
		/// </summary>
		void SetEventName(const wchar_t* name)
		{
			m_eventName = name;
		}
		/// <summary>
		/// �C�x���g�������ς݂�����B
		/// </summary>
		bool IsInvoked()const
		{
			return m_isInvoke;
		}
		/// <summary>
		/// �C�x���g�������ς݂̃t���O��ݒ肷��B
		/// </summary>
		void SetInvokedFlag(bool flag)
		{
			m_isInvoke = flag;
		}

	private:
		bool m_isInvoke = false;	//�C�x���g�����ς݁H
		float m_invokeTime = 0.0f;	//�C�x���g�������ԁB
		std::wstring m_eventName;	//�C�x���g���B
	};
	

	class CAnimationClip:Noncopyable
	{
	public:
		typedef std::vector<KeyFrame*>		keyFramePtrList;

		CAnimationClip() {};
		~CAnimationClip();
		/// <summary>
		/// �A�j���[�V�����N���b�v�𓯊����[�h�B
		/// </summary>
		/// <param name="filePath">�t�@�C���p�X�B</param>
		void Load(const char* filePath);
		/// <summary>
		/// �ǂݍ��݂��I����Ă��邩����B
		/// </summary>
		/// <returns></returns>
		bool IsLoaded()const
		{
			return m_isLoaded;
		}
		/// <summary>
		/// �L�[�t���[���ƃA�j���[�V�����C�x���g���\�z����B
		/// </summary>
		/// <remarks>
		/// ���[�h���I������Ƃ��ɌĂяo���B
		/// </remarks>
		void BuildKeyFramesAndAnimationEvents();
		//���[�v���邩�H
		bool IsLoop()const
		{
			return m_isLoop;
		}
		//���[�v�t���O��ݒ肷��B
		void SetLoopFlag(bool flag)
		{
			m_isLoop = flag;
		}
		//�{�[�����̃L�[�t���[���̃��X�g���擾�B
		const std::vector<keyFramePtrList>& GetKeyFramePtrListArray()const
		{
			return m_keyFramePtrListArray;
		}
		const keyFramePtrList& GetTopBoneKeyFrameList()const
		{
			return *m_topBoneKeyFrameList;
		}
		/// <summary>
		/// �N���b�v�����擾�B
		/// </summary>
		const wchar_t* GetName()const
		{
			return m_clipName.c_str();
		}
		/// <summary>
		/// �A�j���[�V�����C�x���g���擾�B
		/// </summary>
		std::unique_ptr<CAnimationEvent[]>& GetAnimationEvent()
		{
			return m_animationEvent;
		}
		/// <summary>
		/// �A�j���[�V�����C�x���g�̐����擾�B
		/// </summary>
		int GetNumAnimationEvent()const
		{
			return m_tkaFile.GetNumAnimationEvent();
		}
	private:
		using KeyframePtr = std::unique_ptr<KeyFrame>;
		TkaFile m_tkaFile;						//tka�t�@�C���B
		std::wstring m_clipName;				//�A�j���[�V�����N���b�v�̖��O�B
		std::vector<KeyframePtr> m_keyframes;			//�S�ẴL�[�t���[���B
		std::vector<keyFramePtrList> m_keyFramePtrListArray;		//�{�[�����̃L�[�t���[���̃��X�g���Ǘ����邽�߂̔z��B
		std::unique_ptr<CAnimationEvent[]> m_animationEvent;		//�A�j���[�V�����C�x���g�B
		int m_numAnimationEvent = 0;								//�A�j���[�V�����C�x���g�̐��B
		keyFramePtrList* m_topBoneKeyFrameList = nullptr;		//���[�g�{�[���H�̃L�[�t���[�����X�g�B

		bool m_isLoaded = false;
		bool m_isLoop = false;			//���[�v�t���O�B
	};
	//////////////////////CAnimationClip
	using CAnimationClipPtr = std::unique_ptr<CAnimationClip>;
}