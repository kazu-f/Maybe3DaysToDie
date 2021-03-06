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
		//アルベドバッファの初期化。
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
		//法線バッファの初期化。
		auto& normal = GetRenderTarget(EnGBuffer::enGBufferNormal);
		normal.Create(
			Width,
			Height,
			1,
			1,
			DXGI_FORMAT_R8G8B8A8_UNORM,
			DXGI_FORMAT_UNKNOWN
		);
		
		//ワールド座標マップの初期化。
		auto& worldPos = GetRenderTarget(EnGBuffer::enGBufferWorldPos);
		worldPos.Create(
			Width,
			Height,
			1,
			1,
			DXGI_FORMAT_R32G32B32A32_FLOAT,
			DXGI_FORMAT_UNKNOWN
		);
		//スペキュラバッファの初期化。
		auto& spec = GetRenderTarget(EnGBuffer::enGBufferSpecular);
		spec.Create(
			Width,
			Height,
			1,
			1,
			DXGI_FORMAT_R8G8B8A8_UNORM,
			DXGI_FORMAT_UNKNOWN
		);
		//spec.SetRTVClearColor({ 0.0f,0.0f,0.0f,0.0f });		//クリアカラーを設定。
		//影マップの初期化。
		auto& shadow = GetRenderTarget(EnGBuffer::enGBufferShadow);
		shadow.Create(
			Width,
			Height,
			1,
			1,
			DXGI_FORMAT_R32_FLOAT,
			DXGI_FORMAT_UNKNOWN
		);
		//反射率バッファの初期化。
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
		//レンダリングターゲットを設定。
		for (int i = 0; i < arraySize; i++) {
			rts[i] = &m_GBuffer[i];
		}
		//レンダリングターゲット設定待ち。
		rc.WaitUntilToPossibleSetRenderTargets(arraySize, rts);
		//レンダリングターゲットを設定。
		rc.SetRenderTargets(arraySize, rts);
		//レンダリングターゲットをクリア。
		rc.ClearRenderTargetViews(arraySize, rts);
	}
	void CGBufferRender::EndRender(RenderContext& rc)
	{
		const int arraySize = ARRAYSIZE(m_GBuffer);
		RenderTarget* rts[arraySize] = { nullptr };
		//レンダリングターゲットを設定。
		for (int i = 0; i < arraySize; i++) {
			rts[i] = &m_GBuffer[i];
		}
		//書き込みが終わるまで待つ。
		rc.WaitUntilFinishDrawingToRenderTargets(arraySize, rts);
		GraphicsEngine()->ChangeToMainRenderTarget(rc);
		//ディファード登録を解除。
		ClearDefferdModel();
	}
	void CGBufferRender::Render(RenderContext& rc)
	{
		BeginRender(rc);

		GraphicsEngine()->GetRendererManager()->RenderToGBuffer(rc);

		EndRender(rc);
	}
}