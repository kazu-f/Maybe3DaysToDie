#pragma once

#include "WaveFile.h"

namespace Engine {
	namespace prefab {
		class CSoundSource : public IGameObject
		{
		public:
			CSoundSource();			//�R���X�g���N�^�B
			~CSoundSource();		//�f�X�g���N�^�B
			/// <summary>
			/// �������B
			/// </summary>
			/// <remarks>�I���������Đ������̏������B</remarks>
			/// <param name="filePath">�t�@�C���p�X�B(*.wave)�`��</param>
			/// <param name="is3DSound">3D�T�E���h���H</param>
			void Init(const wchar_t* filePath, bool is3DSound = false);
			/// <summary>
			/// �������B
			/// </summary>
			/// <remarks>�I���������Đ������̏������B������̕���������Ƃ��������B</remarks>
			/// <param name="nameKey">���O�L�[�B</param>
			/// <param name="is3DSound">3D�T�E���h���H</param>
			void Init(const WNameKey& nameKey, bool is3DSound = false);
			/// <summary>
			/// �������B
			/// </summary>
			/// <remarks>�X�g���[�~���O�Đ������̏������B</remarks>
			/// <remarks>
			/// <para>�����O�o�b�t�@�ɃX�g���[�~���O�ǂݍ��݂��s���āA�Đ����s���Ă����܂��B</para>
			/// <para>��x�ɓǂݍ��܂��f�[�^�̍ő�T�C�Y��bufferingSize�B</para>
			/// <para>�ǂݍ��܂ꂽ�f�[�^�̓����O�o�b�t�@�ɃR�s�[����Ă����B</para>
			/// </remarks>
			/// <param name="filePath">�t�@�C���p�X�B(*.wave)�`���B</param>
			/// <param name="is3DSound"></param>
			/// <param name="ringBufferSize"></param>
			/// <param name="bufferingSize"></param>
			void InitStreaming(const wchar_t* filePath,
				bool is3DSound = false,
				unsigned int ringBufferSize = 3 * 1024 * 1024,
				unsigned int bufferingSize = 1024 * 512);
			/// <summary>
			/// ����B
			/// </summary>
			void Release();
			/// <summary>
			/// �Đ��B
			/// </summary>
			/// <param name="isLoop">���[�v�Đ����H</param>
			void Play(bool isLoop);
			/// <summary>
			/// ��~�B
			/// </summary>
			void Stop()
			{
				m_sourceVoice->Stop();
				m_isPlaying = false;
			}
			/// <summary>
			/// �ꎞ��~�B
			/// </summary>
			void Pause()
			{
				m_sourceVoice->Stop();
			}
			/// <summary>
			/// �Đ������H
			/// </summary>
			bool IsPlaying()const
			{
				return m_isPlaying;
			}
			/// <summary>
			/// �{�����[����ݒ�B
			/// </summary>
			/// <param name="vol">�{�����[���B</param>
			void SetVolume(float vol)
			{
				m_sourceVoice->SetVolume(vol);
			}
			/// <summary>
			/// �{�����[�����擾�B
			/// </summary>
			float GetVolume()const
			{
				float vol;
				m_sourceVoice->GetVolume(&vol);
				return vol;
			}
			/// <summary>
			/// �����̍��W��ݒ�B
			/// </summary>
			/// <remarks>
			/// <para>3D�T�E���h�̎��ɕK�v�ɂȂ�B</para>
			/// <para>2D�T�E���h�ł͖��������B</para>
			/// </remarks>
			/// <param name="pos">�����̍��W�B</param>
			void SetPosition(const Vector3& pos)
			{
				m_position = pos;
				if (m_isSetPositionFirst)
				{
					m_lastFramePosition = m_position;
					m_isSetPositionFirst = false;
				}
			}
			/// <summary>
			/// �����̍��W���擾�B
			/// </summary>
			const Vector3& GetPosition()const
			{
				return m_position;
			}
			/// <summary>
			/// �����̈ړ����x���擾�B
			/// </summary>
			const Vector3& GetVelocity()
			{
				return m_velocity;
			}
			/// <summary>
			/// ���ʂ��������鋗�����擾�B
			/// </summary>
			const float GetCurveDistanceScaler()const
			{
				return m_curveDistanceScaler;
			}
			/// <summary>
			/// �h�b�v���[���ʂ̓x�����擾�B
			/// </summary>
			const float GetDopplerScaler()const
			{
				return m_dopplerScaler;
			}
			/// <summary>
			/// ���g������擾�B
			/// </summary>
			const float GetFrequencyRetio()const
			{
				return m_frequencyRetio;
			}
			/// <summary>
			/// ���[�v�t���O���擾�B
			/// </summary>
			bool GetLoopFlag() const
			{
				return m_isLoop;
			}
			/// <summary>
			/// �{�C�X�̎��g��������B
			/// </summary>
			/// <remarks>�ڍׂ�IXAudio2SourceVoice��SetFrequencyRaito���Q�ƁB</remarks>
			/// <param name="raito">���g����</param>
			void SetFrequencyRetio(float raito)
			{
				if (m_sourceVoice != nullptr
					&& !m_is3DSound)
				{
					m_sourceVoice->SetFrequencyRatio(raito);
				}
				else {
					m_frequencyRetio = raito;
				}
			}
			/// <summary>
			/// ���ʂ��������鋗���B
			/// </summary>
			void SetCurveDistanceScaler(float scaler)
			{
				m_curveDistanceScaler = scaler;
			}
			/// <summary>
			/// �h�b�v���[���ʁB
			/// </summary>
			void SetDopplerScaler(float scaler)
			{
				m_dopplerScaler = scaler;
			}
			/// <summary>
			/// �\�[�X�{�C�X���擾�B
			/// </summary>
			IXAudio2SourceVoice* GetXAudio2SourceVoice()
			{
				return m_sourceVoice;
			}
			/// <summary>
			/// ���̓`�����l�������擾�B
			/// </summary>
			int GetNumInputChannel()const
			{
				return m_waveFile->GetFormat()->nChannels;
			}
			/// <summary>
			/// ���̕��ˊp�H
			/// </summary>
			FLOAT32* GetEmitterAzimuths()
			{
				return m_emitterAzimuths;
			}
			/// <summary>
			/// �s��W���H���擾�B
			/// </summary>
			FLOAT32* GetMatrixCoefficients()
			{
				return m_matrixCoefficients;
			}
			/// <summary>
			/// �ݒ�H���擾�B
			/// </summary>
			X3DAUDIO_DSP_SETTINGS* GetDspSettings()
			{
				return &m_dspSettings;
			}
		private:
			void InitCommon();
			//�X�g���[�~���O�Đ����̍X�V�����B
			void UpdateStreaming();
			//�I���������Đ����̍X�V�����B
			void UpdateOnMemory();
			//���𗬂��B
			void PlayCommon(char* buff, unsigned int bufferSize);
			/// <summary>
			/// �X�g���[�~���O�o�b�t�@�����O�̊J�n�B
			/// </summary>
			void StartStreamingBuffering();
			/// <summary>
			/// �폜����B
			/// </summary>
			void Remove3DSound();
			/// <summary>
			/// �X�V�B
			/// </summary>
			void Update()override;

		private:
			enum EnStreamingStatus {
				enStreamingBuffering,		//�o�b�t�@�����O���B
				enStreamingQueueing,		//�L���[�C���O���B
			};
			std::shared_ptr<CWaveFile>	m_waveFile;					//�g�`�f�[�^�B
			IXAudio2SourceVoice*		m_sourceVoice = nullptr;	//�\�[�X�{�C�X�B
			bool						m_isLoop = false;			//���[�v�t���O�B
			bool						m_isPlaying = false;		//�Đ����t���O�B
			bool						m_isStreaming = false;		//�X�g���[�~���O�Đ����H
			unsigned int				m_streamingBufferSize = 0;	//�X�g���[�~���O�p�̃o�b�t�@�����O�T�C�Y�B
			unsigned int				m_currentBufferingSize = 0;	//���݂̃o�b�t�@�����O�̃T�C�Y�B
			unsigned int				m_readStartPos = 0;			//�ǂݍ��݂̊J�n�ʒu�B
			unsigned int				m_ringBufferSize = 0;		//�����O�o�b�t�@�̃T�C�Y�B
			EnStreamingStatus			m_streamingState = enStreamingBuffering;		//�X�g���[�~���O�X�e�[�^�X�B
			bool						m_is3DSound = false;		//3D�T�E���h���H
			Vector3						m_position = Vector3::Zero;	//�����̍��W�B3D�T�E���h�̎��ɕK�v�B
			Vector3						m_lastFramePosition = Vector3::Zero;	//������1�t���[���O�̍��W�B3D�T�E���h�̎��ɕK�v�B
			Vector3						m_velocity = Vector3::Zero;	//���x�B3D�T�E���h�̎��ɕK�v�B
			float						m_curveDistanceScaler = 14.0f;	//���ʂ��������鋗���B
			float						m_dopplerScaler = 0.0f;			//�h�b�v���[���ʁB
			float						m_frequencyRetio = 1.0f;		//���g����H
			FLOAT32 m_emitterAzimuths[INPUTCHANNELS];							//���̕��ˊp�H
			FLOAT32 m_matrixCoefficients[INPUTCHANNELS * OUTPUTCHANNELS];		//�s��W���B
			X3DAUDIO_DSP_SETTINGS		m_dspSettings;				//�ݒ�H
			bool m_isSetPositionFirst = true;						//��ԍŏ���setPosition���H
			bool m_isAvailable = false;								//�C���X�^���X�����p�\���H
		};//class CSoundSource;

	}//namespace prefab;
}//namespace Engine;

