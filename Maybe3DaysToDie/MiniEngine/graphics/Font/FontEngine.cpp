#include "MiniEngine.h"
#include "FontEngine.h"

FontEngine::~FontEngine()
{
	m_srvDescriptorHeap->Release();
}

void FontEngine::Init(RenderContext& rc)
{
	auto d3dDevice = GraphicsEngine()->GetD3DDevice();

	//�q�[�v�쐬�B
	D3D12_DESCRIPTOR_HEAP_DESC heapDesc = {};
	heapDesc.NumDescriptors = 1;
	heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	auto hr = d3dDevice->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(&m_srvDescriptorHeap));

	//�A�b�v���[�h�o�b�`�̐ݒ�B
	/*
		����́A�e�N�X�`���Ȃǂ̃��\�[�X��GPU�������ɃA�b�v���[�h���邽�߂̃w���p�[��񋟂��܂��B
		���̃N���X�́AGPU�̃V�F�[�_�[���g�p�����~�b�v�}�b�v�̎����������������܂��B
	*/
	DirectX::ResourceUploadBatch re(d3dDevice);
	re.Begin();
	//SpriteBatch�̃p�C�v���C���X�e�[�g���쐬����B
	DirectX::RenderTargetState renderTargetState;
	renderTargetState.rtvFormats[0] = DXGI_FORMAT_R32G32B32A32_FLOAT;
	renderTargetState.numRenderTargets = 1;
	renderTargetState.dsvFormat = DXGI_FORMAT_D32_FLOAT;
	renderTargetState.sampleMask = UINT_MAX;
	renderTargetState.sampleDesc.Count = 1;

	DirectX::SpriteBatchPipelineStateDescription BatchDesc(renderTargetState);

	//�r���[�B
	D3D12_VIEWPORT viewport;
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;
	viewport.Width = static_cast<FLOAT>(FRAME_BUFFER_W);
	viewport.Height = static_cast<FLOAT>(FRAME_BUFFER_H);

	//�o�b�`�쐬�B
	m_spriteBatch = std::make_unique<DirectX::SpriteBatch>(
		d3dDevice,
		re,
		BatchDesc,
		&viewport
	);

	//�t�H���g�쐬�B
	D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle = m_srvDescriptorHeap->GetCPUDescriptorHandleForHeapStart();
	D3D12_GPU_DESCRIPTOR_HANDLE gpuHandle = m_srvDescriptorHeap->GetGPUDescriptorHandleForHeapStart();
	m_spriteFont = std::make_unique<DirectX::SpriteFont>(
		d3dDevice,
		re,
		L"Assets/font/myfile.spritefont",
		cpuHandle,
		gpuHandle
	);

	re.End(GraphicsEngine()->GetCommandQueue());
}

void FontEngine::BeginDraw()
{
	m_spriteBatch->Begin(
		GraphicsEngine()->GetCommandList(),
		/*
			SpriteBatch.End���Ăяo�����ƁA���ׂẴX�v���C�g���`��Ăяo���V�[�P���X�̏�����
			�`�悳��܂��B�[���͖�������܂��B
		*/
		DirectX::SpriteSortMode_Deferred,
		g_matIdentity
	);
	GraphicsEngine()->GetCommandList()->SetDescriptorHeaps(1, &m_srvDescriptorHeap);
}

void FontEngine::Draw(const wchar_t* text, const Vector2& pos, const Vector4& color, float rotation, float scale, Vector2 pivot)
{
	m_spriteFont->DrawString(
		m_spriteBatch.get(),
		text,
		pos.vec,
		color,
		rotation,
		DirectX::XMFLOAT2(pivot.x, pivot.y),
		scale
	);
}

void FontEngine::EndDraw()
{
	m_spriteBatch->End();
}
