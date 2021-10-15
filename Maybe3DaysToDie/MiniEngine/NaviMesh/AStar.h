#pragma once

#include "NaviMesh.h"

/// <summary>
/// �o�H�T���p�̌v�Z���s���N���X�B
/// </summary>
/// <code>
/// -user�Ăяo���͂����̂݁B
/// Search(param);
/// </code>
namespace Engine {
	class AStar
	{
		using cell = NaviMesh::Cell;
	private:
		/// <summary>
		/// �Y�����X�g�ɐςށB�ς񂾍ۂɃ��X�g�ԍ����X�V����B
		/// </summary>
		/// <param name="cellList">�ςރ��X�g�B</param>
		/// <param name="listNo">�ςރ��X�g�̔ԍ��B</param>
		/// <param name="addCell">�ςރZ���B</param>
		void AddCellList(std::vector<cell*>& cellList, NaviMesh::ListNo& listNo, cell* addCell)
		{
			//�Z����ςށB
			cellList.push_back(addCell);
			//���X�g�ԍ����X�V�B
			addCell->listNum = listNo;
		}
		/// <summary>
		/// �Y���Z�����X�g�ɃZ�����ڏ��B
		/// <para>�ڏ������ۂɁA�ڏ����̗v�f�̓��X�g���������B</para>
		/// <remarks>
		/// �܂����t�@�N�^�����O�ł���B
		/// </remarks>
		/// </summary>
		/// <param name="moveList">�ڏ���B</param>
		/// <param name="moveCell">�ڏ�����Z���B</param>
		/// <param name="moveListNo">�ڏ���̃��X�g�ԍ��B</param>
		void moveCellList(std::vector<cell*>& moveList, cell* moveCell, NaviMesh::ListNo listNo)
		{
			//�ǂ̃��X�g�ɑ����Ă���̂������B
			if (moveCell->listNum == NaviMesh::EnOpenList) {
				//�I�[�v�����X�g�ɑ����Ă���B
				auto it = std::find(m_openCellList.begin(), m_openCellList.end(), moveCell);
				if (it != m_openCellList.end()) {
					//�����B
					m_openCellList.erase(it);
				}
			}
			else if (moveCell->listNum == NaviMesh::EnCloseList) {
				//�N���[�Y���X�g�ɑ����Ă���B
				auto it = std::find(m_closeCellList.begin(), m_closeCellList.end(), moveCell);
				if (it != m_closeCellList.end()) {
					//�����B
					m_closeCellList.erase(it);
				}
			}
			else if (moveCell->listNum == NaviMesh::EnNoneList) {
				//�m�[�����X�g�ɑ����Ă���B
				auto it = std::find(m_noneCellList.begin(), m_noneCellList.end(), moveCell);
				if (it != m_noneCellList.end()) {
					//�����B
					m_noneCellList.erase(it);
				}
			}
			//�ڏ����X�g�Ƀv�b�V���o�b�N�B
			AddCellList(moveList, listNo, moveCell);
		}
		/// <summary>
		/// �w��Z��1(startCell)����w��Z��2(targetCell)�܂ł̋��������߂�B
		/// <para>AStar�Ƃ̃X�^�[�g�Z���Ƃ̊֘A���͂Ȃ��̂Ŋ��Ⴂ���Ȃ��悤�ɁB</para>
		/// </summary>
		/// <param name="startCell">�w��Z��1(startCell)�B</param>
		/// <param name="targetCell">�w��Z��2(targetCell)�B</param>
		/// <returns>�Z��1����Z��2�܂ł̋����B</returns>
		float CalcCellToTargetCell(cell* startCell, cell* targetCell)
		{
			//�w��Z���܂ł̋��������߂�B
			Vector3 toTargetCell = startCell->m_CenterPos - targetCell->m_CenterPos;
			//�����B
			float dist = toTargetCell.Length();
			return dist;
		}
		/// <summary>
		/// �Z�����X�g���쐬�B
		/// <para>���X�g���J���Ă�Z�����X�g�A���Ă�Z�����X�g�B</para>
		/// <para>�Z�����X�g�̏����������BCrateNode�ĂԑO�ɌĂԁB</para>
		/// </summary>
		/// <param name="start">�X�^�[�g�ʒu�B</param>
		/// <param name="goal">�S�[���ʒu�B</param>
		/// <param name="cell">�Z���B</param>
		void CreateCellList(const Vector3& start, Vector3& goal, std::vector<cell>& cells);
		/// <summary>
		/// �O�m�[�h����̃��T�[�`�m�[�h�ւ̃R�X�g���v�Z�B
		/// </summary>
		/// <param name="node">�O�m�[�h�B</param>
		/// <param name="reserchNode">���T�[�`�m�[�h�B</param>
		/// <returns>�O�m�[�h����̃��T�[�`�m�[�h�ւ̃R�X�g�B</returns>
		float ClacTraverseCost(cell* node, cell* reserchNode);
		/// <summary>
		/// �ړI�n�܂ł̃m�[�h���쐬���ĕԋp����B
		/// </summary>
		/// <returns>�ړI�n�܂ł̃m�[�h(�Z��)�B</returns>
		NaviMesh::Cell* CreateNode();
		/// <summary>
		/// �o�H�T�����s�����Z���ɑ΂��ăX���[�W���O���s���B
		/// </summary>
		/// <param name="nodeList">�S�[���܂ł̃m�[�h�B</param>
		/// <returns></returns>
		void Smoothing(std::vector<cell*>& nodeList);
	public:
		/// <summary>
		/// �o�H��T���B
		/// <para>���[�J���ϐ��Ԃ�����Q�ƕt������_����΁B</para>
		/// </summary>
		/// <param name="start">�X�^�[�g�ʒu�B</param>
		/// <param name="goal">�S�[���ʒu�B</param>
		/// <param name="cells">�Z���B</param>
		std::vector<cell*> Search(const Vector3& start, Vector3& goal, std::vector<cell>& cells);
	private:
		std::vector<cell*> m_openCellList;		//�J���Ă�Z�����X�g(�o�H�T�����̃Z�����X�g�ɂȂ�)�B
		std::vector<cell*> m_closeCellList;		//���Ă�Z�����X�g(�o�H�T���ς݂̃Z���̃��X�g�ɂȂ�)�B
		std::vector<cell*> m_noneCellList;		//�܂�������������ĂȂ��Z�����X�g�B�N���[�Y�Z�����X�g����R�X�g���Ⴂ�ꍇ���A���邩�炢��Ȃ��C������Ȃ����B
		cell* m_startCell = nullptr;		//�X�^�[�g�Z���B
		cell* m_goalCell = nullptr;			//�S�[���Z���B
	};
}
