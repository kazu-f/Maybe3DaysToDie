#include "stdafx.h"
#include "DefferdShading.h"

namespace Engine {
	namespace {
		struct SSimpleVertex {
			Vector4 pos;
			Vector2 tex;
		};

		const wchar_t* FX_FILE_PATH = L"Assets/shader/defferd.fx";
		const char* VS_ENTRY = "VSMain";
		const char* PS_ENTRY = "PSMain";

	}

	void CDefferdShading::Init()
	{
		//�V�F�[�_�[�B
		InitShader();
		//�p�C�v���C���X�e�[�g�B
		InitPipelineState();
		//�萔�o�b�t�@�B
		InitConstantBuffer();
		//�f�B�X�N���v�^�q�[�v�B
		CreateDescriptorHeap();
		//�l�p�`�v���~�e�B�u�B
		InitPrimitive();
	}
	void CDefferdShading::Render(RenderContext& rc)
	{
		//�萔�o�b�t�@�̍X�V�B
		SDefferdCB cb;
		cb.mViewProjInv = MainCamera().GetViewProjectionMatrix();
		cb.mViewProjInv.Inverse();			//�t�s��ɂ���B
		m_constantBuffer.CopyToVRAM(cb);

		auto& mainRT = GraphicsEngine()->GetMainRenderTarget();

		//���C�������_�����O�^�[�Q�b�g�`��\�҂��B
		rc.WaitUntilToPossibleSetRenderTarget(mainRT);
		//
		rc.SetRenderTargetAndViewport(&mainRT);
		//���[�g�V�O�l�`����ݒ�B
		rc.SetRootSignature(CPipelineStatesDefault::m_modelDrawRootSignature);
		//�p�C�v���C���X�e�[�g��ݒ�B
		rc.SetPipelineState(m_defferdPipelineState);
		//�f�B�X�N���v�^�q�[�v��ݒ肷��B
		rc.SetDescriptorHeap(m_defferdDescriptorHeap);
		//�t���X�N���[���`��B
		m_primitive.Draw(rc);
		//�`�抮���҂��B
		rc.WaitUntilFinishDrawingToRenderTarget(mainRT);
	}

	void CDefferdShading::InitPrimitive()
	{
		SSimpleVertex vertices[] =
		{
			{
				Vector4(-1.0f,-1.0f,0.0f,1.0f),
				Vector2(0.0f,1.0f)
			},
			{
				Vector4(1.0f,-1.0f,0.0f,1.0f),
				Vector2(1.0f,1.0f)
			},
			{
				Vector4(-1.0f,1.0f,0.0f,1.0f),
				Vector2(0.0f,0.0f)
			},
			{
				Vector4(1.0f,1.0f,0.0f,1.0f),
				Vector2(1.0f,0.0f)
			}
		};
		short indices[] = { 0,1,2,3 };
		PrimitiveInitData primitiveData;
		//���_�o�b�t�@�̏��
		primitiveData.vertexSize = sizeof(vertices);
		primitiveData.vertexStride = sizeof(SSimpleVertex);
		primitiveData.pSrcVertexBuffer = vertices;
		//�C���f�b�N�X�o�b�t�@�̏��
		primitiveData.indexSize = sizeof(indices);
		primitiveData.indexStride = sizeof(short);
		primitiveData.pSrcIndexBuffer = indices;
		//�v���~�e�B�u�g�|���W�[�B
		primitiveData.topology = enPrimitiveTopology_TriangleStrip;

		//�쐬�B
		m_primitive.Create(primitiveData);
	}
	void CDefferdShading::InitShader()
	{
		m_vsDefferd.LoadVS(FX_FILE_PATH, VS_ENTRY);
		m_psDefferd.LoadPS(FX_FILE_PATH, PS_ENTRY);
	}
	void CDefferdShading::InitPipelineState()
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
		psoDesc.pRootSignature = CPipelineStatesDefault::m_modelDrawRootSignature.Get();
		psoDesc.VS = CD3DX12_SHADER_BYTECODE(m_vsDefferd.GetCompiledBlob());
		psoDesc.PS = CD3DX12_SHADER_BYTECODE(m_psDefferd.GetCompiledBlob());
		psoDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
		psoDesc.RasterizerState.CullMode = D3D12_CULL_MODE_NONE;
		psoDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
		psoDesc.DepthStencilState.DepthEnable = FALSE;
		psoDesc.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ZERO;
		psoDesc.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_LESS_EQUAL;
		psoDesc.DepthStencilState.StencilEnable = FALSE;
		psoDesc.SampleMask = UINT_MAX;
		psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
		psoDesc.NumRenderTargets = 1;
		psoDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
		psoDesc.DSVFormat = DXGI_FORMAT_D32_FLOAT;
		psoDesc.BlendState.IndependentBlendEnable = FALSE;
		psoDesc.SampleDesc.Count = 1;
		m_defferdPipelineState.Init(psoDesc);
	}
	void CDefferdShading::InitConstantBuffer()
	{
		//�萔�o�b�t�@�̍쐬�B
		m_constantBuffer.Init(sizeof(SDefferdCB), nullptr);
	}
	void CDefferdShading::CreateDescriptorHeap()
	{
		//G-Buffer�B
		CGBufferRender* gBuffer = GraphicsEngine()->GetGBuffer().get();
		//���C�g�}�l�[�W���[�B
		auto* ligMgr = GraphicsEngine()->GetLightManager().get();
		//�萔�o�b�t�@�B
		m_defferdDescriptorHeap.RegistConstantBuffer(0, m_constantBuffer);
		m_defferdDescriptorHeap.RegistConstantBuffer(1, ligMgr->GetLightParamConstantBuffer());
		//�V�F�[�_�[���\�[�X�B
		int srvNo = 0;
		for (; srvNo < static_cast<int>(EnGBuffer::enGBufferNum); srvNo++)
		{
			m_defferdDescriptorHeap.RegistShaderResource(srvNo, gBuffer->GetGBufferTexture(static_cast<EnGBuffer>(srvNo)));
		}
		m_defferdDescriptorHeap.RegistShaderResource(srvNo, m_cubeMapTexture);
		srvNo++;
		m_defferdDescriptorHeap.RegistShaderResource(srvNo, ligMgr->GetDirectionLightStructuredBuffer());
		srvNo++;


		//�쐬�B
		m_defferdDescriptorHeap.Commit();
	}
}