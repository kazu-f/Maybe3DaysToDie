#include "stdafx.h"
#include "GraphicsEngine.h"

namespace Engine {
	CGraphicsEngine::~CGraphicsEngine()
	{
		WaitDraw();
		//��n���B
		if (m_commandQueue) {
			m_commandQueue->Release();
		}
		if (m_swapChain) {
			m_swapChain->Release();
		}
		if (m_rtvHeap) {
			m_rtvHeap->Release();
		}
		if (m_dsvHeap) {
			m_dsvHeap->Release();
		}
		if (m_commandAllocator) {
			m_commandAllocator->Release();
		}
		if (m_commandList) {
			m_commandList->Release();
		}
		if (m_pipelineState) {
			m_pipelineState->Release();
		}
		for (auto& rt : m_renderTargets) {
			if (rt) {
				rt->Release();
			}
		}
		if (m_depthStencilBuffer) {
			m_depthStencilBuffer->Release();
		}
		if (m_fence) {
			m_fence->Release();
		}

		if (m_d3dDevice) {
			m_d3dDevice->Release();
		}

		CloseHandle(m_fenceEvent);
	}
	void CGraphicsEngine::WaitDraw()
	{
		//�`��I���҂�
		// Signal and increment the fence value.
		const UINT64 fence = m_fenceValue;
		m_commandQueue->Signal(m_fence, fence);
		m_fenceValue++;

		// Wait until the previous frame is finished.
		if (m_fence->GetCompletedValue() < fence)
		{
			m_fence->SetEventOnCompletion(fence, m_fenceEvent);
			WaitForSingleObject(m_fenceEvent, INFINITE);
		}
	}
	bool CGraphicsEngine::Init(HWND hwnd, const SInitParam& initParam)
	{
		auto hdc = GetDC(hwnd);
		auto rate = GetDeviceCaps(hdc, VREFRESH);
		if (rate >= 120) {
			m_vsyncInterval = 2;
		}
		m_frameBufferWidth = initParam.frameBuffer_W;
		m_frameBufferHeight = initParam.frameBuffer_H;

		//�f�o�C�X�ɃA�N�Z�X���邽�߂̃C���^�[�t�F�[�X���쐬�B
		auto dxgiFactory = CreateDXGIFactory();
		//D3D�f�o�C�X�̍쐬�B
		if (!CreateD3DDevice(dxgiFactory)) {
			//D3D�f�o�C�X�̍쐬�Ɏ��s�����B
			MessageBox(hwnd, TEXT("D3D�f�o�C�X�̍쐬�Ɏ��s���܂����B"), TEXT("�G���["), MB_OK);
			return false;
		}
		//�R�}���h�L���[�̍쐬�B
		if (!CreateCommandQueue()) {
			//�R�}���h�L���[�̍쐬�Ɏ��s�����B
			MessageBox(hwnd, TEXT("�R�}���h�L���[�̍쐬�Ɏ��s���܂����B"), TEXT("�G���["), MB_OK);
			return false;
		}
		//�X���b�v�`�F�C�����쐬�B
		if (!CreateSwapChain(hwnd, m_frameBufferWidth, m_frameBufferHeight, dxgiFactory)) {
			//�X���b�v�`�F�C���̍쐬�Ɏ��s�B
			MessageBox(hwnd, TEXT("�X���b�v�`�F�C���̍쐬�Ɏ��s���܂����B"), TEXT("�G���["), MB_OK);
			return false;
		}

		//�t���[���o�b�t�@�p�̃f�B�X�N���v�^�q�[�v���쐬����B
		if (!CreateDescriptorHeapForFrameBuffer()) {
			MessageBox(hwnd, TEXT("�t���[���o�b�t�@�p�̃f�B�X�N���v�^�q�[�v�̍쐬�Ɏ��s���܂����B"), TEXT("�G���["), MB_OK);
			return false;
		}

		//�t���[���o�b�t�@�p��RTV���쐬����B
		if (!CreateRTVForFameBuffer()) {
			MessageBox(hwnd, TEXT("�t���[���o�b�t�@�p��RTV�̍쐬�Ɏ��s���܂����B"), TEXT("�G���["), MB_OK);
			return false;

		}

		//�t���[���o�b�t�@�p��DSV���쐬����B
		if (!CreateDSVForFrameBuffer(m_frameBufferWidth, m_frameBufferHeight)) {
			MessageBox(hwnd, TEXT("�t���[���o�b�t�@�p��DSV�̍쐬�Ɏ��s���܂����B"), TEXT("�G���["), MB_OK);
			return false;
		}

		//�R�}���h�A���P�[�^�̍쐬�B
		m_d3dDevice->CreateCommandAllocator(
			D3D12_COMMAND_LIST_TYPE_DIRECT,
			IID_PPV_ARGS(&m_commandAllocator));

		if (!m_commandAllocator) {
			MessageBox(hwnd, TEXT("�R�}���h�A���P�[�^�̍쐬�Ɏ��s���܂����B"), TEXT("�G���["), MB_OK);
			return false;
		}

		//�R�}���h���X�g�̍쐬�B
		if (!CreateCommandList()) {
			MessageBox(hwnd, TEXT("�R�}���h���X�g�̍쐬�Ɏ��s���܂����B"), TEXT("�G���["), MB_OK);
			return false;
		}

		//GPU�Ɠ������Ƃ邽�߂̃I�u�W�F�N�g���쐬����B
		if (!CreateSynchronizationWithGPUObject()) {
			MessageBox(hwnd, TEXT("GPU�Ɠ������Ƃ邽�߂̃I�u�W�F�N�g�̍쐬�Ɏ��s���܂����B"), TEXT("�G���["), MB_OK);
			return false;
		}

		//�����_�����O�R���e�L�X�g�̍쐬�B
		m_renderContext.Init(m_commandList);

		//���C�������_�����O�^�[�Q�b�g�̏������B
		float clearCol[] = { 0.5f,0.5f,0.5f,1.0f };
		if(m_mainRenderTarget.Create(
			static_cast<int>(m_frameBufferWidth),
			static_cast<int>(m_frameBufferHeight),
			1,
			1,
			DXGI_FORMAT_R32G32B32A32_FLOAT,
			DXGI_FORMAT_D32_FLOAT,
			clearCol) == false ) {
			ENGINE_ASSERT(false, "���C�������_�����O�^�[�Q�b�g�̍쐬�Ɏ��s�B");
			return false;
		}

		//�p�C�v���C���X�e�[�g���������B
		CPipelineStatesDefault::Init();

		//�r���[�|�[�g���������B
		m_viewport.TopLeftX = 0;
		m_viewport.TopLeftY = 0;
		m_viewport.Width = static_cast<FLOAT>(m_frameBufferWidth);
		m_viewport.Height = static_cast<FLOAT>(m_frameBufferHeight);
		m_viewport.MinDepth = D3D12_MIN_DEPTH;
		m_viewport.MaxDepth = D3D12_MAX_DEPTH;

		//�V�U�����O��`���������B
		m_scissorRect.left = 0;
		m_scissorRect.top = 0;
		m_scissorRect.right = m_frameBufferWidth;
		m_scissorRect.bottom = m_frameBufferHeight;

		//CBR_SVR�̃f�B�X�N���v�^�̃T�C�Y���擾�B
		m_cbrSrvDescriptorSize = m_d3dDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);


		//���������I������̂�DXGI��j���B
		dxgiFactory->Release();

		//�J����������������B
		m_camera2D.SetUpdateProjMatrixFunc(Camera::enUpdateProjMatrixFunc_Ortho);
		m_camera2D.SetWidth(static_cast<float>(m_frameBufferWidth));
		m_camera2D.SetHeight(static_cast<float>(m_frameBufferHeight));
		m_camera2D.SetPosition({ 0.0f, 0.0f, -1.0f });
		m_camera2D.SetTarget({ 0.0f, 0.0f, 0.0f });

		m_camera3D.SetPosition({ 0.0f, 50.0f, 200.0f });
		m_camera3D.SetTarget({ 0.0f, 50.0f, 0.0f });


		//���C�g�}�l�[�W���[�̍쐬�B
		m_lightManager = std::make_unique<CLightManager>();
		m_lightManager->Init();
		//�V���h�E�}�b�v�̍쐬�B
		m_shadowMap = std::make_unique<CShadowMap>();
		m_shadowMap->Init(initParam.graphicsConf.shadowConf);
		//GBuffer�̍쐬�B
		m_gBuffer = std::make_unique<CGBufferRender>();
		m_gBuffer->Init();
		//�f�B�t�@�[�h�p�N���X�쐬�B
		m_defferd = std::make_unique<CDefferdShading>();
		m_defferd->Init();
		//�|�X�g�G�t�F�N�g�B
		m_postEffect = std::make_unique<CPostEffect>();
		m_postEffect->Create(initParam.graphicsConf.postEffectConf);
		//�t�F�[�h�B
		m_fade = std::make_unique<CFade>();
		m_fade->Init();

		//�t���X�N���[���R�s�[�p�̃X�v���C�g�̏������B
		SpriteInitData spriteData;
		spriteData.m_fxFilePath = Sprite::SPRITE_SHADER_PATH;
		spriteData.m_textures[0] = &m_mainRenderTarget.GetRenderTargetTexture();
		spriteData.m_width = static_cast<float>(m_frameBufferWidth);
		spriteData.m_height = static_cast<float>(m_frameBufferHeight);
		spriteData.m_isAlpha = false;			//���u�����f�B���O�͖����B
		m_copyFullScreenSprite.Init(spriteData);

		//DXGI_FORMAT effectFormat[] =
		//{
		//	DXGI_FORMAT_R8G8B8A8_UNORM
		//};

		//m_renderer = EffekseerRendererDX12::Create(
		//	GetD3DDevice(),
		//	m_commandQueue,
		//	static_cast<int32_t>(2),
		//	effectFormat,
		//	static_cast<int32_t>(1),
		//	DXGI_FORMAT_D32_FLOAT,
		//	true,
		//	static_cast < int32_t>(2000)
		//);

		return true;
	}

	IDXGIFactory4* CGraphicsEngine::CreateDXGIFactory()
	{
		UINT dxgiFactoryFlags = 0;
#ifdef _DEBUG
		//�f�o�b�O�R���g���[���[������΁A�f�o�b�O���C���[������DXGI���쐬����B
		ID3D12Debug* debugController;
		if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController))))
		{
			debugController->EnableDebugLayer();

			// Enable additional debug layers.
			dxgiFactoryFlags |= DXGI_CREATE_FACTORY_DEBUG;
			debugController->Release();
		}
#endif
		IDXGIFactory4* factory;
		CreateDXGIFactory2(dxgiFactoryFlags, IID_PPV_ARGS(&factory));
		return factory;
	}

	bool CGraphicsEngine::CreateD3DDevice(IDXGIFactory4* dxgiFactory)
	{
		D3D_FEATURE_LEVEL fuatureLevel[] = {
			D3D_FEATURE_LEVEL_12_1,	//Direct3D 12.1�̋@�\���g���B
			D3D_FEATURE_LEVEL_12_0	//Direct3D 12.0�̋@�\���g���B
		};

		IDXGIAdapter* adapterTmp = nullptr;
		IDXGIAdapter* adapterVender[Num_GPUVender] = { nullptr };	//�e�x���_�[�̃A�_�v�^�[�B
		IDXGIAdapter* adapterMaxVideoMemory = nullptr;				//�ő�r�f�I�������̃A�_�v�^�B
		IDXGIAdapter* useAdapter = nullptr;							//�ŏI�I�Ɏg�p����A�_�v�^�B
		SIZE_T videoMemorySize = 0;
		for (int i = 0; dxgiFactory->EnumAdapters(i, &adapterTmp) != DXGI_ERROR_NOT_FOUND; i++) {
			DXGI_ADAPTER_DESC desc;
			adapterTmp->GetDesc(&desc);

			if (desc.DedicatedVideoMemory > videoMemorySize) {
				//������̃r�f�I�������̕��������̂ŁA��������g���B
				adapterMaxVideoMemory = adapterTmp;
				videoMemorySize = desc.DedicatedVideoMemory;
			}
			if (wcsstr(desc.Description, L"NVIDIA") != nullptr) {
				//NVIDIA��
				adapterVender[GPU_VenderNvidia] = adapterTmp;
			}
			else if (wcsstr(desc.Description, L"AMD") != nullptr) {
				//AMD��
				adapterVender[GPU_VenderAMD] = adapterTmp;
			}
			else if (wcsstr(desc.Description, L"Intel") != nullptr) {
				//Intel��
				adapterVender[GPU_VenderIntel] = adapterTmp;
			}
		}
		//�g�p����A�_�v�^�[�����߂�B
		if (adapterVender[GPU_VenderNvidia] != nullptr) {
			//NVIDIA�����ŗD��
			useAdapter = adapterVender[GPU_VenderNvidia];
		}
		else if (adapterVender[GPU_VenderAMD] != nullptr) {
			//����AMD���D��B
			useAdapter = adapterVender[GPU_VenderAMD];
		}
		else {
			//NVIDIA��AMD��GPU���Ȃ���΃r�f�I����������ԑ�������g���B
			useAdapter = adapterMaxVideoMemory;
		}
		for (auto fuatureLevel : fuatureLevel) {

			auto hr = D3D12CreateDevice(
				useAdapter,
				fuatureLevel,
				IID_PPV_ARGS(&m_d3dDevice)
			);
			if (SUCCEEDED(hr)) {
				//D3D�f�o�C�X�̍쐬�ɐ��������B
				break;
			}
		}
		return m_d3dDevice != nullptr;
	}
	bool CGraphicsEngine::CreateCommandQueue()
	{
		D3D12_COMMAND_QUEUE_DESC queueDesc = {};
		queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
		queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;

		auto hr = m_d3dDevice->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&m_commandQueue));
		if (FAILED(hr)) {
			//�R�}���h�L���[�̍쐬�Ɏ��s�����B
			return false;
		}
		return true;
	}
	bool CGraphicsEngine::CreateSwapChain(
		HWND hwnd,
		UINT frameBufferWidth,
		UINT frameBufferHeight,
		IDXGIFactory4* dxgiFactory
	)
	{
		DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
		swapChainDesc.BufferCount = FRAME_BUFFER_COUNT;
		swapChainDesc.Width = frameBufferWidth;
		swapChainDesc.Height = frameBufferHeight;
		swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
		swapChainDesc.SampleDesc.Count = 1;

		IDXGISwapChain1* swapChain;
		dxgiFactory->CreateSwapChainForHwnd(
			m_commandQueue,
			hwnd,
			&swapChainDesc,
			nullptr,
			nullptr,
			&swapChain
		);
		//IDXGISwapChain3�̃C���^�[�t�F�[�X���擾�B
		swapChain->QueryInterface(IID_PPV_ARGS(&m_swapChain));
		swapChain->Release();
		//IDXGISwapChain3�̃C���^�[�t�F�[�X���擾�B
		m_currentBackBufferIndex = m_swapChain->GetCurrentBackBufferIndex();
		return true;
	}
	bool CGraphicsEngine::CreateDescriptorHeapForFrameBuffer()
	{
		//RTV�p�̃f�B�X�N���v�^�q�[�v���쐬����B
		D3D12_DESCRIPTOR_HEAP_DESC desc = {};
		desc.NumDescriptors = FRAME_BUFFER_COUNT;
		desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
		desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
		auto hr = m_d3dDevice->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&m_rtvHeap));
		if (FAILED(hr)) {
			//RTV�p�̃f�B�X�N���v�^�q�[�v�̍쐬�Ɏ��s�����B
			return false;
		}
		//�f�B�X�N���v�^�̃T�C�Y���擾�B
		m_rtvDescriptorSize = m_d3dDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

		//DSV�p�̃f�B�X�N���v�^�q�[�v���쐬����B
		desc.NumDescriptors = 1;
		desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
		hr = m_d3dDevice->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&m_dsvHeap));
		if (FAILED(hr)) {
			//DSV�p�̃f�B�X�N���v�^�q�[�v�̍쐬�Ɏ��s�����B
			return false;
		}
		//�f�B�X�N���v�^�̃T�C�Y���擾�B
		m_dsvDescriptorSize = m_d3dDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_DSV);
		return true;
	}
	bool CGraphicsEngine::CreateRTVForFameBuffer()
	{
		D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = m_rtvHeap->GetCPUDescriptorHandleForHeapStart();

		//�t�����g�o�b�t�@���o�b�N�o�b�t�@�p��RTV���쐬�B
		for (UINT n = 0; n < FRAME_BUFFER_COUNT; n++) {
			m_swapChain->GetBuffer(n, IID_PPV_ARGS(&m_renderTargets[n]));
			m_d3dDevice->CreateRenderTargetView(
				m_renderTargets[n], nullptr, rtvHandle
			);
			rtvHandle.ptr += m_rtvDescriptorSize;
		}
		return true;
	}
	bool CGraphicsEngine::CreateDSVForFrameBuffer(UINT frameBufferWidth, UINT frameBufferHeight)
	{
		D3D12_CLEAR_VALUE dsvClearValue;
		dsvClearValue.Format = DXGI_FORMAT_D32_FLOAT;
		dsvClearValue.DepthStencil.Depth = 1.0f;
		dsvClearValue.DepthStencil.Stencil = 0;

		CD3DX12_RESOURCE_DESC desc(
			D3D12_RESOURCE_DIMENSION_TEXTURE2D,
			0,
			frameBufferWidth,
			frameBufferHeight,
			1,
			1,
			DXGI_FORMAT_D32_FLOAT,
			1,
			0,
			D3D12_TEXTURE_LAYOUT_UNKNOWN,
			D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL | D3D12_RESOURCE_FLAG_DENY_SHADER_RESOURCE);

		auto d3dxHeapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
		auto hr = m_d3dDevice->CreateCommittedResource(
			&d3dxHeapProperties,
			D3D12_HEAP_FLAG_NONE,
			&desc,
			D3D12_RESOURCE_STATE_DEPTH_WRITE,
			&dsvClearValue,
			IID_PPV_ARGS(&m_depthStencilBuffer)
		);
		if (FAILED(hr)) {
			//�[�x�X�e���V���o�b�t�@�̍쐬�Ɏ��s�B
			return false;
		}
		//�f�B�X�N���v�^���쐬
		D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle = m_dsvHeap->GetCPUDescriptorHandleForHeapStart();

		m_d3dDevice->CreateDepthStencilView(
			m_depthStencilBuffer, nullptr, dsvHandle
		);

		return true;
	}
	bool CGraphicsEngine::CreateCommandList()
	{
		//�R�}���h���X�g�̍쐬�B
		m_d3dDevice->CreateCommandList(
			0, D3D12_COMMAND_LIST_TYPE_DIRECT, m_commandAllocator, nullptr, IID_PPV_ARGS(&m_commandList)
		);
		if (!m_commandList) {
			return false;
		}
		//�R�}���h���X�g�͊J����Ă����Ԃō쐬�����̂ŁA�����������B
		m_commandList->Close();

		return true;
	}
	bool CGraphicsEngine::CreateSynchronizationWithGPUObject()
	{
		m_d3dDevice->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&m_fence));
		if (!m_fence) {
			//�t�F���X�̍쐬�Ɏ��s�����B
			return false;
		}
		m_fenceValue = 1;
		//�������s���Ƃ��̃C�x���g�n���h�����쐬����B
		m_fenceEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);
		if (m_fenceEvent == nullptr) {
			return false;
		}
		return true;
	}
	void CGraphicsEngine::Update()
	{
		//�J�������X�V����B
		m_camera2D.Update();
		m_camera3D.Update();

	}
	void CGraphicsEngine::PreRenderUpdate()
	{
		//���C�g�̍X�V�����B
		m_lightManager->LightUpdate();
		//�V���h�E�}�b�v�̍X�V�����B
		m_shadowMap->Update();
	}
	void CGraphicsEngine::Render(CGameObjectManager* goMgr)
	{
		BeginRender();

		PreRender(goMgr);
		
		DefferdShading(goMgr);

		ForwardRender(goMgr);

		PostRender(goMgr);

		m_fade->Update();
		m_fade->FadeRender(m_renderContext);

		EndRender();
 	}
	void CGraphicsEngine::PreRender(CGameObjectManager* goMgr)
	{
		//�V���h�E�}�b�v���O�ɍs�������B
		goMgr->PreRender(m_renderContext);

		//�w�����V���h�E���̏����B
		m_shadowMap->RenderToShadowMap(m_renderContext);
		m_shadowMap->WaitEndRenderToShadowMap(m_renderContext);
		ChangeToMainRenderTarget(m_renderContext);

		m_renderContext.SetRenderStep(enRenderStep_PreRender);
		//Gbuffer�ɏ������݂��s���B
		m_gBuffer->Render(m_renderContext);
	}
	void CGraphicsEngine::DefferdShading(CGameObjectManager* goMgr)
	{
		//���C�g���̍X�V�B
		m_lightManager->Render(m_renderContext);
		//�f�B�t�@�[�h�����_�����O���s���B
		m_defferd->Render(m_renderContext);
	}
	void CGraphicsEngine::ForwardRender(CGameObjectManager* goMgr)
	{
		//�����_�����O�X�e�b�v���t�H���[�h�����_�����O�ɂ���B
		m_renderContext.SetRenderStep(EnRenderStep::enRenderStep_ForwardRender);
		//�����_�����O�^�[�Q�b�g��ݒ�B
		m_renderContext.SetRenderTarget(
			m_mainRenderTarget.GetRTVCpuDescriptorHandle(),
			m_gBuffer->GetRenderTarget(EnGBuffer::enGBufferAlbed).GetDSVCpuDescriptorHandle()
		);
		//�t�H���[�h�����_�����O�p�X�B
		goMgr->ForwardRender(m_renderContext);

		PhysicsWorld().DebugDrawWorld(m_renderContext);
	}
	void CGraphicsEngine::PostRender(CGameObjectManager* goMgr)
	{
		//�����_�����O�X�e�b�v���|�X�g�����_�����O�ɂ���B
		m_renderContext.SetRenderStep(EnRenderStep::enRenderStep_PostRender);

		//�|�X�g�G�t�F�N�g���|����B
		m_postEffect->Render(m_renderContext);

		goMgr->PostRender(m_renderContext);
	}
	void CGraphicsEngine::BeginRender()
	{
		m_frameIndex = m_swapChain->GetCurrentBackBufferIndex();

		//�R�}���h�A���P�[�^�������Z�b�g�B
		m_commandAllocator->Reset();
		//�����_�����O�R���e�L�X�g�����Z�b�g�B
		m_renderContext.Reset(m_commandAllocator, m_pipelineState);
		//�r���[�|�[�g��ݒ�B
		//�r���[�|�[�g��ݒ�B
		m_renderContext.SetViewport(m_viewport);
		//�V�U�����O��`��ݒ�B
		m_renderContext.SetScissorRect(m_scissorRect);
		//�����_�����O�^�[�Q�b�g�����C���ɂ���B
		//�����_�����O�^�[�Q�b�g�Ƃ��ė��p�\�܂ő҂B
		m_renderContext.WaitUntilToPossibleSetRenderTarget(m_mainRenderTarget.GetRenderTargetTexture().Get());
		//�����_�����O�^�[�Q�b�g��ݒ�B
		m_renderContext.SetRenderTarget(m_mainRenderTarget.GetRTVCpuDescriptorHandle(), m_mainRenderTarget.GetDSVCpuDescriptorHandle());
		const float clearColor[] = { 0.5f,0.5f,0.5f,1.0f };
		m_renderContext.ClearRenderTargetView(m_mainRenderTarget.GetRTVCpuDescriptorHandle(), clearColor);
		m_renderContext.ClearDepthStencilView(m_mainRenderTarget.GetDSVCpuDescriptorHandle(), 1.0f);

		//m_currentFrameBufferRTVHandle = m_rtvHeap->GetCPUDescriptorHandleForHeapStart();
		//m_currentFrameBufferRTVHandle.ptr += m_frameIndex * m_rtvDescriptorSize;
		////�[�x�X�e���V���o�b�t�@�̃f�B�X�N���v�^�q�[�v�̊J�n�A�h���X���擾�B
		//m_currentFrameBufferDSVHandle = m_dsvHeap->GetCPUDescriptorHandleForHeapStart();
		////�o�b�N�o�b�t�@�������_�����O�^�[�Q�b�g�Ƃ��Đݒ�\�ɂȂ�܂ő҂B
		//m_renderContext.WaitUntilToPossibleSetRenderTarget(m_renderTargets[m_frameIndex]);

		////�����_�����O�^�[�Q�b�g��ݒ�B
		//m_renderContext.SetRenderTarget(m_currentFrameBufferRTVHandle, m_currentFrameBufferDSVHandle);

		//const float clearColor[] = { 0.5f, 0.5f, 0.5f, 1.0f };
		//m_renderContext.ClearRenderTargetView(m_currentFrameBufferRTVHandle, clearColor);
		//m_renderContext.ClearDepthStencilView(m_currentFrameBufferDSVHandle, 1.0f);

	}
	void CGraphicsEngine::ChangeToMainRenderTarget(RenderContext& rc)
	{
		rc.SetRenderTarget(m_mainRenderTarget.GetRTVCpuDescriptorHandle(), m_mainRenderTarget.GetDSVCpuDescriptorHandle());
	}
	void CGraphicsEngine::EndRender()
	{
		//�o�b�N�o�b�t�@�Ƀe�N�X�`�����R�s�[
		{
			// �����_�����O�^�[�Q�b�g�ւ̕`�����݊����҂�
			//m_renderContext.WaitUntilFinishDrawingToRenderTarget(m_renderTargets[m_frameIndex]);
			m_renderContext.WaitUntilFinishDrawingToRenderTarget(m_mainRenderTarget.GetRenderTargetTexture().Get());

			m_currentFrameBufferRTVHandle = m_rtvHeap->GetCPUDescriptorHandleForHeapStart();
			m_currentFrameBufferRTVHandle.ptr += m_frameIndex * m_rtvDescriptorSize;
			//�[�x�X�e���V���o�b�t�@�̃f�B�X�N���v�^�q�[�v�̊J�n�A�h���X���擾�B
			m_currentFrameBufferDSVHandle = m_dsvHeap->GetCPUDescriptorHandleForHeapStart();
			//�o�b�N�o�b�t�@�������_�����O�^�[�Q�b�g�Ƃ��Đݒ�\�ɂȂ�܂ő҂B
			m_renderContext.WaitUntilToPossibleSetRenderTarget(m_renderTargets[m_frameIndex]);

			//�����_�����O�^�[�Q�b�g��ݒ�B
			m_renderContext.SetRenderTarget(m_currentFrameBufferRTVHandle, m_currentFrameBufferDSVHandle);

			const float clearColor[] = { 0.5f, 0.5f, 0.5f, 1.0f };
			m_renderContext.ClearRenderTargetView(m_currentFrameBufferRTVHandle, clearColor);
			m_renderContext.ClearDepthStencilView(m_currentFrameBufferDSVHandle, 1.0f);

			m_copyFullScreenSprite.Draw(m_renderContext, m_camera2D.GetViewMatrix(), m_camera2D.GetProjectionMatrix());
			//�����_�����O�^�[�Q�b�g�ւ̏������݊����҂��B
			m_renderContext.WaitUntilToPossibleSetRenderTarget(m_renderTargets[m_frameIndex]);
		}

		//�����_�����O�R���e�L�X�g�����B
		m_renderContext.Close();

		//�R�}���h�����s�B
		ID3D12CommandList* ppCommandLists[] = { m_commandList };
		m_commandQueue->ExecuteCommandLists(_countof(ppCommandLists), ppCommandLists);

		// Present the frame.
		m_swapChain->Present(m_vsyncInterval, 0);

		//�`�抮���҂��B
		WaitDraw();
	}

	void CGraphicsEngine::ExecuteCommand()
	{
		//// �����_�����O�^�[�Q�b�g�ւ̕`�����݊����҂�
		//m_renderContext.WaitUntilFinishDrawingToRenderTarget(m_renderTargets[m_frameIndex]);

		//�����_�����O�R���e�L�X�g�����B
		m_renderContext.Close();

		//�R�}���h�����s�B
		ID3D12CommandList* ppCommandLists[] = { m_commandList };
		m_commandQueue->ExecuteCommandLists(_countof(ppCommandLists), ppCommandLists);
		//�`�抮���҂��B
		WaitDraw();
	}
}