#pragma once

class FootIK
{
private:
	struct SFoot {
		Bone* m_bone;		//���̃{�[��
		CCapsuleCollider m_collider;		//�{�[���̈ʒu�ɂ���R���C�_�[
	};
public:
	struct FootIKParam {
		const wchar_t* footBoneName_0 = nullptr;		//���̃{�[���̖��O�P
		const wchar_t* footBoneName_1 = nullptr;		//���̃{�[���̖��O�Q
		const wchar_t* rootBoneName = nullptr;		//IK�������n�߂郋�[�g�{�[��
		float footCapsuleColliderRadius_0 = 0.0f;		//�J�v�Z���R���C�_�[�̔��a�P
		float footCapsuleColliderRadius_1 = 0.0f;		//�J�v�Z���R���C�_�[�̔��a�Q
		float footCapsuleColliderHeight_0 = 0.0f;		//�J�v�Z���R���C�_�[�̍����P
		float footCapsuleColliderHeight_1 = 0.0f;		//�J�v�Z���R���C�_�[�̍����Q
	};

private:
	FootIK() {}
	~FootIK() {}
public:

	/// <summary>
	/// FootIK��L���ɂ���
	/// </summary>
	/// <param name="skeleton">IK��������X�P���g��</param>
	/// <param name="param">IK�ɕK�v�ȃp�����[�^</param>
	void Enable(Skeleton* skeleton,const FootIKParam& param);

	/// <summary>
	/// IK�𖳌��ɂ���
	/// </summary>
	void Disable()
	{
		m_IsEnable = false;
	}

	/// <summary>
	/// IK��������
	/// </summary>
	void ApplyIK();

private:
	/// <summary>
	/// IK�̍ŏI�ʒu���v�Z����
	/// </summary>
	bool CalcIKTargetPos(const SFoot& foot,Vector3&target);

	/// <summary>
	/// CCD_IK
	/// </summary>
	/// <param name="foot">IK�������鑫</param>
	/// <param name="target">�ڕW�n�_</param>
	void CCD_IK(const SFoot& foot, Vector3 target);

private:
	int m_RootBoneID = -1;		//���[�g�{�[����ID
	Skeleton* m_skeleton = nullptr;		//�X�P���g��
	SFoot m_foots[2];		//��
	bool m_IsEnable = false;		//IK���L�����ǂ���
};