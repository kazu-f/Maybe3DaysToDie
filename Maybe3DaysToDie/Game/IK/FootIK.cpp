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
	Matrix lastMat = m_skeleton->GetBone(m_RootBoneID)->GetWorldMatrix();
	//行列から位置を取得
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

	//レイの作成
	btTransform start, end;
	start.setIdentity();
	end.setIdentity();
	//始点はコライダーの中心
	start.setOrigin(
	{
		pos.x,
		pos.y+100.0f,
		pos.z
	});
	////10cm下に向けてレイを飛ばす
	end.setOrigin(
	{	
		pos.x,
		pos.y,
		pos.z
	});
	//10cm下に向けてレイを飛ばす
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
		//ヒットしなかった
		return false;
	}

	//ここから下はレイヒットしたときの処理
	target = callback.hitPos;
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
	////while(true)
	////{ 
	//for (int i = 0; i < 5; i++)
	//{		
	//	int parentID = foot.m_bone->GetParentBoneNo();
	//	//自分のポジションを取得
	//	Matrix currentMat = foot.m_bone->GetWorldMatrix();
	//	Vector3 currentPos = { currentMat.m[3][0],currentMat.m[3][1],currentMat.m[3][2] };
	//	while (parentID != m_RootBoneID)
	//	{
	//		//親のボーンを取得
	//		Bone* parentBone = m_skeleton->GetBone(parentID);
	//		//親のポジションを取得
	//		Matrix parentMat = parentBone->GetWorldMatrix();
	//		Vector3 parentPos = { parentMat.m[3][0],parentMat.m[3][1],parentMat.m[3][2] };

	//		//親から自分の位置への方向を計算(ベクトル１)
	//		Vector3 ToCurrentPos = currentPos - parentPos;
	//		ToCurrentPos.Normalize();
	//		//親からターゲットへの方向を計算(ベクトル２)
	//		Vector3 ToTargetPos = target - parentPos;
	//		ToTargetPos.Normalize();
	//		//ベクトル１をベクトル２に一致させるための最短回転量
	//		float angle = acos(ToCurrentPos.Dot(ToTargetPos));
	//		//回転軸を求める
	//		Vector3 rotateAxis = Vector3::Zero;
	//		rotateAxis.Cross(ToCurrentPos, ToTargetPos);
	//		rotateAxis.Normalize();
	//		//回転軸と回転量からQuaternionを作成
	//		Quaternion qRot = Quaternion::Identity;
	//		qRot.SetRotation(rotateAxis, angle);

	//		//回転行列を計算
	//		Matrix mAddRot = Matrix::Identity;
	//		mAddRot.MakeRotationFromQuaternion(qRot);
	//		//親の行列に回転行列をかける
	//		//parentMat.m[3][0] = 0.0f;
	//		//parentMat.m[3][1] = 0.0f;
	//		//parentMat.m[3][2] = 0.0f;
	//		parentMat =  parentMat * mAddRot;
	//		parentMat.m[3][0] = parentPos.x;
	//		parentMat.m[3][1] = parentPos.y;
	//		parentMat.m[3][2] = parentPos.z;
	//		Skeleton::UpdateBoneWorldMatrixForIK(*parentBone, parentMat);
	//		//さらに親のIDを取得する
	//		parentID = parentBone->GetParentBoneNo();
	//	}
	//	currentPos = { currentMat.m[3][0],currentMat.m[3][1],currentMat.m[3][2] };
	//	Vector3 diff = currentPos - target;
	//	if (diff.LengthSq() < 0.01f)
	//	{
	//		//ターゲットとの差がほとんどなくなったのでIK終了
	//		break;
	//	}
	//}
	//for (int i = 0; i < 1; i++)
	//{
	//	//親のボーン番号を取得
	//	int parentID = foot.m_bone->GetParentBoneNo();
	//	while (parentID != m_RootBoneID)
	//	{
	//		//ルートボーンまで回す
	//		//エフェクタの位置を取得
	//		Matrix effectorMat = foot.m_bone->GetWorldMatrix();
	//		Vector3 effectorPos = { effectorMat.m[3][0],effectorMat.m[3][1],effectorMat.m[3][2] };
	//		//現在注目しているボーンの位置を取得
	//		Matrix currentMat = m_skeleton->GetBone(parentID)->GetWorldMatrix();
	//		Vector3 currentPos = { currentMat.m[3][0],currentMat.m[3][1],currentMat.m[3][2] };

	//		//ローカル座標系への変換
	//		Matrix currentInvMat = currentMat;
	//		currentInvMat.Inverse();
	//		//エフェクタ、ターゲットの注目しているボーンのローカル位置
	//		//エフェクター
	//		Vector3 localEffectorPos = effectorPos;
	//		currentInvMat.Apply(localEffectorPos);
	//		//ターゲット
	//		Vector3 localTargetPos = target;
	//		currentInvMat.Apply(localTargetPos);

	//		//基準からエフェクタへの方向(ベクトル１)
	//		Vector3 CurrentToEffector = localEffectorPos;
	//		CurrentToEffector.Normalize();
	//		//基準からターゲットへの方向(ベクトル２)
	//		Vector3 CurrentToTarget = localTargetPos;
	//		CurrentToTarget.Normalize();

	//		//ベクトル１をベクトル２に一致させるための最短回転量
	//		//回転角
	//		float angle = acos(CurrentToEffector.Dot(CurrentToTarget));
	//		angle = max(min(1.0f, angle), 0.0f);
	//		//回転軸
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
	//		//ワールド行列に反映
	//		currentMat.m[3][0] = 0.0f;
	//		currentMat.m[3][1] = 0.0f;
	//		currentMat.m[3][2] = 0.0f;
	//		//追加の回転を加える
	//		currentMat = mAddRot * currentMat;
	//		currentMat.m[3][0] = currentPos.x;
	//		currentMat.m[3][1] = currentPos.y;
	//		currentMat.m[3][2] = currentPos.z;
	//		////現在のボーンから下のボーンに回転を適応する
	//		//Bone* currentBone = m_skeleton->GetBone(parentID);
	//		//currentBone->SetWorldMatrix(currentMat);
	//		parentID = currentBone->GetParentBoneNo();
	//		//ローカル行列を求める
	//		Matrix localMat;
	//		if (parentID != -1)
	//		{
	//			//ルートじゃない時
	//			Matrix ToParentSpaceMat = m_skeleton->GetBone(parentID)->GetWorldMatrix();
	//			//逆行列
	//			ToParentSpaceMat.Inverse();
	//			localMat = currentMat * ToParentSpaceMat;
	//			//localMat *= mAddRot;
	//			currentBone->SetLocalMatrix(localMat);
	//		}
	//		//ルートボーンから下の骨のワールド行列を再計算する
	//		//Skeleton::UpdateBoneWorldMatrix(*currentBone, m_skeleton->GetBone(parentID)->GetWorldMatrix());
	//	}
	//}
	//while (true)
	//{
	for (int i = 0; i < 5; i++) 
	{
		//親のボーンを取得
		int parentID = foot.m_bone->GetParentBoneNo();
		//行列を取得
		const Matrix& mat = foot.m_bone->GetWorldMatrix();
		while (parentID != m_RootBoneID)
		{
			//行列から位置を取得
			Vector3 pos = { mat.m[3][0],mat.m[3][1],mat.m[3][2] };
			Vector3 diff = target - pos;
			if (diff.Length() < 0.001f)
			{
				return;
			}
			//ルートボーンまで計算を繰り返す
			Bone* currentBone = nullptr;
			//計算するボーンを取得
			currentBone = m_skeleton->GetBone(parentID);
			//ワールド行列を取得
			Matrix currentMat = currentBone->GetWorldMatrix();
			//行列を取得
			Vector3 currentBonePos = { currentMat.m[3][0],currentMat.m[3][1],currentMat.m[3][2] };

			Matrix currentInvMat = currentMat;
			currentInvMat.Inverse();
			//エフェクター
			Vector3 localEffectorPos = pos;
			currentInvMat.Apply(localEffectorPos);
			//ターゲット
			Vector3 localTargetPos = target;
			currentInvMat.Apply(localTargetPos);
			//基準からエフェクタへの方向(ベクトル１)
			Vector3 CurrentToEffector = localEffectorPos;
			CurrentToEffector.Normalize();
			//基準からターゲットへの方向(ベクトル２)
			Vector3 CurrentToTarget = localTargetPos;
			CurrentToTarget.Normalize();
			//回転軸を求める
			Vector3 rotateAxis;
			rotateAxis.Cross(CurrentToEffector, CurrentToTarget);
			rotateAxis.Normalize();
			//回転を補正するための回転行列を求める
			float angle = acosf(max(-1.0f, min(1.0f, CurrentToEffector.Dot(CurrentToTarget))));

			////エフェクターへのベクトル
			//Vector3 ToEffecter = pos - currentBonePos;
			////ターゲットへのベクトル
			//Vector3 ToTarget = target - currentBonePos;
			////正規化
			//ToEffecter.Normalize();
			//ToTarget.Normalize();
			////回転軸を求める
			//Vector3 rotateAxis;
			//rotateAxis.Cross(ToEffecter, ToTarget);
			//rotateAxis.Normalize();
			////回転を補正するための回転行列を求める
			//float angle = acosf(max(-1.0f,min(1.0f, ToEffecter.Dot(ToTarget))));

			Quaternion qRot;
			qRot.SetRotation(rotateAxis, angle);
			Matrix mAddRot;
			mAddRot.MakeRotationFromQuaternion(qRot);
			////ワールド行列に反映
			//currentMat.m[3][0] = 0.0f;
			//currentMat.m[3][1] = 0.0f;
			//currentMat.m[3][2] = 0.0f;
			////追加の回転を加える
			//currentMat = mAddRot * currentMat;
			////ポジションをセット
			//currentMat.m[3][0] = currentBonePos.x;
			//currentMat.m[3][1] = currentBonePos.y;
			//currentMat.m[3][2] = currentBonePos.z;

			//ローカル行列を求める
			Matrix localMat;
			//親のIDを入れる
			parentID = currentBone->GetParentBoneNo();
			if (parentID != -1)
			{
				//ルートじゃない時
				Matrix ToParentSpaceMat = m_skeleton->GetBone(parentID)->GetWorldMatrix();
				//逆行列
				ToParentSpaceMat.Inverse();
				//ローカル行列にする
				localMat = currentMat * ToParentSpaceMat;
				//追加の回転を加える
				localMat = mAddRot * localMat;

				currentBone->SetLocalMatrix(localMat);
			}
			//ルートボーンから下の骨のワールド行列を再計算する
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
	////目標座標を計算する
	//Vector3 target;
	//if (CalcIKTargetPos(m_foots[0], target) == false)
	//{
	//	//目標が定まらなかった
	//	return;
	//}
	////計算できたのでIKをかけていく
	//CCD_IK(m_foots[0], target);

}