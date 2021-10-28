#include "MiniEngine.h"
#include "IndexBuffer.h"


namespace Engine {

	IndexBuffer::~IndexBuffer()
	{
		if (m_indexBuffer) {
			m_indexBuffer->Release();
		}
	}
	void IndexBuffer::Init(int size, int stride)
	{
		//�T�C�Y��4�o�C�g�ɕϊ��B
		if (stride == 2) {
			m_sizeInBytes = size * 2;
		}
		else {
			//stride = 4�̎�size���Ȃ��Ȃ��Ă�������ł����H
			m_sizeInBytes = size;
		}
		m_strideInBytes = stride;
		auto d3dDevice = GraphicsEngine()->GetD3DDevice();
		auto d3dxHeapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
		auto d3dxResourceDesc = CD3DX12_RESOURCE_DESC::Buffer(m_sizeInBytes);
		auto hr = d3dDevice->CreateCommittedResource(
			&d3dxHeapProperties,
			D3D12_HEAP_FLAG_NONE,
			&d3dxResourceDesc,
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			IID_PPV_ARGS(&m_indexBuffer));

		//�C���f�b�N�X�o�b�t�@�̃r���[���쐬�B
		m_indexBufferView.BufferLocation = m_indexBuffer->GetGPUVirtualAddress();


		m_indexBufferView.Format = DXGI_FORMAT_R32_UINT;
		m_indexBufferView.SizeInBytes = m_sizeInBytes;

		//�C���f�b�N�X�̐����v�Z�B
		m_count = m_sizeInBytes / 4;
	}
	void IndexBuffer::Copy(void* srcIndecies)
	{
		uint32_t* pData;
		m_indexBuffer->Map(0, nullptr, (void**)&pData);
		if (m_strideInBytes == 2)
		{
			short* pSrcIndecies = (short*)srcIndecies;
			for (int i = 0; i < m_count; i++) {
				pData[i] = pSrcIndecies[i];
			}
		}
		else {
			int* pSrcIndecies = (int*)srcIndecies;
			for (int i = 0; i < m_count; i++) {
				pData[i] = pSrcIndecies[i];
			}
		}
		m_indexBuffer->Unmap(0, nullptr);
	}

}