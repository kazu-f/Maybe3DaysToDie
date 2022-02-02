#include "stdafx.h"
#include "FootIK.h"
#include "RayTest.h"

void FootIK::Enable(Skeleton* skeleton, FootIKParam& param)
{
	//スケルトンをセット
	m_skeleton = skeleton;
	//有効フラグを立てる
	m_IsEnable = true;
	//足のボーン1つ目
	int boneID = m_skeleton->FindBoneID(param.footBoneName_0);
	//ボーンの取得
	m_foots[0].m_bone = m_skeleton->GetBone(boneID);
	//コライダーの作成
	m_foots[0].m_collider.Create(param.footCapsuleColliderRadius_0, param.footCapsuleColliderHeight_0);

	//足のボーン2つ目
	boneID = m_skeleton->FindBoneID(param.footBoneName_1);
	//ボーンの取得
	m_foots[1].m_bone = m_skeleton->GetBone(boneID);
	//コライダーの作成
	m_foots[1].m_collider.Create(param.footCapsuleColliderRadius_1, param.footCapsuleColliderHeight_1);

	//ルートボーンを検索
	m_RootBoneID = m_skeleton->FindBoneID(param.rootBoneName);
}

bool FootIK::CalcIKTargetPos(const SFoot& foot, Vector3& target)
{
	if (foot.m_bone->GetParentBoneNo() == -1)
	{
		//親がいない。
		return false;
	}
	//ワールド行列を取得
	Matrix mat = foot.m_bone->GetWorldMatrix();
	//行列から位置を取得
	Vector3 pos = { mat.m[3][0],mat.m[3][1],mat.m[3][2] };

	//レイの作成
	btVector3 start, end;
	//始点はコライダーの中心
	start.setValue(pos.x, pos.y, pos.z);
	//10cm下に向けてレイを飛ばす
	end.setValue(
		pos.x,
		pos.y - 10.0f,
		pos.z
	);

	RayResult callback;
	PhysicsWorld().RayTest(start, end, callback);
	if (callback.isHit == false)
	{
		//ヒットしなかった
		return false;
	}

	//ここから下はレイヒットしたときの処理
	target = callback.hitColPos;
	//距離を調べる
	Vector3 diff = target - pos;
	if (diff.LengthSq() < 0.01f)
	{
		//近すぎるとき計算する必要ないのでfalse
		return false;
	}
	return true;
}

void FootIK::CCD_IK(const SFoot& foot, Vector3 target)
{
	//親のボーンを取得
	int parentID = foot.m_bone->GetParentBoneNo();
	//行列を取得
	Matrix mat = foot.m_bone->GetWorldMatrix();
	//行列から位置を取得
	Vector3 pos = { mat.m[3][0],mat.m[3][1],mat.m[3][2] };
	//while (true)
	//{
	for (int i = 0; i < 5; i++) {
		while (parentID != m_RootBoneID)
		{
			//ルートボーンまで計算を繰り返す
			Bone* currentBone = nullptr;
			//計算するボーンを取得
			currentBone = m_skeleton->GetBone(parentID);
			//ワールド行列を取得
			Matrix currentMat = currentBone->GetWorldMatrix();
			//行列を取得
			Vector3 currentBonePos = { currentMat.m[3][0],currentMat.m[3][1],currentMat.m[3][2] };
			//エフェクターへのベクトル
			Vector3 ToEffecter = pos - currentBonePos;
			//ターゲットへのベクトル
			Vector3 ToTarget = target - currentBonePos;
			//正規化
			ToEffecter.Normalize();
			ToTarget.Normalize();
			//回転軸を求める
			Vector3 rotateAxis;
			rotateAxis.Cross(ToEffecter, ToTarget);
			rotateAxis.Normalize();
			//回転を補正するための回転行列を求める
			float angle = acos(min(1.0f, ToEffecter.Dot(ToTarget)));
			Quaternion qRot;
			qRot.SetRotation(rotateAxis, angle);
			Matrix mAddRot;
			mAddRot.MakeRotationFromQuaternion(qRot);
			//ワールド行列に反映
			currentMat.m[3][0] = 0.0f;
			currentMat.m[3][1] = 0.0f;
			currentMat.m[3][2] = 0.0f;
			//追加の回転を加える
			currentMat = currentMat * mAddRot;
			//ポジションをセット
			currentMat.m[3][0] = currentBonePos.x;
			currentMat.m[3][1] = currentBonePos.y;
			currentMat.m[3][2] = currentBonePos.z;

			//ローカル行列を求める
			Matrix localMat;
			parentID = currentBone->GetParentBoneNo();
			if (parentID != -1)
			{
				//ルートじゃない時
				Matrix ToParentSpaceMat = m_skeleton->GetBone(parentID)->GetWorldMatrix();
				//逆行列
				ToParentSpaceMat.Inverse();
				localMat = currentMat * ToParentSpaceMat;
				currentBone->SetLocalMatrix(localMat);
			}
			//ルートボーンから下の骨のワールド行列を再計算する
			Skeleton::UpdateBoneWorldMatrix(*currentBone, m_skeleton->GetBone(m_RootBoneID)->GetWorldMatrix());
		}
		Vector3 diff = pos - target;
		if (diff.LengthSq() < 0.01f)
		{
			//ターゲットとの差がほとんどなくなったのでIK終了
			return;
		}
	}
	//}
}

void FootIK::ApplyIK()
{
	if (m_IsEnable == false)
	{
		//FootIKが無効
		return;
	}
	for (auto& foot : m_foots)
	{
		//目標座標を計算する
		Vector3 target;
		if (CalcIKTargetPos(foot, target) == false)
		{
			//目標が定まらなかった
			continue;
		}
		//計算できたのでIKをかけていく
		CCD_IK(foot, target);
	}
}