#pragma once
/// <summary>
/// ���f�������_�[
/// </summary>
#include "graphics/Model/Model.h"
#include "graphics/Animation/Animation.h"


namespace Engine {
	namespace prefab {
		/// <summary>
		/// 3D���f����\������@�\�B
		/// </summary>
		class ModelRender : public IGameObject
		{
		public:
			/// <summary>
			/// �J�n����
			/// </summary>
			/// <returns></returns>
			bool Start() override;
			/// <summary>
			/// ���S���̏����B
			/// </summary>
			void OnDestroy()override;
			/// <summary>
			/// �X�V�����B
			/// </summary>
			void Update() override;
			/// <summary>
			/// �|�X�g�X�V�����B
			/// </summary>
			void PostUpdate() override
			{
			}
			/// <summary>
			/// ���O�����_�����O�B
			/// </summary>
			void PreRender(RenderContext& rc)override;
			/// <summary>
			/// �t�H���[�h�����_�����O�̃p�X�ŌĂ΂�鏈���B
			/// </summary>
			/// <param name="renderContext"></param>
			void ForwardRender(RenderContext& rc) override;
			/// <summary>
			/// GBuffer�������݂ŌĂ΂��֐��B
			/// </summary>
			/// <param name="rc">�����_�����O�R���e�L�X�g�B</param>
			void RenderToGBuffer(RenderContext& rc)
			{
				//GBuffer�֏������ށB
				m_model.Draw(rc, m_numInstance);
			}
			/// <summary>
			/// �V���h�E�}�b�v�ւ̕`��ŌĂ΂��֐��B
			/// </summary>
			/// <param name="rc">�����_�����O�R���e�L�X�g�B</param>
			/// <param name="mLVP">���C�g�r���[�v���W�F�N�V�����s��B</param>
			/// <param name="shadowMapNo">�V���h�E�}�b�v�ԍ��B</param>
			void RenderToShadowMap(RenderContext& rc, Matrix mLVP, int shadowMapNo)
			{
				//�V���h�E�}�b�v�ɏ������ށB
				m_shadowModel[shadowMapNo].Draw(rc, mLVP, m_numInstance);
			}
		public:
			/// <summary>
			/// ���f���̏����������B
			/// </summary>
			/// <param name="modelData">Model�̃f�[�^�B</param>
			/// <param name="animClipDatas">�A�j���[�V�����N���b�v�̏������f�[�^�̔z��B</param>
			/// <param name="animClipsNum">�z��̃T�C�Y�B</param>
			void Init(ModelInitData& modelData, AnimClipInitData animClipDatas[] = nullptr, int animClipsNum = 0, int maxInstance = 1);

			/// <summary>
			/// ���f���}�e���A���̌����B
			/// </summary>
			/// <param name="findMaterial">�}�e���A�����������Ƃ��ɌĂяo���R�[���o�b�N�֐��B</param>
			void FindMaterial(OnFindMateral findMaterial)
			{
				m_model.FindMaterial(findMaterial);
			}
			/// <summary>
			/// �A���x�h�J���[�������ւ���B
			/// </summary>
			/// <param name="tex">�A���x�h�e�N�X�`���B</param>
			void ChangeAlbedo(Texture& tex)
			{
				m_model.ChangeAlbedo(tex);
			}

		public:		//���W�Ȃǂ̕ύX���s���֐��B
			/// <summary>
			/// ���f�����ړ�������B
			/// </summary>
			/// <param name="move">�ړ���</param>
			void Move(const Vector3& move)
			{
				m_position += move;
			}
			/// <summary>
			/// ���W���擾�B
			/// </summary>
			const Vector3& GetPosition() const
			{
				return m_position;
			}
			/// <summary>
			/// ���f������]������B
			/// </summary>
			/// <param name="rot">��]��</param>
			void Rotate(const Quaternion& rot)
			{
				//��]�����Z����B
				m_rotation *= rot;
			}
			/// <summary>
			/// ��]���擾
			/// </summary>
			/// <returns>��]��</returns>
			const Quaternion& GetRotation()const
			{
				return m_rotation;
			}

			/// <summary>
			/// �g�嗦���擾
			/// </summary>
			/// <returns>�g�嗦</returns>
			const Vector3& GetScale()const
			{
				return m_scale;
			}
			/// <summary>
			/// ���W��ݒ�B
			/// </summary>
			/// <param name="pos">���W</param>
			void SetPosition(const Vector3& pos)
			{
				m_position = pos;
			}
			void SetPosition(float x, float y, float z)
			{
				m_position.Set(x, y, z);
			}
			/// <summary>
			/// ��]��ݒ�B
			/// </summary>
			/// <param name="rot"></param>
			void SetRotation(Quaternion rot)
			{
				m_rotation = rot;
			}
			/// <summary>
			/// �g�嗦��ݒ�B
			/// </summary>
			/// <param name="scale"></param>
			void SetScale(const Vector3& scale)
			{
				m_scale = scale;
			}
			void SetScale(float xScale, float yScale, float zScale)
			{
				m_scale.Set(xScale, yScale, zScale);
			}
			/// <summary>
			/// ���Ȕ����F��ݒ肷��B
			/// </summary>
			/// <param name="emission">���Ȕ����F�B</param>
			void SetEmissionColor(const Vector3& emission)
			{
				m_model.SetEmissionColor(emission);
			}
			/// <summary>
			/// �V���h�E�L���X�^�[�t���O��ݒ�B
			/// </summary>
			/// <remarks>
			/// �V���h�E�L���X�^�[�t���O��true�ɂȂ��Ă���ƁA
			/// �V���h�E�}�b�v�ւ̃����_�����O���s����B
			/// </remarks>
			/// <param name="flag"></param>
			void SetShadowCasterFlag(bool flag)
			{
				m_isShadowCaster = flag;
			}
			/// <summary>
			/// �V���h�E���V�[�o�[�t���O��ݒ�B
			/// </summary>
			/// <remarks>
			/// �V���h�E���V�[�o�[�t���O��true�ɂȂ��Ă���ƁA
			/// �V���h�E�}�b�v���Q�Ƃ��āA���̃I�u�W�F�N�g����̉e��������B
			/// </remarks>
			/// <param name="flag"></param>
			void SetShadowReceiverFlag(bool flag)
			{
				m_model.SetShadowReceiverFlag(flag);
			}
			/// <summary>
			/// �t�H���[�h�����_�����O���s�����H
			/// </summary>
			/// <param name="flag">true�Ńt�H���[�h�����_�����O���s����B</param>
			void SetForwardRenderFlag(bool flag)
			{
				m_isForwardRender = flag;
			}
			/// <summary>
			/// �C���X�^���V���O�`��p�̃f�[�^�X�V�̑O�ɌĂԁB
			/// </summary>
			void ResetInstancingDatas()
			{
				m_numInstance = 0;
			}
			/// <summary>
			/// �C���X�^���V���O�`��p�̍s��f�[�^���X�V����B
			/// </summary>
			/// <param name="pos">���W</param>
			/// <param name="rot">��]</param>
			/// <param name="scale">�g�嗦</param>
			void UpdateInstancingData(
				const Vector3& pos,
				const Quaternion& rot,
				const Vector3& scale
			);
			/// <summary>
			/// �J�����O�����邩�ǂ�����ݒ�B
			/// </summary>
			void SetIsCulling(bool isCulling)
			{
				m_isCulling = isCulling;
			}
			/// <summary>
			/// �J�����O����Ƃ��̉����ʂ��w��B
			/// </summary>
			void SetCullingFar(const float culfar)
			{
				m_cullingFar = culfar;
			}

			/// <summary>
			/// �C���X�^���V���O�`�悩�H
			/// </summary>
			bool IsInstancing()
			{
				return m_maxInstance > 1;
			}
			/// <summary>
			/// �Đ�����A�j���[�V������ύX����B
			/// </summary>
			/// <param name="animNo">�A�j���[�V�����ԍ�</param>
			/// <param name="interpolateTime">�⊮����</param>
			void PlayAnimation(int animNo, float interpolateTime)
			{
				if (m_animation.IsInited()) {
					m_animation.Play(animNo, interpolateTime);
				}
			}
			/// <summary>
			/// ���f�����擾�B
			/// </summary>
			/// <returns></returns>
			Model& GetModel()
			{
				return m_model;
			}
			/// <summary>
			/// �A�j���[�V������footstep�̈ړ��ʂ��擾����B
			/// </summary>
			/// <returns></returns>
			const Vector3& GetFootstepMove() const
			{
				if (m_animation.IsInited()) {
					return m_animation.CalsFootstepDeltaInWorldSpace(m_rotation, m_scale);
				}
				return Vector3::Zero;
			}

			const ModelInitData& GetInitData()const
			{
				return m_modeInitData;
			}
		private:	//�������֐��B
			/// <summary>
			/// �C���X�^���V���O�`��p��SB�\�z�B
			/// </summary>
			/// <param name="maxInstance">�C���X�^���X���B</param>
			void InitInstancing(int maxInstance);
			/// /// <summary>
			/// �X�P���g����ǂݍ��ށB
			/// </summary>
			void InitSkelton(const char* filePath);
			/// <summary>
			/// �A�j���[�V������ǂݍ��ށB
			/// </summary>
			/// <param name="animClipDatas"></param>
			/// <param name="animClipsNum"></param>
			void InitAnimation(AnimClipInitData* animClipDatas, int animClipsNum);
			/// <summary>
			/// ���f�����������B
			/// </summary>
			/// <param name="initData">���f���̏������f�[�^�B</param>
			void InitModel(ModelInitData& initData);
			/// <summary>
			/// �V���h�E�}�b�v�p���f���������B
			/// </summary>
			void InitShadowModel();

			/// <summary>
			/// GPU�ɃC���X�^���V���O�`��p�̃f�[�^�𑗂�B
			/// </summary>
			void SendGPUInstancingDatas()
			{
				if (m_maxInstance > 1) {
					m_instancingDataSB.Update(m_instancingData.get());
				}
			}
		private:
			/// <summary>
			/// �������X�e�[�^�X�B
			/// </summary>
			enum EnInitStatus {
				enInitStatus_NotCallInitFunc,			//�������֐����܂��B
				enInitStatus_StartInitModel,			//�������X�e�b�v���J�n����B
				enInitStatus_WaitInitSkeleton,			//�X�P���g���̏������҂��B
				enInitStatus_WaitInitAnimationClips,	//�A�j���[�V�����N���b�v�̏������҂��B
				enInitStatus_WaitInitAnimation,	//�A�j���[�V�����̏������҂��B
				enInitStatus_WaitInitModel,				//���f���������҂��B
				enInitStatus_Completed,					//�����������B
			};
			EnInitStatus m_initStatus = enInitStatus_NotCallInitFunc;	//�������X�e�[�^�X�B
			Model m_model;		//���f���B
			Model m_shadowModel[NUM_SHADOW_MAP];		//�V���h�E�}�b�v�`��p���f���B
			Vector3 m_position = Vector3::Zero;				//���W�B
			Quaternion	m_rotation = Quaternion::Identity;	//��]�B
			Vector3 m_scale = Vector3::One;					//�g�嗦�B
			Skeleton m_skeleton;							//�X�P���g���B
			CAnimation m_animation;							//�A�j���[�V�����B
			ModelInitData m_modeInitData;						//���f���̏������f�[�^�B
			std::vector <AnimClipInitData> m_animClipInitDatas;	//�A�j���[�V�����N���b�v�̏������f�[�^�B
			std::vector <CAnimationClipPtr> m_animClips;	//�A�j���[�V�����N���b�v�̔z��B
			std::unique_ptr<Matrix[]> m_instancingData;	//�C���X�^���V���O�`��p�̃f�[�^�B
			StructuredBuffer m_instancingDataSB;		//�C���X�^���V���O�`��p�̃o�b�t�@�B
			int m_maxInstance = 1;		//�C���X�^���V���O�`��̍ő吔�B
			int m_numInstance = 0;		//�C���X�^���X�̐��B
			float m_cullingFar = 0.0f;
			bool m_isEnableInstancing = false;				//�C���X�^���V���O�`�悪�L�����H
			bool m_isCulling = false;						//�J�����O���s�����ǂ����B
			bool m_isShadowCaster = false;					//�V���h�E�L���X�^�\�t���O�B
			bool m_isForwardRender = false;					//�t�H���[�h�����_�����O���s�����H
		};
	}
}


