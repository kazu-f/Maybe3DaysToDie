#include "stdafx.h"
#include "SoundEngine.h"
#include "SoundSource.h"

namespace Engine {
	namespace prefab {
		CSoundSource::CSoundSource()
		{
			memset(m_emitterAzimuths, 0, sizeof(m_emitterAzimuths));
			memset(m_matrixCoefficients, 0, sizeof(m_matrixCoefficients));
		}
		CSoundSource::~CSoundSource()
		{
			Release();
		}
		void CSoundSource::InitCommon()
		{
			m_dspSettings.SrcChannelCount = INPUTCHANNELS;					//�\�[�X�`�����l�����B
			m_dspSettings.DstChannelCount = SoundEngine().GetNumChannel();	//���݂́H�o�̓`�����l�����B
			m_dspSettings.pMatrixCoefficients = m_matrixCoefficients;		//�s��W���H
			m_dspSettings.pDelayTimes = nullptr;							//�f�B���C�H
			m_dspSettings.DopplerFactor = 1.0f;								//�h�b�v���[���ʁH
			m_dspSettings.LPFDirectCoefficient = 0.821412854f;				//�䐔�l�H
			m_dspSettings.LPFReverbCoefficient = 0.75f;						//���o�[�u�H
			m_dspSettings.ReverbLevel = 0.69114286f;						//���o�[�u���x���H
			m_dspSettings.EmitterToListenerAngle = 0.0f;					//�����̊p�x�H
			m_dspSettings.EmitterToListenerDistance = 10.0f;				//���X�i�[�Ƃ̋����B
			m_dspSettings.EmitterVelocityComponent = 0.0f;					//�ړ����x�B
			m_dspSettings.ListenerVelocityComponent = 0.0f;					//���X�i�[�ړ����x�B
		}
		void CSoundSource::Init(const wchar_t* filePath, bool is3DSound)
		{
			if (SoundEngine().IsAvailable() == false)
			{
				//�T�E���h�G���W�������p�s�B
				ENGINE_MESSAGE_BOX("�T�E���h�G���W�������p�ł��܂���B");
				return;
			}
			m_isAvailable = false;
			m_waveFile = SoundEngine().GetWaveFileBank().FindWaveFile(0, filePath);
			if (!m_waveFile)
			{
				m_waveFile.reset(new CWaveFile);
				bool result = m_waveFile->Open(filePath);
				if (result == false)
				{
					//wave�t�@�C���̓ǂݍ��݂Ɏ��s�B
					SoundEngine().GetWaveFileBank().UnregistWaveFile(0, m_waveFile);
					m_waveFile.reset();
					//���f�B
					return;
				}
				m_waveFile->AllocReadBuffer(m_waveFile->GetSize());		//wave�t�@�C���̃T�C�Y���̓ǂݍ��݃o�b�t�@���m�ۂ���B
				SoundEngine().GetWaveFileBank().RegistWaveFile(0, m_waveFile);		//�o�^�B
				unsigned int dummy;
				m_waveFile->Read(m_waveFile->GetReadBuffer(), m_waveFile->GetSize(), &dummy);
				m_waveFile->ResetFile();
			}

			//�T�E���h�{�C�X�\�[�X���쐬�B
			m_sourceVoice = SoundEngine().CreateXAudio2SourceVoice(m_waveFile.get(), is3DSound);
			if (is3DSound) {
				SoundEngine().Add3DSoundSource(this);
			}
			InitCommon();

			m_is3DSound = is3DSound;
			m_isAvailable = true;
		}
		void CSoundSource::Init(const WNameKey& nameKey, bool is3DSound)
		{
			if (SoundEngine().IsAvailable() == false)
			{
				//�T�E���h�G���W�������p�s�B
				ENGINE_MESSAGE_BOX("�T�E���h�G���W�������p�ł��܂���B");
				return;
			}
			m_isAvailable = false;
			m_waveFile = SoundEngine().GetWaveFileBank().FindWaveFile(0, nameKey);
			if (!m_waveFile) {
				m_waveFile.reset(new CWaveFile);
				m_waveFile->Open(nameKey.GetName());
				SoundEngine().GetWaveFileBank().RegistWaveFile(0, m_waveFile);
				m_waveFile->AllocReadBuffer(m_waveFile->GetSize());		//wave�t�@�C���̃T�C�Y���̓ǂݍ��݃o�b�t�@���m�ۂ���B
				SoundEngine().GetWaveFileBank().RegistWaveFile(0, m_waveFile);
				unsigned int dummy;
				m_waveFile->Read(m_waveFile->GetReadBuffer(), m_waveFile->GetSize(), &dummy);
				m_waveFile->ResetFile();
			}
			//�T�E���h�{�C�X�\�[�X���쐬�B
			m_sourceVoice = SoundEngine().CreateXAudio2SourceVoice(m_waveFile.get(), is3DSound);
			if (is3DSound) {
				SoundEngine().Add3DSoundSource(this);
			}
			InitCommon();

			m_is3DSound = is3DSound;
			m_isAvailable = true;
		}

		void CSoundSource::InitStreaming(const wchar_t* filePath, bool is3DSound, unsigned int ringBufferSize, unsigned int bufferingSize)
		{
			if (SoundEngine().IsAvailable() == false) {
				//�T�E���h�G���W�������p�s�B
				ENGINE_MESSAGE_BOX("�T�E���h�G���W�������p�ł��܂���B");
				return;
			}
			m_isAvailable = false;
			//�X�g���[�~���O��CWaveFile�̎g���܂킵�͂ł��Ȃ��B
			m_waveFile.reset(new CWaveFile);
			m_waveFile->Open(filePath);

			m_isStreaming = true;
			m_streamingBufferSize = bufferingSize;
			m_waveFile->AllocReadBuffer(ringBufferSize);
			m_ringBufferSize = ringBufferSize;
			m_readStartPos = 0;
			m_currentBufferingSize = 0;
			//�T�E���h�{�C�X�\�[�X���쐬�B
			m_sourceVoice = SoundEngine().CreateXAudio2SourceVoice(m_waveFile.get(), is3DSound);
			if (is3DSound) {
				SoundEngine().Add3DSoundSource(this);
			}
			InitCommon();

			m_is3DSound = is3DSound;
			m_isAvailable = true;
		}
		void CSoundSource::Release()
		{
			if (m_isStreaming) {
				if (m_waveFile) {
					m_waveFile->Release();
				}
			}
			if (m_sourceVoice != nullptr) {
				m_sourceVoice->DestroyVoice();
				m_sourceVoice = nullptr;
			}
			Remove3DSound();
			DeleteGO(this);
		}
		void CSoundSource::PlayCommon(char* buff, unsigned int bufferSize)
		{
			XAUDIO2_BUFFER buffer = { 0 };
			buffer.pAudioData = reinterpret_cast<BYTE*>(buff);
			buffer.Flags = XAUDIO2_END_OF_STREAM;	// tell the source voice not to expect any data after this buffer
			buffer.AudioBytes = bufferSize;
			if (m_sourceVoice != nullptr && bufferSize > 0) {
				//�Đ��J�n�B
				if (FAILED(m_sourceVoice->SubmitSourceBuffer(&buffer))) {
					Release();
					ENGINE_LOG("Failed m_sourceVoice->SubmitSourceBuffer");
					return;
				}
			}
		}
		void CSoundSource::StartStreamingBuffering()
		{
			char* readStartBuff = m_waveFile->GetReadBuffer();
			m_readStartPos += m_currentBufferingSize;
			if (m_readStartPos + m_streamingBufferSize >= m_ringBufferSize) {
				//�����O�o�b�t�@�̃T�C�Y�𒴂���B
				//�z����B
				m_readStartPos = 0;
			}
			m_waveFile->ReadAsync(&readStartBuff[m_readStartPos], m_streamingBufferSize, &m_currentBufferingSize);
			m_streamingState = enStreamingBuffering;
		}
		void CSoundSource::Play(bool isLoop)
		{
			if (m_isAvailable == false) {
				return;
			}
			if (m_isPlaying) {
				//�Đ����̂��̂��ĊJ����B
				m_sourceVoice->Start(0);
			}
			else {
				if (m_isStreaming) {
					//�o�b�t�@�����O�J�n�B
					m_waveFile->ResetFile();
					StartStreamingBuffering();
					m_sourceVoice->Start(0, 0);
				}
				else {
					m_sourceVoice->FlushSourceBuffers();
					m_sourceVoice->Start(0);
					PlayCommon(m_waveFile->GetReadBuffer(), m_waveFile->GetSize());
				}
				m_isPlaying = true;
			}
			m_isLoop = isLoop;
		}
		void CSoundSource::UpdateStreaming()
		{
			if (!m_isPlaying) {
				return;
			}
			if (m_streamingState == enStreamingBuffering) {
				//�o�b�t�@�����O���B
				if (m_waveFile->IsReadEnd()) {
					//�o�b�t�@�����O���I������B
					m_streamingState = enStreamingQueueing;
				}
			}
			if (m_streamingState == enStreamingQueueing) {
				//�L���[�C���O���B
				XAUDIO2_VOICE_STATE state;
				m_sourceVoice->GetState(&state);
				if (state.BuffersQueued <= 2) {		//�L���[�C���O����Ă���o�b�t�@��2�ȉ��ɂȂ�����L���[�C���O�B
					char* buff = m_waveFile->GetReadBuffer();
					PlayCommon(&buff[m_readStartPos], m_currentBufferingSize);
					if (m_currentBufferingSize == 0) {
						//�ǂݍ��񂾃T�C�Y��0�Ȃ疖�[�܂œǂݍ��݂��I������B
						if (m_isLoop) {
							//���[�v����H
							//wave�t�@�C���̓ǂݍ��݈ʒu�����Z�b�g���ăo�b�t�@�����O�ĊJ�B
							m_waveFile->ResetFile();
							StartStreamingBuffering();
						}
						else {
							//���[�v���Ȃ��ꍇ�̓L���[����ɂȂ������_�ōĐ��I���B
							if (state.BuffersQueued == 0) {
								//�Đ��I���B
								m_isPlaying = false;
								DeleteGO(this);
								Remove3DSound();
							}
						}
					}
					else {
						//�����o�b�t�@�����O����B
						StartStreamingBuffering();
					}
				}
			}
		}
		void CSoundSource::Remove3DSound()
		{
			if (m_is3DSound) {
				SoundEngine().Remove3DSoundSource(this);
				m_is3DSound = false;
			}
		}
		void CSoundSource::UpdateOnMemory()
		{
			if (!m_isPlaying) {
				return;
			}
			XAUDIO2_VOICE_STATE state;

			m_sourceVoice->GetState(&state);
			if (state.BuffersQueued <= 0) {
				m_isPlaying = false;
				if (m_isLoop) {
					//���[�v�B
					Play(m_isLoop);
				}
				else {
					DeleteGO(this);
					Remove3DSound();
				}
			}
		}
		void CSoundSource::Update()
		{
			if (m_isAvailable == false) {
				return;
			}

			if (m_isStreaming) {
				//�X�g���[�~���O�Đ����̍X�V�B
				UpdateStreaming();
			}
			else {
				//�I���������Đ����̍X�V�����B
				UpdateOnMemory();
			}
			if (m_is3DSound == true) {
				//�����̈ړ����x���X�V�B
				m_velocity.Subtract(m_position, m_lastFramePosition);
				m_velocity.Div(GameTime().GetFrameDeltaTime());
				m_lastFramePosition = m_position;
			}
		}
	}
}
