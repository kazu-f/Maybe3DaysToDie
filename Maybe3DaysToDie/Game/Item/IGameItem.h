#pragma once

/// <summary>
/// ゲームのアイテムの基底クラス。
/// </summary>
class IGameItem
{
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

private:
	std::string m_itemName;	//アイテム名。
	int m_itemID = -1;		//アイテムID。
	prefab::ModelRender* m_itemModel = nullptr;		//アイテムのモデル。
	prefab::CSpriteRender* m_itemIcon = nullptr;	//アイテムのアイコン。
};

