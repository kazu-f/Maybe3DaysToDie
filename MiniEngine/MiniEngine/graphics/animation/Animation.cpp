#include "stdafx.h"
#include "Animation.h"

namespace Engine {
	namespace {
		//DCC�c�[���ł̃A�j���[�V������ł�1�t���[���̌o�ߎ���(s)
		const float DELTA_SEC_PER_FRAME_ON_DCC_TOOL = 1.0f / 30.0f;
	}
	CAnimation::CAnimation()
	{
	}
	CAnimation::~CAnimation()
	{
	}
	void CAnimation::Init(Skeleton & skeleton, const std::vector<std::unique_ptr<CAnimationClip >>& animClips)
	{
		if (animClips.empty())
		{
			MessageBoxA(NULL, "�A�j���[�V�����N���b�v���X�g����ł��B", "abort", MB_OK);
			std::abort();	//�ُ�I���B
		}
		//�X�P���g���̃A�h���X�擾�B
		m_skeleton = &skeleton;
		//�A�j���[�V�����N���b�v�̃A�h���X�擾�����X�g�֐ςށB
		for (auto& animClip : animClips) {
			m_animationClips.push_back(animClip.get());
		}
		//////footstep�{�[���̔ԍ��𒲂ׂ�B
		int footstepBoneNo = -1;
		int numBone = m_skeleton->GetNumBones();
		for (int boneNo = 0; boneNo < numBone; boneNo++) {
			auto bone = m_skeleton->GetBone(boneNo);
			if (wcscmp(bone->GetName(), L"footstep") == 0) {
				//footstep�{�[�������������B
				footstepBoneNo = boneNo;
				break;
			}
		}
		//////�A�j���[�V�����Đ��R���g���[���̏������B
		for (auto& ctr : m_animationPlayController) {
			ctr.Init(m_skeleton, footstepBoneNo);
		}

		//0�Ԗڂ̃A�j���[�V�������Đ�����B
		Play(0);
		m_isInited = true;
	}
	/// <summary>
	/// ���[�J���|�[�Y�̍X�V�B
	/// </summary>
	void CAnimation::UpdateLocalPose(float deltaTime)
	{
		//�⊮���Ԃ��o�߂�����B
		m_interpolateTime += deltaTime;
		if (m_interpolateTime >= 1.0f) {
			//�⊮�����������B
			//���݂̍ŏI�A�j���[�V�����R���g���[���ւ̃C���f�b�N�X���J�n�C���f�b�N�X�ɂȂ�B
			m_startAnimationPlayController = GetLastAnimationControllerIndex();
			m_numAnimationPlayController = 1;
			m_interpolateTime = 1.0f;
		}
		for (int i = 0; i < m_numAnimationPlayController - 1; i++) {
			int index = GetAnimationControllerIndex(m_startAnimationPlayController, i);
			m_animationPlayController[index].Update(deltaTime, this);
		}
		//�Ō�̃|�[�Y������i�߂�B
		int lastIndex = GetLastAnimationControllerIndex();
		m_animationPlayController[lastIndex].Update(deltaTime, this);
	}
	void CAnimation::UpdateGlobalPose()
	{
		//�O���[�o���|�[�Y�v�Z�p�̃��������X�^�b�N����m�ہB
		int numBone = m_skeleton->GetNumBones();
		Quaternion* qGlobalPose = (Quaternion*)alloca(sizeof(Quaternion) * numBone);
		Vector3* vGlobalPose = (Vector3*)alloca(sizeof(Vector3) * numBone);
		Vector3* vGlobalScale = (Vector3*)alloca(sizeof(Vector3) * numBone);

		m_footstepDeltaValue = Vector3::Zero;
		//�l���������B
		for (int i = 0; i < numBone; i++)
		{
			qGlobalPose[i] = Quaternion::Identity;
			vGlobalPose[i] = Vector3::Zero;
			vGlobalScale[i] = Vector3::One;
		}
		//�O���[�o���|�[�Y���v�Z���Ă����B
		int startIndex = m_startAnimationPlayController;
		for (int i = 0; i < m_numAnimationPlayController; i++) {
			//�C���f�b�N�X�擾�B
			int index = GetAnimationControllerIndex(startIndex, i);
			//�⊮�����擾�B
			float interpolateRate = m_animationPlayController[index].GetInterpolateRate();
			//���[�J���{�[���s��̎擾�B
			const auto& localBoneMatrix = m_animationPlayController[index].GetBoneLocalMatrix();
			//footstep�̈ړ��ʂ��擾�B
			auto deltaValueFootStep = m_animationPlayController[index].GetFootStepDeltaValueOnUpdate();
			//footstep�̈ړ��ʂ̕⊮
			m_footstepDeltaValue.Lerp(interpolateRate, m_footstepDeltaValue, deltaValueFootStep);

			for (int boneNo = 0; boneNo < numBone; boneNo++){
				//���s�ړ��̕⊮�B
				Matrix m = localBoneMatrix[boneNo];
				vGlobalPose[boneNo].Lerp(
					interpolateRate,
					vGlobalPose[boneNo],
					*(Vector3*)m.m[3]
				);
				//���s�ړ��������폜
				m.m[3][0] = 0.0f;
				m.m[3][1] = 0.0f;
				m.m[3][2] = 0.0f;

				//�g�听���̕⊮�B
				Vector3 vBoneScale;
				vBoneScale.x = (*(Vector3*)m.m[0]).Length();
				vBoneScale.y = (*(Vector3*)m.m[1]).Length();
				vBoneScale.z = (*(Vector3*)m.m[2]).Length();

				vGlobalScale[boneNo].Lerp(
					interpolateRate,
					vGlobalScale[boneNo],
					vBoneScale
				);
				//�g�听���������H����̂�
				m.m[0][0] /= vBoneScale.x;
				m.m[0][1] /= vBoneScale.x;
				m.m[0][2] /= vBoneScale.x;

				m.m[1][0] /= vBoneScale.y;
				m.m[1][1] /= vBoneScale.y;
				m.m[1][2] /= vBoneScale.y;

				m.m[2][0] /= vBoneScale.z;
				m.m[2][1] /= vBoneScale.z;
				m.m[2][2] /= vBoneScale.z;

				//��]�̕⊮
				Quaternion qBone;
				qBone.SetRotation(m);
				qGlobalPose[boneNo].Slerp(interpolateRate, qGlobalPose[boneNo], qBone);
			}
		}
		//�O���[�o���|�[�Y���X�P���g���ɔ��f�����Ă����B
		for (int boneNo = 0; boneNo < numBone; boneNo++) {
			//�g��s����쐬�B
			Matrix scaleMatrix;
			scaleMatrix.MakeScaling(vGlobalScale[boneNo]);
			//��]�s����쐬�B
			Matrix rotMatrix;
			rotMatrix.MakeRotationFromQuaternion(qGlobalPose[boneNo]);
			//���s�ړ��s����쐬�B
			Matrix transMatrix;
			transMatrix.MakeTranslation(vGlobalPose[boneNo]);

			//�S�����������āA�{�[���s����쐬�B
			Matrix boneMatrix;
			boneMatrix = scaleMatrix * rotMatrix;
			boneMatrix = boneMatrix * transMatrix;

			m_skeleton->SetBoneLocalMatrix(
				boneNo,
				boneMatrix
			);

		}

		//�ŏI�A�j���[�V�����ȊO�͕⊮�������Ă����珜�����Ă����B
		int numAnimationPlayController = m_numAnimationPlayController;
		for (int i = 1; i < numAnimationPlayController; i++) {
			int index = GetAnimationControllerIndex(startIndex, i);
			if (m_animationPlayController[index].GetInterpolateRate() > 0.99999f) {
				//�⊮���I����Ă���̂ŃA�j���[�V�����̊J�n�ʒu��O�ɂ���B
				m_startAnimationPlayController = index;
				numAnimationPlayController = m_numAnimationPlayController - i;
			}
		}
		m_numAnimationPlayController = numAnimationPlayController;

	}
	Vector3 CAnimation::CalsFootstepDeltaInWorldSpace(Quaternion rotation, Vector3 scale) const
	{
		auto footstepDeltaValueInWorldSpace = m_footstepDeltaValue;

		Matrix mBias = Matrix::Identity;
		mBias.MakeRotationX(Math::PI * -0.5f);
		mBias.Apply(footstepDeltaValueInWorldSpace);

		//�t�b�g�X�e�b�v�̈ړ��ʂ��g�傷��B
		footstepDeltaValueInWorldSpace.x *= scale.x;
		footstepDeltaValueInWorldSpace.y *= scale.y;
		footstepDeltaValueInWorldSpace.y *= scale.y;
		//�t�b�g�X�e�b�v�̈ړ��ʂ��񂷁B
		rotation.Apply(footstepDeltaValueInWorldSpace);
		//�t�b�g�X�e�b�v�̈ړ��ʂ��I�C���[�ϕ�����B
		float t = m_deltaTimeOnUpdate / DELTA_SEC_PER_FRAME_ON_DCC_TOOL;
		footstepDeltaValueInWorldSpace *= t;

		return footstepDeltaValueInWorldSpace;
	}
	void CAnimation::Progress(float deltaTime)
	{
		if (m_numAnimationPlayController == 0) {
			return;
		}
		//�o�ߎ��Ԃ��L�^�B
		m_deltaTimeOnUpdate = deltaTime;

		//���[�J���|�[�Y�̍X�V���s���B
		UpdateLocalPose(deltaTime);

		//�O���[�o���|�[�Y���v�Z����B
		UpdateGlobalPose();
	}
}