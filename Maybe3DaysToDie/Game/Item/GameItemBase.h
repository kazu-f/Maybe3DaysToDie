#pragma once

/// <summary>
/// クラフトに必要な素材データ。
/// </summary>
struct SCraftMaterialData
{
	int itemID = -1;	//クラフトに使うアイテムのID。
	int itemNum = 1;	//クラフトに使うアイテムの必要数。
};

/// <summary>
/// アイテムの基本データ。
/// </summary>
class SItemData
{
public:
	int itemID = -1;					//アイテムID。
	int stuckNum = 1;					//アイテムのスタック可能数。
	int itemType = -1;					//アイテムタイプ。
	std::string itemName = "";		//アイテムの名前。
	std::string tkmPath = "";		//アイテムのモデルデータ。
	std::string iconPath = "";		//アイテムのアイコンデータ。
	std::vector<SCraftMaterialData> craftMaterialDatas;		//クラフトに必要なアイテムのデータ。
	std::vector<int> craftableItemIDs;						//このアイテムからクラフト可能先のID。
};

using SItemDataPtr = std::unique_ptr<SItemData>;		//アイテムの基本データ構造体のユニークポインタ。

/// <summary>
/// ゲームのアイテムの基底クラス。
/// </summary>
class GameItemBase
{
public:
	GameItemBase(SItemDataPtr & itemData);
	virtual ~GameItemBase();

public:
	//モデルのワールド行列を作るためのデータをセット。
	void SetModelWorldMatrix(const Vector3& pos,const Quaternion& rot,const Vector3& scale = Vector3::One)
	{
		m_itemModel->SetPosition(pos);
		m_itemModel->SetRotation(rot);
		m_itemModel->SetScale(scale);
	}
	//アイテムを表示するか。
	void SetItemModelEnable(bool isEnable)
	{
		m_itemModel->SetActiveFlag(isEnable);
	}
	//アイテムのアイコンの位置を設定。
	void SetIconPosition(const Vector2& pos)
	{
		m_itemIcon->SetPosition(pos);
	}
	//アイテムのアイコンを表示するか。
	void SetItemIconEnable(bool isEnable)
	{
		m_itemIcon->SetActiveFlag(isEnable);
	}

	/// <summary>
	/// アイテムデータを取得。
	/// </summary>
	/// <returns></returns>
	SItemData* GetIdemData()
	{
		return m_itemData.get();
	}

private:
	SItemDataPtr m_itemData;
	prefab::ModelRender* m_itemModel = nullptr;		//アイテムのモデル。
	prefab::CSpriteRender* m_itemIcon = nullptr;	//アイテムのアイコン。
};

