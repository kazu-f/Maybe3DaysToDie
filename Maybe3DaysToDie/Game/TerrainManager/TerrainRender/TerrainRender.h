#pragma once

namespace nsTerrain {

	/// <summary>
	/// 地形の頂点データ。
	/// </summary>
	struct Vertex {
		Vector3 m_pos;
		Vector2 m_uv;
	};

	//地形描画クラスの初期化データ。
	struct TerrainInitData {
		int vertexNum = 0;			//頂点数。

	};

	class TerrainRender : public IGameObject
	{
	public:
		bool Start()override final;
		void Update()override final;
		void ForwardRender(RenderContext& rc)override final;
		/// <summary>
		/// 初期化。
		/// </summary>
		void Init(TerrainInitData& initData);

		/// <summary>
		/// 頂点を追加する。
		/// </summary>
		/// <param name="vert"></param>
		void AddVertex(const Vertex& vert)
		{
			m_vertices[m_vertexCount] = vert;
			m_indices[m_vertexCount] = m_vertexCount;
			m_vertexCount++;
		}

	private:
		void InitVertexBuffer(int maxVertexNum);
		void InitIndexBuffer(int maxIndexNum);
		void InitShader();			//シェーダーの初期化。
		void InitPipelineState();	//パイプラインステートの初期化。
		void InitConstantBuffer();	//定数バッファの初期化。
		void InitTexrure();			//テクスチャ初期化。
		void InitDescriptorHeap();	//ディスクリプタヒープの初期化。

	private:
		struct SCBTerrin{
			Matrix mView;	//ビュー行列。
			Matrix mProj;	//プロジェクション行列。
		};

	private:
		Texture* m_terrainTex = nullptr;				//地形のテクスチャ。
		Shader m_vsTerrain;					//地形用の頂点シェーダー。
		Shader m_psTerrain;					//地形用のピクセルシェーダー。
		PipelineState m_terrainPS;			//地形用のパイプラインステート。
		ConstantBuffer m_cbTerrain;			//地形用の定数バッファ。
		DescriptorHeap m_descriptorHeap;	//地形用ディスクリプタヒープ。
		VertexBuffer m_vertexBuffer;		//地形の頂点バッファ。
		IndexBuffer m_indexBuffer;			//地形のインデックスバッファ。
		std::vector<Vertex> m_vertices;	//頂点の配列。
		std::vector<short> m_indices;			//インデックス番号の配列。
		int m_vertexCount = 0;
	};

}
