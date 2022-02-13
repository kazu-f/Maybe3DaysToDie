#include "MiniEngine.h"
#include "ModelRender.h"

namespace Engine {
	namespace prefab {

		void ModelRender::Init(ModelInitData& modelData, AnimClipInitData animClipDatas[], int animClipsNum, int maxInstance)
		{
			InitInstancing(maxInstance);			//インスタンシング描画初期化。
			InitSkelton(modelData.m_tkmFilePath);	//スケルトン初期化。
			InitAnimation(animClipDatas, animClipsNum);	//アニメーション初期化。
			InitModel(modelData);					//モデル初期化。
			InitShadowModel();						//シャドウマップモデル初期化。
		}

		bool ModelRender::SubStart()
		{
			return m_model.IsInited();
		}

		void ModelRender::SubOnDestroy()
		{

		}

		void ModelRender::Update()
		{
			if (m_animation.IsInited()) {
				//アニメーションを再生。
				m_animation.Progress(GameTime().GetFrameDeltaTime());
			}

			//モデルを更新。
			if (!m_isEnableInstancing) {
				m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
			}

			if (m_skeleton.IsInited()) {
				//スケルトンを更新。
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
					//TODO:あまり好ましくないカリングしてるから直したい。
					if (screenPos.x < -1.2f || screenPos.x > 1.2f ||
						screenPos.y < -1.2f || screenPos.y > 1.2f ||
						viewPosZ > m_cullingFar || viewPosZ < -100.0f)
					{
						return;
					}
				}
				auto worldMat = m_model.CalcWorldMatrix(pos, rot, scale);
				//インスタンシングデータを更新する。
				m_instancingData[m_numInstance] = worldMat;

				m_numInstance++;
			}
			else {
				ENGINE_LOG("Model::UpdateInstancingData	invalid UpdateInstancingData.");
			}
		}

		void ModelRender::OnRenderShadowMap(RenderContext& rc, int shadowMapNo, const Matrix& lvpMatrix)
		{
			if (m_isShadowCaster) {
				m_shadowModel[shadowMapNo].Draw(rc, lvpMatrix, m_numInstance);
			}
		}

		void ModelRender::OnRenderToGBuffer(RenderContext& rc)
		{
			//ディファードレンダリングを行うか？。
			if (!m_isForwardRender) {
				m_model.Draw(rc, m_numInstance);
			}
		}

		void ModelRender::OnForwardRender(RenderContext& renderContext)
		{
			//フォワードレンダリングを行う。
			if (m_isForwardRender) {
				m_model.Draw(renderContext, m_numInstance);
			}
		}

		void ModelRender::InitInstancing(int maxInstance)
		{
			m_maxInstance = maxInstance;
			//インスタンシング描画を行う？
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
			//スケルトンを読み込む。
			m_skeleton.Init(skeletonFilePath.c_str());
		}

		void ModelRender::InitAnimation(AnimClipInitData* animClipDatas, int animClipsNum)
		{
			//アニメーションの初期化データをコピー。
			if (animClipDatas == nullptr
				|| !m_skeleton.IsInited())
			{
				//アニメーションのデータがない、
				//もしくはスケルトンが初期化できていない。
				return;
			}
			for (int i = 0; i < animClipsNum; i++)
			{
				m_animClipInitDatas.push_back(animClipDatas[i]);
			}
			//アニメーションのデータがある。
			for (auto& initData : m_animClipInitDatas)
			{
				//アニメーションクリップのロード。
				auto animClip = std::make_unique<CAnimationClip>();
				animClip->Load(initData.tkaFilePath.c_str());
				//キーフレームとかアニメーションイベントの設定とか。
				animClip->SetLoopFlag(initData.isLoop);
				animClip->BuildKeyFramesAndAnimationEvents();
				m_animClips.push_back(std::move(animClip));
			}
			
			//アニメーションを初期化。
			m_animation.Init(m_skeleton, m_animClips);
		}
		void ModelRender::InitModel(ModelInitData& initData)
		{
			//データをコピー。
			m_modeInitData = initData;
			//インスタンシング描画用のSBを設定。
			if (m_isEnableInstancing)
			{
				m_modeInitData.m_instancingDataSB = &m_instancingDataSB;
			}
			//スケルトンを設定。
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
				//シャドウマップ用のモデル読み込み。
				m_shadowModel[i].Init(m_modeInitData);
			}
		}
	}
}