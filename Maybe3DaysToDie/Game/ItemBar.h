#pragma once
namespace {
	const int SelectNum = 8;	//�A�C�e���o�[�̐�
}
class ItemBar : public IGameObject
{
public:
	bool Start()override;
	void Update()override;

private:
	prefab::CSpriteRender* m_ItemIcon = nullptr;
	prefab::CSpriteRender* m_SelectItemIcon = nullptr;
	Vector3 m_SelectPos[SelectNum] = {};	//�I�𒆂̃A�C�e���o�[�̈ʒu
	int m_SelectNum = 0;						//���I�����Ă���A�C�e���o�[�̃X���b�gNo
};

