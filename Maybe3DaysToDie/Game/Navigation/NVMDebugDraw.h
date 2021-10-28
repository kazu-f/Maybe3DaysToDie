#pragma once

#include "NVMGenerator.h"
//#include "TerrainManager/TerrainRender/TerrainRender.h"

class NVMDebugDraw
{
public:	
	//ライン。
	struct Line {
		Vector3 start;		//始点。
		Vector3 end;		//終点。
	};
public:
	/// <summary>
	/// 描画用の初期化。
	/// </summary>
	/// <param name="indexList"></param>
	void Init(std::vector<short>& indexList);
	/// <summary>
	/// 描画。
	/// </summary>
	/// <param name="vertexCount"></param>
	void Render(int& vertexCount);
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
	VertexBuffer m_vertexBuffer;		//頂点バッファー。
	IndexBuffer m_indexBuffer;			//インデックスバッファー。
	PipelineState m_pipelineState;		//パイプラインステート。
	RootSignature m_rootSignature;		//ルートシグネチャ。
	DescriptorHeap m_heap;				//ディスクリプタヒープ。
	//セルワイヤーフレーム表示用メンバ。
	VertexBuffer m_vertexBuck;			//背景用頂点バッファー。
	int indexSize = 0;
	IndexBuffer m_indexBuck;			//背景用インデックスバッファー。
	PipelineState m_pipelineStateBuck;	//背景用パイプラインステート。
	//隣接セル表示用メンバ。
	VertexBuffer m_lineVertexBuffer;		//線分描画の頂点バッファー。
	std::vector<short> m_lineIndexs;		//線分描画のインデックス。
	IndexBuffer m_lineIndexBuffer;			//線分描画インデックスバッファー。
	PipelineState m_lineDrawPipelineState;	//線分描画パイプラインステート。
	std::vector<Line> m_linkCellLine;		//隣接セルを表すラインの配列。
};

