#pragma once
class Player;
/// <summary>
/// �v���C���[�̋󕠓x��\���N���X
/// </summary>
class PlayerHunger final : public IGameObject
{
private:
	/// <summary>
	/// New���ꂽ����GameObject����Ă΂�� 
	/// �������p�֐�
	/// </summary>
	/// <returns>true���Ԃ�܂Ń��[�v����</returns>
	bool Start() override final;

	/// <summary>
	/// ���t���[���Ă΂��X�V�֐�
	/// </summary>
	void Update()override final;

	/// <summary>
	/// delete������GameObject����Ă΂��֐�
	/// </summary>
	void OnDestroy()override final;

public:
	const void SetMax(const int maxHun) {
		m_MaxHunger = maxHun;
	}

	void SetPlayer(Player* pp) {
		m_Player = pp;
	}

	void Reset() {
		m_Hunder = m_MaxHunger;
	}
private:
	/// <summary>
	/// ���݂̋󕠃Q�[�W������������
	/// </summary>
	void CurrentSpriteInit();

	/// <summary>
	/// �󕠃Q�[�W�̘g������������
	/// </summary>
	void FlameSpriteInit();
private:
	prefab::CSpriteRender* m_CurrentSprite = nullptr;	//���݂̋󕠃Q�[�W
	prefab::CSpriteRender* m_FlameSprite = nullptr;		//�󕠃Q�[�W�̘g

	float m_HungeryTime = 1.0f;							//�������󂭎���
	float m_HungeryCountTime = 0.0f;					//�o�ߎ���
	int m_Hunder = 1;									//�󕠓x
	int m_MaxHunger = 1;								//������
	
	Player* m_Player = nullptr;							//�v���C���[�̃|�C���^
};

