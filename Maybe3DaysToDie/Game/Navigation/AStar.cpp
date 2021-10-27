#include "stdafx.h"
#include "AStar.h"
#include "NVMGenerator.h"

void AStar::CreateCellList(Vector3& start, Vector3& goal, std::vector<Cell>& cells)
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
	moveCellList(m_openCellList, m_startCell, NVMGenerator::EnOpenList);
#endif
}


NVMGenerator::Cell* AStar::CreateNode()
{
	while (m_openCellList.size() != 0) {
		//調査対象セル。
		Cell* reserchCell = nullptr;
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
			std::vector<Cell*> linkNodeList;
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
					moveCellList(m_openCellList, linkCell, NVMGenerator::EnOpenList);
				}//新しく隣接していたセルの調査とパラメーター代入。
			}//隣接していたセルの調査とパラメーター代入が終了。
		}//現在調査しているリサーチセルの調査が終了。
		//調査終わったのでクローズリストに積む。
		moveCellList(m_closeCellList, reserchCell, NVMGenerator::EnCloseList);
	}//オープンリストが0になった。ゴールまでの経路なし。
	//MessageBoxA(nullptr, "経路の検索に失敗しました。", "NaviMesh::AStar", MB_OK);
	return nullptr;
}

float AStar::ClacTraverseCost(Cell* node, Cell* reserchNode)
{
	//コスト。
	float cost = 0.0f;
	//前のノードからのコストを計算。
	Vector3 dist = reserchNode->m_CenterPos - node->m_CenterPos;
	return cost = dist.Length();
}

std::vector<NVMGenerator::Cell*> AStar::Search(Vector3& start, Vector3& goal, std::vector<Cell>& cells)
{
	//セルリストの初期化。
	CreateCellList(start, goal, cells);
	//ノードを作成。
	Cell* goalCellNode = CreateNode();

	//ノード情報を管理しやすいように、リストに変換。
	//スタート位置から近い順。
	std::vector<Cell*> m_nodeCellList;
	//現在のセル。
	Cell* currentNode = goalCellNode;
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
	//if (m_nodeCellList.size() > 2) {
	//	//スムージング。
	//	Smoothing(m_nodeCellList);
	//}
	return m_nodeCellList;
}