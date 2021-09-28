#include "stdafx.h"
#include "SoundEngine.h"
#include "WaveFile.h"
#include "SoundSource.h"

#define NUM_PRESETS 30				//�v���Z�b�g�̐��B
namespace Engine {

	namespace {
		//�}�C�N���\�t�g�̃T���v��������������Ă����T�E���h�R�[���B
		
		//�T�E���h�R�[�����w�肵�āA�|�p�I�Ȍ��ʂ̂��߂Ƀ��X�i�[�ɕ�������ǉ����܂��B
		//���X�i�[�̔w��ɂ���G�~�b�^�[�́A�����ł�茸������悤�ɒ�`����Ă��܂��B
		//LPF�J�b�g�I�t���g�����Ⴍ�A
		//�܂������������o�[�u�Z���h���x��������܂��B
		static const X3DAUDIO_CONE Listener_DirectionalCone = { X3DAUDIO_PI * 5.0f / 6.0f, X3DAUDIO_PI * 11.0f / 6.0f, 1.0f, 0.75f, 0.0f, 0.25f, 0.708f, 1.0f };

		//��葁�����[���I�t����悤��LFE���x���̋����Ȑ����w�肵�܂�
		//���ׂĂ̔�LFE�`�����l���A�T�u�E�[�t�@�[����茀�I�ɗ��p���܂��B
		static const X3DAUDIO_DISTANCE_CURVE_POINT Emitter_LFE_CurvePoints[3] = { 0.0f, 1.0f, 0.25f, 0.0f, 1.0f, 0.0f };
		static const X3DAUDIO_DISTANCE_CURVE       Emitter_LFE_Curve = { (X3DAUDIO_DISTANCE_CURVE_POINT*)&Emitter_LFE_CurvePoints[0], 3 };

		//���o�[�u�Z���h����������悤�Ƀ��o�[�u�Z���h���x���̋����J�[�u���w�肵�܂�
		//����������u���Ă���A���[���I�t���Ė����ɂ��܂��B
		//���ڃ`���l���͋����ƂƂ��ɂ܂��܂��������A
		//����ɂ́A���o�[�u�ƃ_�C���N�g�̃T�E���h����グ����ʂ�����܂��B
		//�����̔F�����������܂��B
		static const X3DAUDIO_DISTANCE_CURVE_POINT Emitter_Reverb_CurvePoints[3] = { 0.0f, 0.5f, 0.75f, 1.0f, 1.0f, 0.0f };
		static const X3DAUDIO_DISTANCE_CURVE       Emitter_Reverb_Curve = { (X3DAUDIO_DISTANCE_CURVE_POINT*)&Emitter_Reverb_CurvePoints[0], 3 };

		XAUDIO2FX_REVERB_I3DL2_PARAMETERS PRESET_PARAMS[NUM_PRESETS] =
		{
			XAUDIO2FX_I3DL2_PRESET_FOREST,
			XAUDIO2FX_I3DL2_PRESET_DEFAULT,
			XAUDIO2FX_I3DL2_PRESET_GENERIC,
			XAUDIO2FX_I3DL2_PRESET_PADDEDCELL,
			XAUDIO2FX_I3DL2_PRESET_ROOM,
			XAUDIO2FX_I3DL2_PRESET_BATHROOM,
			XAUDIO2FX_I3DL2_PRESET_LIVINGROOM,
			XAUDIO2FX_I3DL2_PRESET_STONEROOM,
			XAUDIO2FX_I3DL2_PRESET_AUDITORIUM,
			XAUDIO2FX_I3DL2_PRESET_CONCERTHALL,
			XAUDIO2FX_I3DL2_PRESET_CAVE,
			XAUDIO2FX_I3DL2_PRESET_ARENA,
			XAUDIO2FX_I3DL2_PRESET_HANGAR,
			XAUDIO2FX_I3DL2_PRESET_CARPETEDHALLWAY,
			XAUDIO2FX_I3DL2_PRESET_HALLWAY,
			XAUDIO2FX_I3DL2_PRESET_STONECORRIDOR,
			XAUDIO2FX_I3DL2_PRESET_ALLEY,
			XAUDIO2FX_I3DL2_PRESET_CITY,
			XAUDIO2FX_I3DL2_PRESET_MOUNTAINS,
			XAUDIO2FX_I3DL2_PRESET_QUARRY,
			XAUDIO2FX_I3DL2_PRESET_PLAIN,
			XAUDIO2FX_I3DL2_PRESET_PARKINGLOT,
			XAUDIO2FX_I3DL2_PRESET_SEWERPIPE,
			XAUDIO2FX_I3DL2_PRESET_UNDERWATER,
			XAUDIO2FX_I3DL2_PRESET_SMALLROOM,
			XAUDIO2FX_I3DL2_PRESET_MEDIUMROOM,
			XAUDIO2FX_I3DL2_PRESET_LARGEROOM,
			XAUDIO2FX_I3DL2_PRESET_MEDIUMHALL,
			XAUDIO2FX_I3DL2_PRESET_LARGEHALL,
			XAUDIO2FX_I3DL2_PRESET_PLATE,
		};
	}

	CSoundEngine::CSoundEngine()
	{
		memset(m_hx3DAudio, 0, sizeof(m_hx3DAudio));
	}

	CSoundEngine::~CSoundEngine()
	{
		Release();
	}
	void CSoundEngine::Init()
	{
		//Com�R���|�[�l���g�̏������B
		//COM�̃X���b�h�Ԃ̓������̐ݒ�B
		CoInitializeEx(NULL, COINIT_MULTITHREADED);
		unsigned int flags = 0;		//�t���O�B

		HRESULT hr;

		//XAUDIO2���������B
		{
			if (FAILED(hr = XAudio2Create(&m_xAudio2, flags)))
			{
				ENGINE_MESSAGE_BOX(
					"Faild XAudio2Create\n"
					"�I�[�f�B�I�f�o�C�X�̏������Ɏ��s���܂����B"
				);
					return;
			}
			if (FAILED(hr = m_xAudio2->CreateMasteringVoice(&m_masteringVoice)))
			{
				Release();
				ENGINE_MESSAGE_BOX(
					"Faild CreateMesteringVoice\n"
					"�I�[�f�B�I�f�o�C�X�̏������Ɏ��s���܂����B"
				);
				return;
			}
		}
		XAUDIO2_VOICE_DETAILS voiceDetails;
		m_masteringVoice->GetVoiceDetails(&voiceDetails);
		m_masteringVoice->GetChannelMask(&m_channelMask);

		m_nChannels = voiceDetails.InputChannels;

		//���o�[�u�G�t�F�N�g���쐬�B
		{
			flags = 0;
			if (FAILED(hr = XAudio2CreateReverb(&m_reverbEffect, flags)))
			{
				Release();
				ENGINE_MESSAGE_BOX(
					"Faild XAudio2CreateReverb\n"
					"�I�[�f�B�I�f�o�C�X�̏������Ɏ��s���܂����B"
				);
				return;
			}
		}
		//�T�u�~�b�N�X�{�C�X���쐬�B
		{
			XAUDIO2_EFFECT_DESCRIPTOR effects[] = { {m_reverbEffect,TRUE,1} };
			XAUDIO2_EFFECT_CHAIN effectChain = { 1,effects };

			if (FAILED(hr = m_xAudio2->CreateSubmixVoice(&m_submixVoice, voiceDetails.InputChannels,
				voiceDetails.InputSampleRate, 0, 0, NULL, &effectChain)))
			{
				Release();
				ENGINE_MESSAGE_BOX(
					"Faild CreateSubmixVoice\n"
					"�I�[�f�B�I�f�o�C�X�̏������Ɏ��s���܂����B"
				);
				return;
			}
		}
		//�f�t�H���g��FX�p�����[�^��ݒ�B
		XAUDIO2FX_REVERB_PARAMETERS native;
		ReverbConvertI3DL2ToNative(&PRESET_PARAMS[0], &native);
		m_submixVoice->SetEffectParameters(0, &native, sizeof(native));
		//3D�I�[�f�B�I�̏������B
		const float SPEEDFSOUND = X3DAUDIO_SPEED_OF_SOUND;
		X3DAudioInitialize(m_channelMask, SPEEDFSOUND, m_hx3DAudio);
		m_listener.Position = { 0.0f,0.0f,0.0f };		//�I�[�f�B�I���X�i�[�̍��W�B
		m_listener.OrientFront = { 0.0f,0.0f,1.0f };	//�I�[�f�B�I���X�i�[�̑O�����B
		m_listener.OrientTop = { 0.0f,1.0f,0.0f };		//�I�[�f�B�I���X�i�[�̏�����B

		//�����������B
		m_isInited = true;
	}
	void CSoundEngine::Release()
	{
		//ToDO�g�`�f�[�^���o���N����B

		if (m_submixVoice != nullptr)
		{
			m_submixVoice->DestroyVoice();
			m_submixVoice = nullptr;
		}
		if (m_reverbEffect != nullptr)
		{
			m_reverbEffect->Release();
			m_reverbEffect = nullptr;
		}
		if (m_masteringVoice != nullptr)
		{
			m_masteringVoice->DestroyVoice();
			m_masteringVoice = nullptr;
		}		
		if (m_xAudio2 != nullptr)
		{
			m_xAudio2->Release();
			m_xAudio2 = nullptr;
		}
		//COM�̉���B
		CoUninitialize();
	}
	IXAudio2SourceVoice* CSoundEngine::CreateXAudio2SourceVoice(CWaveFile* waveFile, bool is3DSound)
	{
		ENGINE_ASSERT(waveFile->GetFormat()->nChannels <= INPUTCHANNELS, "Channel over");
		IXAudio2SourceVoice* pSourceVoice;
		if (is3DSound == false)
		{
			//2D�T�E���h�B
			if (FAILED(m_xAudio2->CreateSourceVoice(&pSourceVoice, waveFile->GetFormat())))
			{
				ENGINE_WARNING_LOG("Failed CreateSourceVoice");
				return nullptr;
			}
		}
		else {
			//3D�T�E���h�B
			XAUDIO2_SEND_DESCRIPTOR sendDescriptors[2];
			sendDescriptors[0].Flags = XAUDIO2_SEND_USEFILTER; // LPF direct-path
			sendDescriptors[0].pOutputVoice = m_masteringVoice;
			sendDescriptors[1].Flags = XAUDIO2_SEND_USEFILTER; // LPF reverb-path -- omit for better performance at the cost of less realistic occlusion
			sendDescriptors[1].pOutputVoice = m_submixVoice;

			const XAUDIO2_VOICE_SENDS sendList = { 2,sendDescriptors };
			if (FAILED(m_xAudio2->CreateSourceVoice(&pSourceVoice, waveFile->GetFormat(), 0, 2.0f, NULL, &sendList)))
			{
				ENGINE_WARNING_LOG("Failed CreateSourceVoice");
				return nullptr;
			}
		}

		return pSourceVoice;
	}

	void CSoundEngine::Update()
	{
		if (!m_isInited) {
			return;
		}
		//�T�E���h���X�i�[�̑O�������v�Z�B
		//@todo ������ւ��SoundListener�N���X�Ɍ�ňړ�������B
		//@todo �O�����̌v�Z�����ꂾ�Ɠs���������B
		if (m_listener.Position.x != m_listenerPosition.x
			|| m_listener.Position.z != m_listenerPosition.z
			) {
			//���X�i�[��XZ���ʏ�œ����Ă���B
			Vector3 listenerPos;
			listenerPos.Set(m_listener.Position);
			//�����������v�Z�B
			Vector3 vDelta;
			vDelta.Subtract(m_listenerPosition, listenerPos);
			m_fListenerAngle = float(atan2(m_listener.OrientFront.x, m_listener.OrientFront.z));

			if (m_UseListenerCone == true) {
				m_listener.pCone = (X3DAUDIO_CONE*)&Listener_DirectionalCone;
			}
			else {
				m_listener.pCone = NULL;
			}
		}
		float deltaTime = GameTime().GetFrameDeltaTime();
		if (deltaTime > 0.0f) {
			//���X�i�[�̈ړ����x���v�Z����B
			Vector3 vel;
			vel.Set(m_listener.Position);
			vel.Subtract(m_listenerPosition, vel);
			vel.Div(deltaTime);
			m_listenerPosition.CopyTo(m_listener.Position);
			vel.CopyTo(m_listener.Velocity);
			//if (vel.LengthSq() > 0.01f) {
			//	vel.Normalize();
			//	vel.CopyTo(m_listener.OrientFront);
			//}
		}
		DWORD dwCalcFlags = X3DAUDIO_CALCULATE_MATRIX | X3DAUDIO_CALCULATE_DOPPLER
			| X3DAUDIO_CALCULATE_LPF_DIRECT | X3DAUDIO_CALCULATE_LPF_REVERB
			| X3DAUDIO_CALCULATE_REVERB;
		if (m_useRedirectToLFE)
		{
			// On devices with an LFE channel, allow the mono source data
			// to be routed to the LFE destination channel.
			dwCalcFlags |= X3DAUDIO_CALCULATE_REDIRECT_TO_LFE;
		}

		//3D�T�E���h�̌v�Z�B
		for (auto& soundSource : m_3dSoundSource) {
			if (!soundSource->IsPlaying())continue;

			X3DAUDIO_EMITTER emitter;

			emitter.pCone = &m_emitterCone;
			emitter.pCone->InnerAngle = 0.0f;
			// Setting the inner cone angles to X3DAUDIO_2PI and
			// outer cone other than 0 causes
			// the emitter to act like a point emitter using the
			// INNER cone settings only.
			emitter.pCone->OuterAngle = 0.0f;
			// Setting the outer cone angles to zero causes
			// the emitter to act like a point emitter using the
			// OUTER cone settings only.
			emitter.pCone->InnerVolume = 0.0f;
			emitter.pCone->OuterVolume = 1.0f;
			emitter.pCone->InnerLPF = 0.0f;
			emitter.pCone->OuterLPF = 1.0f;
			emitter.pCone->InnerReverb = 0.0f;
			emitter.pCone->OuterReverb = 1.0f;


			emitter.OrientFront = { 0, 0, 1 };
			emitter.OrientTop = { 0, 1, 0 };
			soundSource->GetPosition().CopyTo(emitter.Position);
			soundSource->GetVelocity().CopyTo(emitter.Velocity);

			// Use of Inner radius allows for smoother transitions as
			// a sound travels directly through, above, or below the listener.
			// It also may be used to give elevation cues.
			emitter.InnerRadius = 2.0f;
			emitter.InnerRadiusAngle = X3DAUDIO_PI / 4.0f;
			
			emitter.ChannelCount = INPUTCHANNELS;
			emitter.ChannelRadius = 1.0f;
			emitter.pChannelAzimuths = soundSource->GetEmitterAzimuths();


			emitter.pVolumeCurve = (X3DAUDIO_DISTANCE_CURVE*)&X3DAudioDefault_LinearCurve;
			emitter.pLFECurve = (X3DAUDIO_DISTANCE_CURVE*)&Emitter_LFE_Curve;
			emitter.pLPFDirectCurve = NULL; // use default curve
			emitter.pLPFReverbCurve = NULL; // use default curve
			emitter.pReverbCurve = (X3DAUDIO_DISTANCE_CURVE*)&Emitter_Reverb_Curve;
			//�������鋗���ɔ�Ⴗ��
			emitter.CurveDistanceScaler = soundSource->GetCurveDistanceScaler();
			//�h�b�v���[���ʂ̓x����
			emitter.DopplerScaler = soundSource->GetDopplerScaler();


			X3DAUDIO_DSP_SETTINGS* dspSettings = soundSource->GetDspSettings();
			X3DAudioCalculate(m_hx3DAudio, &m_listener, &emitter, dwCalcFlags,
				dspSettings);
			IXAudio2SourceVoice* voice = soundSource->GetXAudio2SourceVoice();
			if (voice != nullptr)
			{
				// Apply X3DAudio generated DSP settings to XAudio2
				voice->SetFrequencyRatio(soundSource->GetFrequencyRetio() * dspSettings->DopplerFactor);
				voice->SetOutputMatrix(m_masteringVoice, soundSource->GetNumInputChannel(), m_nChannels,
					soundSource->GetMatrixCoefficients());

				voice->SetOutputMatrix(m_submixVoice, soundSource->GetNumInputChannel(), 1, &dspSettings->ReverbLevel);

				XAUDIO2_FILTER_PARAMETERS FilterParametersDirect = { LowPassFilter, 2.0f * sinf(X3DAUDIO_PI / 6.0f * dspSettings->LPFDirectCoefficient), 1.0f }; // see XAudio2CutoffFrequencyToRadians() in XAudio2.h for more information on the formula used here
				voice->SetOutputFilterParameters(m_masteringVoice, &FilterParametersDirect);
				XAUDIO2_FILTER_PARAMETERS FilterParametersReverb = { LowPassFilter, 2.0f * sinf(X3DAUDIO_PI / 6.0f * dspSettings->LPFReverbCoefficient), 1.0f }; // see XAudio2CutoffFrequencyToRadians() in XAudio2.h for more information on the formula used here
				voice->SetOutputFilterParameters(m_submixVoice, &FilterParametersReverb);
			}
		}

	}
}
