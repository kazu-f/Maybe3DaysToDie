#pragma once

namespace Engine {

	class CFade
	{
	public:
		CFade();
		~CFade();
		/// <summary>
		/// �����������B
		/// </summary>
		void Init();
		/// <summary>
		/// �X�V�����B
		/// </summary>
		void Update();
		/// <summary>
		/// �t�F�[�h�̕`����s���B
		/// </summary>
		void FadeRender(RenderContext& rc);
		/// <summary>
		/// �`�掖�O�����B
		/// </summary>
		void BeginRender(RenderContext& rc);
		/// <summary>
		/// �`��㏈���B
		/// </summary>
		void EndRender(RenderContext& rc);
		/// <summary>
		/// �t�F�[�h�C�����J�n����B
		/// </summary>
		void StartFadeIn()
		{
			m_state = enState_fadeIn;
		}
		/// <summary>
		/// �t�F�[�h�A�E�g���J�n����B
		/// </summary>
		void StartFadeOut()
		{
			m_state = enState_fadeOut;
		}
		/// <summary>
		/// �t�F�[�h�����ǂ����B
		/// </summary>
		/// <returns></returns>
		bool IsFade()
		{
			return m_state != enState_idle;
		}
		/// <summary>
		/// �t�F�[�h�̎��Ԃ�ݒ肷��B
		/// </summary>
		void SetFadeTime(const float fadeTime)
		{
			//0�������̂��߂ɍŒ�l��0.2�b�ɂ��Ă����B
			m_fadeTime = max(0.2f, fadeTime);
		}
		/// <summary>
		/// ���݂̃t�F�[�h�̐i�s�����擾�B
		/// </summary>
		const float GetFadeRate()
		{
			return 1.0f - m_currentAlpha;
		}

		static CFade* GetInstance()
		{
			return m_instance;
		}
	private:
		static CFade* m_instance;
	private:
		enum EnFadeState {
			enState_fadeIn,		//!<�t�F�[�h�C�����B
			enState_fadeOut,	//!<�t�F�[�h�A�E�g���B
			enState_idle		//!<�A�C�h�����B
		};
		Sprite m_sprite;						//�X�v���C�g�B
		EnFadeState m_state = enState_idle;		//��ԁB
		float m_currentAlpha = 1.0f;			//���݂̃��l�B
		float m_fadeTime = 1.0f;				//�t�F�[�h���s������(�b)�B
	};

}
