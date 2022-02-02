#include "stdafx.h"
#include "FootIK.h"
#include "RayTest.h"

void FootIK::Enable(Skeleton* skeleton, FootIKParam& param)
{
	//�X�P���g�����Z�b�g
	m_skeleton = skeleton;
	//�L���t���O�𗧂Ă�
	m_IsEnable = true;
	//���̃{�[��1��
	int boneID = m_skeleton->FindBoneID(param.footBoneName_0);
	//�{�[���̎擾
	m_foots[0].m_bone = m_skeleton->GetBone(boneID);
	//�R���C�_�[�̍쐬
	m_foots[0].m_collider.Create(param.footCapsuleColliderRadius_0, param.footCapsuleColliderHeight_0);

	//���̃{�[��2��
	boneID = m_skeleton->FindBoneID(param.footBoneName_1);
	//�{�[���̎擾
	m_foots[1].m_bone = m_skeleton->GetBone(boneID);
	//�R���C�_�[�̍쐬
	m_foots[1].m_collider.Create(param.footCapsuleColliderRadius_1, param.footCapsuleColliderHeight_1);

	//���[�g�{�[��������
	m_RootBoneID = m_skeleton->FindBoneID(param.rootBoneName);
}

bool FootIK::CalcIKTargetPos(const SFoot& foot, Vector3& target)
{
	if (foot.m_bone->GetParentBoneNo() == -1)
	{
		//�e�����Ȃ��B
		return false;
	}
	//���[���h�s����擾
	Matrix mat = foot.m_bone->GetWorldMatrix();
	//�s�񂩂�ʒu���擾
	Vector3 pos = { mat.m[3][0],mat.m[3][1],mat.m[3][2] };

	//���C�̍쐬
	btVector3 start, end;
	//�n�_�̓R���C�_�[�̒��S
	start.setValue(pos.x, pos.y, pos.z);
	//10cm���Ɍ����ă��C���΂�
	end.setValue(
		pos.x,
		pos.y - 10.0f,
		pos.z
	);

	RayResult callback;
	PhysicsWorld().RayTest(start, end, callback);
	if (callback.isHit == false)
	{
		//�q�b�g���Ȃ�����
		return false;
	}

	//�������牺�̓��C�q�b�g�����Ƃ��̏���
	target = callback.hitColPos;
	//�����𒲂ׂ�
	Vector3 diff = target - pos;
	if (diff.LengthSq() < 0.01f)
	{
		//�߂�����Ƃ��v�Z����K�v�Ȃ��̂�false
		return false;
	}
	return true;
}

void FootIK::CCD_IK(const SFoot& foot, Vector3 target)
{
	//�e�̃{�[�����擾
	int parentID = foot.m_bone->GetParentBoneNo();
	//�s����擾
	Matrix mat = foot.m_bone->GetWorldMatrix();
	//�s�񂩂�ʒu���擾
	Vector3 pos = { mat.m[3][0],mat.m[3][1],mat.m[3][2] };
	//while (true)
	//{
	for (int i = 0; i < 5; i++) {
		while (parentID != m_RootBoneID)
		{
			//���[�g�{�[���܂Ōv�Z���J��Ԃ�
			Bone* currentBone = nullptr;
			//�v�Z����{�[�����擾
			currentBone = m_skeleton->GetBone(parentID);
			//���[���h�s����擾
			Matrix currentMat = currentBone->GetWorldMatrix();
			//�s����擾
			Vector3 currentBonePos = { currentMat.m[3][0],currentMat.m[3][1],currentMat.m[3][2] };
			//�G�t�F�N�^�[�ւ̃x�N�g��
			Vector3 ToEffecter = pos - currentBonePos;
			//�^�[�Q�b�g�ւ̃x�N�g��
			Vector3 ToTarget = target - currentBonePos;
			//���K��
			ToEffecter.Normalize();
			ToTarget.Normalize();
			//��]�������߂�
			Vector3 rotateAxis;
			rotateAxis.Cross(ToEffecter, ToTarget);
			rotateAxis.Normalize();
			//��]��␳���邽�߂̉�]�s������߂�
			float angle = acos(min(1.0f, ToEffecter.Dot(ToTarget)));
			Quaternion qRot;
			qRot.SetRotation(rotateAxis, angle);
			Matrix mAddRot;
			mAddRot.MakeRotationFromQuaternion(qRot);
			//���[���h�s��ɔ��f
			currentMat.m[3][0] = 0.0f;
			currentMat.m[3][1] = 0.0f;
			currentMat.m[3][2] = 0.0f;
			//�ǉ��̉�]��������
			currentMat = currentMat * mAddRot;
			//�|�W�V�������Z�b�g
			currentMat.m[3][0] = currentBonePos.x;
			currentMat.m[3][1] = currentBonePos.y;
			currentMat.m[3][2] = currentBonePos.z;

			//���[�J���s������߂�
			Matrix localMat;
			parentID = currentBone->GetParentBoneNo();
			if (parentID != -1)
			{
				//���[�g����Ȃ���
				Matrix ToParentSpaceMat = m_skeleton->GetBone(parentID)->GetWorldMatrix();
				//�t�s��
				ToParentSpaceMat.Inverse();
				localMat = currentMat * ToParentSpaceMat;
				currentBone->SetLocalMatrix(localMat);
			}
			//���[�g�{�[�����牺�̍��̃��[���h�s����Čv�Z����
			Skeleton::UpdateBoneWorldMatrix(*currentBone, m_skeleton->GetBone(m_RootBoneID)->GetWorldMatrix());
		}
		Vector3 diff = pos - target;
		if (diff.LengthSq() < 0.01f)
		{
			//�^�[�Q�b�g�Ƃ̍����قƂ�ǂȂ��Ȃ����̂�IK�I��
			return;
		}
	}
	//}
}

void FootIK::ApplyIK()
{
	if (m_IsEnable == false)
	{
		//FootIK������
		return;
	}
	for (auto& foot : m_foots)
	{
		//�ڕW���W���v�Z����
		Vector3 target;
		if (CalcIKTargetPos(foot, target) == false)
		{
			//�ڕW����܂�Ȃ�����
			continue;
		}
		//�v�Z�ł����̂�IK�������Ă���
		CCD_IK(foot, target);
	}
}