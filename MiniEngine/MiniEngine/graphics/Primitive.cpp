#include "stdafx.h"
#include "Primitive.h"

Engine::CPrimitive::CPrimitive()
{
}

Engine::CPrimitive::~CPrimitive()
{
}

void Engine::CPrimitive::Create(PrimitiveInitData& initData)
{
	m_vertexBuffer.Init(initData.vertexSize, initData.vertexStride);
	m_indexBuffer.Init(initData.indexSize, initData.indexStride);
	m_vertexBuffer.Copy(initData.pSrcVertexBuffer);
	m_indexBuffer.Copy(initData.pSrcIndexBuffer);
	m_topology = initData.topology;
}

void Engine::CPrimitive::Draw(RenderContext& rc)
{
	//���_�o�b�t�@��ݒ�B
	rc.SetVertexBuffer(m_vertexBuffer);
	//�C���f�b�N�X�o�b�t�@��ݒ�B
	rc.SetIndexBuffer(m_indexBuffer);
	//�v���~�e�B�u�g�|���W�[��ݒ�B
	rc.SetPrimitiveTopology(static_cast<D3D12_PRIMITIVE_TOPOLOGY>(m_topology));
	//�`��B
	rc.DrawIndexed(m_indexBuffer.GetCount(), 1);
}
