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
	/// <summary>
	/// ���݂̃X�^�~�i�X�v���C�g��������
	/// </summary>
	void CurrentSpriteInit();
	/// <summary>
	/// �X�^�~�i�t���[����������
	/// </summary>
	void FlameSpriteInit();
	
	/// <summary>
	/// �A�C�R����������
	/// </summary>
	void IConSpriteInit();
private:
	float m_RegeneTime = 1.0f;				//���W�F�l�ł����莞��
	float m_nowRegeneTimer = 0.0f;			//��莞�Ԉȏ�ɂȂ�ƃ��W�F�l�ł���
	int m_Stamina = 100;					//�X�^�~�i
	int m_MaxStamina = 100;
	prefab::CSpriteRender* m_CurrentSprite = nullptr;	
	prefab::CSpriteRender* m_FlameSprite = nullptr;
	prefab::CSpriteRender* m_IConSprite = nullptr;
};

