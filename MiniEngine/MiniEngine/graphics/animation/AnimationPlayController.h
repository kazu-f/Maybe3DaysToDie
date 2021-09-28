#pragma once

/// <summary>
/// �A�j���[�V�����v���C�R���g���[���[�B
/// </summary>

namespace Engine {
	class Skeleton;
	class CAnimationClip;
	class CAnimation;

	/// <summary>
	/// �A�j���[�V�����̍Đ��R���g���[���B
	/// </summary>
	/// <remarks>
	/// ��̃A�j���[�V�����N���b�v�ɑ΂��ăA�j���[�V������i�߂āA���[�J���|�[�Y���v�Z����B
	/// </remarks>

	class CAnimationPlayController : Noncopyable
	{
	public:
		//�R���X�g���N�^�B
		CAnimationPlayController()
		{
		}
		//�f�X�g���N�^�B
		~CAnimationPlayController()
		{
		}
		/// <summary>
		/// �����������B
		/// </summary>
		/// <param name="skeleton">�X�P���g���f�[�^�̃A�h���X</param>
		/// <param name="footStepBoneNo">footstep�{�[���̔ԍ�</param>
		void Init(Skeleton* skeleton, int footStepBoneNo);
		/// <summary>
		/// �A�j���[�V�����N���b�v�̕ύX�B
		/// </summary>
		/// <param name="clip">�ύX��̃N���b�v</param>
		void ChangeAnimationClip(CAnimationClip* clip)
		{
			m_animationClip = clip;
			m_currentKeyFrameNo = 0;
			m_time = 0.0f;
			m_isPlaying = true;
			m_footstepPos = Vector3::Zero;
			m_footstepDeltaValue = Vector3::Zero;
			//�A�j���[�V�����C�x���g�̔����t���O��S��false�ɂ���B
			auto& animEventArray = m_animationClip->GetAnimationEvent();
			for (auto i = 0; i < m_animationClip->GetNumAnimationEvent(); i++) {
				animEventArray[i].SetInvokedFlag(false);
			}
		}
		/// <summary>
		/// �⊮���Ԃ̐ݒ肩�ȁB
		/// </summary>
		void SetInterpolateTime(float interpolateTime)
		{
			if (interpolateTime < 0.0f)
			{
				MessageBoxA(NULL, "�A�j���[�V�����̕⊮���Ԃ��}�C�i�X�̒l�I", "Warning!!", MB_OK);
			}
			m_interpolateEndTime = interpolateTime;
			m_interpolateTime = 0.0f;
		}
		/// <summary>
		/// �⊮�����擾����B
		/// </summary>
		float GetInterpolateRate()const
		{
			if (m_interpolateEndTime <= 0.0f)
			{
				return 1.0f;
			}
			return min(1.0f, m_interpolateTime / m_interpolateEndTime);
		}
		/// <summary>
		/// �A�j���[�V������i�߂�B
		/// </summary>
		/// <param name="deltaTime">�A�j���[�V������i�߂鎞�ԁB</param>
		/// <param name="animation">�A�j���[�V�����N���X�̃A�h���X�B</param>
		void Update(float deltaTime, CAnimation* animation);
		/// <summary>
		/// ���[�J���{�[���s����擾�B
		/// </summary>
		const std::vector<Matrix>& GetBoneLocalMatrix()const
		{
			return m_boneMatrix;
		}
		/// <summary>
		/// �A�j���[�V�����N���b�v�̎擾�B
		/// </summary>
		CAnimationClip* GetAnimClip()const
		{
			return m_animationClip;
		}
		/// <summary>
		/// �A�j���[�V�������Đ����H
		/// </summary>
		bool IsPlaying()const
		{
			return m_isPlaying;
		}
		/// <summary>
		/// Update�֐����Ăяo�������́Afootstep�{�[���ړ��ʂ��擾�B
		/// </summary>
		Vector3 GetFootStepDeltaValueOnUpdate()const
		{
			return m_footstepDeltaValue;
		}
	private:	//////////�N���X�����֐��B
		/// <summary>
		/// �A�j���[�V�����C�x���g���N������B
		/// </summary>
		void InvokeAnimationEvent(CAnimation* animation);
		/// <summary>
		/// ���[�v�Đ����J�n����Ƃ��̏����B
		/// </summary>
		void StartLoop();
		/// <summary>
		/// ���[�g�̃{�[����Ԃł̃{�[���s����v�Z����B
		/// </summary>
		/// <param name="bone">�v�Z���鍜</param>
		/// <param name="parentMatrix">�e�̍s��</param>
		void CalcBoneMatrixInRootBoneSpace(Bone& bone, Matrix parentMatrix);
		/// <summary>
		/// �{�[���s����A�j���[�V�����N���b�v����T���v�����O����B
		/// </summary>
		void SamplingBoneMatrixFromAnimationClip();
		/// <summary>
		/// ���[�g�{�[����Ԃł̍s����v�Z����B�����Ȃ�Ver
		/// </summary>
		void CalcBoneMatrixInRootBoneSpace();
		/// <summary>
		/// footstep�{�[���̕ω��ʂ��T���v�����O����B
		/// </summary>
		void SamplingDataValueFootstepBone();
		/// <summary>
		/// footstep�{�[���̍��W��S�̂̍����猸�Z����B
		/// </summary>
		void SubtractFootstepBonePosFromAllBone();
		/// <summary>
		/// �L�[�t���[����i�߂�B
		/// </summary>
		void ProgressKeyframeNo(float deltaTime);

	private:
		CAnimationClip* m_animationClip = nullptr;		//�A�j���[�V�����N���b�v�B
		int m_currentKeyFrameNoLastFrame = 0;			//��t���[���O�̃L�[�t���[���ԍ��B
		int m_currentKeyFrameNo = 0;					//���ݍĐ����̃L�[�t���[���ԍ��B
		float m_time = 0.0f;								//�Ȃ񂩂̎��ԁH�Ȃ񂾂�H
		std::vector<Matrix>	m_boneMatrix;				//���̃R���g���[���ōĐ����̃A�j���[�V�����̃{�[���s��B
		float m_interpolateTime = 0.0f;					//�⊮���ԁB
		float m_interpolateEndTime = 0.0f;				//�⊮�I�����ԁB
		bool m_isPlaying = false;						//�Đ������H
		Skeleton* m_skeleton = nullptr;					//�X�P���g���f�[�^�B
		Vector3 m_footstepDeltaValue = Vector3::Zero;	//�t�b�g�X�e�b�v�̈ړ��x�N�g���B
		Vector3 m_footstepPos = Vector3::Zero;			//�t�b�g�X�e�b�v�{�[���̍��W�B
		int m_footstepBoneNo = -1;						//�t�b�g�X�e�b�v�̃{�[���ԍ��B
	};
	/////////AnimationPlayController

}