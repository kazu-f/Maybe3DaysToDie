#pragma once

#include "NVMGenerator.h"

/// <summary>
/// NVMを利用して経路を探査するアルゴリズム。
/// </summary>
class AStar
{
	using Cell = NVMGenerator::Cell;
private:
	/// <summary>
	/// 該当リストに積む。積んだ際にリスト番号も更新する。
	/// </summary>
	/// <param name="cellList">積むリスト。</param>
	/// <param name="listNo">積むリストの番号。</param>
	/// <param name="addCell">積むセル。</param>
	void AddCellList(std::vector<Cell*>& cellList, NVMGenerator::ListNo& listNo, Cell* addCell)
	{
		//セルを積む。
		cellList.push_back(addCell);
		//リスト番号も更新。
		addCell->listNum = listNo;
	}
	float ClacTraverseCost(Cell* node, Cell* reserchNode);
	/// <summary>
	/// 指定セル1(startCell)から指定セル2(targetCell)までの距離を求める。
	/// <para>AStarとのスタートセルとの関連性はないので勘違いしないように。</para>
	/// </summary>
	/// <param name="startCell">指定セル1(startCell)。</param>
	/// <param name="targetCell">指定セル2(targetCell)。</param>
	/// <returns>セル1からセル2までの距離。</returns>
	float CalcCellToTargetCell(Cell* startCell, Cell* targetCell)
	{
		//指定セルまでの距離を求める。
		Vector3 toTargetCell = startCell->m_CenterPos - targetCell->m_CenterPos;
		//距離。
		float dist = toTargetCell.Length();
		return dist;
	}
	/// <summary>
	/// 該当セルリストにセルを移譲。
	/// <para>移譲した際に、移譲元の要素はリストから消える。</para>
	/// <remarks>
	/// まだリファクタリングできる。
	/// </remarks>
	/// </summary>
	/// <param name="moveList">移譲先。</param>
	/// <param name="moveCell">移譲するセル。</param>
	/// <param name="moveListNo">移譲先のリスト番号。</param>
	void moveCellList(std::vector<Cell*>& moveList, Cell* moveCell, NVMGenerator::ListNo listNo)
	{
		//どのリストに属しているのか検索。
		if (moveCell->listNum == NVMGenerator::EnOpenList) {
			//オープンリストに属している。
			auto it = std::find(m_openCellList.begin(), m_openCellList.end(), moveCell);
			if (it != m_openCellList.end()) {
				//消す。
				m_openCellList.erase(it);
			}
		}
		else if (moveCell->listNum == NVMGenerator::EnCloseList) {
			//クローズリストに属している。
			auto it = std::find(m_closeCellList.begin(), m_closeCellList.end(), moveCell);
			if (it != m_closeCellList.end()) {
				//消す。
				m_closeCellList.erase(it);
			}
		}
		else if (moveCell->listNum == NVMGenerator::EnNoneList) {
			//ノーンリストに属している。
			auto it = std::find(m_noneCellList.begin(), m_noneCellList.end(), moveCell);
			if (it != m_noneCellList.end()) {
				//消す。
				m_noneCellList.erase(it);
			}
		}
		//移譲リストにプッシュバック。
		AddCellList(moveList, listNo, moveCell);
	}
	/// <summary>
	/// セルリストを作成。
	/// <para>リスト→開いてるセルリスト、閉じてるセルリスト。</para>
	/// <para>セルリストの初期化処理。CrateNode呼ぶ前に呼ぶ。</para>
	/// </summary>
	/// <param name="start">スタート位置。</param>
	/// <param name="goal">ゴール位置。</param>
	/// <param name="cell">セル。</param>
	void CreateCellList(Vector3& start, Vector3& goal, std::vector<Cell>& cells);
	/// <summary>
	/// 目的地までのノードを作成して返却する。
	/// </summary>
	/// <returns>目的地までのノード(セル)。</returns>
	NVMGenerator::Cell* CreateNode();
public:
	/// <summary>
	/// 経路を探索。
	/// <para>ローカル変数返すから参照付けたらダメ絶対。</para>
	/// </summary>
	/// <param name="start">スタート位置。</param>
	/// <param name="goal">ゴール位置。</param>
	/// <param name="cells">セル。</param>
	std::vector<Cell*> Search(Vector3& start, Vector3& goal, std::vector<Cell>& cells);
private:
	std::vector<Cell*> m_openCellList;		//経路探査中のセルリスト。
	std::vector<Cell*> m_closeCellList;		//経路探査済みセルリスト。
	std::vector<Cell*> m_noneCellList;		//何も処理を行っていいないセルリスト。
	Cell* m_startCell = nullptr;			//スタートセル。
	Cell* m_goalCell = nullptr;				//ゴールセル。
};

