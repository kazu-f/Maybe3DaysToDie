#pragma once
/// <summary>
/// �v���C���[�̋󕠓x��\���N���X
/// </summary>
class PlayerHunger : public IGameObject
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
	const void SetMaxHunger(const int maxHun) {
		m_MaxHunger = maxHun;
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

	/// <summary>
	/// �󕠃A�C�R��������������
	/// </summary>
	void IConSpriteInit();
private:
	prefab::CSpriteRender* m_CrrentSprite = nullptr;	//���݂̋󕠃Q�[�W
	prefab::CSpriteRender* m_FlameSprite = nullptr;		//�󕠃Q�[�W�̘g
	prefab::CSpriteRender* m_IConSprite = nullptr;		//�󕠃A�C�R��

	float m_HungryTime = 0.0f;							//�������󂭎���
	int m_Hunder = 100;									//�󕠓x
	int m_MaxHunger = 100;								//������
};

