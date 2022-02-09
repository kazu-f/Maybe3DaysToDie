#include "stdafx.h"
#include "TerrainRender.h"

namespace nsTerrain {
	bool TerrainRender::SubStart()
	{

		return true;
	}
	void TerrainRender::Update()
	{
		if (InputKeyCode().IsTriggerKey(VK_F3)) {
			m_isRenderTerrain = !m_isRenderTerrain;
		}

		//���[���h�s����X�V�B
		Matrix mTrans, mRot, mScale;
		mTrans.MakeTranslation(m_position);
		mRot.MakeRotationFromQuaternion(m_rotation);
		mScale.MakeScaling(m_scale);
		m_world = mScale * mRot * mTrans;
	}
	void TerrainRender::Init(TerrainInitData& initData)
	{
		m_initData = initData;
		//���_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@�쐬�B
		InitVertexBuffer(initData.vertexNum);
		InitIndexBuffer(initData.vertexNum);
		//�V�F�[�_�[�쐬�B
		InitShader();
		//�p�C�v���C���X�e�[�g�쐬�B
		InitPipelineState();
		//�萔�o�b�t�@�쐬�B
		InitConstantBuffer();
		//�e�N�X�`���ǂݍ��݁B
		InitTexrure();
		//�f�B�X�N���v�^�q�[�v�쐬�B
		InitDescriptorHeap();
	}
	void TerrainRender::InitVertexBuffer(int maxVertexNum)
	{
		m_vertices.resize(maxVertexNum);
		//���_�o�b�t�@�̍쐬�B
		int vertStride = sizeof(TerrainVertex);
		m_vertexBuffer.Init(vertStride * maxVertexNum, vertStride);
	}
	void TerrainRender::InitIndexBuffer(int maxIndexNum)
	{
		m_indices.resize(maxIndexNum);
		m_indexBuffer.Init(sizeof(int) * maxIndexNum, sizeof(int));
	}
	void TerrainRender::InitShader()
	{
		m_vsTerrain.LoadVS(L"Assets/shader/Terrain.fx", "VSTerrainMain");
		if (m_isForward) {
			m_psTerrain.LoadPS(L"Assets/shader/Terrain.fx", "PSTerrainMain");
		}
		else {
			m_psTerrain.LoadPS(L"Assets/shader/Terrain.fx", "PSMain_TerrainRenderGBuffer");
		}
	}
	void TerrainRender::InitPipelineState()
	{
		// ���_���C�A�E�g���`����B
		D3D12_INPUT_ELEMENT_DESC inputElementDescs[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
			{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
		};

		//�p�C�v���C���X�e�[�g���쐬�B
		D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc = { 0 };
		psoDesc.InputLayout = { inputElementDescs, _countof(inputElementDescs) };
		psoDesc.pRootSignature = CPipelineStatesDefault::m_modelDrawRootSignature.Get();
		psoDesc.VS = CD3DX12_SHADER_BYTECODE(m_vsTerrain.GetCompiledBlob());
		psoDesc.PS = CD3DX12_SHADER_BYTECODE(m_psTerrain.GetCompiledBlob());
		psoDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
		psoDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
		psoDesc.DepthStencilState.DepthEnable = TRUE;
		psoDesc.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
		psoDesc.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_LESS_EQUAL;
		psoDesc.DepthStencilState.StencilEnable = FALSE;
		psoDesc.SampleMask = UINT_MAX;
		psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
		psoDesc.NumRenderTargets = 1;
		psoDesc.RTVFormats[0] = DXGI_FORMAT_R32G32B32A32_FLOAT;		//�A���x�h�J���[�o�͗p�B
		psoDesc.DSVFormat = DXGI_FORMAT_D32_FLOAT;
		psoDesc.SampleDesc.Count = 1;

		m_terrainPS.Init(psoDesc);
	}
	void TerrainRender::InitConstantBuffer()
	{
		//�萔�o�b�t�@���쐬�B
		m_cbTerrain.Init(sizeof(SCBTerrin));

	}
	void TerrainRender::InitTexrure()
	{
		const auto& nullTexMaps = GraphicsEngine()->GetNullTextureMaps();

		const char* filePath = nullptr;
		char* map = nullptr;
		unsigned int mapSize;
		//m_terrainTex = ResourceEngine().GetTextureFromBank("Assets/modelData/Terrain/DirtTexture.dds");
		m_terrainTex = ResourceEngine().GetTextureFromBank("Assets/modelData/CubeBlock/T_GroundDirt_01_D.DDS");
		if (m_terrainTex == nullptr)
		{
			m_terrainTex = new Texture;
			//m_terrainTex->InitFromDDSFile(L"Assets/modelData/Terrain/DirtTexture.dds");
			m_terrainTex->InitFromDDSFile(L"Assets/modelData/CubeBlock/T_GroundDirt_01_D.DDS");
			ResourceEngine().RegistTextureToBank("Assets/modelData/CubeBlock/T_GroundDirt_01_D.DDS", m_terrainTex);
		}
	}
	void TerrainRender::InitDescriptorHeap()
	{
		m_descriptorHeap.RegistConstantBuffer(0, m_cbTerrain);
		m_descriptorHeap.RegistConstantBuffer(1, GraphicsEngine()->GetLightManager()->GetLightParamConstantBuffer());		//���C�g�̐ݒ�(1��)�B
		m_descriptorHeap.RegistConstantBuffer(3, GraphicsEngine()->GetShadowMap()->GetShadowMapConstantBuffer());		//�V���h�E�}�b�v�̐ݒ�(3��)�B

		m_descriptorHeap.RegistShaderResource(0, *m_terrainTex);
		m_descriptorHeap.RegistShaderResource(1, GraphicsEngine()->GetLightManager()->GetDirectionLightStructuredBuffer());	//���C�g�̐ݒ�(1��)�B

		m_descriptorHeap.RegistShaderResource(6, *GraphicsEngine()->GetShadowMap()->GetShadowMapTexture(0));
		m_descriptorHeap.RegistShaderResource(7, *GraphicsEngine()->GetShadowMap()->GetShadowMapTexture(1));
		m_descriptorHeap.RegistShaderResource(8, *GraphicsEngine()->GetShadowMap()->GetShadowMapTexture(2));

		m_descriptorHeap.Commit();
	}

	void TerrainRender::OnRenderToGBuffer(RenderContext& rc)
	{
		if (m_isForward) return;
		//�J������萔�o�b�t�@�ő���B
		SCBTerrin cbTerrain;
		cbTerrain.mWorld = m_world;
		cbTerrain.mView = MainCamera().GetViewMatrix();
		cbTerrain.mProj = MainCamera().GetProjectionMatrix();
		cbTerrain.isShadowReceiver = 1;
		//�萔�o�b�t�@�ɃR�s�[�B
		m_cbTerrain.CopyToVRAM(&cbTerrain);

		//�n�`�X�V����������GPU�̃f�[�^�X�V�B
		if (m_isUpdateTerrain) {
			//���_�o�b�t�@�ɒ��_�f�[�^���R�s�[�B
			m_vertexBuffer.Copy(&m_vertices[0]);
			//�C���f�b�N�X�o�b�t�@�ɃC���f�b�N�X�f�[�^���R�s�[�B
			m_indexBuffer.Copy(&m_indices[0]);
			m_isUpdateTerrain = false;
		}

		//���_�o�b�t�@�̐ݒ�B
		rc.SetVertexBuffer(m_vertexBuffer);
		//�C���f�b�N�X�o�b�t�@�̐ݒ�B
		rc.SetIndexBuffer(m_indexBuffer);
		//�p�C�v���C���X�e�[�g�̐ݒ�B
		rc.SetPipelineState(m_terrainPS);
		//�f�B�X�N���v�^�q�[�v�̐ݒ�B
		rc.SetDescriptorHeap(m_descriptorHeap);
		//�`��ɂ̓g���C�A���O�����X�g���g���I
		rc.SetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		//�`��B
		if (m_isRenderTerrain) {
			rc.DrawIndexed(m_vertexCount);
		}
	}
	void TerrainRender::OnForwardRender(RenderContext& rc)
	{
		if (!m_isForward) return;
		//�J������萔�o�b�t�@�ő���B
		SCBTerrin cbTerrain;
		cbTerrain.mWorld = m_world;
		cbTerrain.mView = MainCamera().GetViewMatrix();
		cbTerrain.mProj = MainCamera().GetProjectionMatrix();
		cbTerrain.isShadowReceiver = 1;
		//�萔�o�b�t�@�ɃR�s�[�B
		m_cbTerrain.CopyToVRAM(&cbTerrain);

		//�n�`�X�V����������GPU�̃f�[�^�X�V�B
		if (m_isUpdateTerrain) {
			//���_�o�b�t�@�ɒ��_�f�[�^���R�s�[�B
			m_vertexBuffer.Copy(&m_vertices[0]);
			//�C���f�b�N�X�o�b�t�@�ɃC���f�b�N�X�f�[�^���R�s�[�B
			m_indexBuffer.Copy(&m_indices[0]);
			m_isUpdateTerrain = false;
		}

		//���_�o�b�t�@�̐ݒ�B
		rc.SetVertexBuffer(m_vertexBuffer);
		//�C���f�b�N�X�o�b�t�@�̐ݒ�B
		rc.SetIndexBuffer(m_indexBuffer);
		//�p�C�v���C���X�e�[�g�̐ݒ�B
		rc.SetPipelineState(m_terrainPS);
		//�f�B�X�N���v�^�q�[�v�̐ݒ�B
		rc.SetDescriptorHeap(m_descriptorHeap);
		//�`��ɂ̓g���C�A���O�����X�g���g���I
		rc.SetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		//�`��B
		if (m_isRenderTerrain) {
			rc.DrawIndexed(m_vertexCount);
		}
	}

}