#include "MiniEngine.h"
#include "NaviMesh.h"
#include "AStar.h"

namespace Engine {
	namespace {
		struct Line {
			Vector3 start;
			Vector3 end;
		};
		float CalcLen(Vector3& v0, Vector3& v1)
		{
			float len;
			len = sqrt((v0.x - v1.x) * (v0.x - v1.x) + (v0.y - v1.y) * (v0.y - v1.y) + (v0.z - v1.z) * (v0.z - v1.z));
			return len;
		}
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
	}
	void AStar::CreateCellList(const Vector3& start, Vector3& goal, std::vector<cell>& cells)
	{
#if 0
		//交差ラインテスト。
		Line line0, line1;
		line0.start = { -100, 500, 300 };
		line0.end = { 300, 500, 150 };
		line1.start = { -100, 500, 200 };
		line1.end = { -200, 500, 500 };
		//判定。
		if (IntersectLineToLineXZ(line0, line1) == true) {
			printf("交差していました。\n");
		}
		else {
			printf("交差していません\n");
		}
#else
		//リストをクリア。
		m_openCellList.clear();
		m_closeCellList.clear();
		m_noneCellList.clear();
		//セルをリストに積んでいく。
		for (int cellCount = 0; cellCount < cells.size(); cellCount++) {
			//セルのパラメーターを初期化。
			cells[cellCount].costFromStart = 0.0f;
			cells[cellCount].costToEnd = 0.0f;
			cells[cellCount].m_parent = nullptr;
			cells[cellCount].totalCost = 0.0f;
			//なにもされてないセルリストに積む。
			m_noneCellList.push_back(&cells[cellCount]);
		}
		//最小距離。
		float startMin, goalMin;
		startMin = FLT_MAX;
		goalMin = FLT_MAX;
		//最小距離だったセル番号。
		int startCellNo, goalCellNo;
		startCellNo = -1;
		goalCellNo = -1;
		//開くセルを求める。
		for (int cellCount = 0; cellCount < cells.size(); cellCount++) {
			//ゴール地点から、１番距離が近いセルを求める。
			Vector3 goalToCenter = cells[cellCount].m_CenterPos - goal;
			float dist = goalToCenter.Length();
			if (dist < goalMin) {
				//更新。
				goalMin = dist;
				goalCellNo = cellCount;
				m_goalCell = &cells[cellCount];
			}
			//スタート地点から、一番距離が近いセルを求める。
			Vector3 startToCenter = cells[cellCount].m_CenterPos - start;
			dist = startToCenter.Length();
			if (dist < startMin) {
				//更新。
				startMin = dist;
				startCellNo = cellCount;
				m_startCell = &cells[cellCount];
			}
		}

		//コスト計算。スタート位置のコストって別にいらんかも？
		Vector3 startToGoal = m_goalCell->m_CenterPos - m_startCell->m_CenterPos;
		float dist = startToGoal.Length();
		m_startCell->costToEnd = dist;
		//始点はオープンされる。
		moveCellList(m_openCellList, m_startCell, NaviMesh::EnOpenList);
#endif
	}

	float AStar::ClacTraverseCost(cell* node, cell* reserchNode)
	{
		//コスト。
		float cost = 0.0f;
		//前のノードからのコストを計算。
		Vector3 dist = reserchNode->m_CenterPos - node->m_CenterPos;
		return cost = dist.Length();
	}

	NaviMesh::Cell* AStar::CreateNode()
	{
		while (m_openCellList.size() != 0) {
			//調査対象セル。
			cell* reserchCell = nullptr;
			//コスト。
			float cost = FLT_MAX;
			//開かれてるセルのうち、一番コストが低いもののが調査する対象セルとなる。
			for (auto cell : m_openCellList) {//todo:このループの書き方の方が綺麗なのでは？
				if (cell->costToEnd < cost) {
					//コストが低いので調査セルを変える。
					reserchCell = cell;
					cost = reserchCell->costToEnd;
				}
			}//reserchCell asking completed.

			//調査セル求まったので経路のノードを作成していく。
			if (reserchCell == m_goalCell) {
				//調査のセルがゴールのセルだった。
				//MessageBoxA(nullptr, "経路探索完了！！", "NaviMesh::AStar", MB_OK);
				return reserchCell;
			}
			else {
				//ゴールセルではない。
				//調査中のセルと隣接しているセルのリスト。
				std::vector<cell*> linkNodeList;
				//隣接セルを調べてリストに積む。
				for (int linkCellCount = 0; linkCellCount < 3; linkCellCount++) {
					if (reserchCell->m_linkCell[linkCellCount] != nullptr) {
						linkNodeList.push_back(reserchCell->m_linkCell[linkCellCount]);
					}
				}
				//隣接セルを調査する必要があるのかの識別を行う。
				for (auto& linkCell : linkNodeList) {
					float newCost = reserchCell->costFromStart + ClacTraverseCost(reserchCell, linkCell);
					//クローズセルに積まれているか検索する。
					auto closeListIt = std::find(m_closeCellList.begin(), m_closeCellList.end(), linkCell);
					auto openListIt = std::find(m_openCellList.begin(), m_openCellList.end(), linkCell);
					//調査する必要があるかの識別。
					if ((closeListIt != m_closeCellList.end() || openListIt != m_openCellList.end()) && linkCell->costFromStart <= newCost) {
						//クローズセルまたはオープンセルでコストも改善されないので、こいつはスキップ。
						continue;
					}
					else {
						//新しいセルもしくは、改善されたセルなので情報を保存していく。
						linkCell->m_parent = reserchCell;
						linkCell->costFromStart = newCost;
						linkCell->costToEnd = CalcCellToTargetCell(linkCell, m_goalCell);
						linkCell->totalCost = linkCell->costFromStart + linkCell->costToEnd;
						//調べたセルをオープンセルに変更する。
						moveCellList(m_openCellList, linkCell, NaviMesh::EnOpenList);
					}//新しく隣接していたセルの調査とパラメーター代入。
				}//隣接していたセルの調査とパラメーター代入が終了。
			}//現在調査しているリサーチセルの調査が終了。
			//調査終わったのでクローズリストに積む。
			moveCellList(m_closeCellList, reserchCell, NaviMesh::EnCloseList);
		}//オープンリストが0になった。ゴールまでの経路なし。
		//MessageBoxA(nullptr, "経路の検索に失敗しました。", "NaviMesh::AStar", MB_OK);
		return nullptr;
	}

	void AStar::Smoothing(std::vector<cell*>& nodeCellList)
	{
		//最初のセル。
		cell* baseCell = nodeCellList.back();
		//スムーズ可能かどうか調べるための目的地セル。
		cell* targetCell = baseCell->m_parent->m_parent;
		//リサーチセルはベースセルの親。
		cell* reserchCell = baseCell->m_parent;
		//削除予定リスト。
		std::vector<cell*> deleteCellList;
		//ベースセルの親ノードは確定でスムージング可能なのでスムージングする。
		deleteCellList.push_back(baseCell->m_parent);
		//前の当たり判定調査で消されたセル（復帰可能性のあるセル。）
		cell* deleteCell = baseCell->m_parent;


		while (baseCell->m_parent->m_parent != nullptr) {
			//ノードがなくなるまでスムージングチェック。

			//ベースセルとターゲットセルの間に存在するセルと、ベースセルからターゲットセルに向かう線分と
			//あたり判定調査を行い間に存在するセルすべてと衝突しているならセルをスムージング可能。

			//ベースのセルの中心から、調査セルの中心に向かう線分を求める。
			Line BaseLine;
			BaseLine.start = baseCell->m_CenterPos;
			BaseLine.end = targetCell->m_CenterPos;

			//セルを構成する3本の線分を求める。
			const int MAXLINE = 3;
			Line line[MAXLINE];
			line[0].start = reserchCell->pos[0];
			line[0].end = reserchCell->pos[1];
			line[1].start = reserchCell->pos[1];
			line[1].end = reserchCell->pos[2];
			line[2].start = reserchCell->pos[2];
			line[2].end = reserchCell->pos[0];

			//衝突したかフラグ。
			bool isHit = false;
			for (int lineCount = 0; lineCount < MAXLINE; lineCount++) {
				//当たり判定調査。
				isHit = IntersectLineToLineXZ(BaseLine, line[lineCount]);
				if (isHit) {
					//このセルの当たり判定調査は終了。
					reserchCell = reserchCell->m_parent;
					break;
				}
			}

			if (!isHit) {
				//間に存在するセルと衝突していない、スムージング不可能。
				//セルを更新。
				baseCell = targetCell;
				if (baseCell->m_parent != nullptr) {
					targetCell = baseCell->m_parent->m_parent;
					reserchCell = baseCell->m_parent;
					if (deleteCell != nullptr) {
						//スムージング不可能なので前セルを削除予定リストから復帰させる。
						deleteCellList.erase(std::find(deleteCellList.begin(), deleteCellList.end(), deleteCell));
					}
					//ベースセルの親ノードは確定でスムージング可能なのでスムージングする。
					deleteCellList.push_back(baseCell->m_parent);
					//消す予定セルを更新。
					deleteCell = baseCell->m_parent;
				}
				else {
					//親親が存在しない。
					break;
				}
			}

			if (reserchCell == targetCell) {
				//セルを更新。
				if (targetCell->m_parent == nullptr) {
					//ターゲットせるの親切れ。
					break;
				}
				//ターゲットセルまで到着、スムージング可能なので削除予定リストに積む。
				deleteCellList.push_back(targetCell);
				//このセルは、次のセルの当たり判定で復帰する可能性があるのでバックアップをとっておく。
				deleteCell = targetCell;
				targetCell = targetCell->m_parent;
				reserchCell = baseCell->m_parent;
			}
		}//ノードがなくなった調査終了。

		for (auto deleteC : deleteCellList) {
			//削除予定リストに乗ってたセルは全部消す。
			auto it = std::find(nodeCellList.begin(), nodeCellList.end(), deleteC);
			if (it != nodeCellList.end()) {
				nodeCellList.erase(it);
			}
		}


		//ゴールまでのノードを再構成する。
		for (int nodeNo = 0; nodeNo < nodeCellList.size(); nodeNo++) {
			if (nodeCellList[nodeNo]->costToEnd != 0.0f) {
				//ゴールじゃないなら。親ノードをつなぎなおす。
				//printf("%f, %f\n", nodeCellList[nodeNo]->m_CenterPos.x, nodeCellList[nodeNo]->m_CenterPos.z);
				nodeCellList[nodeNo]->m_parent = nodeCellList[nodeNo + 1];
			}
		}

	}



	std::vector<NaviMesh::Cell*> AStar::Search(const Vector3& start, Vector3& goal, std::vector<cell>& cells)
	{
		//セルリストの初期化。
		CreateCellList(start, goal, cells);
		//ノードを作成。
		cell* goalCellNode = CreateNode();

		//ノード情報を管理しやすいように、リストに変換。
		//スタート位置から近い順。
		std::vector<cell*> m_nodeCellList;
		//現在のセル。
		cell* currentNode = goalCellNode;
		while (currentNode != nullptr)
		{
			//リストに積む。
			m_nodeCellList.insert(m_nodeCellList.begin(), currentNode);
			currentNode = currentNode->m_parent;
			if (currentNode != nullptr) {
				currentNode->child = m_nodeCellList.front();
			}
		}

		//スムージングできる？
		if (m_nodeCellList.size() > 2) {
			//スムージング。
			Smoothing(m_nodeCellList);
		}
		return m_nodeCellList;
	}
}


