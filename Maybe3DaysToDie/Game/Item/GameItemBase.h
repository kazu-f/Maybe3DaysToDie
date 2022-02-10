#pragma once

/// <summary>
/// �N���t�g�ɕK�v�ȑf�ރf�[�^�B
/// </summary>
struct SCraftMaterialData
{
	int itemID = -1;	//�N���t�g�Ɏg���A�C�e����ID�B
	int itemNum = 1;	//�N���t�g�Ɏg���A�C�e���̕K�v���B
};

/// <summary>
/// �A�C�e���̊�{�f�[�^�B
/// </summary>
class SItemData
{
public:
	int itemID = -1;					//�A�C�e��ID�B
	int stuckNum = 1;					//�A�C�e���̃X�^�b�N�\���B
	int itemType = -1;					//�A�C�e���^�C�v�B
	std::string itemName = "";		//�A�C�e���̖��O�B
	std::string tkmPath = "";		//�A�C�e���̃��f���f�[�^�B
	std::string iconPath = "";		//�A�C�e���̃A�C�R���f�[�^�B
	std::vector<SCraftMaterialData> craftMaterialDatas;		//�N���t�g�ɕK�v�ȃA�C�e���̃f�[�^�B
	std::vector<int> craftableItemIDs;						//���̃A�C�e������N���t�g�\���ID�B
};

using SItemDataPtr = std::unique_ptr<SItemData>;		//�A�C�e���̊�{�f�[�^�\���̂̃��j�[�N�|�C���^�B

/// <summary>
/// �Q�[���̃A�C�e���̊��N���X�B
/// </summary>
class GameItemBase
{
public:
	GameItemBase(SItemDataPtr & itemData);
	virtual ~GameItemBase();

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

	/// <summary>
	/// �A�C�e���f�[�^���擾�B
	/// </summary>
	/// <returns></returns>
	SItemData* GetIdemData()
	{
		return m_itemData.get();
	}

private:
	SItemDataPtr m_itemData;
	prefab::ModelRender* m_itemModel = nullptr;		//�A�C�e���̃��f���B
	prefab::CSpriteRender* m_itemIcon = nullptr;	//�A�C�e���̃A�C�R���B
};

