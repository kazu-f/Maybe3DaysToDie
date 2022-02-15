#pragma once

/// <summary>
/// �A�j���[�V�����B
/// </summary>

#include "AnimationClip.h"
#include "AnimationPlayController.h"

namespace Engine {
	class Skeleton;
	using AnimationEventListener = std::function<void(const wchar_t* clipname, const wchar_t* eventName)>;

	class CAnimation : Noncopyable
	{
	public:
		CAnimation();
		~CAnimation();
		/// <summary>
		/// �������ς݂����肷��B
		/// </summary>
		/// <returns>true�ŏ������ς݁B</returns>
		bool IsInited()const
		{
			return m_isInited;
		}
		/// <summary>
		/// �A�j���[�V�����̏����������B
		/// </summary>
		/// <param name="skinModel">�A�j���[�V���������郂�f���B</param>
		/// <param name="animClipList">�A�j���[�V�����N���b�v�̃��X�g�B</param>
		/// <param name="animClipNum">�A�j���[�V�����N���b�v�̐��B</param>
		void Init(Skeleton & skeleton, const std::vector<std::unique_ptr<CAnimationClip >>& animClips);
		/// <summary>
		/// �A�j���[�V�����̍Đ��B
		/// </summary>
		/// <param name="clipNo">�A�j���[�V�����N���b�v�ԍ��B</param>
		/// <param name="interpolateTime">�⊮���ԁB</param>
		void Play(int clipNo, float interpolateTime = 0.0f)
		{
			if (clipNo < m_animationClips.size()) {
				PlayCommon(m_animationClips[clipNo], interpolateTime);
			}
		}
		/// <summary>
		/// �A�j���[�V�����N���b�v�̃��[�v�t���O��ݒ肷��B
		/// </summary>
		/// <param name="clipName">�A�j���[�V�����N���b�v�̖��O</param>
		/// <param name="flag">�t���O</param>
		void SetAnimationClipLoopFlag(const wchar_t* clipName, bool flag)
		{
			auto it = std::find_if(
				m_animationClips.begin(),
				m_animationClips.end(),
				[clipName](auto & clip) { return clip->GetName() == clipName; }
			);
			if (it == m_animationClips.end())
			{
				//������Ȃ������B
				return;
			}
			(*it)->SetLoopFlag(flag);
		}
		/// <summary>
		/// �A�j���[�V�����̍Đ������H
		/// </summary>
		/// <returns></returns>
		bool IsPlaying() const
		{
			int lastIndex = GetLastAnimationControllerIndex();
			return m_animationPlayController[lastIndex].IsPlaying();
		}

		float GetCurrentAnimTime()const
		{
			return m_animationPlayController[GetLastAnimationControllerIndex()].GetCurrentAnimTime();
		}
		/// <summary>
		/// �A�j���[�V������i�߂�B
		/// </summary>
		/// <remarks>
		/// �G���W�������Ŏg�p�����֐��B
		/// �O������͎g�p���Ȃ��I
		/// </remarks>
		/// <param name="deltaTime">�A�j���[�V������i�߂鎞��(s)</param>
		void Progress(float deltaTime);
		/// <summary>
		/// �A�j���[�V�����C�x���g���X�i�[��o�^�B
		/// </summary>
		/// <param name="eventListener">�o�^�������C�x���g���X�i�[�B</param>
		void AddAnimationEventListener(AnimationEventListener eventListener)
		{
			m_animationEventListeners.push_back(eventListener);
		}
		/// <summary>
		/// ���[���h��Ԃł̃t�b�g�X�e�b�v�̈ړ��ʂ��v�Z����B
		/// </summary>
		/// <remarks>
		/// �t�b�g�X�e�b�v�̈ړ��ʂ́A���f���̃��[�g����̑��Έړ��ʁB
		/// ���̂��߁A���[���h��Ԃɕϊ�����̂ɕ��s�ړ��ʂ͕s�v�B
		/// ���f���̉�]�Ɗg�嗦�̂ݎw�肷��B
		/// </remarks>
		/// <param name="rotation"></param>
		/// <param name="scale"></param>
		/// <returns></returns>
		Vector3 CalsFootstepDeltaInWorldSpace(Quaternion rotation, Vector3 scale)const;
	private:
		/// <summary>
		/// �A�j���[�V�����̍Đ�
		/// </summary>
		/// <param name="nectClip"></param>
		/// <param name="interpolateTime"></param>
		void PlayCommon(CAnimationClip * nextClip, float interpolateTime)
		{
			if (nextClip->IsLoaded() == false)
			{
				//�A�j���[�V�����N���b�v�����[�h����Ă��Ȃ��B
				MessageBoxA(NULL, "�A�j���[�V�����N���b�v�����[�h����Ă��Ȃ��B", "Warning!!", MB_OK);
				return;
			}
			int index = GetLastAnimationControllerIndex();
			
			if (m_animationPlayController[index].GetAnimClip() == nextClip) {
				//�����A�j���[�V�����������B
				return;
			}
			if (interpolateTime == 0.0f) {
				//�⊮�����B
				m_numAnimationPlayController = 1;
			}
			else {
				//�⊮����B
				m_numAnimationPlayController++;
			}
			index = GetLastAnimationControllerIndex();
			m_animationPlayController[index].ChangeAnimationClip(nextClip);
			m_animationPlayController[index].SetInterpolateTime(interpolateTime);
			m_interpolateTime = 0.0f;				//�⊮���Ԃ�0��
			m_interpolateTimeEnd = interpolateTime;	//�⊮�I�����Ԃ�ݒ�B

		}
		/// <summary>
		/// ���[�J���|�[�Y�̍X�V�B
		/// </summary>
		/// <param name="deltaTime">�A�j���[�V������i�߂鎞��(s)</param>
		void UpdateLocalPose(float deltaTime);
		/// <summary>
		/// �O���[�o���|�[�Y�̍X�V�B
		/// </summary>
		void UpdateGlobalPose();
	private:
		/// <summary>
		/// �ŏI�|�[�Y�ɂȂ�A�j���[�V�����̃����O�o�b�t�@��ł̃C���f�b�N�X���擾�B
		/// </summary>
		int GetLastAnimationControllerIndex()const
		{
			return GetAnimationControllerIndex(m_startAnimationPlayController, m_numAnimationPlayController - 1);
		}
		/// <summary>
		/// �A�j���[�V�����R���g���[���̃����O�o�b�t�@��ł̃C���f�b�N�X���擾�B
		/// </summary>
		/// <param name="startIndex">�J�n�C���f�b�N�X�B</param>
		/// <param name="localIndex">���[�J���C���f�b�N�X�B</param>
		int GetAnimationControllerIndex(int startIndex, int localIndex)const
		{
			return (startIndex + localIndex) % ANIMATION_PLAY_CONTROLLER_NUM;
		}

	private:
		static const int ANIMATION_PLAY_CONTROLLER_NUM = 32;	//�A�j���[�V�����R���g���[���̐��B
		std::vector<CAnimationClip*>	m_animationClips;		//�A�j���[�V�����N���b�v�̔z��B
		Skeleton* m_skeleton = nullptr;							//�A�j���[�V������K�p����X�P���g���B
		CAnimationPlayController	m_animationPlayController[ANIMATION_PLAY_CONTROLLER_NUM];		//�A�j���[�V�����v���C�R���g���[���B
		int m_numAnimationPlayController = 0;					//���ݎg�p���̃A�j���[�V�����Đ��R���g���[���̐��B
		int m_startAnimationPlayController = 0;					//�A�j���[�V�����R���g���[���̊J�n�C���f�b�N�X�B
		float m_interpolateTime = 0.0f;							//�⊮���ԁB
		float m_interpolateTimeEnd = 0.0f;						//�⊮�I�����ԁB�H
		bool m_isInterpolate = false;							//�⊮�����H
		std::vector<AnimationEventListener> m_animationEventListeners;	//�A�j���[�V�����̃C�x���g���X�i�[�B
		Vector3 m_footstepDeltaValue = Vector3::Zero;			//footstep�{�[���̈ړ��ʁB			//�⊮�����ǂ����B
		float m_deltaTimeOnUpdate = 0.0f;						//Update�֐������s�����Ƃ��̃f���^�^�C���B
		bool m_isInited = false;					//���[�h�ς݂��ǂ����B
	};
	////////////CAnimationClass

}