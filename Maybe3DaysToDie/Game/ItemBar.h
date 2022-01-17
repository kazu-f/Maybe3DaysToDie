#pragma once
namespace {
	const int SelectNum = 8;	//�A�C�e���o�[�̐�
}
class ItemBar : public IGameObject
{
public:
	bool Start()override;
	void Update()override;

	float GetItemSize()const {
		return ItemOneBoxSize;
	}
private:
	prefab::CSpriteRender* m_ItemIcon = nullptr;
	prefab::CSpriteRender* m_SelectItemIcon = nullptr;
	const float ItemOneBoxSize = 75.0f;			//�A�C�e���P�̃T�C�Y
	Vector2 m_SelectPos[SelectNum] = {};	//�I�𒆂̃A�C�e���o�[�̈ʒu
	int m_SelectNum = 0;						//���I�����Ă���A�C�e���o�[�̃X���b�gNo
};

