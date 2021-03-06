#include "stdafx.h"
#include "NVMDebugDraw.h"

void NVMDebugDraw::CreateBuffers(std::vector<int>& indexList,int indexCount)
{
	m_indexCount = indexCount;
	ReleaseBuffers();
	CreateVertexBuffers();
	CreateIndexBuffers(indexList);
}

void NVMDebugDraw::ReleaseBuffers()
{
	m_vertexBuffer.release();
	m_lineVertexBuffer.release();
	m_indexBuffer.release();
	m_lineIndexBuffer.release();
	m_lineIndexs.clear();
}

void NVMDebugDraw::CreateVertexBuffers()
{
	//頂点バッファー初期化。
	m_vertexBuffer = std::make_unique<VertexBuffer>();
	m_vertexBuffer->Init(sizeof(m_allCellPos[0]) * m_allCellPos.size(), sizeof(m_allCellPos[0]));
	m_vertexBuffer->Copy(&m_allCellPos[0]);

	//セルから、隣接セルに向かう線分の頂点バッファーの形成。
	//頂点バッファを形成していく。
	m_lineVertexBuffer = std::make_unique<VertexBuffer>();
	m_lineVertexBuffer->Init(sizeof(Line) * m_linkCellLine.size(), sizeof(Line::start));
	m_lineVertexBuffer->Copy(&m_linkCellLine[0]);

}

void NVMDebugDraw::CreateIndexBuffers(std::vector<int>& indexList)
{
	//インデックスバッファー初期化。
	m_indexBuffer = std::make_unique<IndexBuffer>();
	m_indexBuffer->Init(sizeof(indexList[0]) * indexList.size(), sizeof(indexList[0]));
	m_indexBuffer->Copy(&indexList[0]);
	indexSize = indexList.size();

	//セルから、隣接セルに向かう線分のインデックスバッファーの形成。
	//次にインデックスバッファー。
	//インデックスを形成。
	for (int indexs = 0; indexs < m_linkCellLine.size() * 2; indexs++) {
		m_lineIndexs.push_back(indexs);
	}
	//バッファー作成。
	m_lineIndexBuffer = std::make_unique<IndexBuffer>();
	m_lineIndexBuffer->Init(sizeof(m_lineIndexs[0]) * m_lineIndexs.size(), sizeof(m_lineIndexs[0]));
	m_lineIndexBuffer->Copy(&m_lineIndexs[0]);
}

void NVMDebugDraw::InitPipelineState(PipelineState& pipelineState, RootSignature& rs, Shader& vs, Shader& ps, bool isWire, D3D12_PRIMITIVE_TOPOLOGY_TYPE topology)
{

	// 頂点レイアウトを定義する。
	D3D12_INPUT_ELEMENT_DESC inputElementDescs[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
	};

	//パイプラインステートを作成。
	D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc = { 0 };
	psoDesc.InputLayout = { inputElementDescs, _countof(inputElementDescs) };
	psoDesc.pRootSignature = rs.Get();
	psoDesc.VS = CD3DX12_SHADER_BYTECODE(vs.GetCompiledBlob());
	psoDesc.PS = CD3DX12_SHADER_BYTECODE(ps.GetCompiledBlob());
	psoDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
	if (isWire) {
		psoDesc.RasterizerState.FillMode = D3D12_FILL_MODE_WIREFRAME;
	}
	else {
		psoDesc.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID;
	}

	psoDesc.RasterizerState.CullMode = D3D12_CULL_MODE_NONE;
	psoDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
	psoDesc.DepthStencilState.DepthEnable = TRUE;
	psoDesc.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
	psoDesc.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_LESS_EQUAL;
	psoDesc.DepthStencilState.StencilEnable = FALSE;
	psoDesc.SampleMask = UINT_MAX;
	psoDesc.PrimitiveTopologyType = topology;
	psoDesc.NumRenderTargets = 1;
	psoDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
	psoDesc.DSVFormat = DXGI_FORMAT_D32_FLOAT;
	psoDesc.SampleDesc.Count = 1;
	psoDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
	pipelineState.Init(psoDesc);
}

bool NVMDebugDraw::SubStart()
{
	m_isCellDraw = true;
	m_isLinkDraw = true;
	return true;
}

void NVMDebugDraw::Update()
{
	if (InputKeyCode().IsTriggerKey(VK_F1)) {
		m_isCellDraw = !m_isCellDraw;
	}
	if (InputKeyCode().IsTriggerKey(VK_F2)) {
		m_isLinkDraw = !m_isLinkDraw;
	}
}

void NVMDebugDraw::Init()
{
	//定数バッファ初期化。
	m_CB.Init(sizeof(SConstantBuffer), nullptr);

	//ルートシグネチャを初期化。
	m_rootSignature.Init(
		D3D12_FILTER_MIN_MAG_MIP_LINEAR,
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP,
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP,
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP
	);

	Shader vs, ps, psWire, psLine, psLineRoot;
	vs.LoadVS(L"Assets/shader/NVMDraw.fx", "VSMain");
	ps.LoadPS(L"Assets/shader/NVMDraw.fx", "PSMain");
	psWire.LoadPS(L"Assets/shader/NVMDraw.fx", "PSMainWire");
	psLine.LoadPS(L"Assets/shader/NVMDraw.fx", "PSMainLine");
	psLineRoot.LoadPS(L"Assets/shader/NVMDraw.fx", "PSMainLineRoot");

	//ディスクリプタヒープ設定。
	m_heap.RegistConstantBuffer(0, m_CB);
	m_heap.Commit();

	//パイプラインステートを作成。
	InitPipelineState(m_pipelineState, m_rootSignature, vs, ps, false, D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE);
	//ワイヤーフレーム用のパイプラインステート作成。
	InitPipelineState(m_pipelineStateBuck, m_rootSignature, vs, psWire, true, D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE);
	//線分描画用のパイプラインステート作成。
	InitPipelineState(m_lineDrawPipelineState, m_rootSignature, vs, psLine, false, D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE);

	D3D12_INPUT_ELEMENT_DESC inputElementDescs[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
	};
}

void NVMDebugDraw::OnForwardRender(RenderContext& rc)
{
	Quaternion qRot;
	qRot.SetRotationDegY(0.0f);
	//まずはカメラの行列を送る。
	SConstantBuffer cb;
	cb.mRot.MakeRotationFromQuaternion(qRot);
	cb.mView = MainCamera().GetViewMatrix();
	cb.mProj = MainCamera().GetProjectionMatrix();
	m_CB.CopyToVRAM(&cb);

	//描画。
	rc.SetRootSignature(m_rootSignature);
	rc.SetDescriptorHeap(m_heap);

	if (m_isCellDraw) {
		rc.SetPipelineState(m_pipelineState);
		rc.SetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		rc.SetVertexBuffer(*m_vertexBuffer);
		rc.SetIndexBuffer(*m_indexBuffer);
		rc.DrawIndexed(m_indexCount);

		////パラメーターをパイプライン描画ように変更。
		rc.SetPipelineState(m_pipelineStateBuck);
		rc.DrawIndexed(m_indexCount);
	}
	if (m_isLinkDraw) {
		////パラメーターを線分用描画に変更して、描画。
		rc.SetPipelineState(m_lineDrawPipelineState);
		rc.SetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_LINELIST);
		rc.SetVertexBuffer(*m_lineVertexBuffer);
		rc.SetIndexBuffer(*m_lineIndexBuffer);
		rc.DrawIndexed(m_lineIndexs.size());
	}
}
