#pragma once

#include "NVMDebugDraw.h"
#include "NVMGenerator.h"

/// <summary>
/// NVMを利用して経路を探査するアルゴリズム。
/// </summary>
class AStar
{
	using Cell = NVMGenerator::Cell;
	using Line = NVMDebugDraw::Line;
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
	/// ラインとラインのXZ平面での当たり判定。
	/// </summary>
	/// <param name="line0">ライン０</param>
	/// <param name="line1">ライン１</param>
	/// <returns>trueが返ってくると当たっている</returns>
	bool IntersectLineToLineXZ(Line& line0, Line& line1)
	{
		//ライン0にXZ平面で直交する単位ベクトルを求める。
		//XZ平面での判定。
		line0.start.y = 0;
		line0.end.y = 0;
		line1.start.y = 0;
		line1.end.y = 0;
		//ライン0の始点から終点。
		Vector3 nom = line0.end - line0.start;
		//ラインの法線を求める。
		nom.Cross({ 0,1,0 });
		nom.Normalize();

		//ライン0を含む無限線分との交差判定。
		//ライン0の始点からライン1の終点。
		Vector3 L0StoL1EN = line1.end - line0.start;
		//ライン0の始点からライン1の始点。
		Vector3 L0StoL1SN = line1.start - line0.start;
		//L1の終点と法線の内積。
		float startDot = L0StoL1EN.Dot(nom);
		//L1の始点と法線の内積。
		float endDot = L0StoL1SN.Dot(nom);
		//交差しているなら違う方向。
		float dot = startDot * endDot;
		if (dot < 0.0f) {
			//交差しているので交点を求めていく。
			//辺の絶対値求める。
			float EndLen = fabsf(endDot);
			float StartLen = fabsf(startDot);
			if ((StartLen + EndLen) > 0.0f) {
				//交点の位置を求める。
				//辺の割合を求める。
				float t = EndLen / (StartLen + EndLen);
				//終点から始点。
				Vector3 EtoS = line1.end - line1.start;
				//終点から交点。
				Vector3 EtoHit = EtoS * t;
				//衝突点。
				Vector3 hitPoint = line1.start + EtoHit;
				//始点から衝突点。
				Vector3 StoHit = hitPoint - line1.start;
				EtoHit.Normalize();
				StoHit.Normalize();
				//line1の内積。
				float LineDot = Dot(EtoHit, StoHit);
				if (LineDot < 0) {
					//向かい合っていないので、線分上にない。
					return false;
				}
				//line0
				EtoHit = hitPoint - line0.start;
				StoHit = hitPoint - line0.end;
				LineDot = Dot(EtoHit, StoHit);
				if (LineDot > 0) {
					//向かい合っていないので、線分上にない。
					return false;
				}
				return true;

				////交点。
				//Vector3 hitPos = line1.end + EtoHit;

				////始点、終点への交点。
				//Vector3 StoHit = hitPos - StoHit;

				//auto len = CalcLen(line1.end, line1.start);
				//auto len1 = CalcLen(hitPos, line1.start);
				//auto len2 = CalcLen(line1.end ,hitPos);
				//
				//if (len == len1 + len2) {
				//	return true;
				//}

				//if ((VSL < hitL && hitL < VEL) || (VEL < hitL && hitL < VSL)) {
				//	//片方が小さくて、片方が大きい。
				//}
			}
			//StartLenとEndLenが0よりも小さくなったおかしい。
			return false;
		}
		//交点なし。
		return false;
	}

	/// <summary>
	/// スムージング。
	/// </summary>
	/// <param name="nodeCellList"></param>
	void Smoothing(std::vector<Cell*>& nodeCellList);

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
	void CreateCellList(Vector3& start, Vector3& goal, std::vector<Cell*>& cells);
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
	std::vector<Cell*> Search(Vector3& start, Vector3& goal, std::vector<Cell*>& cells);
private:
	std::vector<Cell*> m_openCellList;		//経路探査中のセルリスト。
	std::vector<Cell*> m_closeCellList;		//経路探査済みセルリスト。
	std::vector<Cell*> m_noneCellList;		//何も処理を行っていいないセルリスト。
	Cell* m_startCell = nullptr;			//スタートセル。
	Cell* m_goalCell = nullptr;				//ゴールセル。
};

