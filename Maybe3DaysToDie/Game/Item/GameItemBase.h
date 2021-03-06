#pragma once

class ItemBar;

struct Item;
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
	int itemTypeID = -1;				//アイテムの種類ごとに割り振られたID。
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

	virtual void SelectItemAction(ItemBar* itemBar);	//このアイテムが選択されたときの処理。
	virtual void UseItemAction1(ItemBar* itemBar);		//左クリックのアクション。
	virtual void UseItemAction2(ItemBar* itemBar) {};	//右クリックのアクション。
	void ResetUseItemSelect(ItemBar* itemBar);

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

	/// <summary>
	/// アイテムデータを取得。
	/// </summary>
	/// <returns></returns>
	SItemData* GetItemData()
	{
		return m_itemData.get();
	}
protected:
	void SetToolHand(ItemBar* itemBar);
	void SetPlaceNone(ItemBar* itemBar);
private:
	SItemDataPtr m_itemData;
	prefab::ModelRender* m_itemModel = nullptr;		//アイテムのモデル。
};

