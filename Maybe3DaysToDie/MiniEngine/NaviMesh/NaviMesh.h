#pragma once

namespace Engine {
	/// <summary>
	/// ナビメッシュ。
	/// </summary>
	class NaviMesh
	{
	public:
		//バイナリデータのセルのデータ構造体。
		struct CellBin {
			int linkCellNumber[3] = { 1 };	//隣接セル番号。
			Vector3 pos[3];
			std::int32_t pad = 0;	//パディング。
			//共用体。
			union {
				std::intptr_t linkCell64[3];
				CellBin* linkCell[3];
			};
		};
		enum ListNo {
			EnNoneList,
			EnCloseList,
			EnOpenList
		};
		/// <summary>
		/// AStarで使用するセル情報。
		/// </summary>
		struct Cell {
			Vector3 pos[3];							//３頂点。
			Cell* m_parent = nullptr;				//親となるセル。
			Cell* child = nullptr;					//子供となるセル。
			Cell* m_linkCell[3] = { nullptr };		//隣接セル。
			Vector3 m_CenterPos = g_vec3Zero;		//セルの中央座標。
			float costFromStart = 0.0f;				//スタートから見たコスト。
			float costToEnd = 0.0f;					//スタート位置からゴール位置までのコスト。
			float totalCost = 0.0f;					//最終的なコスト。
			int listNum = EnNoneList;				//どのリストに属しているか。
		};
	public:
		/// <summary>
		/// NaviMeshをロード。
		/// </summary>
		void Load(const char* filePath);
	public:
		//ここからはNaviMeshをテスト描画する際に必要なコードのため、
		//描画しないユーザーは使用/呼び出ししなくて大丈夫。

		/// <summary>
		/// 描画用初期化。
		/// </summary>
		/// <param name="isWire">ワイヤーフレーム描画にする？</param>
		void InitRender();
		/// <summary>
		/// エージェントの経路を描画。
		/// <para>todo:こいつすごい構造がばある、早いうちに直そう。。</para>
		/// <para>仕様上、ルート更新とかできないなぁ。。。Astarに移譲しよ。</para>
		/// </summary>
		void AgentNodeRender(std::vector<NaviMesh::Cell*>& rootList);
		/// <summary>
		/// 描画準備。
		/// </summary>
		void BeginRender();
		/// <summary>
		/// NaviMeshを描画。
		/// </summary>
		void Render();
		/// <summary>
		/// 描画後処理。
		/// </summary>
		void EndRender();
		/// <summary>
		/// パイプラインステートを作成。
		/// </summary>
		/// <param name="pipelineState">出力先のパイプラインステート。</param>
		/// <param name="rs">ルートシグネチャー。</param>
		/// <param name="vs">頂点シェーダー。</param>
		/// <param name="ps">ピクセルシェーダー。</param>
		/// <param name="isWire">ワイヤーフレーム描画？？</param>
		void InitPipelineState(PipelineState& pipelineState, RootSignature& rs, Shader& vs, Shader& ps, bool isWire, D3D12_PRIMITIVE_TOPOLOGY_TYPE topology);
		/// <summary>
		/// バイナリデータセルを取得。。
		/// </summary>
		/// <returns>バイナリセルデーター。</returns>
		const CellBin* GetCell() const
		{
			return m_cellBin;
		}
		/// <summary>
		/// セルの数を取得。
		/// </summary>
		/// <returns>セルの数。</returns>
		const int& GetCellNum() const
		{
			return m_numCell;
		}
		/// <summary>
		/// セルリストを取得。
		/// </summary>
		/// <returns></returns>
		std::vector<Cell>& GetCellList()
		{
			return m_cell;
		}
	private:
		//定数バッファの構造体定義。
		struct SConstantBuffer {
			Matrix mRot;			//回転行列。
			Matrix mView;			//ビュー行列。
			Matrix mProj;			//プロジェクション行列。
		};
		struct SColorCB {
			Vector4 mColor;			//ポリゴンまたは線分の色。
		};
		/// <summary>
		/// ライン。
		/// </summary>
		struct Line {
			Vector3 start;		//始点。
			Vector3 end;		//終点。
		};
		CellBin* m_cellBin;					//読み込み用バイナリデータセル。リファクタリングしたらたぶんいらない。
		std::vector<Cell> m_cell;			//AStarで使うセル。
		ConstantBuffer m_CB;				//コンスタントバッファー。
		std::vector<Vector3> m_cellPos;			//セルの位置リスト。
		unsigned int m_numCell = 0;			//セルの数。
		Vector3 m_eye;						//視点。

		//NaviMesh表示用メンバ。
		VertexBuffer m_vertexBuffer;		//頂点バッファー。
		IndexBuffer m_indexBuffer;			//インデックスバッファー。
		PipelineState m_pipelineState;		//パイプラインステート。
		RootSignature m_rootSignature;		//ルートシグネチャ。
		DescriptorHeap m_heap;				//ディスクリプタヒープ。
		//セルワイヤーフレーム表示用メンバ。
		VertexBuffer m_vertexBuck;			//背景用頂点バッファー。
		std::vector<int> m_indexs;			//インデックスバッファーのリスト。
		IndexBuffer m_indexBuck;			//背景用インデックスバッファー。
		PipelineState m_pipelineStateBuck;	//背景用パイプラインステート。
		//隣接セル表示用メンバ。
		VertexBuffer m_lineVertexBuffer;		//線分描画の頂点バッファー。
		std::vector<int> m_lineIndexs;			//線分描画のインデックス。
		IndexBuffer m_lineIndexBuffer;			//線分描画インデックスバッファー。
		PipelineState m_lineDrawPipelineState;	//線分描画パイプラインステート。
		std::vector< Line> m_linkCellLine;		//隣接セルを表すラインの配列。
		//エージェントのルート描画用レンダー。
		bool m_rootInited = false;				//初期化フラグ。init作るのめんどくさいからまぁいいや。
		PipelineState m_rootDrawPipelineState;	//線分描画パイプラインステート。
		VertexBuffer m_rootVertexBuffer;		//ルート描画用頂点。
		std::vector<int> m_rootIndexs;			//ルートインデックス。
		IndexBuffer m_rootIndexBuffer;			//線分描画インデックスバッファー。
		std::vector<Line> m_rootCellLine;		//隣接セルを表すラインの配列。
	};
}
