#pragma once
/// <summary>
/// モデルレンダー
/// </summary>
#include "graphics/Model/Model.h"
#include "graphics/Animation/Animation.h"


namespace Engine {
	namespace prefab {
		/// <summary>
		/// 3Dモデルを表示する機能。
		/// </summary>
		class ModelRender : public IGameObject
		{
		public:
			/// <summary>
			/// 開始処理
			/// </summary>
			/// <returns></returns>
			bool Start() override;
			/// <summary>
			/// 死亡時の処理。
			/// </summary>
			void OnDestroy()override;
			/// <summary>
			/// 更新処理。
			/// </summary>
			void Update() override;
			/// <summary>
			/// ポスト更新処理。
			/// </summary>
			void PostUpdate() override
			{
			}
			/// <summary>
			/// 事前レンダリング。
			/// </summary>
			void PreRender(RenderContext& rc)override;
			/// <summary>
			/// フォワードレンダリングのパスで呼ばれる処理。
			/// </summary>
			/// <param name="renderContext"></param>
			void ForwardRender(RenderContext& rc) override;
			/// <summary>
			/// GBuffer書き込みで呼ばれる関数。
			/// </summary>
			/// <param name="rc">レンダリングコンテキスト。</param>
			void RenderToGBuffer(RenderContext& rc)
			{
				//GBufferへ書き込む。
				m_model.Draw(rc, m_numInstance);
			}
			/// <summary>
			/// シャドウマップへの描画で呼ばれる関数。
			/// </summary>
			/// <param name="rc">レンダリングコンテキスト。</param>
			/// <param name="mLVP">ライトビュープロジェクション行列。</param>
			/// <param name="shadowMapNo">シャドウマップ番号。</param>
			void RenderToShadowMap(RenderContext& rc, Matrix mLVP, int shadowMapNo)
			{
				//シャドウマップに書き込む。
				m_shadowModel[shadowMapNo].Draw(rc, mLVP, m_numInstance);
			}
		public:
			/// <summary>
			/// モデルの初期化処理。
			/// </summary>
			/// <param name="modelData">Modelのデータ。</param>
			/// <param name="animClipDatas">アニメーションクリップの初期化データの配列。</param>
			/// <param name="animClipsNum">配列のサイズ。</param>
			void Init(ModelInitData& modelData, AnimClipInitData animClipDatas[] = nullptr, int animClipsNum = 0, int maxInstance = 1);

			/// <summary>
			/// モデルマテリアルの検索。
			/// </summary>
			/// <param name="findMaterial">マテリアルを見つけたときに呼び出すコールバック関数。</param>
			void FindMaterial(OnFindMateral findMaterial)
			{
				m_model.FindMaterial(findMaterial);
			}
			/// <summary>
			/// アルベドカラーを差し替える。
			/// </summary>
			/// <param name="tex">アルベドテクスチャ。</param>
			void ChangeAlbedo(Texture& tex)
			{
				m_model.ChangeAlbedo(tex);
			}

		public:		//座標などの変更を行う関数。
			/// <summary>
			/// モデルを移動させる。
			/// </summary>
			/// <param name="move">移動量</param>
			void Move(const Vector3& move)
			{
				m_position += move;
			}
			/// <summary>
			/// 座標を取得。
			/// </summary>
			const Vector3& GetPosition() const
			{
				return m_position;
			}
			/// <summary>
			/// モデルを回転させる。
			/// </summary>
			/// <param name="rot">回転量</param>
			void Rotate(const Quaternion& rot)
			{
				//回転を加算する。
				m_rotation *= rot;
			}
			/// <summary>
			/// 回転を取得
			/// </summary>
			/// <returns>回転量</returns>
			const Quaternion& GetRotation()const
			{
				return m_rotation;
			}

			/// <summary>
			/// 拡大率を取得
			/// </summary>
			/// <returns>拡大率</returns>
			const Vector3& GetScale()const
			{
				return m_scale;
			}
			/// <summary>
			/// 座標を設定。
			/// </summary>
			/// <param name="pos">座標</param>
			void SetPosition(const Vector3& pos)
			{
				m_position = pos;
			}
			void SetPosition(float x, float y, float z)
			{
				m_position.Set(x, y, z);
			}
			/// <summary>
			/// 回転を設定。
			/// </summary>
			/// <param name="rot"></param>
			void SetRotation(Quaternion rot)
			{
				m_rotation = rot;
			}
			/// <summary>
			/// 拡大率を設定。
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
			/// 自己発光色を設定する。
			/// </summary>
			/// <param name="emission">自己発光色。</param>
			void SetEmissionColor(const Vector3& emission)
			{
				m_model.SetEmissionColor(emission);
			}
			/// <summary>
			/// シャドウキャスターフラグを設定。
			/// </summary>
			/// <remarks>
			/// シャドウキャスターフラグがtrueになっていると、
			/// シャドウマップへのレンダリングが行われる。
			/// </remarks>
			/// <param name="flag"></param>
			void SetShadowCasterFlag(bool flag)
			{
				m_isShadowCaster = flag;
			}
			/// <summary>
			/// シャドウレシーバーフラグを設定。
			/// </summary>
			/// <remarks>
			/// シャドウレシーバーフラグがtrueになっていると、
			/// シャドウマップを参照して、他のオブジェクトからの影が落ちる。
			/// </remarks>
			/// <param name="flag"></param>
			void SetShadowReceiverFlag(bool flag)
			{
				m_model.SetShadowReceiverFlag(flag);
			}
			/// <summary>
			/// フォワードレンダリングを行うか？
			/// </summary>
			/// <param name="flag">trueでフォワードレンダリングが行われる。</param>
			void SetForwardRenderFlag(bool flag)
			{
				m_isForwardRender = flag;
			}
			/// <summary>
			/// インスタンシング描画用のデータ更新の前に呼ぶ。
			/// </summary>
			void ResetInstancingDatas()
			{
				m_numInstance = 0;
			}
			/// <summary>
			/// インスタンシング描画用の行列データを更新する。
			/// </summary>
			/// <param name="pos">座標</param>
			/// <param name="rot">回転</param>
			/// <param name="scale">拡大率</param>
			void UpdateInstancingData(
				const Vector3& pos,
				const Quaternion& rot,
				const Vector3& scale
			);
			/// <summary>
			/// カリングをするかどうかを設定。
			/// </summary>
			void SetIsCulling(bool isCulling)
			{
				m_isCulling = isCulling;
			}
			/// <summary>
			/// カリングするときの遠平面を指定。
			/// </summary>
			void SetCullingFar(const float culfar)
			{
				m_cullingFar = culfar;
			}

			/// <summary>
			/// インスタンシング描画か？
			/// </summary>
			bool IsInstancing()
			{
				return m_maxInstance > 1;
			}
			/// <summary>
			/// 再生するアニメーションを変更する。
			/// </summary>
			/// <param name="animNo">アニメーション番号</param>
			/// <param name="interpolateTime">補完時間</param>
			void PlayAnimation(int animNo, float interpolateTime)
			{
				if (m_animation.IsInited()) {
					m_animation.Play(animNo, interpolateTime);
				}
			}
			/// <summary>
			/// モデルを取得。
			/// </summary>
			/// <returns></returns>
			Model& GetModel()
			{
				return m_model;
			}
			/// <summary>
			/// アニメーションのfootstepの移動量を取得する。
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
		private:	//初期化関数。
			/// <summary>
			/// インスタンシング描画用のSB構築。
			/// </summary>
			/// <param name="maxInstance">インスタンス数。</param>
			void InitInstancing(int maxInstance);
			/// /// <summary>
			/// スケルトンを読み込む。
			/// </summary>
			void InitSkelton(const char* filePath);
			/// <summary>
			/// アニメーションを読み込む。
			/// </summary>
			/// <param name="animClipDatas"></param>
			/// <param name="animClipsNum"></param>
			void InitAnimation(AnimClipInitData* animClipDatas, int animClipsNum);
			/// <summary>
			/// モデルを初期化。
			/// </summary>
			/// <param name="initData">モデルの初期化データ。</param>
			void InitModel(ModelInitData& initData);
			/// <summary>
			/// シャドウマップ用モデル初期化。
			/// </summary>
			void InitShadowModel();

			/// <summary>
			/// GPUにインスタンシング描画用のデータを送る。
			/// </summary>
			void SendGPUInstancingDatas()
			{
				if (m_maxInstance > 1) {
					m_instancingDataSB.Update(m_instancingData.get());
				}
			}
		private:
			/// <summary>
			/// 初期化ステータス。
			/// </summary>
			enum EnInitStatus {
				enInitStatus_NotCallInitFunc,			//初期化関数がまだ。
				enInitStatus_StartInitModel,			//初期化ステップを開始する。
				enInitStatus_WaitInitSkeleton,			//スケルトンの初期化待ち。
				enInitStatus_WaitInitAnimationClips,	//アニメーションクリップの初期化待ち。
				enInitStatus_WaitInitAnimation,	//アニメーションの初期化待ち。
				enInitStatus_WaitInitModel,				//モデル初期化待ち。
				enInitStatus_Completed,					//初期化完了。
			};
			EnInitStatus m_initStatus = enInitStatus_NotCallInitFunc;	//初期化ステータス。
			Model m_model;		//モデル。
			Model m_shadowModel[NUM_SHADOW_MAP];		//シャドウマップ描画用モデル。
			Vector3 m_position = Vector3::Zero;				//座標。
			Quaternion	m_rotation = Quaternion::Identity;	//回転。
			Vector3 m_scale = Vector3::One;					//拡大率。
			Skeleton m_skeleton;							//スケルトン。
			CAnimation m_animation;							//アニメーション。
			ModelInitData m_modeInitData;						//モデルの初期化データ。
			std::vector <AnimClipInitData> m_animClipInitDatas;	//アニメーションクリップの初期化データ。
			std::vector <CAnimationClipPtr> m_animClips;	//アニメーションクリップの配列。
			std::unique_ptr<Matrix[]> m_instancingData;	//インスタンシング描画用のデータ。
			StructuredBuffer m_instancingDataSB;		//インスタンシング描画用のバッファ。
			int m_maxInstance = 1;		//インスタンシング描画の最大数。
			int m_numInstance = 0;		//インスタンスの数。
			float m_cullingFar = 0.0f;
			bool m_isEnableInstancing = false;				//インスタンシング描画が有効か？
			bool m_isCulling = false;						//カリングを行うかどうか。
			bool m_isShadowCaster = false;					//シャドウキャスタ―フラグ。
			bool m_isForwardRender = false;					//フォワードレンダリングを行うか？
		};
	}
}


