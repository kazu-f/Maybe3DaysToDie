#include "MiniEngine.h"
#include "ModelRender.h"

namespace Engine {
	namespace prefab {
		bool ModelRender::Start()
		{
			bool inited = false;
			switch (m_initStatus)
			{
			case enInitStatus_NotCallInitFunc:
				//�������֐����܂��Ă΂�Ă��Ȃ��B
				break;
			case enInitStatus_WaitInitModel:	//���f����Init�����҂��B
				if (m_model.IsInited()) {
					std::string skeletonFilePath = m_tkmFilePath;
					int pos = static_cast<int>(skeletonFilePath.find(".tkm"));
					skeletonFilePath.replace(pos, 4, ".tks");
					std::ifstream ifs(skeletonFilePath.c_str());
					if (ifs.is_open()) {
						//tks�t�@�C��������B
						m_skeleton.Init(skeletonFilePath.c_str());
						m_initStatus = enInitStatus_WaitInitSkeleton;
					}
					else {
						//�Ȃ��B
						m_initStatus = enInitStatus_Completed;
					}
				}
				break;
			case enInitStatus_WaitInitSkeleton:
				if (m_skeleton.IsLoaded())
				{
					m_skeleton.BuildBoneMatrices();
					//�X�P���g�������f���Ɗ֘A�t���B�B
					m_model.BindSkeleton(m_skeleton);
					if (m_animClipInitDatas.empty() == false)
					{
						//�A�j���[�V�����̃f�[�^�����邩�B
						for (auto& initData : m_animClipInitDatas)
						{
							auto animClip = std::make_unique<CAnimationClip>();
							animClip->Load(initData.tkaFilePath.c_str());
							m_animClips.push_back(std::move(animClip));
						}
						m_initStatus = enInitStatus_WaitInitAnimationClips;
					}
					else {
						//�Ȃ��B
						m_initStatus = enInitStatus_Completed;
					}
				}
				break;
			case enInitStatus_WaitInitAnimationClips:{
				bool isLoaded = true;
				for (auto& animClip : m_animClips) {
					if (animClip->IsLoaded() == false) {
						//�A�j���[�V�����̃��[�h���܂��ł��Ă��Ȃ��B
						isLoaded = false;
						break;
					}
				}
				if (isLoaded) {
					//�A�j���[�V�����N���b�v���S�����[�h�ł����B
					//�L�[�t���[���Ƃ��A�j���[�V�����C�x���g�̐ݒ�Ƃ��B
					for (int i = 0; i < static_cast<int>(m_animClips.size()); i++) {
						m_animClips[i]->SetLoopFlag(m_animClipInitDatas[i].isLoop);
						m_animClips[i]->BuildKeyFramesAndAnimationEvents();
					}
					//�A�j���[�V�������������B
					m_animation.Init(m_skeleton, m_animClips);
					m_initStatus = enInitStatus_Completed;
				}
			}	break;
			
			case enInitStatus_Completed:
				//�����������B
				inited = true;
				break;
			}

			return inited;
		}
		void ModelRender::OnDestroy()
		{
			//�V���h�E�L���X�^�[�o�^����������B
			auto& shadowMap = GraphicsEngine()->GetShadowMap();
			shadowMap->RemoveShadowCaster(&m_model);
		}
		void ModelRender::Update()
		{
			if (m_animation.IsInited()) {
				//�A�j���[�V�������Đ��B
				m_animation.Progress(GameTime().GetFrameDeltaTime());
			}

			//���f�����X�V�B
			if (!m_model.IsInstancing()) {
				m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
			}

			if (m_skeleton.IsInited()) {
				//�X�P���g�����X�V�B
				if (m_model.IsInstancing()) {
					m_skeleton.Update(g_matIdentity);
				}
				else {
					m_skeleton.Update(m_model.GetWorldMatrix());
				}
			}

		}
		void ModelRender::PreRender(RenderContext& rc)
		{
			if (m_isShadowCaster)
			{
				//�V���h�E�L���X�^�[�ɓo�^����B
				auto& shadowMap = GraphicsEngine()->GetShadowMap();
				shadowMap->RegistShadowCaster(&m_model);
			}
			//�f�B�t�@�[�h�����_�����O���s�����H�B
			if (!m_isForwardRender) {
				GraphicsEngine()->GetGBuffer()->RegistDefferdModel(&m_model);
			}
			//�C���X�^���V���O�`��̃f�[�^���X�V�B
			if (m_model.IsInited())
			{
				m_model.SendGPUInstancingDatas();
			}
		}
		void ModelRender::ForwardRender(RenderContext& renderContext)
		{
			//�t�H���[�h�����_�����O���s���B
			if (m_isForwardRender) {
				m_model.Draw(renderContext);
			}
		}
	}
}