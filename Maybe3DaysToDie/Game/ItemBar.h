#pragma once
namespace {
	const int SelectNum = 8;	//アイテムバーの数
}
class ItemBar : public IGameObject
{
public:
	bool Start()override;
	void Update()override;

private:
	prefab::CSpriteRender* m_ItemIcon = nullptr;
	prefab::CSpriteRender* m_SelectItemIcon = nullptr;
	Vector3 m_SelectPos[SelectNum] = {};	//選択中のアイテムバーの位置
	int m_SelectNum = 0;						//今選択しているアイテムバーのスロットNo
};

