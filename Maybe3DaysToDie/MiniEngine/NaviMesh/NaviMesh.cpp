#include "MiniEngine.h"
#include "NaviMesh.h"

namespace Engine {
	void NaviMesh::Load(const char* filePath)
	{
		FILE* fp = fopen(filePath, "rb");

		if (fp == nullptr) {
			MessageBoxA(nullptr, "ナビゲーションメッシュのファイルパスが間違っています。", "NaviMesh::Error", MB_OK);
			std::abort();
		}

		if (fp) {
			//セルの数を読み込む
			fread(&m_numCell, sizeof(m_numCell), 1, fp);
			m_cell.resize(m_numCell);
			//セルの数分だけメモリをドカッと確保。
			m_cellBin = new CellBin[m_numCell];
			//配列の先頭アドレスをコピー。
			//nvmツールより出力されているリンクセルデーターは、ファイル内相対アドレスデーターとなるため
			//これを実アドレス化するために、m_cellBinのtopAddressを加算してやる必要性がある。
			//この演算を行う際に、intやlongにキャストしていては、環境依存エラーが起きやすくなる。
			//このエラーを回避するため、今回移植性の高い型intptr_tを使用する。
			std::intptr_t topAddress = (std::intptr_t)m_cellBin;
			//セルを読み込んでいく。
			int vertNo = 0;
			for (int i = 0; i < m_numCell; i++) {
				//todo:ここらもうちょいリファクタリングできると思う。 m_cellBin消すくらいまでリファクタリングできそう。
				fread(&m_cellBin[i].linkCellNumber[0], sizeof(m_cellBin[i].linkCellNumber[0]), 1, fp);
				fread(&m_cellBin[i].linkCellNumber[1], sizeof(m_cellBin[i].linkCellNumber[1]), 1, fp);
				fread(&m_cellBin[i].linkCellNumber[2], sizeof(m_cellBin[i].linkCellNumber[2]), 1, fp);
				//まずは頂点。
				fread(&m_cellBin[i].pos[0], sizeof(m_cellBin[i].pos[0]), 1, fp);
				fread(&m_cellBin[i].pos[1], sizeof(m_cellBin[i].pos[1]), 1, fp);
				fread(&m_cellBin[i].pos[2], sizeof(m_cellBin[i].pos[2]), 1, fp);
				//パディングをロード。
				fread(&m_cellBin[i].pad, sizeof(m_cellBin[i].pad), 1, fp);

				//リストに積み積み。
				m_cellPos.push_back(m_cellBin[i].pos[0]);
				m_cellPos.push_back(m_cellBin[i].pos[1]);
				m_cellPos.push_back(m_cellBin[i].pos[2]);
				//続いて隣接セル。ポインタだから64bit。
				fread(&m_cellBin[i].linkCell64[0], sizeof(m_cellBin[i].linkCell64[0]), 1, fp);
				fread(&m_cellBin[i].linkCell64[1], sizeof(m_cellBin[i].linkCell64[1]), 1, fp);
				fread(&m_cellBin[i].linkCell64[2], sizeof(m_cellBin[i].linkCell64[2]), 1, fp);

				//読み込んだバイナリセル情報を基に、AStarで使用するセルに情報を流し込んでいく。
				//隣接セル情報流し込み。
				for (int linkCellNo = 0; linkCellNo < 3; linkCellNo++) {
					if (m_cellBin[i].linkCellNumber[linkCellNo] != INT_MAX) {
						//隣接セル情報あった。
						m_cell[i].m_linkCell[linkCellNo] = &m_cell[m_cellBin[i].linkCellNumber[linkCellNo]];
					}
					else {
						//なかったのでnull入れる。
						m_cell[i].m_linkCell[linkCellNo] = nullptr;
					}
				}
				//中心座標流し込み。
				Vector3 CellCenter;
				for (int posC = 0; posC < 3; posC++) {
					m_cell[i].pos[posC] = m_cellBin[i].pos[posC];
					CellCenter += m_cellBin[i].pos[posC];
				}
				//セルの中心。
				CellCenter /= 3.0f;
				m_cell[i].m_CenterPos = CellCenter;

				//隣接セルの位置情報。
				//fread(, sizeof(Vector3), 1, fp);
				//ここでインデックスバッファー構成しとく。
				m_indexs.push_back(vertNo);
				m_indexs.push_back(vertNo + 1);
				m_indexs.push_back(vertNo + 2);
				vertNo += 3;
				//ファイル内相対アドレスを実アドレス化
				for (int linkCellNo = 0; linkCellNo < 3; linkCellNo++) {
					if (m_cellBin[i].linkCell64[linkCellNo] != -1) {
						m_cellBin[i].linkCell64[linkCellNo] += topAddress;
					}
					else {
						m_cellBin[i].linkCell64[linkCellNo] = 0;
					}
				}

			}
			fclose(fp);
		}

		//ここで全セルを調べて、隣接ライン情報を構築とセルの情報を入れ込む。
		for (int i = 0; i < m_numCell; i++) {
			//次は隣接セルの真ん中も計算する。todo
			for (int linkCell = 0; linkCell < 3; linkCell++) {
				//リンクセル分回す。
				if (m_cell[i].m_linkCell[linkCell] != nullptr) {
					//隣接セルがある場合。
					//ラインを格納する。
					Line line;
					line.start = m_cell[i].m_CenterPos;
					line.end = m_cell[i].m_linkCell[linkCell]->m_CenterPos;
					m_linkCellLine.push_back(line);
				}
			}
		}
		//描画用初期化。
		//InitRender();
	}

	void NaviMesh::AgentNodeRender(std::vector<NaviMesh::Cell*>& rootList)
	{
		if (!m_rootInited) {
			//ライン構成。
			for (int lineC = 0; lineC < rootList.size(); lineC++) {
				if (rootList[lineC] != rootList.back()) {
					//最後はいらない。
					Line line;
					line.start = rootList[lineC]->m_CenterPos;
					line.end = rootList[lineC]->m_parent->m_CenterPos;
					//ルートを形成。
					m_rootCellLine.push_back(line);
				}
			}
			//頂点バッファを形成していく。
			m_rootVertexBuffer.Init(sizeof(Line) * m_rootCellLine.size(), sizeof(Line::start));
			m_rootVertexBuffer.Copy(&m_rootCellLine[0]);
			//インデックスを形成。
			for (int indexs = 0; indexs < m_rootCellLine.size() * 2; indexs++) {
				m_rootIndexs.push_back(indexs);
			}
			//バッファー作成。
			m_rootIndexBuffer.Init(sizeof(m_rootIndexs[0]) * m_rootIndexs.size(), sizeof(m_rootIndexs[0]));
			m_rootIndexBuffer.Copy(&m_rootIndexs[0]);
			m_rootInited = true;
		}
	}

	void NaviMesh::InitRender()
	{
		//頂点バッファー初期化。
		m_vertexBuffer.Init(sizeof(m_cellPos[0]) * m_cellPos.size(), sizeof(m_cellPos[0]));
		m_vertexBuffer.Copy(&m_cellPos[0]);
		//インデックスバッファー初期化。
		m_indexBuffer.Init(sizeof(m_indexs[0]) * m_indexs.size(), sizeof(m_indexs[0]));
		m_indexBuffer.Copy(&m_indexs[0]);

		//セルから、隣接セルに向かう線分の頂点バッファーとインデックスバッファーの形成。
		//頂点バッファを形成していく。
		m_lineVertexBuffer.Init(sizeof(Line) * m_linkCellLine.size(), sizeof(Line::start));
		m_lineVertexBuffer.Copy(&m_linkCellLine[0]);
		//次にインデックスバッファー。
		//インデックスを形成。
		for (int indexs = 0; indexs < m_linkCellLine.size() * 2; indexs++) {
			m_lineIndexs.push_back(indexs);
		}
		//バッファー作成。
		m_lineIndexBuffer.Init(sizeof(m_lineIndexs[0]) * m_lineIndexs.size(), sizeof(m_lineIndexs[0]));
		m_lineIndexBuffer.Copy(&m_lineIndexs[0]);

		//////背景用頂点バッファー初期化。背景は四角形なので４頂点しかいらない。
		//Vector3 v[6]{
		//	//左下の頂点。
		//	{m_vMin.x, m_vMin.y, 0.0f},
		//	//左上の頂点。
		//	{m_vMin.x, m_vMax.y, 0.0f},
		//	//右上の頂点。
		//	{m_vMax.x, m_vMax.y, 0.0f},
		//	//右上の頂点。
		//	{m_vMax.x, m_vMax.y, 0.0f},
		//	//右下の頂点。
		//	{m_vMax.x, m_vMin.y, 0.0f},
		//	//左下の頂点。
		//	{m_vMin.x, m_vMin.y, 0.0f},
		//};
		////初期化。
		//m_vertexBuck.Init(sizeof(v), sizeof(v[0]));
		//m_vertexBuck.Copy(&v[0]);
		////背景用インデックス。
		//int index[6]{
		//	0,1,2,3,4,5
		//};
		//m_indexBuck.Init(sizeof(index), sizeof(index[0]));
		//m_indexBuck.Copy(&index[0]);

		//定数バッファ初期化。
		m_CB.Init(sizeof(SConstantBuffer), nullptr);

		//ルートシグネチャを初期化。
		m_rootSignature.Init(
			D3D12_FILTER_MIN_MAG_MIP_LINEAR,
			D3D12_TEXTURE_ADDRESS_MODE_CLAMP,
			D3D12_TEXTURE_ADDRESS_MODE_CLAMP,
			D3D12_TEXTURE_ADDRESS_MODE_CLAMP
		);

		Shader vs, ps, psWire, psLine, psLineRoot;
		vs.LoadVS(L"Assets/shader/sample.fx", "VSMain");
		ps.LoadPS(L"Assets/shader/sample.fx", "PSMain");
		psWire.LoadPS(L"Assets/shader/sample.fx", "PSMainWire");
		psLine.LoadPS(L"Assets/shader/sample.fx", "PSMainLine");
		psLineRoot.LoadPS(L"Assets/shader/sample.fx", "PSMainLineRoot");

		//ディスクリプタヒープ設定。
		m_heap.RegistConstantBuffer(0, m_CB);
		m_heap.Commit();

		//パイプラインステートを作成。
		InitPipelineState(m_pipelineState, m_rootSignature, vs, ps, false, D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE);
		//ワイヤーフレーム用のパイプラインステート作成。
		InitPipelineState(m_pipelineStateBuck, m_rootSignature, vs, psWire, true, D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE);
		//線分描画用のパイプラインステート作成。
		InitPipelineState(m_lineDrawPipelineState, m_rootSignature, vs, psLine, false, D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE);

		InitPipelineState(m_rootDrawPipelineState, m_rootSignature, vs, psLineRoot, false, D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE);

		D3D12_INPUT_ELEMENT_DESC inputElementDescs[] = {
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
		};

		m_eye = MainCamera().GetPosition();
	}

	void NaviMesh::BeginRender()
	{
	}

	void NaviMesh::Render()
	{
		//Quaternion qRot;
		//qRot.SetRotationDegY(0.0f);
		////まずはカメラの行列を送る。
		//SConstantBuffer cb;
		//cb.mRot.MakeRotationFromQuaternion(qRot);
		//cb.mView = MainCamera().GetViewMatrix();
		//cb.mProj = MainCamera().GetProjectionMatrix();
		//m_CB.CopyToVRAM(&cb);
		//
		////描画。
		//GraphicsEngineObj()->GetRenderContext().SetRootSignature(m_rootSignature);
		//GraphicsEngineObj()->GetRenderContext().SetPipelineState(m_pipelineState);
		//GraphicsEngineObj()->GetRenderContext().SetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		//GraphicsEngineObj()->GetRenderContext().SetDescriptorHeap(m_heap);
		//GraphicsEngineObj()->GetRenderContext().SetVertexBuffer(m_vertexBuffer);
		//GraphicsEngineObj()->GetRenderContext().SetIndexBuffer(m_indexBuffer);
		//GraphicsEngineObj()->GetRenderContext().DrawIndexed(m_indexs.size());

		////パラメーターをパイプライン描画ように変更。
		//GraphicsEngineObj()->GetRenderContext().SetPipelineState(m_pipelineStateBuck);
		//GraphicsEngineObj()->GetRenderContext().DrawIndexed(m_indexs.size());

		////パラメーターを線分用描画に変更して、描画。
		//GraphicsEngineObj()->GetRenderContext().SetPipelineState(m_lineDrawPipelineState);
		//GraphicsEngineObj()->GetRenderContext().SetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_LINELIST);
		//GraphicsEngineObj()->GetRenderContext().SetVertexBuffer(m_lineVertexBuffer);
		//GraphicsEngineObj()->GetRenderContext().SetIndexBuffer(m_lineIndexBuffer);
		//GraphicsEngineObj()->GetRenderContext().DrawIndexed(m_lineIndexs.size());

		////初期化終わったから描画処理～
		//GraphicsEngineObj()->GetRenderContext().SetPipelineState(m_rootDrawPipelineState);
		//GraphicsEngineObj()->GetRenderContext().SetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_LINELIST);
		//GraphicsEngineObj()->GetRenderContext().SetVertexBuffer(m_rootVertexBuffer);
		//GraphicsEngineObj()->GetRenderContext().SetIndexBuffer(m_rootIndexBuffer);
		//GraphicsEngineObj()->GetRenderContext().DrawIndexed(m_rootIndexs.size());
	}

	void NaviMesh::EndRender()
	{
	}

	void NaviMesh::InitPipelineState(PipelineState& pipelineState, RootSignature& rs, Shader& vs, Shader& ps, bool isWire, D3D12_PRIMITIVE_TOPOLOGY_TYPE topology)
	{

		// 頂点レイアウトを定義する。
		D3D12_INPUT_ELEMENT_DESC inputElementDescs[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		};

		//パイプラインステートを作成。
		D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc = { 0 };
		psoDesc.InputLayout = { inputElementDescs, _countof(inputElementDescs) };
		psoDesc.pRootSignature = rs.Get();
		psoDesc.VS = CD3DX12_SHADER_BYTECODE(vs.GetCompiledBlob());
		psoDesc.PS = CD3DX12_SHADER_BYTECODE(ps.GetCompiledBlob());
		psoDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
		if (isWire) {
			psoDesc.RasterizerState.FillMode = D3D12_FILL_MODE_WIREFRAME;
		}
		else {
			psoDesc.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID;
		}

		psoDesc.RasterizerState.CullMode = D3D12_CULL_MODE_NONE;
		psoDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
		psoDesc.DepthStencilState.DepthEnable = TRUE;
		psoDesc.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ZERO;
		psoDesc.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_LESS_EQUAL;
		psoDesc.DepthStencilState.StencilEnable = FALSE;
		psoDesc.SampleMask = UINT_MAX;
		psoDesc.PrimitiveTopologyType = topology;
		psoDesc.NumRenderTargets = 1;
		psoDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
		psoDesc.DSVFormat = DXGI_FORMAT_D32_FLOAT;
		psoDesc.SampleDesc.Count = 1;
		psoDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
		pipelineState.Init(psoDesc);
	}
}
