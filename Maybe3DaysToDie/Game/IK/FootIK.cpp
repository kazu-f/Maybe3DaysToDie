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
	Matrix lastMat = m_skeleton->GetBone(m_RootBoneID)->GetWorldMatrix();
	//�s�񂩂�ʒu���擾
	Vector3 pos = { mat.m[3][0],mat.m[3][1],mat.m[3][2] };
	Vector3 lastPos = { lastMat.m[3][0],lastMat.m[3][1],lastMat.m[3][2] };
	if (!std::isfinite(lastPos.x) || !std::isfinite(lastPos.y) || !std::isfinite(lastPos.z))
	{
		return false;
	}
	Vector3 diffanim = pos - lastPos;
	if (diffanim.LengthSq() < 0.01f)
	{
		return false;
	}

	//���C�̍쐬
	btTransform start, end;
	start.setIdentity();
	end.setIdentity();
	//�n�_�̓R���C�_�[�̒��S
	start.setOrigin(
	{
		pos.x,
		pos.y+100.0f,
		pos.z
	});
	////10cm���Ɍ����ă��C���΂�
	end.setOrigin(
	{	
		pos.x,
		pos.y,
		pos.z
	});
	//10cm���Ɍ����ă��C���΂�
	//end.setOrigin(
	//{	
	//	pos.x,
	//	pos.y-10.0f,
	//	pos.z
	//});

	SweepResultGround callback;
	callback.startPos.Set(start.getOrigin());
	PhysicsWorld().ConvexSweepTest((const btConvexShape*)foot.m_collider.GetBody(), start, end, callback);
	if (callback.isHit == false)
	{
		//�q�b�g���Ȃ�����
		return false;
	}

	//�������牺�̓��C�q�b�g�����Ƃ��̏���
	target = callback.hitPos;
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
	////while(true)
	////{ 
	//for (int i = 0; i < 5; i++)
	//{		
	//	int parentID = foot.m_bone->GetParentBoneNo();
	//	//�����̃|�W�V�������擾
	//	Matrix currentMat = foot.m_bone->GetWorldMatrix();
	//	Vector3 currentPos = { currentMat.m[3][0],currentMat.m[3][1],currentMat.m[3][2] };
	//	while (parentID != m_RootBoneID)
	//	{
	//		//�e�̃{�[�����擾
	//		Bone* parentBone = m_skeleton->GetBone(parentID);
	//		//�e�̃|�W�V�������擾
	//		Matrix parentMat = parentBone->GetWorldMatrix();
	//		Vector3 parentPos = { parentMat.m[3][0],parentMat.m[3][1],parentMat.m[3][2] };

	//		//�e���玩���̈ʒu�ւ̕������v�Z(�x�N�g���P)
	//		Vector3 ToCurrentPos = currentPos - parentPos;
	//		ToCurrentPos.Normalize();
	//		//�e����^�[�Q�b�g�ւ̕������v�Z(�x�N�g���Q)
	//		Vector3 ToTargetPos = target - parentPos;
	//		ToTargetPos.Normalize();
	//		//�x�N�g���P���x�N�g���Q�Ɉ�v�����邽�߂̍ŒZ��]��
	//		float angle = acos(ToCurrentPos.Dot(ToTargetPos));
	//		//��]�������߂�
	//		Vector3 rotateAxis = Vector3::Zero;
	//		rotateAxis.Cross(ToCurrentPos, ToTargetPos);
	//		rotateAxis.Normalize();
	//		//��]���Ɖ�]�ʂ���Quaternion���쐬
	//		Quaternion qRot = Quaternion::Identity;
	//		qRot.SetRotation(rotateAxis, angle);

	//		//��]�s����v�Z
	//		Matrix mAddRot = Matrix::Identity;
	//		mAddRot.MakeRotationFromQuaternion(qRot);
	//		//�e�̍s��ɉ�]�s���������
	//		//parentMat.m[3][0] = 0.0f;
	//		//parentMat.m[3][1] = 0.0f;
	//		//parentMat.m[3][2] = 0.0f;
	//		parentMat =  parentMat * mAddRot;
	//		parentMat.m[3][0] = parentPos.x;
	//		parentMat.m[3][1] = parentPos.y;
	//		parentMat.m[3][2] = parentPos.z;
	//		Skeleton::UpdateBoneWorldMatrixForIK(*parentBone, parentMat);
	//		//����ɐe��ID���擾����
	//		parentID = parentBone->GetParentBoneNo();
	//	}
	//	currentPos = { currentMat.m[3][0],currentMat.m[3][1],currentMat.m[3][2] };
	//	Vector3 diff = currentPos - target;
	//	if (diff.LengthSq() < 0.01f)
	//	{
	//		//�^�[�Q�b�g�Ƃ̍����قƂ�ǂȂ��Ȃ����̂�IK�I��
	//		break;
	//	}
	//}
	//for (int i = 0; i < 1; i++)
	//{
	//	//�e�̃{�[���ԍ����擾
	//	int parentID = foot.m_bone->GetParentBoneNo();
	//	while (parentID != m_RootBoneID)
	//	{
	//		//���[�g�{�[���܂ŉ�
	//		//�G�t�F�N�^�̈ʒu���擾
	//		Matrix effectorMat = foot.m_bone->GetWorldMatrix();
	//		Vector3 effectorPos = { effectorMat.m[3][0],effectorMat.m[3][1],effectorMat.m[3][2] };
	//		//���ݒ��ڂ��Ă���{�[���̈ʒu���擾
	//		Matrix currentMat = m_skeleton->GetBone(parentID)->GetWorldMatrix();
	//		Vector3 currentPos = { currentMat.m[3][0],currentMat.m[3][1],currentMat.m[3][2] };

	//		//���[�J�����W�n�ւ̕ϊ�
	//		Matrix currentInvMat = currentMat;
	//		currentInvMat.Inverse();
	//		//�G�t�F�N�^�A�^�[�Q�b�g�̒��ڂ��Ă���{�[���̃��[�J���ʒu
	//		//�G�t�F�N�^�[
	//		Vector3 localEffectorPos = effectorPos;
	//		currentInvMat.Apply(localEffectorPos);
	//		//�^�[�Q�b�g
	//		Vector3 localTargetPos = target;
	//		currentInvMat.Apply(localTargetPos);

	//		//�����G�t�F�N�^�ւ̕���(�x�N�g���P)
	//		Vector3 CurrentToEffector = localEffectorPos;
	//		CurrentToEffector.Normalize();
	//		//�����^�[�Q�b�g�ւ̕���(�x�N�g���Q)
	//		Vector3 CurrentToTarget = localTargetPos;
	//		CurrentToTarget.Normalize();

	//		//�x�N�g���P���x�N�g���Q�Ɉ�v�����邽�߂̍ŒZ��]��
	//		//��]�p
	//		float angle = acos(CurrentToEffector.Dot(CurrentToTarget));
	//		angle = max(min(1.0f, angle), 0.0f);
	//		//��]��
	//		Vector3 rotationAxis = Vector3::Zero;
	//		rotationAxis.Cross(CurrentToEffector, CurrentToTarget);
	//		rotationAxis.Normalize();

	//		Quaternion qRot = Quaternion::Identity;
	//		qRot.SetRotation(rotationAxis, angle);
	//		Bone* currentBone = m_skeleton->GetBone(parentID);
	//		//qRot.Multiply(qRot, currentBone->GetRotation());
	//		//currentBone->SetRotation(qRot);
	//		//currentBone->RsetLocalMatrix();
	//		Matrix mAddRot = Matrix::Identity;
	//		mAddRot.MakeRotationFromQuaternion(qRot);
	//		//���[���h�s��ɔ��f
	//		currentMat.m[3][0] = 0.0f;
	//		currentMat.m[3][1] = 0.0f;
	//		currentMat.m[3][2] = 0.0f;
	//		//�ǉ��̉�]��������
	//		currentMat = mAddRot * currentMat;
	//		currentMat.m[3][0] = currentPos.x;
	//		currentMat.m[3][1] = currentPos.y;
	//		currentMat.m[3][2] = currentPos.z;
	//		////���݂̃{�[�����牺�̃{�[���ɉ�]��K������
	//		//Bone* currentBone = m_skeleton->GetBone(parentID);
	//		//currentBone->SetWorldMatrix(currentMat);
	//		parentID = currentBone->GetParentBoneNo();
	//		//���[�J���s������߂�
	//		Matrix localMat;
	//		if (parentID != -1)
	//		{
	//			//���[�g����Ȃ���
	//			Matrix ToParentSpaceMat = m_skeleton->GetBone(parentID)->GetWorldMatrix();
	//			//�t�s��
	//			ToParentSpaceMat.Inverse();
	//			localMat = currentMat * ToParentSpaceMat;
	//			//localMat *= mAddRot;
	//			currentBone->SetLocalMatrix(localMat);
	//		}
	//		//���[�g�{�[�����牺�̍��̃��[���h�s����Čv�Z����
	//		//Skeleton::UpdateBoneWorldMatrix(*currentBone, m_skeleton->GetBone(parentID)->GetWorldMatrix());
	//	}
	//}
	//while (true)
	//{
	for (int i = 0; i < 5; i++) 
	{
		//�e�̃{�[�����擾
		int parentID = foot.m_bone->GetParentBoneNo();
		//�s����擾
		const Matrix& mat = foot.m_bone->GetWorldMatrix();
		while (parentID != m_RootBoneID)
		{
			//�s�񂩂�ʒu���擾
			Vector3 pos = { mat.m[3][0],mat.m[3][1],mat.m[3][2] };
			Vector3 diff = target - pos;
			if (diff.Length() < 0.001f)
			{
				return;
			}
			//���[�g�{�[���܂Ōv�Z���J��Ԃ�
			Bone* currentBone = nullptr;
			//�v�Z����{�[�����擾
			currentBone = m_skeleton->GetBone(parentID);
			//���[���h�s����擾
			Matrix currentMat = currentBone->GetWorldMatrix();
			//�s����擾
			Vector3 currentBonePos = { currentMat.m[3][0],currentMat.m[3][1],currentMat.m[3][2] };

			Matrix currentInvMat = currentMat;
			currentInvMat.Inverse();
			//�G�t�F�N�^�[
			Vector3 localEffectorPos = pos;
			currentInvMat.Apply(localEffectorPos);
			//�^�[�Q�b�g
			Vector3 localTargetPos = target;
			currentInvMat.Apply(localTargetPos);
			//�����G�t�F�N�^�ւ̕���(�x�N�g���P)
			Vector3 CurrentToEffector = localEffectorPos;
			CurrentToEffector.Normalize();
			//�����^�[�Q�b�g�ւ̕���(�x�N�g���Q)
			Vector3 CurrentToTarget = localTargetPos;
			CurrentToTarget.Normalize();
			//��]�������߂�
			Vector3 rotateAxis;
			rotateAxis.Cross(CurrentToEffector, CurrentToTarget);
			rotateAxis.Normalize();
			//��]��␳���邽�߂̉�]�s������߂�
			float angle = acosf(max(-1.0f, min(1.0f, CurrentToEffector.Dot(CurrentToTarget))));

			////�G�t�F�N�^�[�ւ̃x�N�g��
			//Vector3 ToEffecter = pos - currentBonePos;
			////�^�[�Q�b�g�ւ̃x�N�g��
			//Vector3 ToTarget = target - currentBonePos;
			////���K��
			//ToEffecter.Normalize();
			//ToTarget.Normalize();
			////��]�������߂�
			//Vector3 rotateAxis;
			//rotateAxis.Cross(ToEffecter, ToTarget);
			//rotateAxis.Normalize();
			////��]��␳���邽�߂̉�]�s������߂�
			//float angle = acosf(max(-1.0f,min(1.0f, ToEffecter.Dot(ToTarget))));

			Quaternion qRot;
			qRot.SetRotation(rotateAxis, angle);
			Matrix mAddRot;
			mAddRot.MakeRotationFromQuaternion(qRot);
			////���[���h�s��ɔ��f
			//currentMat.m[3][0] = 0.0f;
			//currentMat.m[3][1] = 0.0f;
			//currentMat.m[3][2] = 0.0f;
			////�ǉ��̉�]��������
			//currentMat = mAddRot * currentMat;
			////�|�W�V�������Z�b�g
			//currentMat.m[3][0] = currentBonePos.x;
			//currentMat.m[3][1] = currentBonePos.y;
			//currentMat.m[3][2] = currentBonePos.z;

			//���[�J���s������߂�
			Matrix localMat;
			//�e��ID������
			parentID = currentBone->GetParentBoneNo();
			if (parentID != -1)
			{
				//���[�g����Ȃ���
				Matrix ToParentSpaceMat = m_skeleton->GetBone(parentID)->GetWorldMatrix();
				//�t�s��
				ToParentSpaceMat.Inverse();
				//���[�J���s��ɂ���
				localMat = currentMat * ToParentSpaceMat;
				//�ǉ��̉�]��������
				localMat = mAddRot * localMat;

				currentBone->SetLocalMatrix(localMat);
			}
			//���[�g�{�[�����牺�̍��̃��[���h�s����Čv�Z����
			Skeleton::UpdateBoneWorldMatrix(*currentBone, m_skeleton->GetBone(parentID)->GetWorldMatrix());
		}
	}
	m_skeleton->PostSet();
	//m_skeleton->Update(m_skeleton->GetWorldMatrix());
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
	////�ڕW���W���v�Z����
	//Vector3 target;
	//if (CalcIKTargetPos(m_foots[0], target) == false)
	//{
	//	//�ڕW����܂�Ȃ�����
	//	return;
	//}
	////�v�Z�ł����̂�IK�������Ă���
	//CCD_IK(m_foots[0], target);

}