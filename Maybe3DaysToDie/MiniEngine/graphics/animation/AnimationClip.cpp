#include "MiniEngine.h"
#include "AnimationClip.h"

namespace Engine {
	CAnimationClip::~CAnimationClip()
	{
	}
	void CAnimationClip::Load(const char* filePath)
	{
		//TODO:tka�t�@�C���ǂݍ��݂̃t���C�E�F�C�g?
		m_tkaFile.Load(filePath);
		if (m_tkaFile.IsLoaded() == false)
		{
			ENGINE_MESSAGE_BOX(
				"�A�j���[�V�����N���b�v�̃��[�h�Ɏ��s\n"
				"%s\n"
				"�t�@�C���p�X���m�F���Ă��������B",
				filePath
			);
			return;
		}
		//���[�h�ς݁B
		m_isLoaded = true;
	}
	void CAnimationClip::BuildKeyFramesAndAnimationEvents()
	{
		//�A�j���[�V�����C�x���g�̍\�z�B
		{
			auto numAnimEvent = m_tkaFile.GetNumAnimationEvent();
			if (numAnimEvent > 0)
			{
				m_animationEvent = std::make_unique<CAnimationEvent[]>(numAnimEvent);
				int eventNo = 0;
				m_tkaFile.QueryAnimationEvents([&](const TkaFile::AnimationEvent& animEvent) {
					static wchar_t wEventName[256];
					//�C�x���g�������C�h�^������ɕϊ��B
					mbstowcs(wEventName, animEvent.eventName.c_str(), 255);
					m_animationEvent[eventNo].SetInvokeTime(animEvent.invokeTime);
					m_animationEvent[eventNo].SetEventName(wEventName);
					eventNo++;
					});
			}
		}

		//�L�[�t���[�����̍\�z�B
		{
			m_keyframes.reserve(m_tkaFile.GetNumKeyFrame());
			m_tkaFile.QueryKeyFrames([&](const TkaFile::KeyFrame& tkaKeyFrame) {
			auto keyframe = std::make_unique<KeyFrame>();
			//�L�[�t���[���̏��̃R�s�[�B
			keyframe->boneIndex = tkaKeyFrame.boneIndex;
			keyframe->transform = Matrix::Identity;
			keyframe->time = tkaKeyFrame.time;
			for (auto j = 0; j < 4; j++) {
				//�x�N�g������s��ɕϊ��B
				keyframe->transform.m[j][0] = tkaKeyFrame.transform[j].x;
				keyframe->transform.m[j][1] = tkaKeyFrame.transform[j].y;
				keyframe->transform.m[j][2] = tkaKeyFrame.transform[j].z;
			}
			//�L�[�t���[�����X�g�ɐςށB
			m_keyframes.push_back(std::move(keyframe));
			});
		}
		//�{�[���C���f�b�N�X���Ƃ̃L�[�t���[���̘A�����X�g���쐬�B
		{
			m_keyFramePtrListArray.resize(MAX_BONE);
			for (auto& keyframe : m_keyframes) {
				//�{�[���ԍ����ƂɊ���U��B
				m_keyFramePtrListArray[keyframe->boneIndex].push_back(keyframe.get());
				if (m_topBoneKeyFrameList == nullptr) {
					//��ԏ�̃{�[���̃L�[�t���[�����X�g�B
					m_topBoneKeyFrameList = &m_keyFramePtrListArray[keyframe->boneIndex];
				}
			}
		}
	}
}