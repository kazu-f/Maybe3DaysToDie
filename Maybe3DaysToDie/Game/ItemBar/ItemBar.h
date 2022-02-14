#pragma once

class PlacementObject;
class DestroyObject;
class LoadingByChunk;
class Stage;
class Tool;
class SaveDataFile;
class TerrainSave;
class TerrainLoad;
class Stage;
class Player;
class Mause;
class GameItemBase;

struct InventoryItemData {
	GameItemBase* m_itemBase = nullptr;
	int itemCount = 0;
};


namespace {
	const int SelectNum = 8;	//アイテムバーの数
}
class ItemBar : public IGameObject
{
public:
	bool Start()override;
	void Update()override;
	void OnDestroy()override;

	float GetItemSize()const {
		return ItemOneBoxSize;
	}
	void SetWorldData(
		PlacementObject* Po,
		DestroyObject* Do,
		SaveDataFile* Sf,
		Tool* T,
		LoadingByChunk* Lc,
		TerrainSave* Ts,
		TerrainLoad* Tl,
		Stage* s) {
		m_PlacementObject = Po;
		m_DestroyObject = Do;
		m_SaveDataFile = Sf;
		m_Tool = T;
		m_LoadingByChunk = Lc;
		m_TerrainSave = Ts;
		m_TerrainLoad = Tl;
		m_Stage = s;
	}

	void SetPlayer(Player* pl) {
		m_Player = pl;
	}

	Player* GetPlayer()
	{
		return m_Player;
	}

	PlacementObject* GetPlacementObject()
	{
		return m_PlacementObject;
	}

	DestroyObject* GetDestroyObject()
	{
		return m_DestroyObject;
	}
private:
	void ItemSlotKey(int vKey,int slot);
	void SetItemDatas();
private:
	prefab::CSpriteRender* m_ItemIcon = nullptr;
	prefab::CSpriteRender* m_SelectItemIcon = nullptr;
	const float ItemOneBoxSize = 75.0f;			//アイテム１個のサイズ
	Vector2 m_SelectPos[SelectNum] = {};	//選択中のアイテムバーの位置
	int m_SelectNum = 0;						//今選択しているアイテムバーのスロットNo
	PlacementObject* m_PlacementObject = nullptr;
	DestroyObject* m_DestroyObject = nullptr;
	SaveDataFile* m_SaveDataFile = nullptr;
	Tool* m_Tool = nullptr;
	LoadingByChunk* m_LoadingByChunk = nullptr;
	TerrainSave* m_TerrainSave = nullptr;		//地形セーブ用のクラス
	TerrainLoad* m_TerrainLoad = nullptr;
	Stage* m_Stage = nullptr;
	Player* m_Player=nullptr;
	InventoryItemData m_itemInventory[SelectNum];		//配列。
	GameItemBase* m_nullItem = nullptr;

	float m_InstallTime = 0.0f;		//設置できる時間
	float m_DeleteTime = 0.0f;
};

