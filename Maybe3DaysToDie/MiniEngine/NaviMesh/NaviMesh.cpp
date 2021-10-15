#include "MiniEngine.h"
#include "NaviMesh.h"

namespace Engine {
	void NaviMesh::Load(const char* filePath)
	{
		FILE* fp = fopen(filePath, "rb");

		if (fp == nullptr) {
			MessageBoxA(nullptr, "�i�r�Q�[�V�������b�V���̃t�@�C���p�X���Ԉ���Ă��܂��B", "NaviMesh::Error", MB_OK);
			std::abort();
		}

		if (fp) {
			//�Z���̐���ǂݍ���
			fread(&m_numCell, sizeof(m_numCell), 1, fp);
			m_cell.resize(m_numCell);
			//�Z���̐����������������h�J�b�Ɗm�ہB
			m_cellBin = new CellBin[m_numCell];
			//�z��̐擪�A�h���X���R�s�[�B
			//nvm�c�[�����o�͂���Ă��郊���N�Z���f�[�^�[�́A�t�@�C�������΃A�h���X�f�[�^�[�ƂȂ邽��
			//��������A�h���X�����邽�߂ɁAm_cellBin��topAddress�����Z���Ă��K�v��������B
			//���̉��Z���s���ۂɁAint��long�ɃL���X�g���Ă��ẮA���ˑ��G���[���N���₷���Ȃ�B
			//���̃G���[��������邽�߁A����ڐA���̍����^intptr_t���g�p����B
			std::intptr_t topAddress = (std::intptr_t)m_cellBin;
			//�Z����ǂݍ���ł����B
			int vertNo = 0;
			for (int i = 0; i < m_numCell; i++) {
				//todo:������������傢���t�@�N�^�����O�ł���Ǝv���B m_cellBin�������炢�܂Ń��t�@�N�^�����O�ł������B
				fread(&m_cellBin[i].linkCellNumber[0], sizeof(m_cellBin[i].linkCellNumber[0]), 1, fp);
				fread(&m_cellBin[i].linkCellNumber[1], sizeof(m_cellBin[i].linkCellNumber[1]), 1, fp);
				fread(&m_cellBin[i].linkCellNumber[2], sizeof(m_cellBin[i].linkCellNumber[2]), 1, fp);
				//�܂��͒��_�B
				fread(&m_cellBin[i].pos[0], sizeof(m_cellBin[i].pos[0]), 1, fp);
				fread(&m_cellBin[i].pos[1], sizeof(m_cellBin[i].pos[1]), 1, fp);
				fread(&m_cellBin[i].pos[2], sizeof(m_cellBin[i].pos[2]), 1, fp);
				//�p�f�B���O�����[�h�B
				fread(&m_cellBin[i].pad, sizeof(m_cellBin[i].pad), 1, fp);

				//���X�g�ɐςݐς݁B
				m_cellPos.push_back(m_cellBin[i].pos[0]);
				m_cellPos.push_back(m_cellBin[i].pos[1]);
				m_cellPos.push_back(m_cellBin[i].pos[2]);
				//�����ėאڃZ���B�|�C���^������64bit�B
				fread(&m_cellBin[i].linkCell64[0], sizeof(m_cellBin[i].linkCell64[0]), 1, fp);
				fread(&m_cellBin[i].linkCell64[1], sizeof(m_cellBin[i].linkCell64[1]), 1, fp);
				fread(&m_cellBin[i].linkCell64[2], sizeof(m_cellBin[i].linkCell64[2]), 1, fp);

				//�ǂݍ��񂾃o�C�i���Z��������ɁAAStar�Ŏg�p����Z���ɏ��𗬂�����ł����B
				//�אڃZ����񗬂����݁B
				for (int linkCellNo = 0; linkCellNo < 3; linkCellNo++) {
					if (m_cellBin[i].linkCellNumber[linkCellNo] != INT_MAX) {
						//�אڃZ����񂠂����B
						m_cell[i].m_linkCell[linkCellNo] = &m_cell[m_cellBin[i].linkCellNumber[linkCellNo]];
					}
					else {
						//�Ȃ������̂�null�����B
						m_cell[i].m_linkCell[linkCellNo] = nullptr;
					}
				}
				//���S���W�������݁B
				Vector3 CellCenter;
				for (int posC = 0; posC < 3; posC++) {
					m_cell[i].pos[posC] = m_cellBin[i].pos[posC];
					CellCenter += m_cellBin[i].pos[posC];
				}
				//�Z���̒��S�B
				CellCenter /= 3.0f;
				m_cell[i].m_CenterPos = CellCenter;

				//�אڃZ���̈ʒu���B
				//fread(, sizeof(Vector3), 1, fp);
				//�����ŃC���f�b�N�X�o�b�t�@�[�\�����Ƃ��B
				m_indexs.push_back(vertNo);
				m_indexs.push_back(vertNo + 1);
				m_indexs.push_back(vertNo + 2);
				vertNo += 3;
				//�t�@�C�������΃A�h���X�����A�h���X��
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

		//�����őS�Z���𒲂ׂāA�אڃ��C�������\�z�ƃZ���̏�����ꍞ�ށB
		for (int i = 0; i < m_numCell; i++) {
			//���͗אڃZ���̐^�񒆂��v�Z����Btodo
			for (int linkCell = 0; linkCell < 3; linkCell++) {
				//�����N�Z�����񂷁B
				if (m_cell[i].m_linkCell[linkCell] != nullptr) {
					//�אڃZ��������ꍇ�B
					//���C�����i�[����B
					Line line;
					line.start = m_cell[i].m_CenterPos;
					line.end = m_cell[i].m_linkCell[linkCell]->m_CenterPos;
					m_linkCellLine.push_back(line);
				}
			}
		}
		//�`��p�������B
		//InitRender();
	}

	void NaviMesh::AgentNodeRender(std::vector<NaviMesh::Cell*>& rootList)
	{
		if (!m_rootInited) {
			//���C���\���B
			for (int lineC = 0; lineC < rootList.size(); lineC++) {
				if (rootList[lineC] != rootList.back()) {
					//�Ō�͂���Ȃ��B
					Line line;
					line.start = rootList[lineC]->m_CenterPos;
					line.end = rootList[lineC]->m_parent->m_CenterPos;
					//���[�g���`���B
					m_rootCellLine.push_back(line);
				}
			}
			//���_�o�b�t�@���`�����Ă����B
			m_rootVertexBuffer.Init(sizeof(Line) * m_rootCellLine.size(), sizeof(Line::start));
			m_rootVertexBuffer.Copy(&m_rootCellLine[0]);
			//�C���f�b�N�X���`���B
			for (int indexs = 0; indexs < m_rootCellLine.size() * 2; indexs++) {
				m_rootIndexs.push_back(indexs);
			}
			//�o�b�t�@�[�쐬�B
			m_rootIndexBuffer.Init(sizeof(m_rootIndexs[0]) * m_rootIndexs.size(), sizeof(m_rootIndexs[0]));
			m_rootIndexBuffer.Copy(&m_rootIndexs[0]);
			m_rootInited = true;
		}
	}

	void NaviMesh::InitRender()
	{
		//���_�o�b�t�@�[�������B
		m_vertexBuffer.Init(sizeof(m_cellPos[0]) * m_cellPos.size(), sizeof(m_cellPos[0]));
		m_vertexBuffer.Copy(&m_cellPos[0]);
		//�C���f�b�N�X�o�b�t�@�[�������B
		m_indexBuffer.Init(sizeof(m_indexs[0]) * m_indexs.size(), sizeof(m_indexs[0]));
		m_indexBuffer.Copy(&m_indexs[0]);

		//�Z������A�אڃZ���Ɍ����������̒��_�o�b�t�@�[�ƃC���f�b�N�X�o�b�t�@�[�̌`���B
		//���_�o�b�t�@���`�����Ă����B
		m_lineVertexBuffer.Init(sizeof(Line) * m_linkCellLine.size(), sizeof(Line::start));
		m_lineVertexBuffer.Copy(&m_linkCellLine[0]);
		//���ɃC���f�b�N�X�o�b�t�@�[�B
		//�C���f�b�N�X���`���B
		for (int indexs = 0; indexs < m_linkCellLine.size() * 2; indexs++) {
			m_lineIndexs.push_back(indexs);
		}
		//�o�b�t�@�[�쐬�B
		m_lineIndexBuffer.Init(sizeof(m_lineIndexs[0]) * m_lineIndexs.size(), sizeof(m_lineIndexs[0]));
		m_lineIndexBuffer.Copy(&m_lineIndexs[0]);

		//////�w�i�p���_�o�b�t�@�[�������B�w�i�͎l�p�`�Ȃ̂łS���_��������Ȃ��B
		//Vector3 v[6]{
		//	//�����̒��_�B
		//	{m_vMin.x, m_vMin.y, 0.0f},
		//	//����̒��_�B
		//	{m_vMin.x, m_vMax.y, 0.0f},
		//	//�E��̒��_�B
		//	{m_vMax.x, m_vMax.y, 0.0f},
		//	//�E��̒��_�B
		//	{m_vMax.x, m_vMax.y, 0.0f},
		//	//�E���̒��_�B
		//	{m_vMax.x, m_vMin.y, 0.0f},
		//	//�����̒��_�B
		//	{m_vMin.x, m_vMin.y, 0.0f},
		//};
		////�������B
		//m_vertexBuck.Init(sizeof(v), sizeof(v[0]));
		//m_vertexBuck.Copy(&v[0]);
		////�w�i�p�C���f�b�N�X�B
		//int index[6]{
		//	0,1,2,3,4,5
		//};
		//m_indexBuck.Init(sizeof(index), sizeof(index[0]));
		//m_indexBuck.Copy(&index[0]);

		//�萔�o�b�t�@�������B
		m_CB.Init(sizeof(SConstantBuffer), nullptr);

		//���[�g�V�O�l�`�����������B
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

		//�f�B�X�N���v�^�q�[�v�ݒ�B
		m_heap.RegistConstantBuffer(0, m_CB);
		m_heap.Commit();

		//�p�C�v���C���X�e�[�g���쐬�B
		InitPipelineState(m_pipelineState, m_rootSignature, vs, ps, false, D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE);
		//���C���[�t���[���p�̃p�C�v���C���X�e�[�g�쐬�B
		InitPipelineState(m_pipelineStateBuck, m_rootSignature, vs, psWire, true, D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE);
		//�����`��p�̃p�C�v���C���X�e�[�g�쐬�B
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
		////�܂��̓J�����̍s��𑗂�B
		//SConstantBuffer cb;
		//cb.mRot.MakeRotationFromQuaternion(qRot);
		//cb.mView = MainCamera().GetViewMatrix();
		//cb.mProj = MainCamera().GetProjectionMatrix();
		//m_CB.CopyToVRAM(&cb);
		//
		////�`��B
		//GraphicsEngineObj()->GetRenderContext().SetRootSignature(m_rootSignature);
		//GraphicsEngineObj()->GetRenderContext().SetPipelineState(m_pipelineState);
		//GraphicsEngineObj()->GetRenderContext().SetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		//GraphicsEngineObj()->GetRenderContext().SetDescriptorHeap(m_heap);
		//GraphicsEngineObj()->GetRenderContext().SetVertexBuffer(m_vertexBuffer);
		//GraphicsEngineObj()->GetRenderContext().SetIndexBuffer(m_indexBuffer);
		//GraphicsEngineObj()->GetRenderContext().DrawIndexed(m_indexs.size());

		////�p�����[�^�[���p�C�v���C���`��悤�ɕύX�B
		//GraphicsEngineObj()->GetRenderContext().SetPipelineState(m_pipelineStateBuck);
		//GraphicsEngineObj()->GetRenderContext().DrawIndexed(m_indexs.size());

		////�p�����[�^�[������p�`��ɕύX���āA�`��B
		//GraphicsEngineObj()->GetRenderContext().SetPipelineState(m_lineDrawPipelineState);
		//GraphicsEngineObj()->GetRenderContext().SetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_LINELIST);
		//GraphicsEngineObj()->GetRenderContext().SetVertexBuffer(m_lineVertexBuffer);
		//GraphicsEngineObj()->GetRenderContext().SetIndexBuffer(m_lineIndexBuffer);
		//GraphicsEngineObj()->GetRenderContext().DrawIndexed(m_lineIndexs.size());

		////�������I���������`�揈���`
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

		// ���_���C�A�E�g���`����B
		D3D12_INPUT_ELEMENT_DESC inputElementDescs[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		};

		//�p�C�v���C���X�e�[�g���쐬�B
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
