#pragma once
/// <summary>
/// ���Ԃ��v�����A�P���𐔂���N���X
/// �P�����Ƃ̃J�E���g����cpp���̖��O��ԓ��ɂ����`
/// </summary>
class DateTime final : public IGameObject
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
public:
	int GetDay() {
		return m_Day;
	}

	/// <summary>
	/// �z�[�h���ǂ���
	/// </summary>
	/// <returns>�z�[�h�ł����H</returns>
	bool GetHode() const {
		return m_IsHode;
	}

	/// <summary>
	/// �z�[�h���I��������
	/// </summary>
	void FinishHode();
private:
	int m_minit = 0;		//��
	int m_Hours = 0;		//��
	int m_Day = 0;			//��
	float m_Second = 0.0f;	//�b
	CFontRender* m_TimeFont = nullptr;
	bool m_IsHode = false;
};

