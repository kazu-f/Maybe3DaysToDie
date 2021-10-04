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
	float m_RegeneTime = 0.0f;				//���W�F�l�ł����莞��
	float m_nowRegeneTimer = 0.0f;			//��莞�Ԉȏ�ɂȂ�ƃ��W�F�l�ł���
	int m_Stamina = 100;					//�X�^�~�i
};

