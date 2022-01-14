#pragma once

/// <summary>
/// �Q�[���̃A�C�e���̊��N���X�B
/// </summary>
class IGameItem
{
public:
	//���f���̃��[���h�s�����邽�߂̃f�[�^���Z�b�g�B
	void SetModelWorldMatrix(const Vector3& pos,const Quaternion& rot,const Vector3& scale = Vector3::One)
	{
		m_itemModel->SetPosition(pos);
		m_itemModel->SetRotation(rot);
		m_itemModel->SetScale(scale);
	}
	//�A�C�e����\�����邩�B
	void SetItemModelEnable(bool isEnable)
	{
		m_itemModel->SetActiveFlag(isEnable);
	}
	//�A�C�e���̃A�C�R���̈ʒu��ݒ�B
	void SetIconPosition(const Vector2& pos)
	{
		m_itemIcon->SetPosition(pos);
	}
	//�A�C�e���̃A�C�R����\�����邩�B
	void SetItemIconEnable(bool isEnable)
	{
		m_itemIcon->SetActiveFlag(isEnable);
	}

private:
	std::string m_itemName;	//�A�C�e�����B
	int m_itemID = -1;		//�A�C�e��ID�B
	prefab::ModelRender* m_itemModel = nullptr;		//�A�C�e���̃��f���B
	prefab::CSpriteRender* m_itemIcon = nullptr;	//�A�C�e���̃A�C�R���B
};

