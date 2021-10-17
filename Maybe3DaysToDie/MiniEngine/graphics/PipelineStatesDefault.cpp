#include "MiniEngine.h"
#include "PipelineStatesDefault.h"

namespace Engine
{
	//�V�F�[�_�[�̃t�@�C���p�X�ƃG���g���֐����B
	const wchar_t* CPipelineStatesDefault::MODEL_SHADER_PATH = L"Assets/shader/model.fx";								//���f���V�F�[�_�[�̃t�@�C���p�X�B
	const char* CPipelineStatesDefault::VS_MODEL_ENTRY_POINT = "VSMain";												//�ʏ탂�f���̒��_�V�F�[�_�[�B
	const char* CPipelineStatesDefault::VS_MODELINSTANCING_ENTRY_POINT = "VSMainInstancing";							//�C���X�^���V���O���f���̒��_�V�F�[�_�[�B
	const char* CPipelineStatesDefault::VS_SKINMODEL_ENTRY_POINT = "VSMainSkin";										//�X�L�����f���̒��_�V�F�[�_�[�B
	const char* CPipelineStatesDefault::VS_SKINMODELINTANCING_ENTRY_POINT = "VSMainSkinInstancing";						//�X�L������C���X�^���V���O���f���̒��_�V�F�[�_�[�B
	const char* CPipelineStatesDefault::VS_MODEL_SHADOW_ENTRY_POINT = "VSMainNonSkinShadowMap";							//�V���h�E�}�b�v�p���_�V�F�[�_�[�B
	const char* CPipelineStatesDefault::VS_MODEL_SHADOWINSTANCING_ENTRY_POINT = "VSMainNonSkinInstancingShadowMap";		//�V���h�E�}�b�v�E�C���X�^���V���O���f���p���_�V�F�[�_�[�B
	const char* CPipelineStatesDefault::VS_SKINMODEL_SHADOW_ENTRY_POINT = "VSMainSkinShadowMap";						//�V���h�E�}�b�v�E�X�L�����胂�f���p���_�V�F�[�_�[�B
	const char* CPipelineStatesDefault::VS_SKINMODEL_SHADOWINSTANCING_ENTRY_POINT = "VSMainSkinInstancingShadowMap";	//�V���h�E�}�b�v�E�X�L������C���X�^���V���O���f���p���_�V�F�[�_�[�B
	const char* CPipelineStatesDefault::PS_GBUFFER_ENTRY_POINT = "PSMain_RenderGBuffer";								//G-Bffer�ɏ������ރs�N�Z���V�F�[�_�[�B
	const char* CPipelineStatesDefault::PS_SHADOW_ENTRY_POINT = "PSMainShadowMap";										//�V���h�E�}�b�v�ɏ������ރs�N�Z���V�F�[�_�[�B
	const char* CPipelineStatesDefault::PS_TRANS_ENTRY_POINT = "PSMain";												//�t�H���[�h�p���_�V�F�[�_�[�B

	const wchar_t* CPipelineStatesDefault::COPY_SHADER_PATH = L"Assets/shader/copy.fx";				//�R�s�[�p�V�F�[�_�[�̃t�@�C���p�X�B
	const char* CPipelineStatesDefault::VS_COPY_ENTRY_POINT = "VSMain";								//�R�s�[�p���_�V�F�[�_�[�B
	const char* CPipelineStatesDefault::PS_COPY_ENTRY_POINT = "PSMain";								//�R�s�[�p�s�N�Z���V�F�[�_�[�B

	//���f���p�̐ݒ�B
	RootSignature CPipelineStatesDefault::m_modelDrawRootSignature;			//���f���`��p�̃��[�g�V�O�l�`���B
	Shader CPipelineStatesDefault::m_vsModel;								//���f���p�̒��_�V�F�[�_�[�B
	Shader CPipelineStatesDefault::m_vsModelInstancing;						//�C���X�^���V���O���f���p�̒��_�V�F�[�_�[�B
	Shader CPipelineStatesDefault::m_vsSkinModel;							//���f���p�̒��_�V�F�[�_�[�B(�X�L������)
	Shader CPipelineStatesDefault::m_vsSkinModelInstancing;					//�C���X�^���V���O���f���p�̒��_�V�F�[�_�[�B(�X�L������)
	Shader CPipelineStatesDefault::m_psModel;								//���f���p�̃s�N�Z���V�F�[�_�[�B(G-Buffer�������݁B)
	Shader CPipelineStatesDefault::m_vsModelShadowMap;						//�V���h�E�}�b�v�̃��f���p�̒��_�V�F�[�_�[�B
	Shader CPipelineStatesDefault::m_vsModelShadowInstancing;				//�V���h�E�}�b�v�̃C���X�^���X���f���p�B
	Shader CPipelineStatesDefault::m_vsSkinModelShadowMap;					//�V���h�E�}�b�v�̃��f���p�̒��_�V�F�[�_�[�B(�X�L������)
	Shader CPipelineStatesDefault::m_vsSkinModelShadowInstancing;			//�V���h�E�}�b�v�̃C���X�^���X���f���p�B(�X�L������)
	Shader CPipelineStatesDefault::m_psModelShadowMap;						//�V���h�E�}�b�v�̃��f���p�̃s�N�Z���V�F�[�_�[�B
	Shader CPipelineStatesDefault::m_psTransModel;							//�������̃��f���p�̃s�N�Z���V�F�[�_�[�B

	PipelineState CPipelineStatesDefault::m_ModelPipelineState;				//���f���p�̃p�C�v���C���X�e�[�g�B
	PipelineState CPipelineStatesDefault::m_ModelInstancingPipelineState;	//�C���X�^���V���O���f���p�̃p�C�v���C���X�e�[�g�B
	PipelineState CPipelineStatesDefault::m_SkinModelPipelineState;				//���f���p�̃p�C�v���C���X�e�[�g�B(�X�L������)
	PipelineState CPipelineStatesDefault::m_SkinModelInstancingPipelineState;	//�C���X�^���V���O���f���p�̃p�C�v���C���X�e�[�g�B(�X�L������)
	PipelineState CPipelineStatesDefault::m_transModelPipelineState;		//���f���p�̃p�C�v���C���X�e�[�g(�������}�e���A��)�B
	PipelineState CPipelineStatesDefault::m_transSkinModelPipelineState;		//���f���p�̃p�C�v���C���X�e�[�g(�������}�e���A��)�B
	PipelineState CPipelineStatesDefault::m_transModelInstancingPipelineState;		//�C���X�^���V���O���f���p�̃p�C�v���C���X�e�[�g(�������}�e���A��)�B
	PipelineState CPipelineStatesDefault::m_transSkinModelInstancingPipelineState;		//�C���X�^���V���O���f���p�̃p�C�v���C���X�e�[�g(�������}�e���A��)(�X�L������)�B
	PipelineState CPipelineStatesDefault::m_ModelShadowPipelineState;		//�V���h�E�}�b�v�̃��f���p�̃p�C�v���C���X�e�[�g�B
	PipelineState CPipelineStatesDefault::m_ModelShadowInstancingPipelineState;		//�V���h�E�}�b�v�̃C���X�^���X���f���p�B
	PipelineState CPipelineStatesDefault::m_SkinModelShadowPipelineState;		//�V���h�E�}�b�v�̃��f���p�̃p�C�v���C���X�e�[�g�B(�X�L������)
	PipelineState CPipelineStatesDefault::m_SkinModelShadowInstancingPipelineState;		//�V���h�E�}�b�v�̃C���X�^���X���f���p�B(�X�L������)


	//�R�s�[�`��p�̐ݒ�B
	Shader CPipelineStatesDefault::m_vsCopy;								//�R�s�[�p���_�V�F�[�_�[�B
	Shader CPipelineStatesDefault::m_psCopy;								//�R�s�[�p�s�N�Z���V�F�[�_�[�B

	RootSignature CPipelineStatesDefault::m_copyRootSignature;				//�R�s�[�p�̃��[�g�V�O�l�`���B
	PipelineState CPipelineStatesDefault::m_copyPipelineState;				//�R�s�[�p�̃p�C�v���C���X�e�[�g�B


	void CPipelineStatesDefault::Init()
	{
		InitShaders();
		InitRootSignature();
		InitModelPipelineState();
		InitCopyPipelineState();
	}

	void CPipelineStatesDefault::InitShaders()
	{
		//���f���̒��_�V�F�[�_�[�B
		m_vsModel.LoadVS(MODEL_SHADER_PATH, VS_MODEL_ENTRY_POINT);
		m_vsModelInstancing.LoadVS(MODEL_SHADER_PATH, VS_MODELINSTANCING_ENTRY_POINT);
		m_vsSkinModel.LoadVS(MODEL_SHADER_PATH, VS_SKINMODEL_ENTRY_POINT);
		m_vsSkinModelInstancing.LoadVS(MODEL_SHADER_PATH, VS_SKINMODELINTANCING_ENTRY_POINT);

		//GBuffer�ɏ������ރs�N�Z���V�F�[�_�[�B
		m_psModel.LoadPS(MODEL_SHADER_PATH, PS_GBUFFER_ENTRY_POINT);

		//�V���h�E�}�b�v�֘A�B
		m_vsModelShadowMap.LoadVS(MODEL_SHADER_PATH, VS_MODEL_SHADOW_ENTRY_POINT);
		m_vsModelShadowInstancing.LoadVS(MODEL_SHADER_PATH, VS_MODEL_SHADOWINSTANCING_ENTRY_POINT);
		m_vsSkinModelShadowMap.LoadVS(MODEL_SHADER_PATH, VS_SKINMODEL_SHADOW_ENTRY_POINT);
		m_vsSkinModelShadowInstancing.LoadVS(MODEL_SHADER_PATH, VS_SKINMODEL_SHADOWINSTANCING_ENTRY_POINT);
		m_psModelShadowMap.LoadPS(MODEL_SHADER_PATH, PS_SHADOW_ENTRY_POINT);

		//���߃I�u�W�F�N�g�`��B
		m_psTransModel.LoadPS(MODEL_SHADER_PATH, PS_TRANS_ENTRY_POINT);

		//�R�s�[�p�V�F�[�_�[�B
		m_vsCopy.LoadVS(COPY_SHADER_PATH, VS_COPY_ENTRY_POINT);
		m_psCopy.LoadPS(COPY_SHADER_PATH, PS_COPY_ENTRY_POINT);
	}

	void CPipelineStatesDefault::InitRootSignature()
	{
		//���[�g�V�O�l�`�����������B
		m_modelDrawRootSignature.Init(
			D3D12_FILTER_MIN_MAG_MIP_LINEAR,
			D3D12_TEXTURE_ADDRESS_MODE_WRAP,
			D3D12_TEXTURE_ADDRESS_MODE_WRAP,
			D3D12_TEXTURE_ADDRESS_MODE_WRAP);
		//�R�s�[�`��p���[�g�V�O�l�`���B
		m_copyRootSignature.Init(
			D3D12_FILTER_MIN_MAG_MIP_LINEAR,
			D3D12_TEXTURE_ADDRESS_MODE_BORDER,
			D3D12_TEXTURE_ADDRESS_MODE_BORDER,
			D3D12_TEXTURE_ADDRESS_MODE_BORDER
		);
	}

	void CPipelineStatesDefault::InitModelPipelineState()
	{
		// ���_���C�A�E�g���`����B
		D3D12_INPUT_ELEMENT_DESC inputElementDescs[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
			{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
			{ "TANGENT", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 24, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
			{ "BINORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 36, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 48, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
			{ "BLENDINDICES", 0, DXGI_FORMAT_R32G32B32A32_SINT, 0, 56, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
			{ "BLENDWEIGHT", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 72, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		};

		//�p�C�v���C���X�e�[�g���쐬�B
		D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc = { 0 };
		psoDesc.InputLayout = { inputElementDescs, _countof(inputElementDescs) };
		psoDesc.pRootSignature = m_modelDrawRootSignature.Get();
		psoDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
		psoDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
		psoDesc.DepthStencilState.DepthEnable = TRUE;
		psoDesc.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
		psoDesc.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_LESS_EQUAL;
		psoDesc.DepthStencilState.StencilEnable = FALSE;
		psoDesc.SampleMask = UINT_MAX;
		psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
		psoDesc.NumRenderTargets = 6;
		psoDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;		//�A���x�h�J���[�o�͗p�B
		psoDesc.RTVFormats[1] = DXGI_FORMAT_R8G8B8A8_UNORM;			//�@���o�͗p�B	
		psoDesc.RTVFormats[2] = DXGI_FORMAT_R32G32B32A32_FLOAT;	//Z�l�B
		psoDesc.RTVFormats[3] = DXGI_FORMAT_R8G8B8A8_UNORM;			//�X�y�L�����B
		psoDesc.RTVFormats[4] = DXGI_FORMAT_R32_FLOAT;			//�e�B
		psoDesc.RTVFormats[5] = DXGI_FORMAT_R16G16_FLOAT;			//���˗��B
		psoDesc.DSVFormat = DXGI_FORMAT_D32_FLOAT;
		psoDesc.SampleDesc.Count = 1;


		//���f���̃p�C�v���C���X�e�[�g���쐬�B
		{
			psoDesc.VS = CD3DX12_SHADER_BYTECODE(m_vsModel.GetCompiledBlob());
			psoDesc.PS = CD3DX12_SHADER_BYTECODE(m_psModel.GetCompiledBlob());
			m_ModelPipelineState.Init(psoDesc);
		
			//�����ăC���X�^���V���O���f���p���쐬�B
			psoDesc.VS = CD3DX12_SHADER_BYTECODE(m_vsModelInstancing.GetCompiledBlob());
			m_ModelInstancingPipelineState.Init(psoDesc);
		
			//�X�L������B
			psoDesc.VS = CD3DX12_SHADER_BYTECODE(m_vsSkinModel.GetCompiledBlob());
			m_SkinModelPipelineState.Init(psoDesc);

			//�X�L������C���X�^���V���O���f���p���쐬�B
			psoDesc.VS = CD3DX12_SHADER_BYTECODE(m_vsSkinModelInstancing.GetCompiledBlob());
			m_SkinModelInstancingPipelineState.Init(psoDesc);
		}

		//�t�H�[�}�b�g���Z�b�g�B
		for (auto& format : psoDesc.RTVFormats)
		{
			format = DXGI_FORMAT_UNKNOWN;
		}

		//�V���h�E�}�b�v�p�̃p�C�v���C���X�e�[�g���쐬�B
		{
			//�ʏ�`��B
			psoDesc.VS = CD3DX12_SHADER_BYTECODE(m_vsModelShadowMap.GetCompiledBlob());
			psoDesc.PS = CD3DX12_SHADER_BYTECODE(m_psModelShadowMap.GetCompiledBlob());
			psoDesc.RTVFormats[0] = DXGI_FORMAT_R32_FLOAT;
			psoDesc.NumRenderTargets = 1;
			m_ModelShadowPipelineState.Init(psoDesc);
			//�C���X�^���V���O�`��B
			psoDesc.VS = CD3DX12_SHADER_BYTECODE(m_vsModelShadowInstancing.GetCompiledBlob());
			m_ModelShadowInstancingPipelineState.Init(psoDesc);

			//�X�L������B
			psoDesc.VS = CD3DX12_SHADER_BYTECODE(m_vsSkinModelShadowMap.GetCompiledBlob());
			m_SkinModelShadowPipelineState.Init(psoDesc);
			//�X�L������C���X�^���V���O�`��B
			psoDesc.VS = CD3DX12_SHADER_BYTECODE(m_vsSkinModelShadowInstancing.GetCompiledBlob());
			m_SkinModelShadowInstancingPipelineState.Init(psoDesc);

		}

		//�t�H�[�}�b�g���Z�b�g�B
		for (auto& format : psoDesc.RTVFormats)
		{
			format = DXGI_FORMAT_UNKNOWN;
		}

		//�������}�e���A���p�B
		{
			psoDesc.VS = CD3DX12_SHADER_BYTECODE(m_vsModel.GetCompiledBlob());
			psoDesc.PS = CD3DX12_SHADER_BYTECODE(m_psTransModel.GetCompiledBlob());
			psoDesc.RTVFormats[0] = DXGI_FORMAT_R32G32B32A32_FLOAT;		//�A���x�h�J���[�o�͗p�B
			psoDesc.NumRenderTargets = 1;
			psoDesc.BlendState.IndependentBlendEnable = TRUE;
			psoDesc.RasterizerState.CullMode = D3D12_CULL_MODE_NONE;
			psoDesc.BlendState.RenderTarget[0].BlendEnable = TRUE;
			psoDesc.BlendState.RenderTarget[0].SrcBlend = D3D12_BLEND_SRC_ALPHA;
			psoDesc.BlendState.RenderTarget[0].DestBlend = D3D12_BLEND_INV_SRC_ALPHA;
			psoDesc.BlendState.RenderTarget[0].BlendOp = D3D12_BLEND_OP_ADD;
			//�X�L�������B
			m_transModelPipelineState.Init(psoDesc);
			//�C���X�^���V���O�B
			psoDesc.VS = CD3DX12_SHADER_BYTECODE(m_vsModelInstancing.GetCompiledBlob());
			m_transModelInstancingPipelineState.Init(psoDesc);

			//�X�L������B
			psoDesc.VS = CD3DX12_SHADER_BYTECODE(m_vsSkinModel.GetCompiledBlob());
			m_transSkinModelPipelineState.Init(psoDesc);
			//�C���X�^���V���O�B
			psoDesc.VS = CD3DX12_SHADER_BYTECODE(m_vsSkinModelInstancing.GetCompiledBlob());
			m_transSkinModelInstancingPipelineState.Init(psoDesc);


		}
	}

	void CPipelineStatesDefault::InitCopyPipelineState()
	{

		D3D12_INPUT_ELEMENT_DESC inputElementDescs[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0 , 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 16, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
		};
		//�p�C�v���C���X�e�[�g���쐬�B
		D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc = { 0 };
		psoDesc.InputLayout = { inputElementDescs,_countof(inputElementDescs) };		//�z��Ɨv�f���B
		psoDesc.pRootSignature = m_copyRootSignature.Get();									//���[�g�V�O�l�`����ݒ�B
		psoDesc.VS = CD3DX12_SHADER_BYTECODE(m_vsCopy.GetCompiledBlob());
		psoDesc.PS = CD3DX12_SHADER_BYTECODE(m_psCopy.GetCompiledBlob());
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
		psoDesc.RTVFormats[0] = DXGI_FORMAT_R32G32B32A32_FLOAT;
		psoDesc.DSVFormat = DXGI_FORMAT_UNKNOWN;
		psoDesc.SampleDesc.Count = 1;
		//�R�s�[�p�p�C�v���C���X�e�[�g�B
		m_copyPipelineState.Init(psoDesc);
	}

}