#pragma once

#include "TerrainManager/TerrainRender/TerrainRender.h"

class NVMDebugDraw;

/// <summary>
/// ナビゲーションメッシュ生成クラス。
/// </summary>
/// <remarks>
/// このクラスは、サンドボックスのステージからNVMを動的生成するクラス。
/// ステージに変更があった際にもNVM変更する処理が走る（予定）。
/// ブロック１単位を2メッシュとして扱う為、サンドボックス型でのみしか機能しない。
/// </remarks>
class NVMGenerator
{
public:

	//セルの状態。
	enum ListNo {
		EnNoneList,
		EnCloseList,
		EnOpenList
	};

	/// <summary>
	/// AStarで使用するセル情報。
	/// </summary>
	struct Cell {
		Vector3 pos[3];							//３頂点。
		Cell* m_parent = nullptr;				//親となるセル。
		Cell* child = nullptr;					//子供となるセル。
		Cell* m_linkCell[3] = { nullptr };		//隣接セル。
		Vector3 m_CenterPos = g_vec3Zero;		//セルの中央座標。
		float costFromStart = 0.0f;				//スタートから見たコスト。
		float costToEnd = 0.0f;					//スタート位置からゴール位置までのコスト。
		float totalCost = 0.0f;					//最終的なコスト。
		int listNum = EnNoneList;				//どのリストに属しているか。
	};

	using CellList = std::vector<Cell>;
	using ChunkID = Vector2;

private:
	static bool isInstantiate;								//インスタンスが作成されているか。
	bool m_isDebugDraw = false;								//デバッグ描画する？
	NVMDebugDraw* m_nvmDebugDraw = nullptr;					//デバッグ描画。
	std::map<ChunkID, CellList> m_chunkIDtoCellListMap;		//チャンクIDからセルリストを取得するマップ。

public:
	NVMGenerator();
	~NVMGenerator();

public:
	/// <summary>
	/// 地形よりNVMを作成する。
	/// </summary>
	/// <param name="terrain">地形</param>
	/// <param name="isDebugDraw">デバッグ描画。</param>
	void CreateNVM(nsTerrain::TerrainRender* terrain, bool isDebugDraw = false);
	
	/// /// <summary>
	/// 地形データよりNVMを更新する。
	/// <para>ブロックが破壊されたらチャンク分NVMの更新を行う。</para>
	/// </summary>
	/// <param name="terrain"></param>
	void UpdateNVM(nsTerrain::TerrainRender* terrain);
	
	/// /// <summary>
	/// デバッグ描画。
	/// </summary>
	void DebugDraw(nsTerrain::TerrainRender* terrain);
	
	///// /// <summary>
	///// セルリストを取得。
	///// </summary>
	///// <returns></returns>
	//std::vector<Cell>& GetCellList()
	//{
	//	return m_cellList;
	//}

	/// <summary>
	/// デバッグ描画のフラグを切り替える。
	/// </summary>
	void ChangeDrawFlag()
	{
		m_isDebugDraw = !m_isDebugDraw;
	}
};

