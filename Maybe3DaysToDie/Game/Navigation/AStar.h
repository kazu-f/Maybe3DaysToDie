#pragma once

#include "NVMDebugDraw.h"
#include "NVMGenerator.h"

/// <summary>
/// NVM�𗘗p���Čo�H��T������A���S���Y���B
/// </summary>
class AStar
{
	using Cell = NVMGenerator::Cell;
	using Line = NVMDebugDraw::Line;
private:
	/// <summary>
	/// �Y�����X�g�ɐςށB�ς񂾍ۂɃ��X�g�ԍ����X�V����B
	/// </summary>
	/// <param name="cellList">�ςރ��X�g�B</param>
	/// <param name="listNo">�ςރ��X�g�̔ԍ��B</param>
	/// <param name="addCell">�ςރZ���B</param>
	void AddCellList(std::vector<Cell*>& cellList, NVMGenerator::ListNo& listNo, Cell* addCell)
	{
		//�Z����ςށB
		cellList.push_back(addCell);
		//���X�g�ԍ����X�V�B
		addCell->listNum = listNo;
	}
	float ClacTraverseCost(Cell* node, Cell* reserchNode);

	/// <summary>
	/// ���C���ƃ��C����XZ���ʂł̓����蔻��B
	/// </summary>
	/// <param name="line0">���C���O</param>
	/// <param name="line1">���C���P</param>
	/// <returns>true���Ԃ��Ă���Ɠ������Ă���</returns>
	bool IntersectLineToLineXZ(Line& line0, Line& line1)
	{
		//���C��0��XZ���ʂŒ�������P�ʃx�N�g�������߂�B
		//XZ���ʂł̔���B
		line0.start.y = 0;
		line0.end.y = 0;
		line1.start.y = 0;
		line1.end.y = 0;
		//���C��0�̎n�_����I�_�B
		Vector3 nom = line0.end - line0.start;
		//���C���̖@�������߂�B
		nom.Cross({ 0,1,0 });
		nom.Normalize();

		//���C��0���܂ޖ��������Ƃ̌�������B
		//���C��0�̎n�_���烉�C��1�̏I�_�B
		Vector3 L0StoL1EN = line1.end - line0.start;
		//���C��0�̎n�_���烉�C��1�̎n�_�B
		Vector3 L0StoL1SN = line1.start - line0.start;
		//L1�̏I�_�Ɩ@���̓��ρB
		float startDot = L0StoL1EN.Dot(nom);
		//L1�̎n�_�Ɩ@���̓��ρB
		float endDot = L0StoL1SN.Dot(nom);
		//�������Ă���Ȃ�Ⴄ�����B
		float dot = startDot * endDot;
		if (dot < 0.0f) {
			//�������Ă���̂Ō�_�����߂Ă����B
			//�ӂ̐�Βl���߂�B
			float EndLen = fabsf(endDot);
			float StartLen = fabsf(startDot);
			if ((StartLen + EndLen) > 0.0f) {
				//��_�̈ʒu�����߂�B
				//�ӂ̊��������߂�B
				float t = EndLen / (StartLen + EndLen);
				//�I�_����n�_�B
				Vector3 EtoS = line1.end - line1.start;
				//�I�_�����_�B
				Vector3 EtoHit = EtoS * t;
				//�Փ˓_�B
				Vector3 hitPoint = line1.start + EtoHit;
				//�n�_����Փ˓_�B
				Vector3 StoHit = hitPoint - line1.start;
				EtoHit.Normalize();
				StoHit.Normalize();
				//line1�̓��ρB
				float LineDot = Dot(EtoHit, StoHit);
				if (LineDot < 0) {
					//�����������Ă��Ȃ��̂ŁA������ɂȂ��B
					return false;
				}
				//line0
				EtoHit = hitPoint - line0.start;
				StoHit = hitPoint - line0.end;
				LineDot = Dot(EtoHit, StoHit);
				if (LineDot > 0) {
					//�����������Ă��Ȃ��̂ŁA������ɂȂ��B
					return false;
				}
				return true;

				////��_�B
				//Vector3 hitPos = line1.end + EtoHit;

				////�n�_�A�I�_�ւ̌�_�B
				//Vector3 StoHit = hitPos - StoHit;

				//auto len = CalcLen(line1.end, line1.start);
				//auto len1 = CalcLen(hitPos, line1.start);
				//auto len2 = CalcLen(line1.end ,hitPos);
				//
				//if (len == len1 + len2) {
				//	return true;
				//}

				//if ((VSL < hitL && hitL < VEL) || (VEL < hitL && hitL < VSL)) {
				//	//�Е����������āA�Е����傫���B
				//}
			}
			//StartLen��EndLen��0�����������Ȃ������������B
			return false;
		}
		//��_�Ȃ��B
		return false;
	}

	/// <summary>
	/// �X���[�W���O�B
	/// </summary>
	/// <param name="nodeCellList"></param>
	void Smoothing(std::vector<Cell*>& nodeCellList);

	/// <summary>
	/// �w��Z��1(startCell)����w��Z��2(targetCell)�܂ł̋��������߂�B
	/// <para>AStar�Ƃ̃X�^�[�g�Z���Ƃ̊֘A���͂Ȃ��̂Ŋ��Ⴂ���Ȃ��悤�ɁB</para>
	/// </summary>
	/// <param name="startCell">�w��Z��1(startCell)�B</param>
	/// <param name="targetCell">�w��Z��2(targetCell)�B</param>
	/// <returns>�Z��1����Z��2�܂ł̋����B</returns>
	float CalcCellToTargetCell(Cell* startCell, Cell* targetCell)
	{
		//�w��Z���܂ł̋��������߂�B
		Vector3 toTargetCell = startCell->m_CenterPos - targetCell->m_CenterPos;
		//�����B
		float dist = toTargetCell.Length();
		return dist;
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
	void moveCellList(std::vector<Cell*>& moveList, Cell* moveCell, NVMGenerator::ListNo listNo)
	{
		//�ǂ̃��X�g�ɑ����Ă���̂������B
		if (moveCell->listNum == NVMGenerator::EnOpenList) {
			//�I�[�v�����X�g�ɑ����Ă���B
			auto it = std::find(m_openCellList.begin(), m_openCellList.end(), moveCell);
			if (it != m_openCellList.end()) {
				//�����B
				m_openCellList.erase(it);
			}
		}
		else if (moveCell->listNum == NVMGenerator::EnCloseList) {
			//�N���[�Y���X�g�ɑ����Ă���B
			auto it = std::find(m_closeCellList.begin(), m_closeCellList.end(), moveCell);
			if (it != m_closeCellList.end()) {
				//�����B
				m_closeCellList.erase(it);
			}
		}
		else if (moveCell->listNum == NVMGenerator::EnNoneList) {
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
	/// �Z�����X�g���쐬�B
	/// <para>���X�g���J���Ă�Z�����X�g�A���Ă�Z�����X�g�B</para>
	/// <para>�Z�����X�g�̏����������BCrateNode�ĂԑO�ɌĂԁB</para>
	/// </summary>
	/// <param name="start">�X�^�[�g�ʒu�B</param>
	/// <param name="goal">�S�[���ʒu�B</param>
	/// <param name="cell">�Z���B</param>
	void CreateCellList(Vector3& start, Vector3& goal, std::vector<Cell*>& cells);
	/// <summary>
	/// �ړI�n�܂ł̃m�[�h���쐬���ĕԋp����B
	/// </summary>
	/// <returns>�ړI�n�܂ł̃m�[�h(�Z��)�B</returns>
	NVMGenerator::Cell* CreateNode();
public:
	/// <summary>
	/// �o�H��T���B
	/// <para>���[�J���ϐ��Ԃ�����Q�ƕt������_����΁B</para>
	/// </summary>
	/// <param name="start">�X�^�[�g�ʒu�B</param>
	/// <param name="goal">�S�[���ʒu�B</param>
	/// <param name="cells">�Z���B</param>
	std::vector<Cell*> Search(Vector3& start, Vector3& goal, std::vector<Cell*>& cells);
private:
	std::vector<Cell*> m_openCellList;		//�o�H�T�����̃Z�����X�g�B
	std::vector<Cell*> m_closeCellList;		//�o�H�T���ς݃Z�����X�g�B
	std::vector<Cell*> m_noneCellList;		//�����������s���Ă����Ȃ��Z�����X�g�B
	Cell* m_startCell = nullptr;			//�X�^�[�g�Z���B
	Cell* m_goalCell = nullptr;				//�S�[���Z���B
};

