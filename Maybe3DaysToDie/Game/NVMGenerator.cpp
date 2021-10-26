#include "stdafx.h"
#include "NVMGenerator.h"
#include "DestructibleObject/Terrain/Terrain.h"
#include "NVMDebugDraw.h"

bool NVMGenerator::isInstantiate = false;

NVMGenerator::NVMGenerator()
{
	//シングルトン。
	assert(!isInstantiate);
	isInstantiate = true;
}

NVMGenerator::~NVMGenerator()
{
}

void NVMGenerator::CreateNVM(nsTerrain::TerrainRender* terrain, bool isDebugDraw)
{
	//重点の数はメッシュの数。
	int meshCount = terrain->GetCenterArray().size();

	//頂点カウント。
	int vertCount = 0;
	//NVMの基本パラメーターを流し込んでいく。
	for (int mesh = 0; mesh < meshCount; mesh++) {
		//セルを作成する。
		Cell cell;
		//メッシュ全ての３頂点を計算する。
		cell.pos[0] = terrain->GetVertexList().at(vertCount).m_pos;
		cell.pos[1] = terrain->GetVertexList().at(vertCount + 1).m_pos;
		cell.pos[2] = terrain->GetVertexList().at(vertCount + 2).m_pos;
		//重点。
		cell.m_CenterPos = terrain->GetCenterArray().at(mesh);
		//次メッシュの頂点へ。
		vertCount += 3;
		//管理をリストに移す。
		m_cellList.push_back(cell);
	}

	for (auto& baseCell : m_cellList) {
		//メッシュ全体に検索を掛けて、隣接セルを検索。
		int linkCellIndex = 0;	//隣接セル用インデックス。
		for (auto& serchCell : m_cellList) {
			
			//リンクセルを検索していく。
			if (&baseCell == &serchCell) {
				//ベースセルとリンクセルのアドレスが同一なのでスキップ。
				continue;
			}
			
			int linkVertex = 0;	//隣接頂点の数。

			//頂点比較。
			for (auto& baseVertex : baseCell.pos) {
				for (auto& serchVertex : serchCell.pos) {
					if (baseVertex == serchVertex) {
						//頂点が一緒
						linkVertex++;
					}
				}
			}//VertexSerch.

			if (linkVertex >= 2) {
				//隣接ラインが2つあるためこいつは隣接頂点である。
				baseCell.m_linkCell[linkCellIndex] = &serchCell;
				linkCellIndex++;
				if (linkCellIndex == 3) {
					//リンクセル３つ目到達検索を終了。
					break;
				}
			}
		}//linkCellSerch.
	}

	if (isDebugDraw) {
		//デバッグ。
		m_nvmDebugDraw = new NVMDebugDraw;
		m_isDebugDraw = isDebugDraw;

		for (auto& cell : m_cellList) {
			m_nvmDebugDraw->PushVertex(cell.pos[0]);
			m_nvmDebugDraw->PushVertex(cell.pos[1]);
			m_nvmDebugDraw->PushVertex(cell.pos[2]);
			for (auto* linkCell : cell.m_linkCell) {
				if(linkCell == nullptr){
					break;
				}
				//隣接デバッグ用にラインを形成して、格納。
				NVMDebugDraw::Line line;
				line.start = cell.m_CenterPos;
				line.end = linkCell->m_CenterPos;
				m_nvmDebugDraw->PushToLinkCellLine(line);
			}
		}

		m_nvmDebugDraw->Init(terrain->GetIndexList());
	}

	//頂点座標よりセルの隣接セルを計算する。

	//
}

void NVMGenerator::UpdateNVM(nsTerrain::TerrainRender* terrain)
{
}

void NVMGenerator::DebugDraw(nsTerrain::TerrainRender* terrain)
{
	if (!m_isDebugDraw) {
		return;
	}

	m_nvmDebugDraw->Render(terrain->GetVertexCount());
}
