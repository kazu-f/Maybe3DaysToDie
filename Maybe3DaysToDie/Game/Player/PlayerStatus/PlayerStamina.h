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

	/// <summary>
	/// �t�H���g��������
	/// </summary>
	void InitStaminaFont();
	/// <summary>
	/// �t�H���g���X�V
	/// </summary>
	void UpdateStaminaFont();

public:
	const bool IsUseStamina(const int cost) {
		static float DownTime = 0.0f;
		DownTime += GameTime().GetFrameDeltaTime();
		if (m_Stamina >= cost) {
			if (DownTime > 0.5000f) {
				DownTime = 0.0f;
				m_Stamina -= cost;
			}
			return true;
		}
		return false;
	}
	void Reset() {
		m_Stamina = m_MaxStamina;
	}
	void SetMax(int maxSt) {
		m_MaxStamina = maxSt;
	}
private:
	float m_RegeneTime = 2.0f;				//���W�F�l�ł����莞��
	float m_nowRegeneTimer = 0.0f;			//��莞�Ԉȏ�ɂȂ�ƃ��W�F�l�ł���
	int m_Stamina = 100;					//�X�^�~�i
	int m_MaxStamina = 100;					//�ő�X�^�~�i
	prefab::CSpriteRender* m_CurrentSprite = nullptr;	//���݂̃X�^�~�i��\���X�v���C�g
	prefab::CSpriteRender* m_FlameSprite = nullptr;		//�X�^�~�i�̘g
	prefab::CSpriteRender* m_IConSprite = nullptr;		//�A�C�R���̃X�v���C�g
	CFontRender* m_StaminaFont = nullptr;				//�X�^�~�i�̃t�H���g
};

