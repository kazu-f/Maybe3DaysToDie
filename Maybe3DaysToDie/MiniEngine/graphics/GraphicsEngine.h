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
	class CGameObjectManager;
	class CLightManager;
	class CShadowMap;
	class CGBufferRender;
	class CDefferdShading;
	class CPostEffect;
	class CFade;

	/// <summary>
	/// DirectX12�Ɉˑ�����O���t�B�b�N�X�G���W��
	/// </summary>
	class CGraphicsEngine {
	public:
		/// <summary>
		/// �f�X�g���N�^�B
		/// </summary>
		~CGraphicsEngine();
		/// <summary>
		/// ������
		/// </summary>
		/// <remarks>
		/// �{�֐����Ăяo�����Ƃ�DirectX12�̏��������s���܂��B
		/// </remarks>
		/// <param name="hwnd">Window�n���h��</param>
		/// <param name="frameBufferwidth">�t���[���o�b�t�@�̕�</param>
		/// <param name="frameBufferHeight">�t���[���o�b�t�@�̍���</param>
		/// <returns>false���Ԃ��Ă�����쐬�Ɏ��s�B</returns>
		bool Init(HWND hwnd, const SInitParam& initParam);
		/// <summary>
		/// �X�V�����B
		/// </summary>
		void Update();
		/// <summary>
		/// ���O�����_�����O�̍X�V�����B
		/// </summary>
		void PreRenderUpdate();
		/// <summary>
		/// �`����s���B
		/// </summary>
		void Render(CGameObjectManager* goMgr);
	private:
		/// <summary>
		/// �v�������_�����O�B
		/// </summary>
		void PreRender(CGameObjectManager* goMgr);
		/// <summary>
		/// �f�B�t�@�[�h�B
		/// </summary>
		/// <param name="goMgr"></param>
		void DefferdShading(CGameObjectManager* goMgr);
		/// <summary>
		/// �t�H���[�h�����_�����O�B
		/// </summary>
		void ForwardRender(CGameObjectManager* goMgr);
		/// <summary>
		/// �|�X�g�����_�����O�B
		/// </summary>
		void PostRender(CGameObjectManager* goMgr);
		/// <summary>
		/// �����_�����O�J�n�B
		/// </summary>
		/// <remarks>
		/// 1�t���[���̃����_�����O�̊J�n���ɌĂяo���Ă��������B
		/// </remarks>
		void BeginRender();
		/// <summary>
		/// �����_�����O�I���B
		/// </summary>
		/// <remarks>
		/// 1�t���[���̃����_�����O�̏I�����ɌĂяo���Ă��������B
		/// </remarks>
		void EndRender();
	public:
		/// <summary>
		/// D3D�f�o�C�X���擾�B
		/// </summary>
		/// <returns></returns>
		ID3D12Device* GetD3DDevice()
		{
			return m_d3dDevice;
		}
		/// <summary>
		/// �R�}���h���X�g���擾�B
		/// </summary>
		/// <returns></returns>
		ID3D12GraphicsCommandList* GetCommandList()
		{
			return m_commandList;
		}
		/// <summary>
		/// �o�b�N�o�b�t�@�̔ԍ����擾�B
		/// </summary>
		/// <returns>�o�b�N�o�b�t�@�̔ԍ��B</returns>
		UINT GetBackBufferIndex() const
		{
			return m_frameIndex;
		}
		/// <summary>
		/// �R�}���h�L���[���擾�B
		/// </summary>
		/// <returns></returns>
		ID3D12CommandQueue* GetCommandQueue() const
		{
			return m_commandQueue;
		}

		/// <summary>
		/// CBR_SRV�̃f�B�X�N���v�^�̃T�C�Y���擾�B
		/// </summary>
		/// <returns></returns>
		UINT GetCbrSrvDescriptorSize() const
		{
			return m_cbrSrvDescriptorSize;
		}
		/// <summary>
		/// ���C�������_�����O�^�[�Q�b�g���擾�B
		/// </summary>
		RenderTarget& GetMainRenderTarget()
		{
			return m_mainRenderTarget;
		}
		/// <summary>
		/// �����_�����O�R���e�L�X�g���擾�B
		/// </summary>
		/// <returns></returns>
		RenderContext& GetRenderContext()
		{
			return m_renderContext;
		}
		/// <summary>
		/// �t���[���o�b�t�@�̕����擾�B
		/// </summary>
		/// <returns>�t���[���o�b�t�@�̕��B</returns>
		UINT GetFrameBufferWidth() const
		{
			return m_frameBufferWidth;
		}
		/// <summary>
		/// �t���[���o�b�t�@�̍������擾�B
		/// </summary>
		/// <returns>�t���[���o�b�t�@�̍����B</returns>
		UINT GetFrameBufferHeight() const
		{
			return m_frameBufferHeight;
		}
		/// <summary>
		/// �����_�����O�^�[�Q�b�g�����C�������_�����O�^�[�Q�b�g�ɕύX����B
		/// </summary>
		/// <param name="rc"></param>
		void ChangeToMainRenderTarget(RenderContext& rc);
		/// <summary>
		/// ���݂̃t���[���o�b�t�@�̃����_�����O�^�[�Q�b�g�r���[���擾�B
		/// </summary>
		/// <returns></returns>
		D3D12_CPU_DESCRIPTOR_HANDLE GetCurrentFrameBuffuerRTV() const
		{
			return m_currentFrameBufferRTVHandle;
		}
		/// <summary>
		/// �t�H���g�G���W�����擾�B
		/// </summary>
		/// <returns></returns>
		FontEngine& GetFontEngine()
		{
			return m_fontEngine;
		}
		/// <summary>
		/// ���C�g�}�l�[�W���[�̎擾�B
		/// </summary>
		std::unique_ptr<CLightManager>& GetLightManager()
		{
			return m_lightManager;
		}
		/// <summary>
		/// �V���h�E�}�b�v�N���X�̎擾�B
		/// </summary>
		std::unique_ptr<CShadowMap>& GetShadowMap()
		{
			return m_shadowMap;
		}
		/// <summary>
		/// �|�X�g�G�t�F�N�g���擾�B
		/// </summary>
		std::unique_ptr<CPostEffect>& GetPostEffect()
		{
			return m_postEffect;
		}
		/// <summary>
		/// G-Buffer���擾�B
		/// </summary>
		std::unique_ptr<CGBufferRender>& GetGBuffer()
		{
			return m_gBuffer;
		}
		/// <summary>
		/// NULL�e�N�X�`���}�b�v���擾�B
		/// </summary>
		const NullTextureMaps& GetNullTextureMaps()const
		{
			return m_nullTexMaps;
		}
		
		/// <summary>
		/// 3D�J�����̎擾�B
		/// </summary>
		Camera& GetMainCamera()
		{
			return m_camera3D;
		}

		/// <summary>
		/// 2D�J�����̎擾�B
		/// </summary>
		Camera& Get2DCamera()
		{
			return m_camera2D;
		}
		/// <summary>
		/// �f�B�t�@�[�h�̎擾�B
		/// </summary>
		CDefferdShading* GetDefferd()
		{
			return m_defferd.get();
		}

	private:
		/// <summary>
		/// D3D�f�o�C�X�̍쐬�B
		/// </summary>
		/// <returns>true���Ԃ��Ă�����쐬�ɐ����B</returns>
		bool CreateD3DDevice(IDXGIFactory4* dxgiFactory);
		/// <summary>
		/// �R�}���h�L���[�̍쐬�B
		/// </summary>
		/// <returns>true���Ԃ��Ă�����쐬�ɐ����B</returns>
		bool CreateCommandQueue();
		/// <summary>
		/// �X���b�v�`�F�C���̍쐬
		/// </summary>
		/// <param name="hwnd">Window�n���h��</param>
		/// <param name="frameBufferWidth">�t���[���o�b�t�@�̕�</param>
		/// <param name="frameBufferHeight">�t���[���o�b�t�@�̍���</param>
		/// <param name="dxgiFactory">DirectX �O���t�B�b�N�X �C���t���X�g���N�`���[</param>
		/// <returns>true���Ԃ��Ă�����쐬�ɐ����B</returns>
		bool CreateSwapChain(
			HWND hwnd,
			UINT frameBufferWidth,
			UINT frameBufferHeight,
			IDXGIFactory4* dxgiFactory
		);
		/// <summary>
		/// DirectX �O���t�B�b�N�X �C���t���X�g���N�`���[�̍쐬�B
		/// </summary>
		/// <remarks>
		/// DirectX �O���t�B�b�N�X �C���t���X�g���N�`���[��
		/// �J�[�l�� ���[�h �h���C�o�[����уV�X�e�� �n�[�h�E�F�A�ƒʐM���邽�߂̃C���^�[�t�F�[�X�ł��B 
		/// </remarks>
		/// <returns>�쐬���ꂽDXGI</returns>
		IDXGIFactory4* CreateDXGIFactory();
		/// <summary>
		/// �t���[���o�b�t�@�p�̃f�B�X�N���v�^�q�[�v���쐬�B
		/// </summary>
		/// <returns>true���Ԃ��Ă�����쐬�ɐ����B</returns>
		bool CreateDescriptorHeapForFrameBuffer();
		/// <summary>
		/// �t���[���o�b�t�@�p�̃����_�����O�^�[�Q�b�g�r���[���쐬�B
		/// </summary>
		/// <returns>true���Ԃ��Ă�����쐬�ɐ����B</returns>
		bool CreateRTVForFameBuffer();
		/// <summary>
		/// �t���[���o�b�t�@�p�̐[�x�X�e���V���r���[���쐬�B
		/// </summary>
		/// <param name="frameBufferWidth">�t���[���o�b�t�@�̕�</param>
		/// <param name="frameBufferHeight">�t���[���o�b�t�@�̍���</param>
		/// <returns>true���Ԃ��Ă�����쐬�ɐ����B</returns>
		bool CreateDSVForFrameBuffer(UINT frameBufferWidth, UINT frameBufferHeight);
		/// <summary>
		/// �R�}���h���X�g�̍쐬�B
		/// </summary>
		/// <returns>true���Ԃ��Ă�����쐬�ɐ����B</returns>
		bool CreateCommandList();
		/// <summary>
		/// GPU�Ƃ̓����I�u�W�F�N�g�쐬
		/// </summary>
		/// <returns>true���Ԃ��Ă�����쐬�ɐ����B</returns>
		bool CreateSynchronizationWithGPUObject();
		/// <summary>
		/// �`��̊����҂��B
		/// </summary>
		void WaitDraw();
	public:
		enum { FRAME_BUFFER_COUNT = 2 };						//�t���[���o�b�t�@�̐��B
	private:
		//GPU�x���_�[��`�B
		enum GPU_Vender {
			GPU_VenderNvidia,	//NVIDIA
			GPU_VenderAMD,		//Intel
			GPU_VenderIntel,	//AMD
			Num_GPUVender,
		};

		ID3D12Device* m_d3dDevice = nullptr;					//D3D�f�o�C�X�B
		ID3D12CommandQueue* m_commandQueue = nullptr;			//�R�}���h�L���[�B
		IDXGISwapChain3* m_swapChain = nullptr;					//�X���b�v�`�F�C���B
		ID3D12DescriptorHeap* m_rtvHeap = nullptr;				//�����_�����O�^�[�Q�b�g�r���[�̃f�B�X�N���v�^�q�[�v�B
		ID3D12DescriptorHeap* m_dsvHeap = nullptr;				//�[�x�X�e���V���r���[�̃f�B�X�N���v�^�q�[�v�B
		ID3D12CommandAllocator* m_commandAllocator = nullptr;	//�R�}���h�A���P�[�^�B
		ID3D12GraphicsCommandList* m_commandList = nullptr;		//�R�}���h���X�g�B
		ID3D12PipelineState* m_pipelineState = nullptr;			//�p�C�v���C���X�e�[�g�B
		RenderTarget m_mainRenderTarget;						//���C�������_�����O�^�[�Q�b�g�B
		Sprite m_copyFullScreenSprite;							//�t���X�N���[���R�s�[�p�̃X�v���C�g�B
		int m_currentBackBufferIndex = 0;						//���݂̃o�b�N�o�b�t�@�̔ԍ��B
		UINT m_rtvDescriptorSize = 0;							//�t���[���o�b�t�@�̃f�B�X�N���v�^�̃T�C�Y�B
		UINT m_dsvDescriptorSize = 0;							//�[�x�X�e���V���o�b�t�@�̃f�B�X�N���v�^�̃T�C�Y�B
		UINT m_cbrSrvDescriptorSize = 0;						//CBR_SRV�̃f�B�X�N���v�^�̃T�C�Y�B
		ID3D12Resource* m_renderTargets[FRAME_BUFFER_COUNT] = { nullptr };	//�t���[���o�b�t�@�p�̃����_�����O�^�[�Q�b�g�B
		ID3D12Resource* m_depthStencilBuffer = nullptr;	//�[�x�X�e���V���o�b�t�@�B
		D3D12_VIEWPORT m_viewport;			//�r���[�|�[�g�B
		D3D12_RECT m_scissorRect;			//�V�U�����O��`�B
		RenderContext m_renderContext;		//�����_�����O�R���e�L�X�g�B
		D3D12_CPU_DESCRIPTOR_HANDLE m_currentFrameBufferRTVHandle;		//���ݏ������ݒ��̃t���[���o�b�t�@�̃����_�����O�^�[�Q�b�g�r���[�̃n���h���B
		D3D12_CPU_DESCRIPTOR_HANDLE m_currentFrameBufferDSVHandle;		//���ݏ������ݒ��̃t���[���o�b�t�@�̐[�x�X�e���V���r���[��
		// GPU�Ƃ̓����Ŏg�p����ϐ��B
		UINT m_frameIndex = 0;
		HANDLE m_fenceEvent = nullptr;
		ID3D12Fence* m_fence = nullptr;
		UINT64 m_fenceValue = 0;
		UINT m_frameBufferWidth = 0;		//�t���[���o�b�t�@�̕��B
		UINT m_frameBufferHeight = 0;		//�t���[���o�b�t�@�̍����B
		Camera m_camera2D;					//2D�J�����B
		Camera m_camera3D;					//3D�J�����B
		Camera m_cameraPostEffect;			//�|�X�g�G�t�F�N�g�p�J�����B
		NullTextureMaps m_nullTexMaps;						//NULL�e�N�X�`���Ǘ��I�u�W�F�N�g�B
		std::unique_ptr<CLightManager> m_lightManager;		//���C�g�}�l�[�W���[�B
		std::unique_ptr<CShadowMap> m_shadowMap;			//�w�����V���h�E�}�b�v�B
		std::unique_ptr<CGBufferRender> m_gBuffer;			//GBuffer�B
		std::unique_ptr<CDefferdShading> m_defferd;			//�f�B�t�@�[�h�B
		std::unique_ptr<CPostEffect> m_postEffect;			//�|�X�g�G�t�F�N�g�B
		std::unique_ptr<CFade> m_fade;						//�t�F�[�h�B
		
		//SpriteBatch
		std::unique_ptr<DirectX::GraphicsMemory> m_directXTKGfxMemroy;	//�o�b�`�o�^�p��DirectXTK�������B
		FontEngine m_fontEngine;										//�t�H���g�G���W���B

		int m_vsyncInterval = 1;							//VSync�̊Ԋu
		////�G�t�F�N�g�֌W
		//EffekseerRenderer::RendererRef m_renderer;
	};
}
