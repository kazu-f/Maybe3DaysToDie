
/// <summary>
/// �T�E���h�G���W��
/// </summary>

#pragma once
#include "WaveFileBank.h"

#define INPUTCHANNELS 2		//���̓`�����l�����B
#define OUTPUTCHANNELS 8	//�ő�o�̓`�����l�����B
namespace Engine {
	class CWaveFile;
	namespace prefab {
		class CSoundSource;
	}
	/// <summary>
	/// �T�E���h�G���W���N���X�B
	/// </summary>
	class CSoundEngine : Noncopyable
	{
	public:
		CSoundEngine();		//�R���X�g���N�^�B
		~CSoundEngine();	//�f�X�g���N�^�B
		/// <summary>
		/// �������B
		/// </summary>
		void Init();
		/// <summary>
		/// ����B
		/// </summary>
		void Release();
		/// <summary>
		/// �X�V�B
		/// </summary>
		void Update();

		//TODO�T�E���h�\�[�X�֘A�B
		/// <summary>
		/// 3D�T�E���h�\�[�X��ǉ��B
		/// </summary>
		void Add3DSoundSource(prefab::CSoundSource* sound)
		{
			m_3dSoundSource.push_back(sound);
		}
		/// <summary>
		/// 3D�T�E���h�\�[�X������B
		/// </summary>
		void Remove3DSoundSource(prefab::CSoundSource* sound)
		{
			auto it = std::find(m_3dSoundSource.begin(), m_3dSoundSource.end(), sound);
			if (it != m_3dSoundSource.end())
			{
				m_3dSoundSource.erase(it);
			}
		}
		/// <summary>
		/// �T�E���h���X�i�[�̍��W��ݒ�B
		/// </summary>
		/// <remarks>3D�������g���Ă���Ƃ��̌v�Z�Ɏg����B</remarks>
		/// <param name="pos">���W�B</param>
		void SetListenerPosition(const Vector3& pos)
		{
			m_listenerPosition = pos;
		}
		/// <summary>
		/// �T�E���h���X�i�[�̑O������ݒ�B
		/// </summary>
		/// <remarks>3D�������g���Ă���Ƃ��̌v�Z�Ɏg����B</remarks>
		/// <param name="front">�O�����x�N�g���B</param>
		void SetListenerFront(const Vector3& front)
		{
			m_listener.OrientFront.x = front.x;
			m_listener.OrientFront.y = front.y;
			m_listener.OrientFront.z = front.z;
		}
		/// <summary>
		/// �T�E���h���X�i�[�̏������ݒ�B
		/// </summary>
		/// <remarks>3D�������g���Ă���Ƃ��̌v�Z�Ɏg����B</remarks>
		/// <param name="up">������x�N�g���B</param>
		void SetListenerUp(const Vector3& up)
		{
			m_listener.OrientTop.x = up.x;
			m_listener.OrientTop.y = up.y;
			m_listener.OrientTop.z = up.z;
		}
		//XAudio2�̃\�[�X�{�C�X���쐬�B
		IXAudio2SourceVoice* CreateXAudio2SourceVoice(CWaveFile* waveFile, bool is3DSound);

		/// <summary>
		/// �}�X�^�[�{�C�X���擾�B
		/// </summary>
		IXAudio2MasteringVoice* GetMasteringVoice()
		{
			return m_masteringVoice;
		}
		/// <summary>
		/// �T�u�~�b�N�X�{�C�X�B
		/// </summary>
		IXAudio2SubmixVoice* GetSubmixVoice()
		{
			return m_submixVoice;
		}
		/// <summary>
		/// �o�̓`�����l���̐����擾�B
		/// </summary>
		int GetNumChannel()const
		{
			return m_nChannels;
		}
		//�g�`�f�[�^�o���N���擾�B
		CWaveFileBank& GetWaveFileBank()
		{
			return m_waveFileBank;
		}
		/// <summary>
		/// �T�E���h�G���W�������p�\���ǂ�������B
		/// </summary>
		/// <remarks>true���Ԃ��Ă����痘�p�\�B</remarks>
		bool IsAvailable()const
		{
			return m_isInited;
		}

	private:
		IXAudio2* m_xAudio2 = nullptr;							//XAudio
		IXAudio2MasteringVoice* m_masteringVoice = nullptr;		//�}�X�^�[�{�C�X�B
																//�\�[�X�{�C�X�ƃT�u�~�b�N�X�{�C�X�̏o�͂�
																//���ׂĂ܂Ƃ߂ăT�E���h�J�[�h�֑���@�\�����B
		X3DAUDIO_HANDLE m_hx3DAudio;							//3D�I�[�f�B�I�̃n���h���B
		IUnknown* m_reverbEffect = nullptr;						//���o�[�u�G�t�F�N�g�B
		IXAudio2SubmixVoice* m_submixVoice = nullptr;			//�T�u�~�b�N�X�{�C�X�B
																//�֘A�t���������̃\�[�X�{�C�X�̏o�͂�
																//�܂Ƃ߂ăG�t�F�N�g���|����@�\�����B
		DWORD m_channelMask = 0;								//�I�[�f�B�I�`�����l���}�X�N�B
		DWORD m_nChannels = 0;									//�`�����l�����B�X�e���Ior���m����???
		Vector3 m_listenerPosition = Vector3::Zero;				//�I�[�f�B�I���X�i�[�̍��W�B
		float m_fListenerAngle = 0.0f;							//���X�i�[�̌����H
		bool m_UseListenerCone = false;
		bool m_fUseInnerRadius = false;
		bool m_useRedirectToLFE = false;
		bool m_isInited = false;								//�������ς݁H
		X3DAUDIO_LISTENER m_listener;							//�T�E���h���X�i�[�B
		std::list<prefab::CSoundSource*>	m_3dSoundSource;	//3D�T�E���h�̃T�E���h�\�[�X�B
		X3DAUDIO_CONE m_emitterCone;							//�G�~�b�^�[�R�[���H
		CWaveFileBank m_waveFileBank;							//�g�`�f�[�^�̃o���N�B
	};///class CSoungEngine;

}///namespace Engine;

