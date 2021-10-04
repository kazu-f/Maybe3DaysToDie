#pragma once
class PlayerStamina final : public IGameObject
{
private:
	/// <summary>
	/// GameObject�ɐς܂��ƈ�x�����Ă΂�鏉�����֐�
	/// </summary>
	/// <returns>true���Ԃ�܂Ń��[�v����</returns>
	bool Start()override final;

	/// <summary>
	/// ���t���[���Ă΂��X�V�֐�
	/// </summary>
	void Update()override final;

	/// <summary>
	/// Delete���ꂽ�Ƃ��ɌĂ΂��֐�
	/// </summary>
	void OnDestroy()override final;

private:
	prefab::CSpriteRender* m_StaminaCurrentSprite = nullptr;
	prefab::CSpriteRender* m_StaminaFlameSprite = nullptr;
	prefab::CSpriteRender* m_StaminaIConSprite = nullptr;

	float m_RegeneTime = 0.0f;				//���W�F�l�ł����莞��
	float m_nowRegeneTimer = 0.0f;			//��莞�Ԉȏ�ɂȂ�ƃ��W�F�l�ł���
	int m_Stamina = 100;					//�X�^�~�i
	int m_MaxStamina = 100;					//�X�^�~�i�ő�l
											//�ύX���邩������Ȃ��̂Œ萔�ɂ͂��Ȃ�
};

