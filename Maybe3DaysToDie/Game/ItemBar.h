#pragma once
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
	
	LRESULT CALLBACK WindowProc(
		HWND hwnd,      // ウィンドウハンドル
		UINT uMsg,      // メッセージコード
		WPARAM wParam,  // w-パラメータ
		LPARAM lParam   // l-パラメータ
	);
private:
	prefab::CSpriteRender* m_ItemIcon = nullptr;
	prefab::CSpriteRender* m_SelectItemIcon = nullptr;
	const float ItemOneBoxSize = 75.0f;			//アイテム１個のサイズ
	Vector2 m_SelectPos[SelectNum] = {};	//選択中のアイテムバーの位置
	int m_SelectNum = 0;						//今選択しているアイテムバーのスロットNo
};

