#pragma once

#include "tkFile/TkmFile.h"
#include "MeshParts.h"
#include "../Skeleton.h"
namespace Engine {
	enum ModelUpAxis {
		enModelUpAxis_Z,	//Zアップ
		enModelUpAxis_Y,	//Yアップ。
	};
	class IShaderResource;

	/// <summary>
	/// モデルの初期化データ
	/// </summary>
	struct ModelInitData {
		const char* m_tkmFilePath = nullptr;		//tkmファイルパス。
		SShaderInitData m_shaderData;				//読み込むシェーダーのデータ。頂点シェーダーとピクセルシェーダーの両方を指定する必要がある。
		void* m_expandConstantBuffer = nullptr;		//ユーザー拡張の定数バッファ。
		int m_expandConstantBufferSize = 0;			//ユーザー拡張の定数バッファのサイズ。
		IShaderResource* m_expandShaderResoruceView = nullptr;	//ユーザー拡張のシェーダーリソース。1111
		Skeleton* m_skeleton = nullptr;					//スケルトンデータ。
		StructuredBuffer* m_instancingDataSB = nullptr;			//インスタンシング描画用のSB。
		ModelUpAxis m_modelUpAxis = enModelUpAxis_Z;	//モデルの上方向。
	};
	/// <summary>
	/// モデルクラス。
	/// </summary>
	class Model {
	public:
		/// <summary>
		/// tkmファイルから初期化。
		/// </summary>
		/// <param name="initData">初期化データ</param>
		void Init(const ModelInitData& initData,int maxInstance = 1);
		/// <summary>
		/// ワールド行列の更新。
		/// </summary>
		/// <param name="pos">座標</param>
		/// <param name="rot">回転</param>
		/// <param name="scale">拡大率</param>
		void UpdateWorldMatrix(Vector3 pos, Quaternion rot, Vector3 scale)
		{
			m_world = CalcWorldMatrix(pos, rot, scale);
		}


		/// <summary>
		/// ワールド行列を計算
		/// </summary>
		/// <remark>
		/// Modelクラスの設定に基づいたワールド行列の計算が行われます。
		/// 計算されたワールド行列が戻り値として返されます。
		/// 本関数はUpdateWorldMatrixから呼ばれています。
		/// 本関数はワールド行列を計算して、戻すだけです。
		/// Model::m_worldMatrixが更新されるわけではないので、注意してください。
		/// 本クラスの設定に基づいて計算されたワールド行列が必要な場合に使用してください
		/// </remark>
		/// <param name="pos">座標</param>
		/// <param name="rot">回転</param>
		/// <param name="scale">拡大率</param>
		/// <returns>ワールド行列</returns>
		Matrix CalcWorldMatrix(Vector3 pos, Quaternion rot, Vector3 scale);

		/// <summary>
		/// スケルトンを関連付ける。
		/// </summary>
		/// <param name="skeleton">スケルトン</param>
		void BindSkeleton(Skeleton& skeleton)
		{
			m_meshParts.BindSkeleton(skeleton);
		}

		/// <summary>
		/// 描画
		/// </summary>
		/// <param name="renderContext">レンダリングコンテキスト</param>
		void Draw(RenderContext& renderContext,int numInstance = 1);
		/// <summary>
		/// /シャドウマップ用描画。
		/// </summary>
		/// <param name="rc">レンダリングコンテキスト</param>
		/// <param name="mLVP">ライトビュープロジェクション行列</param>
		void Draw(RenderContext& rc, Matrix mLVP, int numInstance = 1);
		/// <summary>
		/// 別のカメラから描画する。
		/// </summary>
		/// <param name="rc">レンダリングコンテキスト</param>
		/// <param name="mView">ビュー行列</param>
		/// <param name="mProj">プロジェクション行列</param>
		void Draw(RenderContext& rc,Matrix mView , Matrix mProj, int numInstance = 1);
		/// <summary>
		/// 初期化済みか？
		/// </summary>
		bool IsInited()
		{
			return m_tkmFile->IsLoaded();
		}
		/// <summary>
		/// ワールド行列を取得。
		/// </summary>
		/// <returns></returns>
		const Matrix& GetWorldMatrix() const
		{
			return m_world;
		}
		/// <summary>
		/// 自己発光色を設定する。
		/// </summary>
		/// <param name="emission">自己発光色。</param>
		void SetEmissionColor(const Vector3& emission)
		{
			m_meshParts.SetEmissionColor(emission);
		}
		/// <summary>
		/// シャドウレシーバーに設定する。
		/// </summary>
		void SetShadowReceiverFlag(bool flag)
		{
			m_meshParts.SetShadowReceiverFlag(flag);
		}
		/// <summary>
		/// tkmファイルを取得。
		/// </summary>
		const TkmFile& GetTkmFile()const
		{
			return *m_tkmFile;
		}
		/// <summary>
		/// モデルマテリアルの検索。
		/// </summary>
		/// <param name="findMaterial">マテリアルを見つけたときに呼び出されるコールバック関数。</param>
		void FindMaterial(OnFindMateral findMaterial)
		{
			m_meshParts.FindMaterial(findMaterial);
		}
	private:

		Matrix m_world;			//ワールド行列。
		TkmFile* m_tkmFile;		//tkmファイル。
		MeshParts m_meshParts;	//メッシュパーツ。
		ModelUpAxis m_modelUpAxis = enModelUpAxis_Z;	//モデルの上方向。
	};
}