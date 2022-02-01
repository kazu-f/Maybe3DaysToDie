#pragma once

class FootIK
{
private:
	struct SFoot {
		Bone* m_bone;		//足のボーン
		CCapsuleCollider m_collider;		//ボーンの位置につけるコライダー
	};
public:
	struct FootIKParam {
		const wchar_t* footBoneName_0 = nullptr;		//足のボーンの名前１
		const wchar_t* footBoneName_1 = nullptr;		//足のボーンの名前２
		const wchar_t* rootBoneName = nullptr;		//IKをかけ始めるルートボーン
		float footCapsuleColliderRadius_0 = 0.0f;		//カプセルコライダーの半径１
		float footCapsuleColliderRadius_1 = 0.0f;		//カプセルコライダーの半径２
		float footCapsuleColliderHeight_0 = 0.0f;		//カプセルコライダーの高さ１
		float footCapsuleColliderHeight_1 = 0.0f;		//カプセルコライダーの高さ２
	};

private:
	FootIK() {}
	~FootIK() {}
public:

	/// <summary>
	/// FootIKを有効にする
	/// </summary>
	/// <param name="skeleton">IKをかけるスケルトン</param>
	/// <param name="param">IKに必要なパラメータ</param>
	void Enable(Skeleton* skeleton,const FootIKParam& param);

	/// <summary>
	/// IKを無効にする
	/// </summary>
	void Disable()
	{
		m_IsEnable = false;
	}

	/// <summary>
	/// IKをかける
	/// </summary>
	void ApplyIK();

private:
	/// <summary>
	/// IKの最終位置を計算する
	/// </summary>
	bool CalcIKTargetPos(const SFoot& foot,Vector3&target);

	/// <summary>
	/// CCD_IK
	/// </summary>
	/// <param name="foot">IKをかける足</param>
	/// <param name="target">目標地点</param>
	void CCD_IK(const SFoot& foot, Vector3 target);

private:
	int m_RootBoneID = -1;		//ルートボーンのID
	Skeleton* m_skeleton = nullptr;		//スケルトン
	SFoot m_foots[2];		//足
	bool m_IsEnable = false;		//IKが有効かどうか
};