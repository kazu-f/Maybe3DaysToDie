#include "stdafx.h"
#include "TerrainRender.h"

namespace nsTerrain {
	bool TerrainRender::Start()
	{

		return true;
	}
	void TerrainRender::Update()
	{

	}
	void TerrainRender::Init(TerrainInitData& initData)
	{
		//頂点バッファとインデックスバッファ作成。
		InitVertexBuffer(initData.vertexNum);
		InitIndexBuffer(initData.vertexNum);
		//シェーダー作成。
		InitShader();
		//パイプラインステート作成。
		InitPipelineState();
		//定数バッファ作成。
		InitConstantBuffer();
		//テクスチャ読み込み。
		InitTexrure();
		//ディスクリプタヒープ作成。
		InitDescriptorHeap();
	}
	void TerrainRender::InitVertexBuffer(int maxVertexNum)
	{
		m_vertices.resize(maxVertexNum);
		//頂点バッファの作成。
		int vertStride = sizeof(Vertex);
		m_vertexBuffer.Init(vertStride * maxVertexNum, vertStride);
	}
	void TerrainRender::InitIndexBuffer(int maxIndexNum)
	{
		m_indices.resize(maxIndexNum);
		m_indexBuffer.Init(2 * maxIndexNum, 2);
	}
	void TerrainRender::InitShader()
	{
		m_vsTerrain.LoadVS(L"Assets/shader/Terrain.fx", "VSMain");
		m_psTerrain.LoadPS(L"Assets/shader/Terrain.fx", "PSMain");
	}
	void TerrainRender::InitPipelineState()
	{
		// 頂点レイアウトを定義する。
		D3D12_INPUT_ELEMENT_DESC inputElementDescs[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
			{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
		};

		//パイプラインステートを作成。
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
		psoDesc.RTVFormats[0] = DXGI_FORMAT_R32G32B32A32_FLOAT;		//アルベドカラー出力用。
		psoDesc.DSVFormat = DXGI_FORMAT_D32_FLOAT;
		psoDesc.SampleDesc.Count = 1;

		m_terrainPS.Init(psoDesc);
	}
	void TerrainRender::InitConstantBuffer()
	{
		//定数バッファを作成。
		m_cbTerrain.Init(sizeof(SCBTerrin));

	}
	void TerrainRender::InitTexrure()
	{
		const auto& nullTexMaps = GraphicsEngine()->GetNullTextureMaps();

		const char* filePath = nullptr;
		char* map = nullptr;
		unsigned int mapSize;
		m_terrainTex = ResourceEngine().GetTextureFromBank("Assets/modelData/preset/NullAlbedo.dds");
		if (m_terrainTex == nullptr)
		{
			filePath = nullTexMaps.GetAlbedoMapFilePath();
			map = nullTexMaps.GetAlbedoMap().get();
			mapSize = nullTexMaps.GetAlbedoMapSize();
			//取得できなければ新しく作成し登録。
			m_terrainTex = new Texture;
			m_terrainTex->InitFromMemory(map, mapSize);
			ResourceEngine().RegistTextureToBank(filePath, m_terrainTex);
		}
	}
	void TerrainRender::InitDescriptorHeap()
	{
		m_descriptorHeap.RegistConstantBuffer(0, m_cbTerrain);
		m_descriptorHeap.RegistConstantBuffer(1, GraphicsEngine()->GetLightManager()->GetLightParamConstantBuffer());		//ライトの設定(1番)。

		m_descriptorHeap.RegistShaderResource(0, *m_terrainTex);
		m_descriptorHeap.RegistShaderResource(1, GraphicsEngine()->GetLightManager()->GetDirectionLightStructuredBuffer());	//ライトの設定(1番)。

		m_descriptorHeap.Commit();
	}

	void TerrainRender::ForwardRender(RenderContext& rc)
	{
		//カメラを定数バッファで送る。
		SCBTerrin cbTerrain;
		cbTerrain.mView = MainCamera().GetViewMatrix();
		cbTerrain.mProj = MainCamera().GetProjectionMatrix();
		//定数バッファにコピー。
		m_cbTerrain.CopyToVRAM(&cbTerrain);

		//頂点バッファに頂点データをコピー。
		m_vertexBuffer.Copy(&m_vertices[0]);
		//インデックスバッファにインデックスデータをコピー。
		m_indexBuffer.Copy(&m_indices[0]);

		//頂点バッファの設定。
		rc.SetVertexBuffer(m_vertexBuffer);
		//インデックスバッファの設定。
		rc.SetIndexBuffer(m_indexBuffer);
		//パイプラインステートの設定。
		rc.SetPipelineState(m_terrainPS);
		//ディスクリプタヒープの設定。
		rc.SetDescriptorHeap(m_descriptorHeap);
		//描画にはトライアングルリストを使え！
		rc.SetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		//描画。
		rc.DrawIndexed(m_vertexCount);

	}

}