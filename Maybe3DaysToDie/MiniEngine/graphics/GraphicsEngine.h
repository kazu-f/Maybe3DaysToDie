#pragma once


#include <d3d12.h>
#include <dxgi.h>
#include <dxgi1_2.h>
#include <dxgi1_3.h>
#include <dxgi1_4.h>

#include "DirectXTK/Inc/DDSTextureLoader.h"
#include "DirectXTK/Inc/ResourceUploadBatch.h"

#include "EngineStruct.h"
#include "RenderContext.h"
#include "RenderTarget.h"
#include "2D/Sprite.h"
#include "Font/FontEngine.h"
#include "NullTextureMaps.h"

#include "camera/Camera.h"

namespace Engine {
	class CLightManager;
	class CShadowMap;
	class CGBufferRender;
	class CDefferdShading;
	class CPostEffect;
	class CFade;
	class CRendererManager;

	/// <summary>
	/// DirectX12に依存するグラフィックスエンジン
	/// </summary>
	class CGraphicsEngine {
	public:
		/// <summary>
		/// デストラクタ。
		/// </summary>
		~CGraphicsEngine();
		/// <summary>
		/// 初期化
		/// </summary>
		/// <remarks>
		/// 本関数を呼び出すことでDirectX12の初期化が行われます。
		/// </remarks>
		/// <param name="hwnd">Windowハンドル</param>
		/// <param name="frameBufferwidth">フレームバッファの幅</param>
		/// <param name="frameBufferHeight">フレームバッファの高さ</param>
		/// <returns>falseが返ってきたら作成に失敗。</returns>
		bool Init(HWND hwnd, const SInitParam& initParam);
		/// <summary>
		/// 更新処理。
		/// </summary>
		void Update();
		/// <summary>
		/// 事前レンダリングの更新処理。
		/// </summary>
		void PreRenderUpdate();
		/// <summary>
		/// 描画を行う。
		/// </summary>
		void Render();
	private:
		/// <summary>
		/// プレレンダリング。
		/// </summary>
		void PreRender();
		/// <summary>
		/// ディファード。
		/// </summary>
		/// <param name="goMgr"></param>
		void DefferdShading();
		/// <summary>
		/// フォワードレンダリング。
		/// </summary>
		void ForwardRender();
		/// <summary>
		/// ポストレンダリング。
		/// </summary>
		void PostRender();
		/// <summary>
		/// 2D描画。
		/// </summary>
		void Render2D();
		/// <summary>
		/// レンダリング開始。
		/// </summary>
		/// <remarks>
		/// 1フレームのレンダリングの開始時に呼び出してください。
		/// </remarks>
		void BeginRender();
		/// <summary>
		/// レンダリング終了。
		/// </summary>
		/// <remarks>
		/// 1フレームのレンダリングの終了時に呼び出してください。
		/// </remarks>
		void EndRender();
	public:
		/// <summary>
		/// D3Dデバイスを取得。
		/// </summary>
		/// <returns></returns>
		ID3D12Device* GetD3DDevice()
		{
			return m_d3dDevice;
		}
		/// <summary>
		/// コマンドリストを取得。
		/// </summary>
		/// <returns></returns>
		ID3D12GraphicsCommandList* GetCommandList()
		{
			return m_commandList;
		}
		/// <summary>
		/// バックバッファの番号を取得。
		/// </summary>
		/// <returns>バックバッファの番号。</returns>
		UINT GetBackBufferIndex() const
		{
			return m_frameIndex;
		}
		/// <summary>
		/// コマンドキューを取得。
		/// </summary>
		/// <returns></returns>
		ID3D12CommandQueue* GetCommandQueue() const
		{
			return m_commandQueue;
		}

		/// <summary>
		/// CBR_SRVのディスクリプタのサイズを取得。
		/// </summary>
		/// <returns></returns>
		UINT GetCbrSrvDescriptorSize() const
		{
			return m_cbrSrvDescriptorSize;
		}
		/// <summary>
		/// メインレンダリングターゲットを取得。
		/// </summary>
		RenderTarget& GetMainRenderTarget()
		{
			return m_mainRenderTarget;
		}
		/// <summary>
		/// レンダリングコンテキストを取得。
		/// </summary>
		/// <returns></returns>
		RenderContext& GetRenderContext()
		{
			return m_renderContext;
		}
		/// <summary>
		/// フレームバッファの幅を取得。
		/// </summary>
		/// <returns>フレームバッファの幅。</returns>
		UINT GetFrameBufferWidth() const
		{
			return m_frameBufferWidth;
		}
		/// <summary>
		/// フレームバッファの高さを取得。
		/// </summary>
		/// <returns>フレームバッファの高さ。</returns>
		UINT GetFrameBufferHeight() const
		{
			return m_frameBufferHeight;
		}
		/// <summary>
		/// レンダリングターゲットをメインレンダリングターゲットに変更する。
		/// </summary>
		/// <param name="rc"></param>
		void ChangeToMainRenderTarget(RenderContext& rc);
		/// <summary>
		/// 現在のフレームバッファのレンダリングターゲットビューを取得。
		/// </summary>
		/// <returns></returns>
		D3D12_CPU_DESCRIPTOR_HANDLE GetCurrentFrameBuffuerRTV() const
		{
			return m_currentFrameBufferRTVHandle;
		}
		/// <summary>
		/// フォントエンジンを取得。
		/// </summary>
		/// <returns></returns>
		FontEngine& GetFontEngine()
		{
			return m_fontEngine;
		}
		/// <summary>
		/// レンダラーマネージャーの取得。
		/// </summary>
		std::unique_ptr<CRendererManager>& GetRendererManager()
		{
			return m_rendererManager;
		}
		/// <summary>
		/// ライトマネージャーの取得。
		/// </summary>
		std::unique_ptr<CLightManager>& GetLightManager()
		{
			return m_lightManager;
		}
		/// <summary>
		/// シャドウマップクラスの取得。
		/// </summary>
		std::unique_ptr<CShadowMap>& GetShadowMap()
		{
			return m_shadowMap;
		}
		/// <summary>
		/// ポストエフェクトを取得。
		/// </summary>
		std::unique_ptr<CPostEffect>& GetPostEffect()
		{
			return m_postEffect;
		}
		/// <summary>
		/// G-Bufferを取得。
		/// </summary>
		std::unique_ptr<CGBufferRender>& GetGBuffer()
		{
			return m_gBuffer;
		}
		/// <summary>
		/// NULLテクスチャマップを取得。
		/// </summary>
		const NullTextureMaps& GetNullTextureMaps()const
		{
			return m_nullTexMaps;
		}
		
		/// <summary>
		/// 3Dカメラの取得。
		/// </summary>
		Camera& GetMainCamera()
		{
			return m_camera3D;
		}

		/// <summary>
		/// 2Dカメラの取得。
		/// </summary>
		Camera& Get2DCamera()
		{
			return m_camera2D;
		}
		/// <summary>
		/// ディファードの取得。
		/// </summary>
		CDefferdShading* GetDefferd()
		{
			return m_defferd.get();
		}

	private:
		/// <summary>
		/// D3Dデバイスの作成。
		/// </summary>
		/// <returns>trueが返ってきたら作成に成功。</returns>
		bool CreateD3DDevice(IDXGIFactory4* dxgiFactory);
		/// <summary>
		/// コマンドキューの作成。
		/// </summary>
		/// <returns>trueが返ってきたら作成に成功。</returns>
		bool CreateCommandQueue();
		/// <summary>
		/// スワップチェインの作成
		/// </summary>
		/// <param name="hwnd">Windowハンドル</param>
		/// <param name="frameBufferWidth">フレームバッファの幅</param>
		/// <param name="frameBufferHeight">フレームバッファの高さ</param>
		/// <param name="dxgiFactory">DirectX グラフィックス インフラストラクチャー</param>
		/// <returns>trueが返ってきたら作成に成功。</returns>
		bool CreateSwapChain(
			HWND hwnd,
			UINT frameBufferWidth,
			UINT frameBufferHeight,
			IDXGIFactory4* dxgiFactory
		);
		/// <summary>
		/// DirectX グラフィックス インフラストラクチャーの作成。
		/// </summary>
		/// <remarks>
		/// DirectX グラフィックス インフラストラクチャーは
		/// カーネル モード ドライバーおよびシステム ハードウェアと通信するためのインターフェースです。 
		/// </remarks>
		/// <returns>作成されたDXGI</returns>
		IDXGIFactory4* CreateDXGIFactory();
		/// <summary>
		/// フレームバッファ用のディスクリプタヒープを作成。
		/// </summary>
		/// <returns>trueが返ってきたら作成に成功。</returns>
		bool CreateDescriptorHeapForFrameBuffer();
		/// <summary>
		/// フレームバッファ用のレンダリングターゲットビューを作成。
		/// </summary>
		/// <returns>trueが返ってきたら作成に成功。</returns>
		bool CreateRTVForFameBuffer();
		/// <summary>
		/// フレームバッファ用の深度ステンシルビューを作成。
		/// </summary>
		/// <param name="frameBufferWidth">フレームバッファの幅</param>
		/// <param name="frameBufferHeight">フレームバッファの高さ</param>
		/// <returns>trueが返ってきたら作成に成功。</returns>
		bool CreateDSVForFrameBuffer(UINT frameBufferWidth, UINT frameBufferHeight);
		/// <summary>
		/// コマンドリストの作成。
		/// </summary>
		/// <returns>trueが返ってきたら作成に成功。</returns>
		bool CreateCommandList();
		/// <summary>
		/// GPUとの同期オブジェクト作成
		/// </summary>
		/// <returns>trueが返ってきたら作成に成功。</returns>
		bool CreateSynchronizationWithGPUObject();
		/// <summary>
		/// 描画の完了待ち。
		/// </summary>
		void WaitDraw();
	public:
		enum { FRAME_BUFFER_COUNT = 2 };						//フレームバッファの数。
	private:
		//GPUベンダー定義。
		enum GPU_Vender {
			GPU_VenderNvidia,	//NVIDIA
			GPU_VenderAMD,		//Intel
			GPU_VenderIntel,	//AMD
			Num_GPUVender,
		};

		ID3D12Device* m_d3dDevice = nullptr;					//D3Dデバイス。
		ID3D12CommandQueue* m_commandQueue = nullptr;			//コマンドキュー。
		IDXGISwapChain3* m_swapChain = nullptr;					//スワップチェイン。
		ID3D12DescriptorHeap* m_rtvHeap = nullptr;				//レンダリングターゲットビューのディスクリプタヒープ。
		ID3D12DescriptorHeap* m_dsvHeap = nullptr;				//深度ステンシルビューのディスクリプタヒープ。
		ID3D12CommandAllocator* m_commandAllocator = nullptr;	//コマンドアロケータ。
		ID3D12GraphicsCommandList* m_commandList = nullptr;		//コマンドリスト。
		ID3D12PipelineState* m_pipelineState = nullptr;			//パイプラインステート。
		RenderTarget m_mainRenderTarget;						//メインレンダリングターゲット。
		Sprite m_copyFullScreenSprite;							//フルスクリーンコピー用のスプライト。
		int m_currentBackBufferIndex = 0;						//現在のバックバッファの番号。
		UINT m_rtvDescriptorSize = 0;							//フレームバッファのディスクリプタのサイズ。
		UINT m_dsvDescriptorSize = 0;							//深度ステンシルバッファのディスクリプタのサイズ。
		UINT m_cbrSrvDescriptorSize = 0;						//CBR_SRVのディスクリプタのサイズ。
		ID3D12Resource* m_renderTargets[FRAME_BUFFER_COUNT] = { nullptr };	//フレームバッファ用のレンダリングターゲット。
		ID3D12Resource* m_depthStencilBuffer = nullptr;	//深度ステンシルバッファ。
		D3D12_VIEWPORT m_viewport;			//ビューポート。
		D3D12_RECT m_scissorRect;			//シザリング矩形。
		RenderContext m_renderContext;		//レンダリングコンテキスト。
		D3D12_CPU_DESCRIPTOR_HANDLE m_currentFrameBufferRTVHandle;		//現在書き込み中のフレームバッファのレンダリングターゲットビューのハンドル。
		D3D12_CPU_DESCRIPTOR_HANDLE m_currentFrameBufferDSVHandle;		//現在書き込み中のフレームバッファの深度ステンシルビューの
		// GPUとの同期で使用する変数。
		UINT m_frameIndex = 0;
		HANDLE m_fenceEvent = nullptr;
		ID3D12Fence* m_fence = nullptr;
		UINT64 m_fenceValue = 0;
		UINT m_frameBufferWidth = 0;		//フレームバッファの幅。
		UINT m_frameBufferHeight = 0;		//フレームバッファの高さ。
		Camera m_camera2D;					//2Dカメラ。
		Camera m_camera3D;					//3Dカメラ。
		Camera m_cameraPostEffect;			//ポストエフェクト用カメラ。
		NullTextureMaps m_nullTexMaps;						//NULLテクスチャ管理オブジェクト。
		std::unique_ptr<CRendererManager> m_rendererManager;//レンダラーマネージャー。
		std::unique_ptr<CLightManager> m_lightManager;		//ライトマネージャー。
		std::unique_ptr<CShadowMap> m_shadowMap;			//指向性シャドウマップ。
		std::unique_ptr<CGBufferRender> m_gBuffer;			//GBuffer。
		std::unique_ptr<CDefferdShading> m_defferd;			//ディファード。
		std::unique_ptr<CPostEffect> m_postEffect;			//ポストエフェクト。
		std::unique_ptr<CFade> m_fade;						//フェード。
		
		//SpriteBatch
		std::unique_ptr<DirectX::GraphicsMemory> m_directXTKGfxMemroy;	//バッチ登録用のDirectXTKメモリ。
		FontEngine m_fontEngine;										//フォントエンジン。

		int m_vsyncInterval = 1;							//VSyncの間隔
		////エフェクト関係
		//EffekseerRenderer::RendererRef m_renderer;
	};
}
