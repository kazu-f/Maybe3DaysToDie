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
private:
	prefab::CSpriteRender* m_CrrentSprite = nullptr;	//���݂̋󕠓x�̃X�v���C�g
	prefab::CSpriteRender* m_FrameSprite = nullptr;		//�󕠃X�v���C�g�̘g
	prefab::CSpriteRender* m_IConSprite = nullptr;		//�󕠃A�C�R��

	float m_HungryTime = 0.0f;							//�������󂭎���
	int m_Hunder = 100;									//�󕠓x
	int m_MaxHunger = 100;								//������
};
