#pragma once

#include "NVMGenerator.h"
//#include "TerrainManager/TerrainRender/TerrainRender.h"

class NVMDebugDraw : public prefab::IRenderer
{
	using VertexBufferPtr = std::unique_ptr<VertexBuffer>;
	using IndexBufferPtr = std::unique_ptr<IndexBuffer>;
public:	
	//ライン。
	struct Line {
		Vector3 start;		//始点。
		Vector3 end;		//終点。
	};
public:
	bool SubStart()override final;
	void Update()override final;
	/// <summary>
	/// 描画用の初期化。
	/// </summary>
	/// <param name="indexList"></param>
	void Init();
	/// <summary>
	/// 描画。
	/// </summary>
	/// <param name="vertexCount"></param>
	void OnForwardRender(RenderContext& rc);
	/// <summary>
	/// 頂点を登録。
	/// </summary>
	/// <param name="pos"></param>
	void PushVertex(Vector3& pos)
	{
		m_allCellPos.push_back(pos);
	}
	/// <summary>
	/// 隣接セルに向かうラインを登録。
	/// </summary>
	/// <param name="toLinkCellLine"></param>
	void PushToLinkCellLine(Line& toLinkCellLine)
	{
		m_linkCellLine.push_back(toLinkCellLine);
	}
	/// <summary>
	/// セル情報をリセット。
	/// </summary>
	void ClearCellData()
	{
		m_allCellPos.clear();
		m_linkCellLine.clear();
	}
	/// <summary>
	/// 頂点バッファとインデックスバッファを作成する。
	/// </summary>
	void CreateBuffers(std::vector<int>& indexList, int indexCount);
private:
	/// <summary>
	/// バッファを開放する処理。
	/// </summary>
	void ReleaseBuffers();
	/// <summary>
	/// 頂点バッファを作成。
	/// </summary>
	void CreateVertexBuffers();
	/// <summary>
	/// インデックスバッファを作成。
	/// </summary>
	void CreateIndexBuffers(std::vector<int>& indexList);
private:
	/// <summary>
	/// パイプラインステートを作成。
	/// </summary>
	/// <param name="pipelineState">出力先のパイプラインステート。</param>
	/// <param name="rs">ルートシグネチャー。</param>
	/// <param name="vs">頂点シェーダー。</param>
	/// <param name="ps">ピクセルシェーダー。</param>
	/// <param name="isWire">ワイヤーフレーム描画？？</param>
	void InitPipelineState(PipelineState& pipelineState, RootSignature& rs, Shader& vs, Shader& ps, bool isWire, D3D12_PRIMITIVE_TOPOLOGY_TYPE topology);
	//定数バッファの構造体定義。
	struct SConstantBuffer {
		Matrix mRot;			//回転行列。
		Matrix mView;			//ビュー行列。
		Matrix mProj;			//プロジェクション行列。
	};

	std::vector<Vector3> m_allCellPos;	//セルを構成する３頂点のリスト。
	//NaviMesh表示用メンバ。
	ConstantBuffer m_CB;				//コンスタントバッファー。
	VertexBufferPtr m_vertexBuffer;		//頂点バッファー。
	IndexBufferPtr m_indexBuffer;			//インデックスバッファー。
	PipelineState m_pipelineState;		//パイプラインステート。
	RootSignature m_rootSignature;		//ルートシグネチャ。
	DescriptorHeap m_heap;				//ディスクリプタヒープ。
	//セルワイヤーフレーム表示用メンバ。
	//VertexBuffer m_vertexBuck;			//背景用頂点バッファー。
	int indexSize = 0;
	//IndexBuffer m_indexBuck;			//背景用インデックスバッファー。
	PipelineState m_pipelineStateBuck;	//背景用パイプラインステート。
	//隣接セル表示用メンバ。
	VertexBufferPtr m_lineVertexBuffer;		//線分描画の頂点バッファー。
	std::vector<int> m_lineIndexs;		//線分描画のインデックス。
	IndexBufferPtr m_lineIndexBuffer;			//線分描画インデックスバッファー。
	PipelineState m_lineDrawPipelineState;	//線分描画パイプラインステート。
	std::vector<Line> m_linkCellLine;		//隣接セルを表すラインの配列。
	int m_indexCount = 0;
	bool m_isCellDraw = false;				//セルのデバッグ表示をするか。
	bool m_isLinkDraw = false;				//リンクの線を表示するか。
};

