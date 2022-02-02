#pragma once

namespace nsTerrain {

	/// <summary>
	/// 地形の頂点データ。
	/// </summary>
	struct TerrainVertex {
		Vector3 m_pos;		//座標。
		Vector3 m_normal;	//法線。
		Vector2 m_uv;		//UV。
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

		//座標設定。
		void SetPosition(const Vector3& pos)
		{
			m_position = pos;
		}
		//回転設定。
		void SetRotation(const Quaternion& rot)
		{
			m_rotation = rot;
		}
		//スケール設定。
		void SetScale(const Vector3& scale)
		{
			m_scale = scale;
		}

		/// <summary>
		/// 頂点を追加する。
		/// </summary>
		/// <param name="vert"></param>
		void AddVertex(const TerrainVertex& vert)
		{
			m_vertices[m_vertexCount] = vert;
			m_indices[m_vertexCount] = m_vertexCount;
			m_vertexCount++;
			m_isUpdateTerrain = true;
		}
		/// <summary>
		/// 三角ポリゴンの中心座標を記録。
		/// </summary>
		/// <param name="center"></param>
		void AddCenter(const Vector3& center)
		{
			m_centers.push_back(center);
		}
		/// <summary>
		/// 三角ポリゴンの中心座標を取得。
		/// </summary>
		/// <returns></returns>
		const std::vector<Vector3>& GetCenterArray()const
		{
			return m_centers;
		}
		/// <summary>
		/// 頂点をクリア。
		/// </summary>
		void ClearVertex()
		{
			m_vertices.clear();
			m_indices.clear();
			m_centers.clear();
			m_vertexCount = 0;
			m_vertices.resize(m_initData.vertexNum);
			m_indices.resize(m_initData.vertexNum);
			m_isUpdateTerrain = true;
		}

	public://getter
		/// <summary>
		/// 地形のバーテックスデータを取得。
		/// </summary>
		/// <returns></returns>
		std::vector<TerrainVertex>& GetVertexList()
		{
			return m_vertices;
		}
		/// <summary>
		/// インデックスリストを取得。
		/// </summary>
		/// <returns></returns>
		std::vector<int>& GetIndexList()
		{
			return m_indices;
		}
		/// <summary>
		/// バーテックスの数取得。
		/// </summary>
		/// <returns></returns>
		int& GetVertexCount()
		{
			return m_vertexCount;
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
			Matrix mWorld;  //ワールド行列。
			Matrix mView;	//ビュー行列。
			Matrix mProj;	//プロジェクション行列。
		};

	private:
		TerrainInitData m_initData;
		Texture* m_terrainTex = nullptr;				//地形のテクスチャ。
		Shader m_vsTerrain;					//地形用の頂点シェーダー。
		Shader m_psTerrain;					//地形用のピクセルシェーダー。
		PipelineState m_terrainPS;			//地形用のパイプラインステート。
		ConstantBuffer m_cbTerrain;			//地形用の定数バッファ。
		DescriptorHeap m_descriptorHeap;	//地形用ディスクリプタヒープ。
		VertexBuffer m_vertexBuffer;		//地形の頂点バッファ。
		IndexBuffer m_indexBuffer;			//地形のインデックスバッファ。
		Vector3 m_position = Vector3::Zero;				//地形の座標。
		Quaternion m_rotation = Quaternion::Identity;	//地形の回転。
		Vector3 m_scale = Vector3::One;				//地形のスケール。
		Matrix m_world = Matrix::Identity;				//地形のワールド行列。
		std::vector<TerrainVertex> m_vertices;	//頂点の配列。
		std::vector<int> m_indices;			//インデックス番号の配列。
		std::vector<Vector3> m_centers;			//三角ポリゴンの中心座標の配列。
		int m_vertexCount = 0;
		bool m_isRenderTerrain = false;		//地形描画する？
		bool m_isUpdateTerrain = false;		//地形変更があったか？
	};

}
