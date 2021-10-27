#include "stdafx.h"
#include "NVMDebugDraw.h"

void NVMDebugDraw::InitPipelineState(PipelineState& pipelineState, RootSignature& rs, Shader& vs, Shader& ps, bool isWire, D3D12_PRIMITIVE_TOPOLOGY_TYPE topology)
{

	// ���_���C�A�E�g���`����B
	D3D12_INPUT_ELEMENT_DESC inputElementDescs[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
	};

	//�p�C�v���C���X�e�[�g���쐬�B
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

void NVMDebugDraw::Init(std::vector<short>& indexList)
{
	//���_�o�b�t�@�[�������B
	m_vertexBuffer.Init(sizeof(m_allCellPos[0]) * m_allCellPos.size(), sizeof(m_allCellPos[0]));
	m_vertexBuffer.Copy(&m_allCellPos[0]);
	//�C���f�b�N�X�o�b�t�@�[�������B
	m_indexBuffer.Init(sizeof(indexList[0]) * indexList.size(), sizeof(indexList[0]));
	m_indexBuffer.Copy(&indexList[0]);
	indexSize = indexList.size();

	//�Z������A�אڃZ���Ɍ����������̒��_�o�b�t�@�[�ƃC���f�b�N�X�o�b�t�@�[�̌`���B
	//���_�o�b�t�@���`�����Ă����B
	m_lineVertexBuffer.Init(sizeof(Line) * m_linkCellLine.size(), sizeof(Line::start));
	m_lineVertexBuffer.Copy(&m_linkCellLine[0]);
	//���ɃC���f�b�N�X�o�b�t�@�[�B
	//�C���f�b�N�X���`���B
	for (int indexs = 0; indexs < m_linkCellLine.size() * 2; indexs++) {
		m_lineIndexs.push_back(indexs);
	}
	//�o�b�t�@�[�쐬�B
	m_lineIndexBuffer.Init(sizeof(m_lineIndexs[0]) * m_lineIndexs.size(), sizeof(m_lineIndexs[0]));
	m_lineIndexBuffer.Copy(&m_lineIndexs[0]);

	//�萔�o�b�t�@�������B
	m_CB.Init(sizeof(SConstantBuffer), nullptr);

	//���[�g�V�O�l�`�����������B
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

	//�f�B�X�N���v�^�q�[�v�ݒ�B
	m_heap.RegistConstantBuffer(0, m_CB);
	m_heap.Commit();

	//�p�C�v���C���X�e�[�g���쐬�B
	InitPipelineState(m_pipelineState, m_rootSignature, vs, ps, false, D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE);
	//���C���[�t���[���p�̃p�C�v���C���X�e�[�g�쐬�B
	InitPipelineState(m_pipelineStateBuck, m_rootSignature, vs, psWire, true, D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE);
	//�����`��p�̃p�C�v���C���X�e�[�g�쐬�B
	InitPipelineState(m_lineDrawPipelineState, m_rootSignature, vs, psLine, false, D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE);

	D3D12_INPUT_ELEMENT_DESC inputElementDescs[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
	};
}

void NVMDebugDraw::Render(int& vertexCount)
{
	Quaternion qRot;
	qRot.SetRotationDegY(0.0f);
	//�܂��̓J�����̍s��𑗂�B
	SConstantBuffer cb;
	cb.mRot.MakeRotationFromQuaternion(qRot);
	cb.mView = MainCamera().GetViewMatrix();
	cb.mProj = MainCamera().GetProjectionMatrix();
	m_CB.CopyToVRAM(&cb);

	//�`��B
	GraphicsEngine()->GetRenderContext().SetRootSignature(m_rootSignature);
	GraphicsEngine()->GetRenderContext().SetPipelineState(m_pipelineState);
	GraphicsEngine()->GetRenderContext().SetDescriptorHeap(m_heap);

	GraphicsEngine()->GetRenderContext().SetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	GraphicsEngine()->GetRenderContext().SetVertexBuffer(m_vertexBuffer);
	GraphicsEngine()->GetRenderContext().SetIndexBuffer(m_indexBuffer);
	GraphicsEngine()->GetRenderContext().DrawIndexed(vertexCount);

	////�p�����[�^�[���p�C�v���C���`��悤�ɕύX�B
	GraphicsEngine()->GetRenderContext().SetPipelineState(m_pipelineStateBuck);
	GraphicsEngine()->GetRenderContext().DrawIndexed(vertexCount);

	////�p�����[�^�[������p�`��ɕύX���āA�`��B
	GraphicsEngine()->GetRenderContext().SetPipelineState(m_lineDrawPipelineState);
	GraphicsEngine()->GetRenderContext().SetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_LINELIST);
	GraphicsEngine()->GetRenderContext().SetVertexBuffer(m_lineVertexBuffer);
	GraphicsEngine()->GetRenderContext().SetIndexBuffer(m_lineIndexBuffer);
	GraphicsEngine()->GetRenderContext().DrawIndexed(m_lineIndexs.size());
}
