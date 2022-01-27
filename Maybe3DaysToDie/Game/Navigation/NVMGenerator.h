#pragma once

#include "TerrainManager/TerrainRender/TerrainRender.h"

class NVMDebugDraw;

/// <summary>
/// �i�r�Q�[�V�������b�V�������N���X�B
/// </summary>
/// <remarks>
/// ���̃N���X�́A�T���h�{�b�N�X�̃X�e�[�W����NVM�𓮓I��������N���X�B
/// �X�e�[�W�ɕύX���������ۂɂ�NVM�ύX���鏈��������i�\��j�B
/// �u���b�N�P�P�ʂ�2���b�V���Ƃ��Ĉ����ׁA�T���h�{�b�N�X�^�ł݂̂����@�\���Ȃ��B
/// </remarks>
class NVMGenerator
{
public:

	//�Z���̏�ԁB
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

	using CellList = std::vector<Cell>;
	using ChunkID = Vector2;

private:
	static bool isInstantiate;								//�C���X�^���X���쐬����Ă��邩�B
	bool m_isDebugDraw = false;								//�f�o�b�O�`�悷��H
	NVMDebugDraw* m_nvmDebugDraw = nullptr;					//�f�o�b�O�`��B
	std::map<ChunkID, CellList> m_chunkIDtoCellListMap;		//�`�����NID����Z�����X�g���擾����}�b�v�B

public:
	NVMGenerator();
	~NVMGenerator();

public:
	/// <summary>
	/// �n�`���NVM���쐬����B
	/// </summary>
	/// <param name="terrain">�n�`</param>
	/// <param name="isDebugDraw">�f�o�b�O�`��B</param>
	void CreateNVM(nsTerrain::TerrainRender* terrain, bool isDebugDraw = false);
	
	/// /// <summary>
	/// �n�`�f�[�^���NVM���X�V����B
	/// <para>�u���b�N���j�󂳂ꂽ��`�����N��NVM�̍X�V���s���B</para>
	/// </summary>
	/// <param name="terrain"></param>
	void UpdateNVM(nsTerrain::TerrainRender* terrain);
	
	/// /// <summary>
	/// �f�o�b�O�`��B
	/// </summary>
	void DebugDraw(nsTerrain::TerrainRender* terrain);
	
	///// /// <summary>
	///// �Z�����X�g���擾�B
	///// </summary>
	///// <returns></returns>
	//std::vector<Cell>& GetCellList()
	//{
	//	return m_cellList;
	//}

	/// <summary>
	/// �f�o�b�O�`��̃t���O��؂�ւ���B
	/// </summary>
	void ChangeDrawFlag()
	{
		m_isDebugDraw = !m_isDebugDraw;
	}
};

