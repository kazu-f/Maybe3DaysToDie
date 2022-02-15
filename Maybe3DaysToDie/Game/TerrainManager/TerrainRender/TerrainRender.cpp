#include "stdafx.h"
#include "TerrainRender.h"
#include "Item/ItemDataFile.h"

namespace nsTerrain {
	TerrainRender::TerrainRender()
	{
		m_material = ItemDataFile::GetInstance()->GetTerrainMaterials();
	}
	bool TerrainRender::SubStart()
	{
		m_isShadowCaster = true;
		m_isRenderTerrain = true;
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
	void TerrainRender::PostUpdate()
	{
		//�n�`�X�V����������GPU�̃f�[�^�X�V�B
		if (m_isUpdateTerrain) {
			//���_�o�b�t�@�ɒ��_�f�[�^���R�s�[�B
			m_vertexBuffer.Copy(&m_vertices[0]);
			//�C���f�b�N�X�o�b�t�@�ɃC���f�b�N�X�f�[�^���R�s�[�B
			m_indexBuffer.Copy(&m_indices[0]);
			m_isUpdateTerrain = false;
		}
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
		m_vsTerrainShadow.LoadVS(L"Assets/shader/Terrain.fx", "VSTerrainMainShadowMap");
		m_psTerrainShadow.LoadPS(L"Assets/shader/Terrain.fx", "PSTerrainMainShadowMap");
	}
	void TerrainRender::InitPipelineState()
	{
		// ���_���C�A�E�g���`����B
		D3D12_INPUT_ELEMENT_DESC inputElementDescs[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
			{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
			{ "TEXTYPE", 0 , DXGI_FORMAT_R32_FLOAT, 0, 32, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
			{ "TEXTYPE", 1 , DXGI_FORMAT_R32_FLOAT, 0, 36, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
			{ "TEXTYPE", 2 , DXGI_FORMAT_R32_FLOAT, 0, 40, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
			{ "TEXTYPE", 3 , DXGI_FORMAT_R32_FLOAT, 0, 44, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
			{ "TEXTYPE", 4 , DXGI_FORMAT_R32_FLOAT, 0, 48, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
			{ "TEXTYPE", 5 , DXGI_FORMAT_R32_FLOAT, 0, 52, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
			{ "TEXTYPE", 6 , DXGI_FORMAT_R32_FLOAT, 0, 56, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
			{ "TEXTYPE", 7 , DXGI_FORMAT_R32_FLOAT, 0, 60, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
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

		psoDesc.VS = CD3DX12_SHADER_BYTECODE(m_vsTerrainShadow.GetCompiledBlob());
		psoDesc.PS = CD3DX12_SHADER_BYTECODE(m_psTerrainShadow.GetCompiledBlob());
		psoDesc.RTVFormats[0] = DXGI_FORMAT_R32_FLOAT;
		psoDesc.NumRenderTargets = 1;
		m_terrainShadowPS.Init(psoDesc);
	}
	void TerrainRender::InitConstantBuffer()
	{
		//�萔�o�b�t�@���쐬�B
		m_cbTerrain.Init(sizeof(SCBTerrin));

	}
	void TerrainRender::InitTexrure()
	{
		const auto& nullTexMaps = GraphicsEngine()->GetNullTextureMaps();

		const char* filePath = nullTexMaps.GetAlbedoMapFilePath();
		m_nullTex = ResourceEngine().GetTextureFromBank(filePath);
		if (m_nullTex == nullptr)
		{
			m_nullTex = new Texture;
			//������ϊ��B
			wchar_t wddsFilePath[1024];
			mbstowcs(wddsFilePath, filePath, 1023);
			m_nullTex->InitFromDDSFile(wddsFilePath);
			ResourceEngine().RegistTextureToBank(filePath, m_nullTex);
		}
		//m_material->InitTexture();
	}
	void TerrainRender::InitDescriptorHeap()
	{
		m_descriptorHeap.RegistConstantBuffer(0, m_cbTerrain);
		m_descriptorHeap.RegistConstantBuffer(1, GraphicsEngine()->GetLightManager()->GetLightParamConstantBuffer());		//���C�g�̐ݒ�(1��)�B
		m_descriptorHeap.RegistConstantBuffer(3, GraphicsEngine()->GetShadowMap()->GetShadowMapConstantBuffer());		//�V���h�E�}�b�v�̐ݒ�(3��)�B

		m_descriptorHeap.RegistShaderResource(0, *m_nullTex);
		m_descriptorHeap.RegistShaderResource(1, GraphicsEngine()->GetLightManager()->GetDirectionLightStructuredBuffer());	//���C�g�̐ݒ�(1��)�B

		m_descriptorHeap.RegistShaderResource(6, *GraphicsEngine()->GetShadowMap()->GetShadowMapTexture(0));
		m_descriptorHeap.RegistShaderResource(7, *GraphicsEngine()->GetShadowMap()->GetShadowMapTexture(1));
		m_descriptorHeap.RegistShaderResource(8, *GraphicsEngine()->GetShadowMap()->GetShadowMapTexture(2));

		for (int i = 0; i < m_material->GetTextureSize(); i++)
		{
			m_descriptorHeap.RegistShaderResource(10 + i, *m_material->GetTextureTypeID(i));
		}

		m_descriptorHeap.Commit();

		m_dhTerrainShadow.resize(NUM_SHADOW_MAP);
		for (int i = 0; i < NUM_SHADOW_MAP; i++)
		{
			m_cbTerrainShadow[i].Init(sizeof(SCBTerrainShadow));
			m_dhTerrainShadow[i].RegistConstantBuffer(0, m_cbTerrainShadow[i]);

			m_dhTerrainShadow[i].Commit();
		}

	}

	void TerrainRender::OnRenderShadowMap(RenderContext& rc, int shadowMapNo, const Matrix& LVP)
	{
		if (!m_isShadowCaster) return;
		if (!m_isRenderTerrain) return;

		SCBTerrainShadow cbTerrain;
		cbTerrain.mWorld = m_world;
		cbTerrain.mLVP = LVP;

		m_cbTerrainShadow[shadowMapNo].CopyToVRAM(&cbTerrain);

		//���_�o�b�t�@�̐ݒ�B
		rc.SetVertexBuffer(m_vertexBuffer);
		//�C���f�b�N�X�o�b�t�@�̐ݒ�B
		rc.SetIndexBuffer(m_indexBuffer);
		//���[�g�V�O�l�`����ݒ�B
		rc.SetRootSignature(CPipelineStatesDefault::m_modelDrawRootSignature);
		//�p�C�v���C���X�e�[�g�̐ݒ�B
		rc.SetPipelineState(m_terrainShadowPS);
		//�f�B�X�N���v�^�q�[�v�̐ݒ�B
		rc.SetDescriptorHeap(m_dhTerrainShadow.at(shadowMapNo));
		//�`��ɂ̓g���C�A���O�����X�g���g���I
		rc.SetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		rc.DrawIndexed(m_vertexCount);
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

		//���_�o�b�t�@�̐ݒ�B
		rc.SetVertexBuffer(m_vertexBuffer);
		//�C���f�b�N�X�o�b�t�@�̐ݒ�B
		rc.SetIndexBuffer(m_indexBuffer);
		//���[�g�V�O�l�`����ݒ�B
		rc.SetRootSignature(CPipelineStatesDefault::m_modelDrawRootSignature);
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

		//���_�o�b�t�@�̐ݒ�B
		rc.SetVertexBuffer(m_vertexBuffer);
		//�C���f�b�N�X�o�b�t�@�̐ݒ�B
		rc.SetIndexBuffer(m_indexBuffer);
		//���[�g�V�O�l�`����ݒ�B
		rc.SetRootSignature(CPipelineStatesDefault::m_modelDrawRootSignature);
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