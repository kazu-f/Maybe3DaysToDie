#include "MiniEngine.h"
#include "PhysicsDebugDraw.h"

namespace Engine {
	namespace {
		static const wchar_t* SHADER_FILEPATH = L"Assets/shader/linePrimitive.fx";
	}

	CPhysicsDebugDraw::CPhysicsDebugDraw()
	{
	}
	CPhysicsDebugDraw::~CPhysicsDebugDraw()
	{
	}
	void CPhysicsDebugDraw::Init()
	{
		InitBuffer();
		InitShader();
		m_rootSignature.Init(
			D3D12_FILTER_MIN_MAG_MIP_LINEAR,
			D3D12_TEXTURE_ADDRESS_MODE_WRAP,
			D3D12_TEXTURE_ADDRESS_MODE_WRAP,
			D3D12_TEXTURE_ADDRESS_MODE_WRAP);
		InitPipelineState();
		InitDescriptorHeap();
	}
	void CPhysicsDebugDraw::drawLine(const btVector3& from, const btVector3& to, const btVector3& color)
	{
		//���_���Z�b�g���Ă����B
		int baseIndex = m_numLine * 2;
		m_vertexData[baseIndex].Set(Vector3(from.x(), from.y(), from.z()));
		m_vertexData[baseIndex + 1].Set(Vector3(to.x(), to.y(), to.z()));
		m_numLine++;
	}
	void CPhysicsDebugDraw::EndDraw()
	{
		//�萔�o�b�t�@�̍X�V�B
		SConstantBuffer cb;
		cb.mView = MainCamera().GetViewMatrix();
		cb.mProj = MainCamera().GetProjectionMatrix();
		m_cb.CopyToVRAM(&cb);

		//���_�̃f�[�^�X�V�B
		m_vertexBuffer.Copy(&m_vertexData[0]);

		//���[�g�V�O�l�`����ݒ�B
		m_renderContext->SetRootSignature(m_rootSignature);
		//�p�C�v���C���X�e�[�g��ݒ�B
		m_renderContext->SetPipelineState(m_pipeLineState);
		//���_�o�b�t�@��ݒ�B
		m_renderContext->SetVertexBuffer(m_vertexBuffer);
		////�C���f�b�N�X�o�b�t�@��ݒ�B
		//m_renderContext->SetIndexBuffer(m_indexBuffer);
		//�v���~�e�B�u�g�|���W�[��ݒ肷��B
		m_renderContext->SetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_LINELIST);
		//�f�B�X�N���v�^�q�[�v��ݒ肷��B
		m_renderContext->SetDescriptorHeap(m_descriptorHeap);
		//�`��
		m_renderContext->Draw(m_numLine * 2);

	}
	void CPhysicsDebugDraw::InitBuffer()
	{
		//���_�o�b�t�@�B
		m_vertexBuffer.Init(static_cast<int>(m_vertexData.size()), sizeof(Vector4));
		m_vertexBuffer.Copy(&m_vertexData[0]);
		////�C���f�b�N�X�o�b�t�@�B
		//m_indexBuffer.Init(0, sizeof(int));
		//�萔�o�b�t�@�B
		m_cb.Init(sizeof(SConstantBuffer), nullptr);
	}
	void CPhysicsDebugDraw::InitShader()
	{
		m_vs.LoadVS(SHADER_FILEPATH, "VSMain");
		m_ps.LoadPS(SHADER_FILEPATH, "PSMain");
	}
	void CPhysicsDebugDraw::InitPipelineState()
	{
		// ���_���C�A�E�g���`����B
		D3D12_INPUT_ELEMENT_DESC inputElementDescs[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 16, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		};

		//�p�C�v���C���X�e�[�g���쐬�B
		D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc = { 0 };
		psoDesc.InputLayout = { inputElementDescs, _countof(inputElementDescs) };
		psoDesc.pRootSignature = m_rootSignature.Get();
		psoDesc.VS = CD3DX12_SHADER_BYTECODE(m_vs.GetCompiledBlob());
		psoDesc.PS = CD3DX12_SHADER_BYTECODE(m_ps.GetCompiledBlob());
		psoDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
		psoDesc.RasterizerState.CullMode = D3D12_CULL_MODE_BACK;
		psoDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
		psoDesc.DepthStencilState.DepthEnable = TRUE;
		psoDesc.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
		psoDesc.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_LESS_EQUAL;
		psoDesc.DepthStencilState.StencilEnable = FALSE;
		psoDesc.SampleMask = UINT_MAX;
		psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE;
		psoDesc.NumRenderTargets = 1;
		psoDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
		psoDesc.DSVFormat = DXGI_FORMAT_D32_FLOAT;
		psoDesc.SampleDesc.Count = 1;
		m_pipeLineState.Init(psoDesc);
	}
	void CPhysicsDebugDraw::InitDescriptorHeap()
	{
		//�萔�o�b�t�@��o�^�B
		m_descriptorHeap.RegistConstantBuffer(0, m_cb);

		//�o�^���m�肷��B
		m_descriptorHeap.Commit();
	}
}
