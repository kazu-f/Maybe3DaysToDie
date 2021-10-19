#include "MiniEngine.h"
#include "ModelRender.h"

namespace Engine {
	namespace prefab {

		void ModelRender::Init(ModelInitData& modelData, AnimClipInitData animClipDatas[], int animClipsNum, int maxInstance)
		{
			InitInstancing(maxInstance);			//�C���X�^���V���O�`�揉�����B
			InitSkelton(modelData.m_tkmFilePath);	//�X�P���g���������B
			InitAnimation(animClipDatas, animClipsNum);	//�A�j���[�V�����������B
			InitModel(modelData);					//���f���������B
			InitShadowModel();						//�V���h�E�}�b�v���f���������B
		}

		bool ModelRender::Start()
		{
			return m_model.IsInited();
		}

		void ModelRender::OnDestroy()
		{
			//�V���h�E�L���X�^�[�o�^����������B
			auto& shadowMap = GraphicsEngine()->GetShadowMap();
			shadowMap->RemoveShadowCaster(this);
			auto& gBuffer = GraphicsEngine()->GetGBuffer();
			gBuffer->RemoveDefferdModel(this);
		}
		void ModelRender::Update()
		{
			if (m_animation.IsInited()) {
				//�A�j���[�V�������Đ��B
				m_animation.Progress(GameTime().GetFrameDeltaTime());
			}

			//���f�����X�V�B
			if (!m_isEnableInstancing) {
				m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
			}

			if (m_skeleton.IsInited()) {
				//�X�P���g�����X�V�B
				if (m_isEnableInstancing) {
					m_skeleton.Update(g_matIdentity);
				}
				else {
					m_skeleton.Update(m_model.GetWorldMatrix());
				}
			}

		}

		void ModelRender::UpdateInstancingData(
			const Vector3& pos,
			const Quaternion& rot,
			const Vector3& scale
		)
		{
			if (m_numInstance < m_maxInstance) {
				if (m_isCulling) {
					Vector4 screenPos = pos;
					GraphicsEngine()->GetMainCamera().GetViewMatrix().Apply(screenPos);
					float viewPosZ = screenPos.z;
					GraphicsEngine()->GetMainCamera().GetProjectionMatrix().Apply(screenPos);
					screenPos.x /= screenPos.w;
					screenPos.y /= screenPos.w;
					screenPos.z /= screenPos.w;
					//TODO:���܂�D�܂����Ȃ��J�����O���Ă邩�璼�������B
					if (screenPos.x < -1.2f || screenPos.x > 1.2f ||
						screenPos.y < -1.2f || screenPos.y > 1.2f ||
						viewPosZ > m_cullingFar || viewPosZ < -100.0f)
					{
						return;
					}
				}
				auto worldMat = m_model.CalcWorldMatrix(pos, rot, scale);
				//�C���X�^���V���O�f�[�^���X�V����B
				m_instancingData[m_numInstance] = worldMat;

				m_numInstance++;
			}
			else {
				ENGINE_LOG("Model::UpdateInstancingData	invalid UpdateInstancingData.");
			}
		}

		void ModelRender::PreRender(RenderContext& rc)
		{
			//�C���X�^���V���O�`��̃f�[�^���X�V�B
			if (m_instancingDataSB.IsInited())
			{
				SendGPUInstancingDatas();
			}
			if (m_isShadowCaster)
			{
				//�V���h�E�L���X�^�[�ɓo�^����B
				auto& shadowMap = GraphicsEngine()->GetShadowMap();
				shadowMap->RegistShadowCaster(this);
			}
			//�f�B�t�@�[�h�����_�����O���s�����H�B
			if (!m_isForwardRender) {
				GraphicsEngine()->GetGBuffer()->RegistDefferdModel(this);
			}
		}
		void ModelRender::ForwardRender(RenderContext& renderContext)
		{
			//�t�H���[�h�����_�����O���s���B
			if (m_isForwardRender) {
				m_model.Draw(renderContext);
			}
		}
		void ModelRender::InitInstancing(int maxInstance)
		{
			m_maxInstance = maxInstance;
			//�C���X�^���V���O�`����s���H
			if (maxInstance > 1) {
				m_maxInstance = maxInstance;
				m_instancingData.reset(new Matrix[maxInstance]);
				m_instancingDataSB.Init(sizeof(Matrix), maxInstance, m_instancingData.get());

				m_isEnableInstancing = true;
			}
		}
		void ModelRender::InitSkelton(const char* filePath)
		{
			std::string skeletonFilePath = filePath;
			int pos = static_cast<int>(skeletonFilePath.find(".tkm"));
			skeletonFilePath.replace(pos, 4, ".tks");
			//�X�P���g����ǂݍ��ށB
			m_skeleton.Init(skeletonFilePath.c_str());
		}
		void ModelRender::InitAnimation(AnimClipInitData* animClipDatas, int animClipsNum)
		{
			//�A�j���[�V�����̏������f�[�^���R�s�[�B
			if (animClipDatas == nullptr
				|| !m_skeleton.IsInited())
			{
				//�A�j���[�V�����̃f�[�^���Ȃ��A
				//�������̓X�P���g�����������ł��Ă��Ȃ��B
				return;
			}
			for (int i = 0; i < animClipsNum; i++)
			{
				m_animClipInitDatas.push_back(animClipDatas[i]);
			}
			//�A�j���[�V�����̃f�[�^������B
			for (auto& initData : m_animClipInitDatas)
			{
				//�A�j���[�V�����N���b�v�̃��[�h�B
				auto animClip = std::make_unique<CAnimationClip>();
				animClip->Load(initData.tkaFilePath.c_str());
				//�L�[�t���[���Ƃ��A�j���[�V�����C�x���g�̐ݒ�Ƃ��B
				animClip->SetLoopFlag(initData.isLoop);
				animClip->BuildKeyFramesAndAnimationEvents();
				m_animClips.push_back(std::move(animClip));
			}
			
			//�A�j���[�V�������������B
			m_animation.Init(m_skeleton, m_animClips);
		}
		void ModelRender::InitModel(ModelInitData& initData)
		{
			//�f�[�^���R�s�[�B
			m_modeInitData = initData;
			//�C���X�^���V���O�`��p��SB��ݒ�B
			if (m_isEnableInstancing)
			{
				m_modeInitData.m_instancingDataSB = &m_instancingDataSB;
			}
			//�X�P���g����ݒ�B
			if (m_skeleton.IsInited())
			{
				m_modeInitData.m_skeleton = &m_skeleton;
			}

			m_model.Init(m_modeInitData,m_maxInstance);
		}
		void ModelRender::InitShadowModel()
		{
			for (int i = 0; i < NUM_SHADOW_MAP; i++)
			{
				//�V���h�E�}�b�v�p�̃��f���ǂݍ��݁B
				m_shadowModel[i].Init(m_modeInitData);
			}
		}
	}
}