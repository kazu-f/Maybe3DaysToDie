#include "stdafx.h"
#include "Bloom.h"

namespace Engine {
	namespace {
		//���_�f�[�^�B
		struct SSimpleVertex {
			Vector4 pos;
			Vector2 tex;
		};
		//�V�F�[�_�[�f�[�^�B
		struct SShaderData {
			const wchar_t* filePath = nullptr;
			const char* funcName = nullptr;
		};
		
		const float BLOOM_WHEIGHT = 25.0f;

		const SShaderData VS = { L"Assets/shader/bloom.fx","VSMain" };		//�ėp���_�V�F�[�_�[�B
		const SShaderData PSLuminance = { L"Assets/shader/bloom.fx","PSSamplingLuminance" };	//�P�x���o�p�s�N�Z���V�F�[�_�[�B
		const SShaderData VSXBlur = { L"Assets/shader/bloom.fx","VSXBlur" };		//X�u���[�p���_�V�F�[�_�[�B
		const SShaderData VSYBlur = { L"Assets/shader/bloom.fx","VSYBlur" };		//Y�u���[�p���_�V�F�[�_�[�B
		const SShaderData PSBlur = { L"Assets/shader/bloom.fx","PSBlur" };			//�u���[�p���_�V�F�[�_�[�B
		const SShaderData PSCombine = { L"Assets/shader/bloom.fx","PSCombine" };	//�{�P�����p�̃s�N�Z���V�F�[�_�[�B

	}

	void CBloom::Init(const SPostEffectConfig& config)
	{
		if (!config.isBloom) {
			ENGINE_LOG("�u���[����K�p���Ȃ��B");
			return;
		}
		//���[�g�V�O�l�`�����쐬�B
		m_rootSignature.Init(
			D3D12_FILTER_MIN_MAG_MIP_LINEAR,
			D3D12_TEXTURE_ADDRESS_MODE_BORDER,
			D3D12_TEXTURE_ADDRESS_MODE_BORDER,
			D3D12_TEXTURE_ADDRESS_MODE_BORDER
		);

		//�V�F�[�_�[�������B
		InitShaders();
		//�����_�����O�^�[�Q�b�g���������B
		InitRenderTargets();
		//�p�C�v���C���X�e�[�g���������B
		InitPipelineState();

		for (auto& cb : m_blurParamCB) {
			//�萔�o�b�t�@���������B
			cb.Init(sizeof(m_blurParam), nullptr);
		}
		//�f�B�X�N���v�^�q�[�v���쐬�B
		CreateDescriptorHeap();

		m_isEnable = true;
	}
	void CBloom::InitRenderTargets()
	{
		int w = GraphicsEngine()->GetFrameBufferWidth();
		int h = GraphicsEngine()->GetFrameBufferHeight();
		//�P�x���o�p�̃����_�����O�^�[�Q�b�g���쐬�B
		bool result = m_luminanceRT.Create(w, h, 1, 1, DXGI_FORMAT_R32G32B32A32_FLOAT, DXGI_FORMAT_UNKNOWN);
		ENGINE_ASSERT(result, "�P�x���o�p�̃����_�����O�^�[�Q�b�g�̍쐬�Ɏ��s�B");

		//�_�E���T���v�����O�p�̃����_�����O�^�[�Q�b�g���쐬����B
		for (int i = 0; i < NUM_DOWN_SAMPRING_RT / 2; i++) {
			int shift = i + 1;		//�V�t�g���Z�Ɏg�����B
			int baseIndex = i * 2;	//�����_�����O�^�[�Q�b�g�̊J�n�ʒu�B
			//���u���[�p
			result = m_downSamplingRT[baseIndex].Create(
				w >> shift,
				h >> (shift - 1),
				1,
				1,
				DXGI_FORMAT_R32G32B32A32_FLOAT,
				DXGI_FORMAT_UNKNOWN
			);
			ENGINE_ASSERT(result, "���u���[�p�̃����_�����O�^�[�Q�b�g�̍쐬�Ɏ��s�B");


			//�c�u���[�p�B
			result = m_downSamplingRT[baseIndex + 1].Create(
				w >> shift,
				h >> shift,
				1,
				1,
				DXGI_FORMAT_R32G32B32A32_FLOAT,
				DXGI_FORMAT_UNKNOWN
			);
			ENGINE_ASSERT(result, "�c�u���[�p�̃����_�����O�^�[�Q�b�g�̍쐬�Ɏ��s�B");
		}
		//�{�P�摜�����p�̃����_�����O�^�[�Q�b�g�쐬�B
		result = m_combineRT.Create(w >> 2, h >> 2, 1, 1, DXGI_FORMAT_R32G32B32A32_FLOAT, DXGI_FORMAT_UNKNOWN);
		ENGINE_ASSERT(result,"�{�P�摜�����p�̃����_�����O�^�[�Q�b�g�̍쐬�Ɏ��s�B")
	}
	void CBloom::InitShaders()
	{
		//�V�F�[�_�[�����[�h�B
		m_vs.LoadVS(VS.filePath, VS.funcName);
		m_psLuminance.LoadPS(PSLuminance.filePath, PSLuminance.funcName);
		m_vsXBlur.LoadVS(VSXBlur.filePath, VSXBlur.funcName);
		m_vsYBlur.LoadVS(VSYBlur.filePath, VSYBlur.funcName);
		m_psBlur.LoadPS(PSBlur.filePath, PSBlur.funcName);
		m_psCombine.LoadPS(PSCombine.filePath, PSCombine.funcName);
	}
	void CBloom::InitPipelineState()
	{
		D3D12_INPUT_ELEMENT_DESC inputElementDescs[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0 , 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 16, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
		};
		//�p�C�v���C���X�e�[�g���쐬�B
		D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc = { 0 };
		psoDesc.InputLayout = { inputElementDescs,_countof(inputElementDescs) };		//�z��Ɨv�f���B
		psoDesc.pRootSignature = m_rootSignature.Get();									//���[�g�V�O�l�`����ݒ�B
		psoDesc.VS = CD3DX12_SHADER_BYTECODE(m_vs.GetCompiledBlob());
		psoDesc.PS = CD3DX12_SHADER_BYTECODE(m_psLuminance.GetCompiledBlob());
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
		//�P�x���o�p�p�C�v���C���X�e�[�g�B
		m_samplingLuminancePipelineState.Init(psoDesc);

		//X�u���[�p�̃p�C�v���C���X�e�[�g�B
		psoDesc.VS = CD3DX12_SHADER_BYTECODE(m_vsXBlur.GetCompiledBlob());
		psoDesc.PS = CD3DX12_SHADER_BYTECODE(m_psBlur.GetCompiledBlob());
		m_xblurLuminancePipelineState.Init(psoDesc);

		//Y�u���[�p�̃p�C�v���C���X�e�[�g�B
		psoDesc.VS = CD3DX12_SHADER_BYTECODE(m_vsYBlur.GetCompiledBlob());
		psoDesc.PS = CD3DX12_SHADER_BYTECODE(m_psBlur.GetCompiledBlob());
		m_yblurLuminancePipelineState.Init(psoDesc);

		//�{�P�摜�����p�̃p�C�v���C���X�e�[�g�B
		psoDesc.BlendState.RenderTarget[0].BlendEnable = FALSE;
		psoDesc.VS = CD3DX12_SHADER_BYTECODE(m_vs.GetCompiledBlob());
		psoDesc.PS = CD3DX12_SHADER_BYTECODE(m_psCombine.GetCompiledBlob());
		m_combineBlurImagePipelineState.Init(psoDesc);

		//�ŏI�����p�̃p�C�v���C���X�e�[�g�B
		psoDesc.BlendState.RenderTarget[0].BlendEnable = TRUE;
		psoDesc.BlendState.RenderTarget[0].BlendOp = D3D12_BLEND_OP_ADD;
		psoDesc.BlendState.RenderTarget[0].SrcBlend = D3D12_BLEND_ONE;
		psoDesc.BlendState.RenderTarget[0].DestBlend = D3D12_BLEND_ONE;
		psoDesc.VS = CD3DX12_SHADER_BYTECODE(CPipelineStatesDefault::m_vsCopy.GetCompiledBlob());
		psoDesc.PS = CD3DX12_SHADER_BYTECODE(CPipelineStatesDefault::m_psCopy.GetCompiledBlob());
		m_combineMainRenderTargetPipelineState.Init(psoDesc);
	}
	void CBloom::CreateDescriptorHeap()
	{
		//�P�x���o�p�̃f�B�X�N���v�^�q�[�v���쐬�B
		m_sampleLuminanceDescriptorHeap.RegistShaderResource(0, GraphicsEngine()->GetMainRenderTarget().GetRenderTargetTexture());
		m_sampleLuminanceDescriptorHeap.Commit();
		
		//�{�P�����p�̃f�B�X�N���v�^�q�[�v���쐬�B
		for (int i = 0; i < NUM_DOWN_SAMPRING_RT / 2; i++) {
			int index = i * 2 + 1;
			m_combineBlurDescriptorHeap.RegistShaderResource(i, m_downSamplingRT[index].GetRenderTargetTexture());
		}
		m_combineBlurDescriptorHeap.Commit();

		//�P�x���o�e�N�X�`����ݒ肷��B
		RenderTarget* prevRt = &m_luminanceRT;

		int rtNo = 0;
		for (int i = 0; i < NUM_DOWN_SAMPRING_RT / 2; i++) {
			//X�u���[�B
			{
				m_downSampleDescriptorHeap[rtNo].RegistShaderResource(0, prevRt->GetRenderTargetTexture());
				m_downSampleDescriptorHeap[rtNo].RegistConstantBuffer(0, m_blurParamCB[rtNo]);
				m_downSampleDescriptorHeap[rtNo].Commit();
			}
			//X�u���[���|�����e�N�X�`�����V�F�[�_�[���\�[�X�Ƃ��Ďg���B
			prevRt = &m_downSamplingRT[rtNo];
			rtNo++;
			//Y�u���[�B
			{
				m_downSampleDescriptorHeap[rtNo].RegistShaderResource(0,prevRt->GetRenderTargetTexture());
				m_downSampleDescriptorHeap[rtNo].RegistConstantBuffer(0, m_blurParamCB[rtNo]);
				m_downSampleDescriptorHeap[rtNo].Commit();
			}
			//�_�E���T���v�����O��̃e�N�X�`�����V�F�[�_�[���\�[�X�Ƃ��Ďg���B
			prevRt = &m_downSamplingRT[rtNo];
			rtNo++;
		}

		m_combineMainRenderTargetDescriptorHeap.RegistShaderResource(0, m_combineRT.GetRenderTargetTexture());
		m_combineMainRenderTargetDescriptorHeap.Commit();
	}
	void CBloom::UpdateWeight(float dispersion)
	{
		float total = 0;
		for (int i = 0; i < NUM_WEIGHTS; i++) {
			m_blurParam.weights[i] = expf(-0.5f * static_cast<float>(i * i) / dispersion);
			total += 2.0f * m_blurParam.weights[i];
		}
		//�K�i��
		for (int i = 0; i < NUM_WEIGHTS; i++) {
			m_blurParam.weights[i] /= total;
		}

	}
	void CBloom::SamplingLuminance(RenderContext& rc, CPostEffect* postEffect)
	{
		//���C�������_�����O�^�[�Q�b�g���e�N�X�`���Ƃ��ė��p�o����悤�ɂȂ�܂őҋ@�B
		rc.WaitUntilToPossibleSetRenderTarget(m_luminanceRT);
		//�p�C�v���C���X�e�[�g��ݒ�B
		rc.SetPipelineState(m_samplingLuminancePipelineState);
		//�����_�����O�^�[�Q�b�g���P�x���o�p�ɐ؂�ւ���B
		rc.SetRenderTargetAndViewport(&m_luminanceRT);
		//�N���A�J���[��ݒ�B
		const float clearColor[] = { 0.0f,0.0f,0.0f,1.0f };
		rc.ClearRenderTargetView(m_luminanceRT.GetRTVCpuDescriptorHandle(), clearColor);
		//�V�F�[�_�[���\�[�X�r���[�ƒ萔�o�b�t�@���Z�b�g����B
		rc.SetDescriptorHeap(m_sampleLuminanceDescriptorHeap);
		//�P�x���o�e�N�X�`����`�悷��B
		postEffect->DrawFullScreenQuad(rc);
		//�`�抮���҂��B
		rc.WaitUntilFinishDrawingToRenderTarget(m_luminanceRT);
	}
	void CBloom::BlurLuminanceTexture(RenderContext& rc, CPostEffect* postEffect)
	{
		//�e�N�X�`���B
		RenderTarget* prevRt = &m_luminanceRT;
		//�����_�����O�^�[�Q�b�g�̃C���f�b�N�X�B
		int rtIndex = 0;
		//�u���[���|���Ă����B
		for (int i = 0; i < NUM_DOWN_SAMPRING_RT / 2; i++){
			//X�u���[�B
			{
				m_blurParam.offset.x = 16.0f / prevRt->GetWidth();
				m_blurParam.offset.y = 0.0f;
				//�萔�o�b�t�@�̒l���X�V�B
				m_blurParamCB[rtIndex].CopyToVRAM(&m_blurParam);

				//���C�������_�����O�^�[�Q�b�g�Ƃ��ė��p�\�҂��B
				rc.WaitUntilToPossibleSetRenderTarget(m_downSamplingRT[rtIndex]);
				//X�u���[�p�̃p�C�v���C���X�e�[�g��ݒ�B
				rc.SetPipelineState(m_xblurLuminancePipelineState);
				//�����_�����O�^�[�Q�b�g��ݒ�B
				rc.SetRenderTargetAndViewport(&m_downSamplingRT[rtIndex]);
				//�V�F�[�_�[���\�[�X�r���[�ƒ萔�o�b�t�@�̃Z�b�g�B
				rc.SetDescriptorHeap(m_downSampleDescriptorHeap[rtIndex]);
				//�h���[�R�[���B
				postEffect->DrawFullScreenQuad(rc);
				//�`�抮���҂��B
				rc.WaitUntilFinishDrawingToRenderTarget(m_downSamplingRT[rtIndex]);
			}
			//Y�u���[�p�Ƀe�N�X�`���ύX�B
			prevRt = &m_downSamplingRT[rtIndex];
			rtIndex++;

			//Y�u���[�B
			{
				m_blurParam.offset.x = 0.0f;
				m_blurParam.offset.y = 16.0f/ prevRt->GetWidth();
				//�萔�o�b�t�@�̒l���X�V�B
				m_blurParamCB[rtIndex].CopyToVRAM(&m_blurParam);

				//���C�������_�����O�^�[�Q�b�g�Ƃ��ė��p�\�҂��B
				rc.WaitUntilToPossibleSetRenderTarget(m_downSamplingRT[rtIndex]);
				//Y�u���[�p�̃p�C�v���C���X�e�[�g��ݒ�B
				rc.SetPipelineState(m_yblurLuminancePipelineState);
				//�����_�����O�^�[�Q�b�g��ݒ�B
				rc.SetRenderTargetAndViewport(&m_downSamplingRT[rtIndex]);
				//�V�F�[�_�[���\�[�X�r���[�ƒ萔�o�b�t�@�̃Z�b�g�B
				rc.SetDescriptorHeap(m_downSampleDescriptorHeap[rtIndex]);
				//�h���[�R�[���B
				postEffect->DrawFullScreenQuad(rc);
				//�`�抮���҂��B
				rc.WaitUntilFinishDrawingToRenderTarget(m_downSamplingRT[rtIndex]);
			}
			//�_�E���T���v�����O������̃e�N�X�`���ɕύX�B
			prevRt = &m_downSamplingRT[rtIndex];
			rtIndex++;
		}

	}
	void CBloom::CombineBlurImage(RenderContext& rc, CPostEffect* postEffect)
	{
		//���C�������_�����O�^�[�Q�b�g�Ƃ��ė��p�\�҂��B
		rc.WaitUntilToPossibleSetRenderTarget(m_combineRT);
		//�{�P�����p�̃p�C�v���C���X�e�[�g���Z�b�g�B
		rc.SetPipelineState(m_combineBlurImagePipelineState);
		//�����_�����O�^�[�Q�b�g��ݒ�B
		rc.SetRenderTargetAndViewport(&m_combineRT);

		//�f�B�X�N���v�^�q�[�v���Z�b�g�B
		rc.SetDescriptorHeap(m_combineBlurDescriptorHeap);
		//�h���[�R�[���B
		postEffect->DrawFullScreenQuad(rc);
		//�`�抮���҂��B
		rc.WaitUntilFinishDrawingToRenderTarget(m_combineRT);
	}
	void CBloom::CombineMainRenderTarget(RenderContext& rc, CPostEffect* postEffect)
	{
		//���C�������_�����O�^�[�Q�b�g���擾�B
		auto& mainRT = GraphicsEngine()->GetMainRenderTarget();
		//�����_�����O�^�[�Q�b�g���p�\�҂��B
		rc.WaitUntilToPossibleSetRenderTarget(mainRT);
		//���C�������_�����O�^�[�Q�b�g�ɍ������邽�߂̃p�C�v���C���X�e�[�g���Z�b�g�B
		rc.SetPipelineState(m_combineMainRenderTargetPipelineState);
		//�����_�����O�^�[�Q�b�g��ݒ�B
		rc.SetRenderTargetAndViewport(&mainRT);

		//�f�B�X�N���v�^�q�[�v�̐ݒ�B
		rc.SetDescriptorHeap(m_combineMainRenderTargetDescriptorHeap);
		//�h���[�R�[���B
		postEffect->DrawFullScreenQuad(rc);
		//�����_�����O�^�[�Q�b�g�������݊����҂��B
		rc.WaitUntilFinishDrawingToRenderTarget(mainRT);
	}
	void CBloom::Render(RenderContext& rc, CPostEffect* postEffect)
	{
		if (!m_isEnable) {
			//����������Ă��Ȃ��B
			return;
		}

		//�d�݂��X�V�B
		UpdateWeight(BLOOM_WHEIGHT);
		//���[�g�V�O�l�`����ݒ�B
		rc.SetRootSignature(m_rootSignature);
		//�P�x�𒊏o�B
		SamplingLuminance(rc, postEffect);
		//�P�x���ڂ����B
		BlurLuminanceTexture(rc, postEffect);
		//�ڂ������摜�������B
		CombineBlurImage(rc, postEffect);
		//���C�������_�����O�^�[�Q�b�g�ɍ����B
		CombineMainRenderTarget(rc, postEffect);
	}
}

