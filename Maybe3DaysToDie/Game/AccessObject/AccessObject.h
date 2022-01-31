#pragma once
#include "SaveDataFile.h"

class AccessObject
{
public:
	AccessObject();
	~AccessObject();

private:
	/// <summary>
	/// 初期化
	/// </summary>
	void Init();

	void OnDestroy();

public:
	/// <summary>
	/// オブジェクトにアクセスする
	/// </summary>
	void Access();

	/// <summary>
	/// セーブデータファイルをセット
	/// </summary>
	void SetSaveData(SaveDataFile* sdf)
	{
		m_SaveData = sdf;
	}

	/// <summary>
	/// アクセス中かどうかを取得
	/// </summary>
	/// <returns>アクセス中の時はtrue</returns>
	bool IsAccess()
	{
		return IsSpriteActive;
	}

	/// <summary>
	/// アクセスを終了する。
	/// ボックスを閉じるときなどに使用
	/// </summary>
	void EndAccess()
	{
		SetAccessFlag(false);
	}

private:
	void SwitchAction(AccessTag tag);

	void SwitchSpriteActive()
	{
		IsSpriteActive = !IsSpriteActive;
		m_BoxSprite->SetActiveFlag(IsSpriteActive);
	}
	
	void SetAccessFlag(bool flag)
	{
		if (IsSpriteActive == flag)
		{
			//フラグに変更ないときreturn
			return;
		}
		IsSpriteActive = flag;
		m_BoxSprite->SetActiveFlag(flag);
	}
private:
	DestructibleObject* m_hitObj = nullptr;
	SaveDataFile* m_SaveData = nullptr;
	prefab::CSpriteRender* m_BoxSprite = nullptr;
	bool IsSpriteActive = false;
};

