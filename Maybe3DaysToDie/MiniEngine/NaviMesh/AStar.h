#pragma once

#include "NaviMesh.h"

/// <summary>
/// 経路探査用の計算を行うクラス。
/// </summary>
/// <code>
/// -user呼び出しはこいつのみ。
/// Search(param);
/// </code>
namespace Engine {
	class AStar
	{
		using cell = NaviMesh::Cell;
	private:
		/// <summary>
		/// 該当リストに積む。積んだ際にリスト番号も更新する。
		/// </summary>
		/// <param name="cellList">積むリスト。</param>
		/// <param name="listNo">積むリストの番号。</param>
		/// <param name="addCell">積むセル。</param>
		void AddCellList(std::vector<cell*>& cellList, NaviMesh::ListNo& listNo, cell* addCell)
		{
			//セルを積む。
			cellList.push_back(addCell);
			//リスト番号も更新。
			addCell->listNum = listNo;
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
		void moveCellList(std::vector<cell*>& moveList, cell* moveCell, NaviMesh::ListNo listNo)
		{
			//どのリストに属しているのか検索。
			if (moveCell->listNum == NaviMesh::EnOpenList) {
				//オープンリストに属している。
				auto it = std::find(m_openCellList.begin(), m_openCellList.end(), moveCell);
				if (it != m_openCellList.end()) {
					//消す。
					m_openCellList.erase(it);
				}
			}
			else if (moveCell->listNum == NaviMesh::EnCloseList) {
				//クローズリストに属している。
				auto it = std::find(m_closeCellList.begin(), m_closeCellList.end(), moveCell);
				if (it != m_closeCellList.end()) {
					//消す。
					m_closeCellList.erase(it);
				}
			}
			else if (moveCell->listNum == NaviMesh::EnNoneList) {
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
		/// 指定セル1(startCell)から指定セル2(targetCell)までの距離を求める。
		/// <para>AStarとのスタートセルとの関連性はないので勘違いしないように。</para>
		/// </summary>
		/// <param name="startCell">指定セル1(startCell)。</param>
		/// <param name="targetCell">指定セル2(targetCell)。</param>
		/// <returns>セル1からセル2までの距離。</returns>
		float CalcCellToTargetCell(cell* startCell, cell* targetCell)
		{
			//指定セルまでの距離を求める。
			Vector3 toTargetCell = startCell->m_CenterPos - targetCell->m_CenterPos;
			//距離。
			float dist = toTargetCell.Length();
			return dist;
		}
		/// <summary>
		/// セルリストを作成。
		/// <para>リスト→開いてるセルリスト、閉じてるセルリスト。</para>
		/// <para>セルリストの初期化処理。CrateNode呼ぶ前に呼ぶ。</para>
		/// </summary>
		/// <param name="start">スタート位置。</param>
		/// <param name="goal">ゴール位置。</param>
		/// <param name="cell">セル。</param>
		void CreateCellList(const Vector3& start, Vector3& goal, std::vector<cell>& cells);
		/// <summary>
		/// 前ノードからのリサーチノードへのコストを計算。
		/// </summary>
		/// <param name="node">前ノード。</param>
		/// <param name="reserchNode">リサーチノード。</param>
		/// <returns>前ノードからのリサーチノードへのコスト。</returns>
		float ClacTraverseCost(cell* node, cell* reserchNode);
		/// <summary>
		/// 目的地までのノードを作成して返却する。
		/// </summary>
		/// <returns>目的地までのノード(セル)。</returns>
		NaviMesh::Cell* CreateNode();
		/// <summary>
		/// 経路探査を行ったセルに対してスムージングを行う。
		/// </summary>
		/// <param name="nodeList">ゴールまでのノード。</param>
		/// <returns></returns>
		void Smoothing(std::vector<cell*>& nodeList);
	public:
		/// <summary>
		/// 経路を探索。
		/// <para>ローカル変数返すから参照付けたらダメ絶対。</para>
		/// </summary>
		/// <param name="start">スタート位置。</param>
		/// <param name="goal">ゴール位置。</param>
		/// <param name="cells">セル。</param>
		std::vector<cell*> Search(const Vector3& start, Vector3& goal, std::vector<cell>& cells);
	private:
		std::vector<cell*> m_openCellList;		//開いてるセルリスト(経路探査中のセルリストになる)。
		std::vector<cell*> m_closeCellList;		//閉じてるセルリスト(経路探査済みのセルのリストになる)。
		std::vector<cell*> m_noneCellList;		//まだ何も処理されてないセルリスト。クローズセルリストからコストが低い場合復帰するからいらない気がするなこいつ。
		cell* m_startCell = nullptr;		//スタートセル。
		cell* m_goalCell = nullptr;			//ゴールセル。
	};
}
