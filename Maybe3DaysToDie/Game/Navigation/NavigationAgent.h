#pragma once

#include "AStar.h"
class NaviMeshManager;
class Stage;

/// <summary>
/// A*ラッパークラス。
/// </summary>
class NavigationAgent
{
public:
	/// <summary>
	/// ジェネレータを設定。
	/// </summary>
	/// <param name="ganerator"></param>
	void SetGenerator(Stage* stage)
	{
		m_stage = stage;
	}
	/// <summary>
	/// フットステップ付き、A*移動。
	/// </summary>
	/// <param name="model">モデルレンダー。</param>
	/// <param name="start">スタート位置。</param>
	/// <param name="goal">到着位置。</param>
	/// <param name="serchTime">AStarを走らせる頻度。</param>
	/// <returns>経路探査が終了したか。</returns>
	bool MoveForFootStep(prefab::ModelRender* model, Vector3& start, Vector3& goal, float serchTime = 3.0f);

	/// <summary>
	/// エージェントの位置、回転を取得。
	/// </summary>
	/// <param name="pos">位置。</param>
	/// <param name="qRot">回転。</param>
	void GetAgentPositionAndRotation(Vector3& pos, Quaternion& qRot)
	{
		pos += m_AgentPos - pos;
		qRot = m_AgentQrot;
	}
private:
	AStar									m_astar;						//経路探査。
	std::vector<NVMGenerator::Cell*>		m_nodeList;						//ノードセル。
	bool									m_isArrive = true;				//到着してる？
	Stage*									m_stage;						//ジェネレーターptr。
	Vector3									m_toWayPoint;					//次の経路に向かうベクトル。
	Vector3									m_AgentPos;						//エージェントの位置。
	Quaternion								m_AgentQrot;					//エージェントの回転。
	float									m_serchTime = 0.0f;				//エージェントが経路を再探査するまでの時間。
};

