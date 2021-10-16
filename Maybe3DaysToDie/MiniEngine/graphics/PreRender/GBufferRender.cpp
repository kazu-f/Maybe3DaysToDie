#include "MiniEngine.h"
#include "GBufferRender.h"

namespace Engine {
	CGBufferRender::CGBufferRender()
	{
	}
	CGBufferRender::~CGBufferRender()
	{
	}
	void CGBufferRender::Init()
	{
		const int Width = static_cast<int>(GraphicsEngine()->GetFrameBufferWidth());
		const int Height = static_cast<int>(GraphicsEngine()->GetFrameBufferHeight());
		//�A���x�h�o�b�t�@�̏������B
		auto& albedo = GetRenderTarget(EnGBuffer::enGBufferAlbed);
		float clearCol[] = { 0.0f,0.0f,0.0f,0.0f };
		albedo.Create(
			Width,
			Height,
			1,
			1,
			DXGI_FORMAT_R8G8B8A8_UNORM,
			DXGI_FORMAT_D32_FLOAT,
			clearCol
		);
		//�@���o�b�t�@�̏������B
		auto& normal = GetRenderTarget(EnGBuffer::enGBufferNormal);
		normal.Create(
			Width,
			Height,
			1,
			1,
			DXGI_FORMAT_R8G8B8A8_UNORM,
			DXGI_FORMAT_UNKNOWN
		);
		
		//���[���h���W�}�b�v�̏������B
		auto& worldPos = GetRenderTarget(EnGBuffer::enGBufferWorldPos);
		worldPos.Create(
			Width,
			Height,
			1,
			1,
			DXGI_FORMAT_R32G32B32A32_FLOAT,
			DXGI_FORMAT_UNKNOWN
		);
		//�X�y�L�����o�b�t�@�̏������B
		auto& spec = GetRenderTarget(EnGBuffer::enGBufferSpecular);
		spec.Create(
			Width,
			Height,
			1,
			1,
			DXGI_FORMAT_R8G8B8A8_UNORM,
			DXGI_FORMAT_UNKNOWN
		);
		//spec.SetRTVClearColor({ 0.0f,0.0f,0.0f,0.0f });		//�N���A�J���[��ݒ�B
		//�e�}�b�v�̏������B
		auto& shadow = GetRenderTarget(EnGBuffer::enGBufferShadow);
		shadow.Create(
			Width,
			Height,
			1,
			1,
			DXGI_FORMAT_R32_FLOAT,
			DXGI_FORMAT_UNKNOWN
		);
		//���˗��o�b�t�@�̏������B
		auto& reflection = GetRenderTarget(EnGBuffer::enGBufferReflection);
		reflection.Create(
			Width,
			Height,
			1,
			1,
			DXGI_FORMAT_R16G16_FLOAT,
			DXGI_FORMAT_UNKNOWN
		);
		
	}
	void CGBufferRender::BeginRender(RenderContext& rc)
	{
		const int arraySize = ARRAYSIZE(m_GBuffer);
		RenderTarget* rts[arraySize] = { nullptr };
		//�����_�����O�^�[�Q�b�g��ݒ�B
		for (int i = 0; i < arraySize; i++) {
			rts[i] = &m_GBuffer[i];
		}
		//�����_�����O�^�[�Q�b�g�ݒ�҂��B
		rc.WaitUntilToPossibleSetRenderTargets(arraySize, rts);
		//�����_�����O�^�[�Q�b�g��ݒ�B
		rc.SetRenderTargets(arraySize, rts);
		//�����_�����O�^�[�Q�b�g���N���A�B
		rc.ClearRenderTargetViews(arraySize, rts);
	}
	void CGBufferRender::EndRender(RenderContext& rc)
	{
		const int arraySize = ARRAYSIZE(m_GBuffer);
		RenderTarget* rts[arraySize] = { nullptr };
		//�����_�����O�^�[�Q�b�g��ݒ�B
		for (int i = 0; i < arraySize; i++) {
			rts[i] = &m_GBuffer[i];
		}
		//�������݂��I���܂ő҂B
		rc.WaitUntilFinishDrawingToRenderTargets(arraySize, rts);
		GraphicsEngine()->ChangeToMainRenderTarget(rc);
		//�f�B�t�@�[�h�o�^�������B
		ClearDefferdModel();
	}
	void CGBufferRender::Render(RenderContext& rc)
	{
		BeginRender(rc);

		for (auto* model : m_defferdModelArray)
		{
			model->RenderToGBuffer(rc);
		}

		EndRender(rc);
	}
}