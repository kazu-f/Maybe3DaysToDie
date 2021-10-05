#pragma once
class PlayerHp final : public IGameObject
{
private:
	/// <summary>
	/// ������
	/// </summary>
	/// <returns>true���Ԃ�܂Ń��[�v����</returns>
	bool Start()override final;

	/// <summary>
	/// ���t���[���Ă΂��X�V�֐�
	/// </summary>
	void Update()override final;

	/// <summary>
	/// Delete���ꂽ�t���[���ŌĂ΂��폜�֐�
	/// </summary>
	void OnDestroy()override final;
public:
	/// <summary>
	/// �ő�Hp��ύX�ł���
	/// </summary>
	/// <param name="maxhp">�ݒ肵����Hp</param>
	void SetMaxHp(const int maxhp) {
		m_MaxHp = maxhp;
	}

	/// <summary>
	/// ���݂�Hp��Ԃ�
	/// </summary>
	/// <returns>hp</returns>
	const int GetHp() {
		return m_Hp;
	}

	/// <summary>
	/// ���R�񕜂̎��Ԃ�ύX�ł���
	/// </summary>
	/// <param name="regeneTime">���R�񕜂̎���</param>
	void SetRegeneTime(const float regeneTime) {
		m_RegeneTime = regeneTime;
	}
private:
	/// <summary>
	/// ���݂�HP�X�v���C�g��������
	/// </summary>
	void InitCurrentSprite();

	/// <summary>
	/// Hp�t���[����������
	/// </summary>
	void InitFrameSprite();

	/// <summary>
	/// HpICon��������
	/// </summary>
	void InitIConSprite();
private:
	prefab::CSpriteRender* m_HpCurrentSprite = nullptr;	//���݂�Hp�X�v���C�g
	prefab::CSpriteRender* m_HpFlameSprite = nullptr;	//HP�̘g
	prefab::CSpriteRender* m_HpICon = nullptr;			//Hp�̃A�C�R��
	int m_Hp = 100;										//���݂�Hp
	int m_MaxHp = 100;									//�ő�Hp
	float m_RegeneTime = 1.0f;							//���R�񕜎���
	float m_nowHpRegeneTime = 0.0f;						//���R�񕜂��Ă���̌o�ߎ���

};