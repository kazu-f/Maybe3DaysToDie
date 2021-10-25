#pragma once

#include "NVMGenerator.h"
//#include "TerrainManager/TerrainRender/TerrainRender.h"

class NVMDebugDraw
{
public:
	void Init(std::vector<short>& indexList);
	void Render(int& vertexCount);

public:
	void PushVertex(Vector3& pos)
	{
		m_allCellPos.push_back(pos);
	}
private:
	/// <summary>
	/// �p�C�v���C���X�e�[�g���쐬�B
	/// </summary>
	/// <param name="pipelineState">�o�͐�̃p�C�v���C���X�e�[�g�B</param>
	/// <param name="rs">���[�g�V�O�l�`���[�B</param>
	/// <param name="vs">���_�V�F�[�_�[�B</param>
	/// <param name="ps">�s�N�Z���V�F�[�_�[�B</param>
	/// <param name="isWire">���C���[�t���[���`��H�H</param>
	void InitPipelineState(PipelineState& pipelineState, RootSignature& rs, Shader& vs, Shader& ps, bool isWire, D3D12_PRIMITIVE_TOPOLOGY_TYPE topology);

	//���C���B
	struct Line {
		Vector3 start;		//�n�_�B
		Vector3 end;		//�I�_�B
	};
	//�萔�o�b�t�@�̍\���̒�`�B
	struct SConstantBuffer {
		Matrix mRot;			//��]�s��B
		Matrix mView;			//�r���[�s��B
		Matrix mProj;			//�v���W�F�N�V�����s��B
	};

	std::vector<Vector3> m_allCellPos;	//�Z�����\������R���_�̃��X�g�B
	//NaviMesh�\���p�����o�B
	ConstantBuffer m_CB;				//�R���X�^���g�o�b�t�@�[�B
	VertexBuffer m_vertexBuffer;		//���_�o�b�t�@�[�B
	IndexBuffer m_indexBuffer;			//�C���f�b�N�X�o�b�t�@�[�B
	PipelineState m_pipelineState;		//�p�C�v���C���X�e�[�g�B
	RootSignature m_rootSignature;		//���[�g�V�O�l�`���B
	DescriptorHeap m_heap;				//�f�B�X�N���v�^�q�[�v�B
	//�Z�����C���[�t���[���\���p�����o�B
	VertexBuffer m_vertexBuck;			//�w�i�p���_�o�b�t�@�[�B
	int indexSize = 0;
	IndexBuffer m_indexBuck;			//�w�i�p�C���f�b�N�X�o�b�t�@�[�B
	PipelineState m_pipelineStateBuck;	//�w�i�p�p�C�v���C���X�e�[�g�B
	//�אڃZ���\���p�����o�B
	VertexBuffer m_lineVertexBuffer;		//�����`��̒��_�o�b�t�@�[�B
	std::vector<int> m_lineIndexs;			//�����`��̃C���f�b�N�X�B
	IndexBuffer m_lineIndexBuffer;			//�����`��C���f�b�N�X�o�b�t�@�[�B
	PipelineState m_lineDrawPipelineState;	//�����`��p�C�v���C���X�e�[�g�B
	std::vector<Line> m_linkCellLine;		//�אڃZ����\�����C���̔z��B
};

