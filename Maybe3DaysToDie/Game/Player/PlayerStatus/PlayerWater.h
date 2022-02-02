#pragma once

class Player;
class PlayerWater final : public IGameObject
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
	/// ���݂̐����X�v���C�g��������
	/// </summary>
	void CurretSpriteInit();

	/// <summary>
	/// �����t���[����������
	/// </summary>
	void FlameSpriteInit();

public:
	void SetPlayer(Player* pp){
		m_Player = pp;
	}
private:
	prefab::CSpriteRender* m_CurrentWaterSprite = nullptr;	//���݂̐����̃X�v���C�g
	prefab::CSpriteRender* m_FlameWaterSprite = nullptr;	//�����̘g�̃X�v���C�g
	float m_WaterCountTime = 0.0f;							//�o�ߎ���
	float m_DecWaterTime = 1.0f;							//�A����������
	int m_Water = 100;										//����
	int m_MaxWater = 100;									//�����̍ő��
	Player* m_Player = nullptr;
};

