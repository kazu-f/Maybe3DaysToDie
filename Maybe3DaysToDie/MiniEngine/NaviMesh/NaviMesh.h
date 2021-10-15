#pragma once

namespace Engine {
	/// <summary>
	/// �i�r���b�V���B
	/// </summary>
	class NaviMesh
	{
	public:
		//�o�C�i���f�[�^�̃Z���̃f�[�^�\���́B
		struct CellBin {
			int linkCellNumber[3] = { 1 };	//�אڃZ���ԍ��B
			Vector3 pos[3];
			std::int32_t pad = 0;	//�p�f�B���O�B
			//���p�́B
			union {
				std::intptr_t linkCell64[3];
				CellBin* linkCell[3];
			};
		};
		enum ListNo {
			EnNoneList,
			EnCloseList,
			EnOpenList
		};
		/// <summary>
		/// AStar�Ŏg�p����Z�����B
		/// </summary>
		struct Cell {
			Vector3 pos[3];							//�R���_�B
			Cell* m_parent = nullptr;				//�e�ƂȂ�Z���B
			Cell* child = nullptr;					//�q���ƂȂ�Z���B
			Cell* m_linkCell[3] = { nullptr };		//�אڃZ���B
			Vector3 m_CenterPos = g_vec3Zero;		//�Z���̒������W�B
			float costFromStart = 0.0f;				//�X�^�[�g���猩���R�X�g�B
			float costToEnd = 0.0f;					//�X�^�[�g�ʒu����S�[���ʒu�܂ł̃R�X�g�B
			float totalCost = 0.0f;					//�ŏI�I�ȃR�X�g�B
			int listNum = EnNoneList;				//�ǂ̃��X�g�ɑ����Ă��邩�B
		};
	public:
		/// <summary>
		/// NaviMesh�����[�h�B
		/// </summary>
		void Load(const char* filePath);
	public:
		//���������NaviMesh���e�X�g�`�悷��ۂɕK�v�ȃR�[�h�̂��߁A
		//�`�悵�Ȃ����[�U�[�͎g�p/�Ăяo�����Ȃ��đ��v�B

		/// <summary>
		/// �`��p�������B
		/// </summary>
		/// <param name="isWire">���C���[�t���[���`��ɂ���H</param>
		void InitRender();
		/// <summary>
		/// �G�[�W�F���g�̌o�H��`��B
		/// <para>todo:�����������\�����΂���A���������ɒ������B�B</para>
		/// <para>�d�l��A���[�g�X�V�Ƃ��ł��Ȃ��Ȃ��B�B�BAstar�Ɉڏ�����B</para>
		/// </summary>
		void AgentNodeRender(std::vector<NaviMesh::Cell*>& rootList);
		/// <summary>
		/// �`�揀���B
		/// </summary>
		void BeginRender();
		/// <summary>
		/// NaviMesh��`��B
		/// </summary>
		void Render();
		/// <summary>
		/// �`��㏈���B
		/// </summary>
		void EndRender();
		/// <summary>
		/// �p�C�v���C���X�e�[�g���쐬�B
		/// </summary>
		/// <param name="pipelineState">�o�͐�̃p�C�v���C���X�e�[�g�B</param>
		/// <param name="rs">���[�g�V�O�l�`���[�B</param>
		/// <param name="vs">���_�V�F�[�_�[�B</param>
		/// <param name="ps">�s�N�Z���V�F�[�_�[�B</param>
		/// <param name="isWire">���C���[�t���[���`��H�H</param>
		void InitPipelineState(PipelineState& pipelineState, RootSignature& rs, Shader& vs, Shader& ps, bool isWire, D3D12_PRIMITIVE_TOPOLOGY_TYPE topology);
		/// <summary>
		/// �o�C�i���f�[�^�Z�����擾�B�B
		/// </summary>
		/// <returns>�o�C�i���Z���f�[�^�[�B</returns>
		const CellBin* GetCell() const
		{
			return m_cellBin;
		}
		/// <summary>
		/// �Z���̐����擾�B
		/// </summary>
		/// <returns>�Z���̐��B</returns>
		const int& GetCellNum() const
		{
			return m_numCell;
		}
		/// <summary>
		/// �Z�����X�g���擾�B
		/// </summary>
		/// <returns></returns>
		std::vector<Cell>& GetCellList()
		{
			return m_cell;
		}
	private:
		//�萔�o�b�t�@�̍\���̒�`�B
		struct SConstantBuffer {
			Matrix mRot;			//��]�s��B
			Matrix mView;			//�r���[�s��B
			Matrix mProj;			//�v���W�F�N�V�����s��B
		};
		struct SColorCB {
			Vector4 mColor;			//�|���S���܂��͐����̐F�B
		};
		/// <summary>
		/// ���C���B
		/// </summary>
		struct Line {
			Vector3 start;		//�n�_�B
			Vector3 end;		//�I�_�B
		};
		CellBin* m_cellBin;					//�ǂݍ��ݗp�o�C�i���f�[�^�Z���B���t�@�N�^�����O�����炽�Ԃ񂢂�Ȃ��B
		std::vector<Cell> m_cell;			//AStar�Ŏg���Z���B
		ConstantBuffer m_CB;				//�R���X�^���g�o�b�t�@�[�B
		std::vector<Vector3> m_cellPos;			//�Z���̈ʒu���X�g�B
		unsigned int m_numCell = 0;			//�Z���̐��B
		Vector3 m_eye;						//���_�B

		//NaviMesh�\���p�����o�B
		VertexBuffer m_vertexBuffer;		//���_�o�b�t�@�[�B
		IndexBuffer m_indexBuffer;			//�C���f�b�N�X�o�b�t�@�[�B
		PipelineState m_pipelineState;		//�p�C�v���C���X�e�[�g�B
		RootSignature m_rootSignature;		//���[�g�V�O�l�`���B
		DescriptorHeap m_heap;				//�f�B�X�N���v�^�q�[�v�B
		//�Z�����C���[�t���[���\���p�����o�B
		VertexBuffer m_vertexBuck;			//�w�i�p���_�o�b�t�@�[�B
		std::vector<int> m_indexs;			//�C���f�b�N�X�o�b�t�@�[�̃��X�g�B
		IndexBuffer m_indexBuck;			//�w�i�p�C���f�b�N�X�o�b�t�@�[�B
		PipelineState m_pipelineStateBuck;	//�w�i�p�p�C�v���C���X�e�[�g�B
		//�אڃZ���\���p�����o�B
		VertexBuffer m_lineVertexBuffer;		//�����`��̒��_�o�b�t�@�[�B
		std::vector<int> m_lineIndexs;			//�����`��̃C���f�b�N�X�B
		IndexBuffer m_lineIndexBuffer;			//�����`��C���f�b�N�X�o�b�t�@�[�B
		PipelineState m_lineDrawPipelineState;	//�����`��p�C�v���C���X�e�[�g�B
		std::vector< Line> m_linkCellLine;		//�אڃZ����\�����C���̔z��B
		//�G�[�W�F���g�̃��[�g�`��p�����_�[�B
		bool m_rootInited = false;				//�������t���O�Binit���̂߂�ǂ���������܂�������B
		PipelineState m_rootDrawPipelineState;	//�����`��p�C�v���C���X�e�[�g�B
		VertexBuffer m_rootVertexBuffer;		//���[�g�`��p���_�B
		std::vector<int> m_rootIndexs;			//���[�g�C���f�b�N�X�B
		IndexBuffer m_rootIndexBuffer;			//�����`��C���f�b�N�X�o�b�t�@�[�B
		std::vector<Line> m_rootCellLine;		//�אڃZ����\�����C���̔z��B
	};
}
