#include "stdafx.h"
#include "Tonemap.h"

namespace Engine {
	namespace {
		const wchar_t* SHADER_FILEPATH = L"Assets/shader/tonemap.fx";

		//-----------------------------------------------------------------------------
		// Name: GetSampleOffsets_DownScale4x4
		// Desc: Get the texture coordinate offsets to be used inside the DownScale4x4
		//       pixel shader.
		//-----------------------------------------------------------------------------
		HRESULT GetSampleOffsets_DownScale4x4(DWORD dwWidth, DWORD dwHeight, Vector4 avSampleOffsets[])
		{
			if (NULL == avSampleOffsets)
				return E_INVALIDARG;

			float tU = 1.0f / dwWidth;
			float tV = 1.0f / dwHeight;

			// Sample from the 16 surrounding points. Since the center point will be in
			// the exact center of 16 texels, a 0.5f offset is needed to specify a texel
			// center.
			int index = 0;
			for (int y = 0; y < 4; y++)
			{
				for (int x = 0; x < 4; x++)
				{
					avSampleOffsets[index].x = (x - 1.5f) * tU;
					avSampleOffsets[index].y = (y - 1.5f) * tV;

					index++;
				}
			}

			return S_OK;
		}
	}

	void CTonemap::Init(const SPostEffectConfig& config)
	{
		if (!config.tonemap.isEnable)
		{
			ENGINE_LOG("�g�[���}�b�v��K�p���Ȃ��B")
			return;
		}

		//�����_�����O�^�[�Q�b�g�̍쐬�B
		CreateRenderTargets();

		//���[�g�V�O�l�`���̍쐬�B
		m_rootSignature.Init(
			D3D12_FILTER_MIN_MAG_MIP_LINEAR,
			D3D12_TEXTURE_ADDRESS_MODE_CLAMP,
			D3D12_TEXTURE_ADDRESS_MODE_CLAMP,
			D3D12_TEXTURE_ADDRESS_MODE_CLAMP
		);

		//�V�F�[�_�[�̏������B
		InitShader();

		//�p�C�v���C���X�e�[�g�̍쐬�B
		InitPipelineState();

		//�萔�o�b�t�@�̍쐬�B
		CreateConstantBuffer();

		//�f�B�X�N���v�^�q�[�v�̍쐬�B
		CreateDescriptorHeap();

		m_isEnable = config.tonemap.isEnable;
		SetLuminance(config.tonemap.luminance);
	}

	void CTonemap::CreateRenderTargets()
	{
		//�P�x���o�p�̃����_�����O�^�[�Q�b�g�쐬�B
		for (int i = 0; i < NUM_CALC_AVG_RT; i++)
		{
			int rtSize = 1 << (2 * i);
			m_calcAvgRT[i].Create(
				rtSize,
				rtSize,
				1,
				1,
				DXGI_FORMAT_R32G32B32A32_FLOAT,
				DXGI_FORMAT_UNKNOWN
			);
		}
		//�ŏI�I�Ƀg�[���}�b�v�Ŏg�p���镽�ϋP�x���������ރ����_�����O�^�[�Q�b�g���쐬�B
		for (auto& rt : m_avgRT) {
			rt.Create(
				1,
				1,
				1,
				1,
				DXGI_FORMAT_R32G32B32A32_FLOAT,
				DXGI_FORMAT_UNKNOWN
			);
		}

	}

	void CTonemap::InitShader()
	{
		m_vsShader.LoadVS(SHADER_FILEPATH, "VSMain");
		m_psCalcLuminanceLogAverage.LoadPS(SHADER_FILEPATH, "PSCalcLuminanceLogAverage");
		m_psCalcLuminanceAverage.LoadPS(SHADER_FILEPATH, "PSCalcLuminanceAverage");
		m_psCalcLuminanceExpAverage.LoadPS(SHADER_FILEPATH, "PSCalcLuminanceExpAverage");
		m_psCalcAdaptedLuminance.LoadPS(SHADER_FILEPATH, "PSCalcAdaptedLuminance");
		m_psCalcAdaptedLuminanceFirst.LoadPS(SHADER_FILEPATH, "PSCalcAdaptedLuminanceFirst");
		m_psFinal.LoadPS(SHADER_FILEPATH, "PSFinal");
	}

	void CTonemap::InitPipelineState()
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
		psoDesc.VS = CD3DX12_SHADER_BYTECODE(m_vsShader.GetCompiledBlob());

		//�P�x�̑ΐ����ς����߂�p�C�v���C���X�e�[�g�B
		psoDesc.PS = CD3DX12_SHADER_BYTECODE(m_psCalcLuminanceLogAverage.GetCompiledBlob());
		m_calcLumionanceLogAveragePipelineState.Init(psoDesc);
		//�_�E���T���v�����O�̃p�C�v���C���X�e�[�g�B
		psoDesc.PS = CD3DX12_SHADER_BYTECODE(m_psCalcLuminanceAverage.GetCompiledBlob());
		m_calcLuminanceAveragePipelineState.Init(psoDesc);
		//�P�x�̎w�����ς����߂�p�C�v���C���X�e�[�g�B
		psoDesc.PS = CD3DX12_SHADER_BYTECODE(m_psCalcLuminanceExpAverage.GetCompiledBlob());
		m_calcLuminanceExpAveragePipelineState.Init(psoDesc);
		//���Ï����̂��߂̃p�C�v���C���X�e�[�g�B
		psoDesc.PS = CD3DX12_SHADER_BYTECODE(m_psCalcAdaptedLuminance.GetCompiledBlob());
		m_calcAdaptedLuminancePipelineState.Init(psoDesc);
		//���Ï����̂��߂̃p�C�v���C���X�e�[�g�B(�V�[�����؂�ւ�������p�B)
		psoDesc.PS = CD3DX12_SHADER_BYTECODE(m_psCalcAdaptedLuminanceFirst.GetCompiledBlob());
		m_calcAdaptedLuminanceFirstPipelineState.Init(psoDesc);
		//�ŏI�`��̃p�C�v���C���X�e�[�g�B
		psoDesc.PS = CD3DX12_SHADER_BYTECODE(m_psFinal.GetCompiledBlob());
		m_finalPipelineState.Init(psoDesc);
	}

	void CTonemap::CreateConstantBuffer()
	{
		m_cbTonemapCommon.Init(sizeof(m_tonemapParam), &m_tonemapParam);
		for (int i = 0; i < NUM_CALC_AVG_RT; i++)
		{
			m_cbCalcLuminanceLog[i].Init(sizeof(m_avSampleOffsets), m_avSampleOffsets);
		}
	}

	void CTonemap::CreateDescriptorHeap()
	{
		//���ϋP�x�v�Z�p�̃f�B�X�N���v�^�q�[�v�̍쐬�B
		{
			//�z��ԍ��B
			int curNo = NUM_CALC_AVG_RT - 1;
			//�P�x�̑ΐ����ς̌v�Z�B
			m_calcAvgDescriptorHeap[curNo].RegistConstantBuffer(0, m_cbCalcLuminanceLog[curNo]);
			m_calcAvgDescriptorHeap[curNo].RegistShaderResource(0, GraphicsEngine()->GetMainRenderTarget().GetRenderTargetTexture());
			m_calcAvgDescriptorHeap[curNo].Commit();

			curNo--;
			//�e�N�X�`���̃_�E���T���v�����O�B
			while (curNo > 0) {
				m_calcAvgDescriptorHeap[curNo].RegistConstantBuffer(0, m_cbCalcLuminanceLog[curNo]);
				m_calcAvgDescriptorHeap[curNo].RegistShaderResource(0, m_calcAvgRT[curNo + 1].GetRenderTargetTexture());
				m_calcAvgDescriptorHeap[curNo].Commit();
				curNo--;
			}
			//�P�x�̕��ώw���̌v�Z�B
			m_calcAvgDescriptorHeap[curNo].RegistConstantBuffer(0, m_cbCalcLuminanceLog[curNo]);
			m_calcAvgDescriptorHeap[curNo].RegistShaderResource(0, m_calcAvgRT[curNo + 1].GetRenderTargetTexture());
			m_calcAvgDescriptorHeap[curNo].Commit();

		}//���ϋP�x�v�Z�p�̃f�B�X�N���v�^�q�[�v�I���B

		//���Ï����̌v�Z�B
		for (int i = 0; i < 2; i++)
		{
			m_calcAdaptedLuminanceDescriptorHeap[i].RegistConstantBuffer(1, m_cbTonemapCommon);
			m_calcAdaptedLuminanceDescriptorHeap[i].RegistShaderResource(1, m_calcAvgRT[0].GetRenderTargetTexture());	//���ϋP�x�B
			m_calcAdaptedLuminanceDescriptorHeap[i].RegistShaderResource(2, m_avgRT[1 ^ i].GetRenderTargetTexture());	//��t���[���O�̕��ϋP�x�B
			m_calcAdaptedLuminanceDescriptorHeap[i].Commit();
		}

		//�ŏI�`��p�̃f�B�X�N���v�^�q�[�v�B
		for (int i = 0; i < 2; i++) {
			m_finalDescriptorHeap[i].RegistShaderResource(0, GraphicsEngine()->GetMainRenderTarget().GetRenderTargetTexture());		//�V�[���e�N�X�`���B
			m_finalDescriptorHeap[i].RegistShaderResource(1, m_avgRT[i].GetRenderTargetTexture());
			m_finalDescriptorHeap[i].Commit();
		}
	}

	void CTonemap::CalcLuminanceAverage(RenderContext& rc, CPostEffect* postEffect)
	{
		if (!m_isEnable) {
			return;
		}
		//�ΐ����ς����߂�B
		float tU, tV;
		tU = 1.0f / (3.0f * m_calcAvgRT[NUM_CALC_AVG_RT - 1].GetWidth());
		tV = 1.0f / (3.0f * m_calcAvgRT[NUM_CALC_AVG_RT - 1].GetHeight());

		int index = 0;
		for (int x = -1; x <= 1; x++)
		{
			for (int y = -1; y <= 1; y++)
			{
				m_avSampleOffsets[index].x = x * tU;
				m_avSampleOffsets[index].y = y * tV;

				index++;
			}
		}

		int curRtNo = NUM_CALC_AVG_RT - 1;
		//�P�x�̕��ϑΐ������߂�B
		{
			//�����_�����O�^�[�Q�b�g�̗��p�\�҂��B
			rc.WaitUntilToPossibleSetRenderTarget(m_calcAvgRT[curRtNo]);
			m_cbCalcLuminanceLog[curRtNo].CopyToVRAM(m_avSampleOffsets);		//�萔�o�b�t�@�̍X�V�B
			rc.SetDescriptorHeap(m_calcAvgDescriptorHeap[curRtNo]);
			rc.SetPipelineState(m_calcLumionanceLogAveragePipelineState);
			rc.SetRenderTargetAndViewport(&m_calcAvgRT[curRtNo]);
			//�h���[�R�[���B
			postEffect->DrawFullScreenQuad(rc);
			//�����_�����O�^�[�Q�b�g�̏������݊����҂��B
			rc.WaitUntilFinishDrawingToRenderTarget(m_calcAvgRT[curRtNo]);
		}
		curRtNo--;
		//�_�E���T���v�����O���s���ĕ��ς����߂�B
		{
			while (curRtNo > 0) {
				//�萔�o�b�t�@�̒l���v�Z�B
				GetSampleOffsets_DownScale4x4(m_calcAvgRT[curRtNo].GetWidth(), m_calcAvgRT[curRtNo].GetHeight(), m_avSampleOffsets);
				//�����_�����O�^�[�Q�b�g�̗��p�\�҂��B
				rc.WaitUntilToPossibleSetRenderTarget(m_calcAvgRT[curRtNo]);
				m_cbCalcLuminanceLog[curRtNo].CopyToVRAM(m_avSampleOffsets);		//�萔�o�b�t�@�̍X�V�B
				rc.SetDescriptorHeap(m_calcAvgDescriptorHeap[curRtNo]);
				rc.SetPipelineState(m_calcLuminanceAveragePipelineState);
				rc.SetRenderTargetAndViewport(&m_calcAvgRT[curRtNo]);
				//�h���[�R�[���B
				postEffect->DrawFullScreenQuad(rc);
				//�����_�����O�^�[�Q�b�g�̏������݊����҂��B
				rc.WaitUntilFinishDrawingToRenderTarget(m_calcAvgRT[curRtNo]);

				curRtNo--;
			}
		}
		//exp�֐���p���čŏI���ς����߂�B
		{
			//�萔�o�b�t�@�̒l���v�Z�B
			GetSampleOffsets_DownScale4x4(m_calcAvgRT[curRtNo].GetWidth(), m_calcAvgRT[curRtNo].GetHeight(), m_avSampleOffsets);
			//�����_�����O�^�[�Q�b�g�̗��p�\�҂��B
			rc.WaitUntilToPossibleSetRenderTarget(m_calcAvgRT[curRtNo]);
			m_cbCalcLuminanceLog[curRtNo].CopyToVRAM(m_avSampleOffsets);		//�萔�o�b�t�@�̍X�V�B
			rc.SetDescriptorHeap(m_calcAvgDescriptorHeap[curRtNo]);
			rc.SetPipelineState(m_calcLuminanceExpAveragePipelineState);
			rc.SetRenderTargetAndViewport(&m_calcAvgRT[curRtNo]);
			//�h���[�R�[���B
			postEffect->DrawFullScreenQuad(rc);
			//�����_�����O�^�[�Q�b�g�̏������݊����҂��B
			rc.WaitUntilFinishDrawingToRenderTarget(m_calcAvgRT[curRtNo]);
		}
		//���Ï����B
		{
			//�V�[�����؂�ւ���ď���B
			m_currentAvgRT = 1 ^ m_currentAvgRT;

			//�����_�����O�^�[�Q�b�g�̗��p�\�҂��B
			rc.WaitUntilToPossibleSetRenderTarget(m_avgRT[m_currentAvgRT]);
			rc.SetDescriptorHeap(m_calcAdaptedLuminanceDescriptorHeap[m_currentAvgRT]);
			if (m_isFirstWhenChangeScene == true)
			{
				rc.SetPipelineState(m_calcAdaptedLuminanceFirstPipelineState);
				//����t���O�������B
				m_isFirstWhenChangeScene = false;
			}
			else {
				rc.SetPipelineState(m_calcAdaptedLuminancePipelineState);
			}
			rc.SetRenderTargetAndViewport(&m_avgRT[m_currentAvgRT]);
			//�h���[�R�[���B
			postEffect->DrawFullScreenQuad(rc);
			//�����_�����O�^�[�Q�b�g�̏������݊����҂��B
			rc.WaitUntilFinishDrawingToRenderTarget(m_avgRT[m_currentAvgRT]);
		}

	}

	void CTonemap::Render(RenderContext& rc, CPostEffect* postEffect)
	{
		if (!m_isEnable)
		{
			return;
		}
		//�g�[���}�b�v�̋��ʒ萔�o�b�t�@���X�V�B
		m_tonemapParam.deltaTime = GameTime().GetFrameDeltaTime();
		m_cbTonemapCommon.CopyToVRAM(m_tonemapParam);
		//���ϋP�x�̌v�Z�B
		CalcLuminanceAverage(rc, postEffect);

		//�g�[���}�b�v�̍ŏI�`��B
		auto& mainRT = GraphicsEngine()->GetMainRenderTarget();
		//�����_�����O�^�[�Q�b�g���p�\�҂��B
		rc.WaitUntilToPossibleSetRenderTarget(mainRT);
		rc.SetPipelineState(m_finalPipelineState);
		rc.SetDescriptorHeap(m_finalDescriptorHeap[m_currentAvgRT]);
		rc.SetRenderTargetAndViewport(&mainRT);
		//�`��B
		postEffect->DrawFullScreenQuad(rc);
		//�����_�����O�^�[�Q�b�g�������݊����҂��B
		rc.WaitUntilFinishDrawingToRenderTarget(mainRT);
	}

}